#include "uart_modbus.h"
#define SUCCESS 1
#define ERROR 0

int init_modbus() {
    
    uart0_filestream = -1;

    uart0_filestream = open("/dev/serial0", O_RDWR | O_NOCTTY | O_NDELAY);      //Open in non blocking read/write mode
    
    if (uart0_filestream == -1)
    {
        printf("Erro - Não foi possível iniciar a UART.\n");
    }
    else
    {
        printf("UART inicializada!\n");
    }    
}

void set_options_modbus() {

    tcgetattr(uart0_filestream, &options);

    options.c_cflag = B9600 | CS8 | CLOCAL | CREAD;     //<Set baud rate

    options.c_iflag = IGNPAR;

    options.c_oflag = 0;

    options.c_lflag = 0;

    tcflush(uart0_filestream, TCIFLUSH);

    tcsetattr(uart0_filestream, TCSANOW, &options);
}

void get_data_modbus(char device_code, char request_code, char subcode) {

    unsigned char tx_buffer[20] = {device_code, request_code, subcode, 3, 1, 1, 2};
    
    short crc = calcula_CRC(tx_buffer, 7);
    
    memcpy(&tx_buffer[7], (const void *)&crc, 2);

    int tx_length = 9;

    if (uart0_filestream != -1)
    {
        
        int count = write(uart0_filestream, &tx_buffer[0], tx_length);
        
        if (count < 0)
        {
            printf("UART TX error\n");
        }

        usleep(100000);
    }
}


void send_data_modbus(char device_code, char request_code, char subcode, int control_value) {

    unsigned char tx_buffer[20] = {device_code, request_code, subcode, 3, 1, 1, 2};

    memcpy(&tx_buffer[7], (const void *)&control_value, 4);
    
    short crc = calcula_CRC(tx_buffer, 11);
    
    memcpy(&tx_buffer[11], (const void *)&crc, 2);

    int tx_length = 13;

    if (uart0_filestream != -1)
    {
        int count = write(uart0_filestream, &tx_buffer[0], tx_length);
        
        if (count < 0)
        {
            printf("UART TX error\n");
        }

        usleep(100000);
    }
}


int check_crc(unsigned char *rx_buffer, int rx_length)
{
    short crc_calculated, crc_from_uart;

    if (rx_length > 0)
    {
        memcpy(&crc_from_uart, (const void *)(rx_buffer + 7), 2);

        crc_calculated = calcula_CRC(rx_buffer, 7);

        if (crc_calculated == crc_from_uart) {
            return SUCCESS;
        }
        
        return ERROR;
    }
    else
        return ERROR;
}

float read_modbus() {
    int rx_length = 0, out_crc = 0;
    unsigned char rx_buffer[256];
    float response;
    
    rx_length = read(uart0_filestream, (void *)rx_buffer, 255);
    out_crc = check_crc(&rx_buffer[0], rx_length);

    // if(out_crc != 1) {
    //     printf("CRC ERROR\n");
    //     return -1;
    // }

    memcpy(&response, &rx_buffer[3], 4);

    return response;
}

void close_uart_modbus() {
    close(uart0_filestream);
}