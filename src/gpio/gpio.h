#ifndef __GPIO__
#define __GPIO__

/*
  Control Intensity of LED using PWM on Raspberry pi
  http://www.electronicwings.com
 */

#include <wiringPi.h> //Used for GPIO
#include <softPwm.h>  //Used for GPIO
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* Constants */
#define PWM_PIN_RESISTOR 23
#define PWM_PIN_AIR_COOLER 24
#define DELAY_5 500000
#define MIN_INTENSITY 1
#define MAX_INTENSITY 100
#define MIN_AIR_COOLER_INTENSITY -40


void init_GPIO();
void bind_gpio(int intensity);
void unbind_gpio();

#endif // __GPIO__