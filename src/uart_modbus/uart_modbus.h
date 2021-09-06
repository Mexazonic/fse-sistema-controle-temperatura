#ifndef UART_MODBUS_H_
#define UART_MODBUS_H_

#include <stdio.h>
#include <unistd.h>         //Used for UART
#include <fcntl.h>          //Used for UART
#include <termios.h>        //Used for UART
#include <string.h>
#include "crc16/crc16.h"

int uart0_filestream; // filestream
struct termios options; // uart options

typedef struct  {
    float TI, TR, TE;
    int signal_key;
} control_vars;

int init_modbus();
void set_options_modbus();
void write_modbus(char device_code, char request_code, char subcode, int control_value);
int check_crc(unsigned char *rx_buffer, int rx_length);
float read_modbus();
void close_uart_modbus() {

#endif /* UART_MODBUS_H_ */