#ifndef CSV_H_
#define CSV_H_

time_t rawtime;
struct tm *info;
char datetime[80];

void init_csv();
void save_csv(float TI, double TE, float TR, double control_signal);

#endif /* CSV_H_ */