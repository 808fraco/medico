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
    int i, Temp; //! Temp es usado para el control de DNI y obra social.
    printf("Paciente #%i\n", *carga);
    //! Nombre y apellido
    printf("Nombre?\n");
    fgets(p[*carga].nombre, 30, stdin);

    printf("Apellido?\n");
    fgets(p[*carga].apellido, 30, stdin);

    //! DNI
    printf("DNI?\n");
    scanf("%d", &dniTemp);

    while(Temp < 0 || Temp > 99999999){ //Control de DNI
        printf("Numero de DNI fuera de rango, ingrese uno correctamente\n");
        scanf("%d", &Temp);
    }
    for(i=0;i<c;i++){ //Control de que el DNI sea unico
        if(p[i].dni == dniTemp){
            printf("El DNI ingresado ya esta registrado. Por favor ingrese el DNI correctamente.\n");
            scanf("%d", &dniTemp);
            while(dniTemp == p[i].dni || dniTemp < 0 || dniTemp > 99999999){
                printf("El DNI ingresado ya esta registrado. Por favor ingrese el DNI correctamente.\n");
                scanf("%d", &dniTemp);
            }
        }else{
            p[*carga].dni = dniTemp;
        }
    }
    getchar();
    //! Obra social
    printf("Tiene obra social? Indique segun las opciones.\n");
    printf("[1. Si | 0. No]");
    scanf("%d", &Temp);
    while(Temp < 0 || Temp > 1){ //Control de opciones
        printf("Numero digitado fuera de rango, ingrese correctamente el numero.\n");
        scanf("%d", &Temp);
    }
    P[*carga].osocial = Temp;
    (*carga)++;
}

#endif // PACIENTE_H_INCLUDED
