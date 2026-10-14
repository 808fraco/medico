#ifndef PACIENTE_H_INCLUDED
#define PACIENTE_H_INCLUDED
#include <stdlib.h>
#include <string.h>
typedef struct{
    char nombre[30];
    char apellido[30];
    int dni;
    int osocial; //1. si tiene | 0. no tiene
}Paciente;
//! Inicializacion
void init(Paciente *p){
    p->nombre[0] = '\0';
    p->apellido[0] = '\0';
    p->dni = 0;
    p->osocial = 0;
}
//! Setters
void setNombre(Paciente *p, char n[]){
    strcpy(p->nombre,n);
}
void setApellido(Paciente *p, char a[]){
    strcpy(p->apellido,a);
}
void setDNI(Paciente *p, int d){
    if(d>99999999 || d<1000000){
        printf("N%cmero de DNI fuera del rango actual.\n",163);
        return;
    }else{
        p->dni = d;
    }
}
void setOSocial(Paciente *p, int o){
    if(o == 0){
        p->osocial = o;
    }else if(o==1){
        p->osocial = o;
    }else{
        printf("N%cmero incorrecto. Debe ser 1 o 0.\n",163);
    }
}
//! Getters
char* getNombre(Paciente p){
    char *n;
    n = (char*)malloc(strlen(p.nombre)+1);
    if(n==NULL){
        printf("No hay suficiente memoria.\n");
        return NULL;
    }else{
        strcpy(n,p.nombre);
        return n;
    }
}
char* getApellido(Paciente p){
    char *a;
    a = (char*)malloc(strlen(p.apellido)+1);
    if(a==NULL){
        printf("No hay suficiente memoria.\n");
        return NULL;
    }else{
        strcpy(a,p.apellido);
        return a;
    }
}
int getOSocial(Paciente p){
    return p.osocial;
}
int getDNI(Paciente p){
    return p.dni;
}
#endif // PACIENTE_H_INCLUDED
