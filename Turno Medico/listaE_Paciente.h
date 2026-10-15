#ifndef LISTAESTATICA_H_INCLUDED
#define LISTAESTATICA_H_INCLUDED
#include "paciente.h"
#define MAX 30
typedef struct{
    Paciente vipd[MAX];
    int cursor;
    int ultimo;
}LPaciente;


void inic(LPaciente *p){
    p->cursor = -1;
    p->ultimo = -1;
}

int isEmpty(LPaciente p){
    return(p.ultimo == -1);
}

int isFull(LPaciente p){
    return(p.ultimo == MAX-1);
}

int isOos(LPaciente p){
    return(p.cursor == -1);
}
void reset(LPaciente *p){
    if(isEmpty(*p)){
        p->cursor = -1;
    }else{
        p->cursor = 0;
    }
}

void forwards(LPaciente *p){
    if(!isOos(*p)){
        if(p->cursor < p->ultimo){
            p->cursor++;
        }else{
            p->cursor = -1;
        }
    }
}

Paciente copy(LPaciente p){
    if(isOos(p)){
        printf("Error: Intento de copia con cursor fuera de estructura.\n");
        exit(1);
    }
    return p.vipd[p.cursor];
}

void insert(LPaciente *p, Paciente elem){
    int i;
    if(isFull(*p)){
        printf("Error de Desborde: La lista está llena.\n");
        return;
    }
    if(isEmpty(*p) || isOos(*p)){
        p->ultimo++;
        p->vipd[p->ultimo] = elem;
        p->cursor = p->ultimo;
    }else{
        for(i=p->ultimo; i>=p->cursor; i--){
            p->vipd[i+1] = p->vipd[i];
        }
        p->vipd[p->cursor] = elem;
        p->ultimo++;
    }
}
void supress(LPaciente *p){
    if(isOos(*p) || isEmpty(*p)){
        printf("Error de Desfonde/OOS: No hay elemento corriente para suprimir.\n");
        return;
    }
    int i;
    for(i=p->cursor;i<p->ultimo;i++){
        p->vipd[i] = p->vipd[i+1];
    }
    p->ultimo--;
    if(p->ultimo == -1){
        p->cursor = -1;
    }else if(p->cursor > p->ultimo){
        p->cursor = p->ultimo;
    }
}


#endif // LISTAESTATICA_H_INCLUDED
