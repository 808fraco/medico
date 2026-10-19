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
int isEmpty(Lista l){
    if(l.acceso == NULL){ // Si no existe un nodo dentro de acceso, devuelve 1
        return 1;
    }else{ // y sino, devuelve 0 indicando q existe al menos un nodo dentro de la lista
        return 0;
    }
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
    l->aux = NULL; // el cursor auxiliar apunta a NULL indicando que no hay nada atras del cursor
}

void forwardL(Lista *l){
    l->aux = l->cursor; // el cursor auxiliar apunta a donde estaba cursor
    l->cursor = l->cursor->siguiente; // el cursor avanza al siguiente nodo
}
//! copy, insert y supress
Turno copyL(Lista l){
    return l.cursor->vipd;
}

void insertL(Lista *l, Turno elem){
    Nodo *n;
    n = (Nodo*)malloc(sizeof(Nodo));
    if(n==NULL){
        return;
    }else{
        n->vipd = elem; //guarda el elemento dentro del nodo
        n->siguiente = l->cursor; //engancha el nuevo nodo hacia adelante
        //! REVISION
        if(l->aux == NULL){ //insertamos al inicio si esta vacia
            l->acceso = n;
        }else if(l->aux != NULL){ //insertamos en el medio o al final, y hacemos que el siguiente del anterior, apunte a n
            l->aux->siguiente = n;
        }
        l->cursor = n;
    }
}

void supressL(Lista *l){
    Nodo *temp = l->cursor; // guardamos el nodo donde esta el cursor en un nodo temporal
    if(l->aux == NULL){ // si el auxiliar de la lista apunta a nada
        l->acceso = temp->siguiente; // entonces el acceso pasa a apuntar al nodo siguiente

    }else if(l->aux != NULL){ // y sino, si el auxiliar es distinto a null (al menos un nodo adentro de la lista)
        l->aux->siguiente = temp->siguiente; // el auxiliar pasara a valer el siguiente del nodo borrado
    }

    l->cursor = temp->siguiente; // el cursor pasara a valer el nodo siguiente del nodo borrado
    free(temp);
}
#endif // LISTAVO_TURNO_H_INCLUDED
