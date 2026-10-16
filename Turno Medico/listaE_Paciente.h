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
    return(p.cursor == -1 ||p.cursor > p.ultimo);
}
void reset(LPaciente *p){
    if(isEmpty(*p)){
        p->cursor = -1;
    }else{
        p->cursor = 0;
    }
}

void forwards(LPaciente *p){
    p->cursor++;
}

Paciente copy(LPaciente p){
    if(isOos(p)){ //Control dentro del main
        exit(1);
    }
    return p.vipd[p.cursor];
}

void insert(LPaciente *p, Paciente elem){
    int i;
    if(isFull(*p)){ //Control dentro del main
        return;
    }
    if(isEmpty(*p)){
         p->cursor =0;
        p->ultimo++;
        p->vipd[p->cursor] = elem;

    }else{
        for(i=p->ultimo+1; i>p->cursor; i--){
            p->vipd[i] = p->vipd[i-1];
        }
        p->vipd[p->cursor] = elem;
        p->ultimo++;
    }
}
void supress(LPaciente *p){
    if(isOos(*p) || isEmpty(*p)){
        return;
    } //Control dentro del main
    int i;
    for(i=p->cursor;i<p->ultimo;i++){
        p->vipd[i] = p->vipd[i+1];
    }
    p->ultimo--;
    if(p->ultimo == -1){
        p->cursor = -1;// En el caso de que se elemine el primer elemento
    }
}
#endif // LISTAESTATICA_H_INCLUDED
