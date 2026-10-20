#ifndef TDATURNO_H_INCLUDED
#define TDATURNO_H_INCLUDED

#include <string.h>
#include "fecha.h"

#define MAX_MUTUAL 100

// Estados del turno
#define SOLICITADO 1
#define CONFIRMADO 2
#define ATENDIDO 3
#define CANCELADO 4

// Datos que tiene cada turno
typedef struct {
    int id_turno;
    int dni_paciente;
    float monto;
    char mutual[MAX_MUTUAL];
    Fecha fecha;
    int estado;
} Turno;

// Inicializa el turno
void initTurno(Turno *t) {
    (*t).id_turno = 0;
    (*t).dni_paciente = 0;
    (*t).monto = 0.0;
    strcpy((*t).mutual, "SIN MUTUAL");
    initFecha(&((*t).fecha));
    (*t).estado = SOLICITADO;
}

// Carga los datos del turno
void setIdTurno(Turno *t, int id) {
    (*t).id_turno = id;
}

void setDniPacienteTurno(Turno *t, int dni) {
    (*t).dni_paciente = dni;
}

void setMontoTurno(Turno *t, float monto) {
    (*t).monto = monto;
}

void setMutualTurno(Turno *t, char mut[]) {
    strcpy((*t).mutual, mut);
}

void setFechaTurno(Turno *t, Fecha f) {
    (*t).fecha = f;
}

void setEstadoTurno(Turno *t, int estado) {
    (*t).estado = estado;
}

// Devuelve los datos del turno
int getIdTurno(Turno t) {
    return t.id_turno;
}

int getDniPacienteTurno(Turno t) {
    return t.dni_paciente;
}

float getMontoTurno(Turno t) {
    return t.monto;
}

char* getMutualTurno(Turno t) {
    char *m;
    m = (char*)malloc(strlen(t.mutual)+1);
    if(m==NULL){
        return;
    }else{
        strcpy(m,t.mutual);
        return m;
    }
}

Fecha getFechaTurno(Turno t) {
    return t.fecha;
}

int getEstadoTurno(Turno t) {
    return t.estado;
}

// Devuelve una copia del turno completo
Turno getTurno(Turno t) {
    return t;
}


#endif
