 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "csv.h"

void init_csv()
{
    FILE *f;

    f = fopen("dados.csv", "w");
    fprintf(f, "Data/Hora, TI, TE, TR, Intensidade\n");
    fclose(f);
}

void save_csv(float TI, double TE, float TR, double control_signal)
{
    FILE *f;
    fpt = fopen("log_temperature_system.csv", "a");

    time_t rawtime;
    struct tm *info;
    char datetime[80];

    time(&rawtime);

    info = localtime(&rawtime);

    strftime(datetime, 80, "%d/%m/%Y %H:%M:%S", info);

    fprintf(f, "%s, %f, %lf, %f, %lf\n", datetime, TI, TE, TR, control_signa);
    fclose(f);
}