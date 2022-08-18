#include <furi_hal.h>
#include <stream_buffer.h>

#include "gps_uart.h"

#define RX_BUF_SIZE 0

typedef enum {
    WorkerEvtStop = (1 << 0),
    WorkerEvtRxDone = (1 << 1),
} WorkerEvtFlags;

#define WORKER_ALL_RX_EVENTS                                                      \
    (WorkerEvtStop | WorkerEvtRxDone)

struct GpsUart {
    FuriThread* thread;
    StreamBufferHandle_t rx_stream;
    uint8_t rx_buf[RX_BUF_SIZE];
};

static void gps_uart_on_irq_cb(UartIrqEvent ev, uint8_t data, void* context) {
    GpsUart* gps_uart = (GpsUart*)context;
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    if(ev == UartIrqEventRXNE) {
        xStreamBufferSendFromISR(gps_uart->rx_stream, &data, 1, &xHigherPriorityTaskWoken);
        furi_thread_flags_set(furi_thread_get_id(gps_uart->thread), WorkerEvtRxDone);
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }
}

static void gps_uart_serial_init(GpsUart* gps_uart, uint8_t uart_ch) {
    if(uart_ch == FuriHalUartIdUSART1) {
        furi_hal_console_disable();
    } else if(uart_ch == FuriHalUartIdLPUART1) {
        furi_hal_uart_init(uart_ch, GPS_BAUD_RATE);
    }
    furi_hal_uart_set_irq_cb(uart_ch, gps_uart_on_irq_cb, gps_uart);
}

static void gps_uart_serial_deinit(GpsUart* gps_uart, uint8_t uart_ch) {
    UNUSED(gps_uart);
    furi_hal_uart_set_irq_cb(uart_ch, NULL, NULL);
    if(uart_ch == FuriHalUartIdUSART1)
        furi_hal_console_enable();
    else if(uart_ch == FuriHalUartIdLPUART1)
        furi_hal_uart_deinit(uart_ch);
}

static int32_t gps_uart_worker(void* context) {
	GpsUart* gps_uart = (GpsUart*)context;

	gps_uart->rx_stream = xStreamBufferCreate(RX_BUF_SIZE * 5, 1);

	gps_uart_serial_init(gps_uart, FuriHalUartIdUSART1);

    while(1) {
        uint32_t events =
            furi_thread_flags_wait(WORKER_ALL_RX_EVENTS, FuriFlagWaitAny, FuriWaitForever);
        furi_check((events & FuriFlagError) == 0);
        if(events & WorkerEvtStop) break;
        if(events & WorkerEvtRxDone) {
            size_t len =
                xStreamBufferReceive(gps_uart->rx_stream, gps_uart->rx_buf, RX_BUF_SIZE, 0);
            if(len > 0) {
            	// TODO: send data to callback for NMEA processing & display
        		xStreamBufferReset(gps_uart->rx_stream);
            }
        }
    }

    gps_uart_serial_deinit(gps_uart, FuriHalUartIdUSART1);

    vStreamBufferDelete(gps_uart->rx_stream);

	return 0;
}

GpsUart* gps_uart_enable() {
    GpsUart* gps_uart = malloc(sizeof(GpsUart));

    gps_uart->thread = furi_thread_alloc();
    furi_thread_set_name(gps_uart->thread, "GpsUartWorker");
    furi_thread_set_stack_size(gps_uart->thread, 1024);
    furi_thread_set_context(gps_uart->thread, gps_uart);
    furi_thread_set_callback(gps_uart->thread, gps_uart_worker);

    furi_thread_start(gps_uart->thread);
    return gps_uart;
}

void gps_uart_disable(GpsUart* gps_uart) {
    furi_assert(gps_uart);
    furi_thread_flags_set(furi_thread_get_id(gps_uart->thread), WorkerEvtStop);
    furi_thread_join(gps_uart->thread);
    furi_thread_free(gps_uart->thread);
    free(gps_uart);
}
