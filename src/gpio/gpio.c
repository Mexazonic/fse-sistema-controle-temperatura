#include "gpio.h"

void init_GPIO()
{
    wiringPiSetup();

    pinMode(PWM_PIN_RESISTOR, OUTPUT);
    
    softPwmCreate(PWM_PIN_RESISTOR, MIN_INTENSITY, MAX_INTENSITY);
    
    pinMode(PWM_PIN_AIR_COOLER, OUTPUT);
    
    softPwmCreate(PWM_PIN_AIR_COOLER, MIN_INTENSITY,MAX_INTENSITY);
    printf("GPIO Initialized.\n");
}   

void bind_gpio(int intensity)
{
    if (intensity > 0)
    {
        printf("Resistor %d: %d AND Ventoinha%d: %d\n", PWM_PIN_RESISTOR, abs(intensity), PWM_PIN_AIR_COOLER, 0);
        softPwmWrite(PWM_PIN_AIR_COOLER, MIN_INTENSITY);
        
        softPwmWrite(PWM_PIN_RESISTOR, abs(intensity));
    }
    else if (intensity <= MIN_AIR_COOLER_INTENSITY)
    {
        printf("Resistor %d: %d AND Ventoinha%d: %d\n", PWM_PIN_RESISTOR, 0, PWM_PIN_AIR_COOLER, abs(intensity));
        softPwmWrite(PWM_PIN_RESISTOR, MIN_INTENSITY);
        
        softPwmWrite(PWM_PIN_AIR_COOLER, abs(intensity));
    }
    else
    {
        printf("Equilibrado");
        softPwmWrite(PWM_PIN_AIR_COOLER, MIN_INTENSITY);
        
        softPwmWrite(PWM_PIN_RESISTOR, MIN_INTENSITY);
    }
}

void unbind_gpio()
{
    softPwmWrite(PWM_PIN_AIR_COOLER, MIN_INTENSITY);
    
    usleep(DELAY_5);

    softPwmWrite(PWM_PIN_RESISTOR, MIN_INTENSITY);
    
    usleep(DELAY_5);
    printf("GPIO Closed.\n");
}