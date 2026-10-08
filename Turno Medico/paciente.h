#ifndef PACIENTE_H_INCLUDED
#define PACIENTE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 390
typedef struct{
    char nombre[30];
    char apellido[30];
    int dni;
    int osocial;
}Paciente;

void cargarPaciente(Paciente p[], int *carga,int c){
    int i, dniTemp;
    printf("Paciente #%i\n", *carga);
    printf("Nombre?\n");
    fgets(p[*carga].nombre, 30, stdin);
    printf("Apellido?\n");
    fgets(p[*carga].apellido, 30, stdin);
    printf("DNI?\n");
    scanf("%d", &dniTemp);
    while(dniTemp < 0 || dniTemp > 99999999){
        printf("Numero de DNI fuera de rango, ingrese uno correctamente\n");
        scanf("%d", &dniTemp);
    }
    for(i=0;i<c;i++){
        if(p[i].dni == dniTemp){
            printf("El DNI ingresado ya esta registrado. Por favor ingrese el DNI correctamente.\n");
            scanf("%d", &dniTemp);
            while(dniTemp == p[i].dni || dniTemp < 0 || dniTemp > 99999999){
                printf("El DNI ingresado ya esta registrado. Por favor ingrese el DNI correctamente.\n");
                scanf("%d", &dniTemp);
            }
        }else{
            p[*carga].dni = dniTemp;
            printf("DNI en posicion %d=%d\n", *carga, p[*carga].dni = dniTemp);
        }
    }
    getchar();
    (*carga)++;
}

#endif // PACIENTE_H_INCLUDED
