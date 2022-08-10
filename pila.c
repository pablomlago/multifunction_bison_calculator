#include <stdlib.h>
#include "pila.h"

typedef struct tipo_celda* pila;

struct tipo_celda {
    tipoelemPila elemento;
    struct tipo_celda * sig;
};

//Stack of files containing instructions to be processed
pila stackInput;
//Stack of file descriptors to dinamic libraries
pila stackDinamic;

void crearPila(pila *P) {
    *P = NULL;
}

void destruirPila(pila *P) {
    pila aux;
    aux = *P;
    while (aux != NULL) {
        aux = aux->sig;
        free(*P);
        *P = aux;
    }
}

unsigned esVaciaPila(pila P) {
    return P == NULL;
}

tipoelemPila tope(pila P) {
  tipoelemPila t;
    if (!esVaciaPila(P)) /*si pila no vacía*/
        t = P->elemento;
  return t;
}

void push(pila *P, tipoelemPila E) {
    pila aux;
    aux = (pila) malloc(sizeof (struct tipo_celda));
    aux->elemento = E;
    aux->sig = *P;
    *P = aux;
}

void pop(pila *P) {
    pila aux;
    if (!esVaciaPila(*P)) /*si pila no vacía*/ {
        aux = *P;
        *P = (*P)->sig;
        free(aux);
    }
}
