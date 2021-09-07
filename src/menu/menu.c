#include "menu.h"
#include <stdio.h>

int control_option;
int temp_reference_option;
int temp_reference;
float hysteresis;
double KP, KI, KD;

void menu(control_vars *params) {
    printf("==== Bem vindo ao controle de temperatura ====\n\n");
    control_menu();
    temp_reference_menu();
    
}

void control_menu() {
    
    printf("1) On-Off\n");
    printf("2) PID\n");
    printf("\nSelecione a estrategia de controle: ");
    
    scanf("%d", &control_option);
    params->control_option = control_option;

    switch(control_option) {
        case 1:
            printf("\nOn-off selecionado.\n");
            printf("Digite a histerese:");
            scanf("%f", &hysteresis);
            params->hysteresis = hysteresis;
            printf("\n");
            break;
        case 2:
            printf("\nPID selecionado.\n\n");
            printf("Digite o KP:");
            scanf("%f", &KP);
            params->KP = KP;
            
            printf("\n");
            printf("Digite o KI:");
            scanf("%f", &KI);
            params->KI = KI;

            printf("\n");
            printf("Digite o KD:");
            scanf("%f", &KD);
            params->KD = KD;

            printf("\n");
            break;
        default:
            printf("\nOpção inválida. Escolha novamente.\n\n");
            control_menu();
    }
}

void temp_reference_menu() {
    printf("\n1) Potenciometro\n");
    printf("2) Via teclado\n");
    printf("\nSelecione a forma de entrada da temperatura de referência: ");
    
    scanf("%d", &temp_reference_option);
    params->temp_reference_option = temp_reference_option;

    switch(temp_reference_option) {
        case 1:
            printf("\nPotenciomtro selecionado.\n\n");
            break;
        case 2:
            printf("\nDigite a Temp. de referencia:");
            scanf("%f", &temp_reference);
            params->TR = temp_reference;
            printf("\n");
            break;
        default:
            printf("\nOpção inválida. Escolha novamente.\n\n");
            temp_reference_menu();
    }
}