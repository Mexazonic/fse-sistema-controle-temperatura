 
#include "csv.h"

void init_csv()
{
    FILE *f;

    f = fopen("log_temperature_system.csv", "w");
    fprintf(f, "Data/Hora, TI, TE, TR, Valor_de_acionamento_dos_atuadores\n");
    fclose(f);
}

void save_csv(float TI, double TE, float TR, double control_signal)
{
    FILE *f;
    f = fopen("log_temperature_system.csv", "a");

    time(&seed);

    args = localtime(&seed);

    strftime(datetime, 80, "%d/%m/%Y %H:%M:%S", args);

    fprintf(f, "%s, %f, %lf, %f, %lf\n", datetime, TI, TE, TR, control_signal);
    fclose(f);
}