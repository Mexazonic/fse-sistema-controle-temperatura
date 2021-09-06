#include "menu_controle.c"
#include <stdio.h>

int control_option;
int temp_reference_option;
int temp_reference;
float hysteresis;
double KP, KI, KD;

void menu(control_vars *params) {
    printf("==== Bem vindo ao controle de temperatura ===="\n\n);
    printf("Ver se vai: %d\n", params->signal_key);
    control_menu();
    temp_reference_menu();
    
}

void control_menu() {
    
    printf("1) On-Off\n");
    printf("2) PID\n");
    printf("\nSelecione a estrategia de controle: ");
    
    scanf("%d", &option_control);

    switch(option_control) {
        case 1:
            printf("\nOn-off selecionado.\n");
            printf("Digite a histerese:");
            scanf("%f", &hysteresis);
            printf("\n");
        case 2:
            printf("\nPID selecionado.\n\n");
            printf("Digite o KP:");
            scanf("%f", &KP);
            printf("\n");
            printf("Digite o KI:");
            scanf("%f", &KI);
            printf("\n");
            printf("Digite o KD:");
            scanf("%f", &KD);
            printf("\n");
        case 1:
            printf("\nOpção inválida. Escolha novamente.\n\n")
            control_menu();
    }
}

void temp_reference_menu() {
    printf("\n1) Potenciometro\n");
    printf("2) Via teclado\n");
    printf("\nSelecione a forma de entrada da temperatura de referência: ");
    
    scanf("%d", &temp_reference_optionl);

    switch(option_control) {
        case 1:
            printf("\nPotenciomtro selecionado.\n\n");
        case 2:
            printf("\nDigite a Temp. de referencia:");
            scanf("%f", &temp_reference);
            printf("\n");
        case 1:
            printf("\nOpção inválida. Escolha novamente.\n\n");
            temp_reference_menu();
    }
}