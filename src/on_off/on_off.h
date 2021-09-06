#ifndef ON_OFF_H_
#define ON_OFF_H_

void on_off_setup(float hysteresis_);
void on_off_update_ref(float temp_ref_);
double on_off_control(float temp_output);

#endif /* ON_OFF_H_ */