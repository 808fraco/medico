#ifndef PACIENTE_H_INCLUDED
#define PACIENTE_H_INCLUDED
#include <stdlib.h>
#include <string.h>
typedef struct{
    char nombre[30];
    char apellido[30];
    long int dni;
    int osocial; //1. si tiene | 0. no tiene
}Paciente;
//! Inicializacion
void init(Paciente *p){
    strcpy(p->nombre,"");
    strcpy(p->apellido,"");
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
        p->dni = d;
}
void setOSocial(Paciente *p, int o){
        p->osocial = o;
}
//! Getters
char* getNombre(Paciente p){
    char *n;
    n = (char*)malloc(strlen(p.nombre)+1);
    if(n==NULL){
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
