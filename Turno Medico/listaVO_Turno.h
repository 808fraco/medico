#ifndef LISTAVO_TURNO_H_INCLUDED
#define LISTAVO_TURNO_H_INCLUDED
#include "turno.h"
typedef struct nodo{
    Turno vipd;
    struct nodo *siguiente;
}Nodo;

typedef struct{
    Nodo *acceso;
    Nodo *cursor;
    Nodo *aux;
}Lista;
//! init
void inicLista(Lista *l){
    l->acceso = NULL;
    l->cursor = NULL;
    l->aux = NULL;
}

//! empty, isOol (is out of list)
int isEmptyL(Lista l){
    if(l.acceso == NULL){ // Si no existe un nodo dentro de acceso, devuelve 1
        return 1;
    }else{ // y sino, devuelve 0 indicando q existe al menos un nodo dentro de la lista
        return 0;
    }
}

int isFullL(Lista l){
    Nodo *n = (Nodo*)malloc(sizeof(Nodo));
    if(n == NULL){
        return 1;
    }
    free(n);
    return 0;
}

int isOol(Lista l){
    if(l.cursor == NULL){ // si el cursor no apunta a nada, devuelve 1
        return 1;
    }else{ // y sino, devuelve 0 si apunta a un nodo
        return 0;
    }
}
//! Funciones de cursores (reset, forward)
void resetL(Lista *l){
    l->cursor = l->acceso; // mueve el cursor al acceso (primer nodo)
    l->aux = l->acceso; // lo mismo para el auxiliar
}

void forwardL(Lista *l){
    l->aux = l->cursor; // el cursor auxiliar apunta a donde estaba cursor
    l->cursor = l->cursor->siguiente; // el cursor avanza al siguiente nodo
}
//! copy, insert y supress
Turno copyL(Lista l){ // copia el vipd donde esta apuntando el cursor
    return l.cursor->vipd;
}

void insertL(Lista *l, Turno elem){
    Nodo *n;
    n = (Nodo*)malloc(sizeof(Nodo));
    if(n==NULL){
        return;
    }else{
        n->vipd = elem; //guarda el elemento dentro del nodo
        n->siguiente = l->cursor; //engancha el nuevo nodo al siguiente nodo donde apunta cursor
        if(l->aux == l->cursor){ //insertamos al inicio de la lista
            l->acceso = n;
            l->cursor=l->acceso;
            l->aux=l->acceso;
        }else { //insertamos en el medio o al final. 
            l->aux->siguiente = n;
            l->cursor=n;
        }
    }
}

void supressL(Lista *l){
    if(l->aux == l->cursor){ // elimina el primer nodo de la lista cuando el cursor este apuntando al acceso
        l->acceso = l->cursor->siguiente; // entonces el acceso pasa al nodo siguiente
        free(l->cursor);
        l->cursor=l->acceso;
        l->aux=l->acceso;

    }else { // y sino, eliminar en el medio o al final de la lista
        l->aux->siguiente = l->cursor->siguiente; // y engancha el nodo anterior con el posterior al borrado
        free(l->cursor);
        l->cursor=l->aux->siguiente;
    }
}
#endif // LISTAVO_TURNO_H_INCLUDED
