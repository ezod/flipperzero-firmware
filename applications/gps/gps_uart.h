#pragma once

#define GPS_BAUD_RATE 9600

typedef struct GpsUart GpsUart;

typedef struct {
    float latitude;
    float longitude;
} GpsStatus;

GpsUart* gps_uart_enable();

void gps_uart_disable(GpsUart* gps_uart);
