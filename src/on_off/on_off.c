#include "on_off.h"

double hysteresis;
double temp_ref = 0.0;
double temp_output = 0.0;
int sinal_de_controle_MAX = 100.0;
int sinal_de_controle_MIN = -100.0;

void on_off_setup(float hysteresis_){
    hysteresis = hysteresis_;
}

void on_off_update_ref(float temp_ref_){
    temp_ref = temp_ref_;
}

double on_off_control(float temp_output){
    
	double range = hysteresis / 2;
	
	if(temp_output < temp_ref - range) {
		return sinal_de_controle_MAX;
	} else if(temp_output > temp_ref + range) {
		return sinal_de_controle_MIN;
	} else {
		return 0;
	}
}