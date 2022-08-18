#pragma once

#define GPS_BAUD_RATE 9600

typedef struct GpsUart GpsUart;

GpsUart* gps_uart_enable();

void gps_uart_disable(GpsUart* gps_uart);
