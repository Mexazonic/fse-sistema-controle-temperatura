#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>

#include "sensorBME280/bme280.h"
#include "driver_lcd_16x2/lcd.h"
#include "uart_modbus/uart_modbus.h"
#include "pid/pid.h"
#include "gpio/gpio.h"
//#include "control_menu/menu.h"

// delay between samples in microseconds
#define DELAY 1000000
// Width of the graph (128 - 40)
#define WIDTH 88

int T, P, H;

typedef struct  {
    float TI, TR, TE;
    int signal_key;
} control_vars;


void init_setup();
void close_connections();

int main(int argc, char *argv[])
{
	/* Vars */
	control_vars params;
    double control_value = 0;

	/* Initial Setup */
	init_setup();

	/* Menu */
	// menu();

	/* System loop */
	for (int i=0; i<20; i++) // read values twice a second for 1 minute
	{	
		// BME280
		bme280ReadValues(&T, &P, &H);
		T -= 150; 
		params.TE = (float)T/100.0;

		/* UART */
		write_modbus(0x01, 0x23, 0xC1);
		params.TI = read_modbus();

		write_modbus(0x01, 0x23, 0xC2);
		params.TR = read_modbus();
		
		write_modbus(0x01, 0x23, 0xC3);
		params.signal_key = (int) read_modbus();

		/* TI must be at leat equal to TE*/
		if (params.TI >= params.TE) {
			printf("Leitura %d: te = %3.2f ti. = %3.2f, tr: %3.2f Key: %d\n", i, params.TE, params.TI, params.TR, params.signal_key);

			/* LCD */
			lcd_write_tmp(params.TE, params.TI, params.TR);

			/* PID */
			pid_atualiza_referencia(params.TR);
			control_value = pid_controle(params.TI);

			/* GPIO */
			bind_gpio(control_value);
		}

		sleep(1);
	}

	/* Close connections */
	close_connections();

	return 0;
}

void init_setup(){

	double KP = 5.0, KI = 1.0, KD = 5.0;

	/* UART Modbus setup*/
	init_modbus();
    
    set_options_modbus();

	//* BME280 setup*/
	bme280Init(1, 0x76);
	
	/* LCD setup*/
	lcd_init();

	/* PID setup */
    pid_configura_constantes(KP, KI, KD);	

	/* GPIO setup */
	init_GPIO();

	usleep(1000000);
}

void close_connections() {
	
	/* close GPIO */
    unbind_gpio();
    exit(0);
}