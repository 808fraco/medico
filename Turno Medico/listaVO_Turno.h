#ifndef LISTAVO_TURNO_H_INCLUDED
#define LISTAVO_TURNO_H_INCLUDED
#include "turno.h"
typedef struct{
    int vipd;
    struct nodo *siguiente;
}Nodo;

typedef struct{
    Nodo *acceso;
    Nodo *cursor;
    Nodo *aux;
}Lista;

void inicLista(Lista *l){
    l->acceso = NULL;
    l->cursor = NULL;
    l->aux = NULL;
}


#endif // LISTAVO_TURNO_H_INCLUDED
