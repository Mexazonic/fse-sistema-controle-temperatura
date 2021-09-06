#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>

#include "sensorBME280/bme280.h"
#include "driver_lcd_16x2/lcd.h"
#include "uart_modbus/uart_modbus.h"
// #include "gpio/gpio.h"
//#include "control_menu/menu.h"

// delay between samples in microseconds
#define DELAY 1000000
// Width of the graph (128 - 40)
#define WIDTH 88

int T, P, H;

typedef struct  {
    float TI, TR, TE;
    int key;
} control_vars;

void init();

int main(int argc, char *argv[])
{
	/* Vars */
	control_vars params;

	/* Initial Setup */
	init();
	//menu();

	for (int i=0; i<5; i++) // read values twice a second for 1 minute
	{
		printf("Leitura: %d \n\n\n", i);
		
		// BME280
		bme280ReadValues(&T, &P, &H);
		T -= 150; 
		params.TE = (float)T/100.0;

		// UART
		write_modbus(0x01, 0x23, 0xC1);
		params.TI = read_modbus();

		write_modbus(0x01, 0x23, 0xC2);
		params.TR = read_modbus();
		
		write_modbus(0x01, 0x23, 0xC3);
		params.key = read_modbus();

		printf("\nLeitura %d: te = %3.2f ti. = %3.2f, tr: %3.2f Key: %d\n", i, params.TE, params.TI, params.TR, (int) params.key);

		sleep(1);

		// LCD
		lcd_write_tmp(params.TE, params.TI, params.TR);

		// switch((int) key) {
		// 	case 0:
		// 		printf("Onoff");
		// 	case 1:
		// 		printf("PID");
		// 	default:
		// 		printf("None");
		// }
	}

return 0;
}

void init() {
	/* UART Modbus setup*/
	init_modbus();
    
    set_options_modbus();

	//* BME280 setup*/
	bme280Init(1, 0x76);
	
	/* LCD setup*/
	lcd_init();

	/* GPIO setup */
	// init_GPIO();

	usleep(1000000);
}