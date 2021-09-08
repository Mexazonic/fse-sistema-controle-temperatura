#ifndef CSV_H_
#define CSV_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

time_t seed;
struct tm *args;
char datetime[80];

void init_csv();
void save_csv(float TI, double TE, float TR, double control_signal);

#endif /* CSV_H_ */