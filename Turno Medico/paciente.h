//test
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
    int osocial; //1. si tiene | 0. no tiene
}Paciente;
void mostrarPaciente(Paciente p[], int carga){
    int i;
    for(i=0;i<carga;i++){
        printf("\n=============================\n");
        printf("Paciente #%d\n", i+1);
        printf("Nombre: %s", p[i].nombre);
        printf("Apellido: %s", p[i].apellido);
        printf("DNI: %d\n", p[i].dni);
        if(p[i].osocial = 1){
            printf("Obra social: si");
        }else{
            printf("Obra social: no");
        }
    }
}
void modPaciente(Paciente p[], int n,int opcion){
    int i,Temp;
    switch(opcion){
    // si quiere modificar el nombre completo
    case 1:
    printf("Nombre?\n");
    fgets(p[n].nombre, 30, stdin);
    break;

    // si quiere modificar el apellido
    case 2:
    printf("Apellido?\n");
    fgets(p[n].apellido, 30, stdin);
    break;

    // si quiere modificar el DNI (con controles)
    case 3:
    printf("DNI?\n");
    scanf("%d", &Temp);

    while(Temp < 0 || Temp > 99999999){ //Control de DNI
        printf("Numero de DNI fuera de rango, ingrese uno correctamente\n");
        scanf("%d", &Temp);
    }
    for(i=0;i<MAX;i++){ //Control de que el DNI sea unico
        if(p[i].dni == Temp){
            printf("El DNI ingresado ya esta registrado. Por favor ingrese el DNI correctamente.\n");
            scanf("%d", &Temp);
            while(Temp == p[i].dni || Temp < 0 || Temp > 99999999){

                if(Temp < 0 || Temp > 99999999){
                    printf("El DNI ingresado esta fuera del rango. Digite el DNI correctamente.\n");
                }else{
                    printf("El DNI ingresado ya esta registrado. Por favor ingrese el DNI correctamente.\n");
                }
                scanf("%d", &Temp);
            }
        }
    }
    p[n].dni = Temp;
    getchar();
    break;

    //si quiere modificar si tiene obra social o no
    case 4:
    printf("Tiene obra social el paciente? Indique segun las opciones.\n");
    printf("[1. Si | 0. No]");
    scanf("%d", &Temp);
    while(Temp < 0 || Temp > 1){ //Control de opciones
        printf("Numero digitado fuera de rango, ingrese correctamente el numero.\n");
        scanf("%d", &Temp);
    }
    p[n].osocial = Temp;
    }
}
void cargarPaciente(Paciente p[], int *carga,int c){
    int i, Temp; //! Temp es usado para el control de DNI y obra social.
    printf("Paciente #%i\n", *carga + 1);
    //! Nombre y apellido
    printf("Nombre?\n");
    fgets(p[*carga].nombre, 30, stdin);

    printf("Apellido?\n");
    fgets(p[*carga].apellido, 30, stdin);

    //! DNI
    printf("DNI?\n");
    scanf("%d", &Temp);

    while(Temp < 0 || Temp > 99999999){ //Control de DNI
        printf("Numero de DNI fuera de rango, ingrese uno correctamente\n");
        scanf("%d", &Temp);
    }
    for(i=0;i<c;i++){ //Control de que el DNI sea unico
        if(p[i].dni == Temp){
            printf("El DNI ingresado ya esta registrado. Por favor ingrese el DNI correctamente.\n");
            scanf("%d", &Temp);
            while(Temp == p[i].dni || Temp < 0 || Temp > 99999999){
                if(Temp < 0 || Temp > 99999999){
                    printf("El DNI ingresado esta fuera del rango. Digite el DNI correctamente.\n");
                }else{
                    printf("El DNI ingresado ya esta registrado. Por favor ingrese el DNI correctamente.\n");
                }
                scanf("%d", &Temp);
            }
        }//else{
            //p[*carga].dni = Temp;
        //}
    }
    p[*carga].dni = Temp;
    getchar();
    //! Obra social
    printf("Tiene obra social? Indique segun las opciones.\n");
    printf("[1. Si | 0. No]\n");
    scanf("%d", &Temp);
    while(Temp < 0 || Temp > 1){ //Control de opciones
        printf("Numero digitado fuera de rango, ingrese correctamente el numero.\n");
        scanf("%d", &Temp);
    }
    p[*carga].osocial = Temp;
    getchar();
    (*carga)++;
}

#endif // PACIENTE_H_INCLUDED
