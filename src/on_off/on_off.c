#include "on_off.h"
#include <stdio.h>

double hysteresis;
double temp_ref = 0.0;
double temp_output = 0.0;

void on_off_setup(float hysteresis_){
    hysteresis = hysteresis_;
}

void on_off_update_ref(float temp_ref_){
    temp_ref = temp_ref_;
}

double on_off_control(float temp_output){
    
	double range = hysteresis / 2;
	
	if(temp_output < temp_ref - range) {
		return 100.0;
	} else if(temp_output > temp_ref + range) {
		return -100.0;
	} else {
		return 0;
	}
}