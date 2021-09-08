#ifndef UART_MODBUS_H_
#define UART_MODBUS_H_

#include <stdio.h>
#include <unistd.h>         //Used for UART
#include <fcntl.h>          //Used for UART
#include <termios.h>        //Used for UART
#include <string.h>
#include "../crc16/crc16.h"

int uart0_filestream; // filestream
struct termios options; // uart options

typedef struct  {
    float TI, TR, TE;
    int signal_key; // on_off || PID from selector key
    float hysteresis;
    int control_option; // onoff || PID || stdin selection
    int temp_reference_option; // Pontentiometer || stdin
    double KP, KI, KD;
} control_vars;

int init_modbus();
void set_options_modbus();
void get_data_modbus(char device_code, char request_code, char subcode);
void send_data_modbus(char device_code, char request_code, char subcode, int control_value);
int check_crc(unsigned char *rx_buffer, int rx_length);
float read_modbus();
void close_uart_modbus();

#endif /* UART_MODBUS_H_ */