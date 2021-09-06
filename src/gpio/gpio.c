/*
  Control Intensity of LED using PWM on Raspberry pi
  http://www.electronicwings.com
 */

#include <wiringPi.h> //Used for GPIO
#include <softPwm.h>  //Used for GPIO
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* Variáveis Globais do GPIO */
#define PWM_PIN_RESISTOR 23
#define PWM_PIN_AIR_COOLER 24

void init_GPIO()
{
    wiringPiSetup();

    pinMode(PWM_PIN_RESISTOR, OUTPUT);
    
    softPwmCreate(PWM_PIN_RESISTOR, 1, 100);
    
    pinMode(PWM_PIN_AIR_COOLER, OUTPUT);
    
    softPwmCreate(PWM_PIN_AIR_COOLER, 1, 100);
}

void bind_gpio(int intensity)
{
    if (intensity > 0)
    {
        softPwmWrite(PWM_PIN_AIR_COOLER, 0);
        
        softPwmWrite(PWM_PIN_RESISTOR, abs(intensity));
    }
    else if (intensity <= -40)
    {
        softPwmWrite(PWM_PIN_RESISTOR, 0);
        
        softPwmWrite(PWM_PIN_AIR_COOLER, abs(intensity));
    }
    else
    {
        softPwmWrite(PWM_PIN_AIR_COOLER, 0);
        
        softPwmWrite(PWM_PIN_RESISTOR, 0);
    }
}

void unbind_gpio()
{
    softPwmWrite(PWM_PIN_AIR_COOLER, 0);
    
    usleep(500000);

    softPwmWrite(PWM_PIN_RESISTOR, 0);
    
    usleep(500000);
}