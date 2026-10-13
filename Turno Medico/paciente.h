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



#endif // PACIENTE_H_INCLUDED
