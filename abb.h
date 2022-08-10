#ifndef __ABB_LIB
#define __ABB_LIB
#include "pila.h"
/**
 * Tipo de dato abstracto para arbol binario con clave de
 * ordenacion y elemento de celda.
 */

///////////////////////////////////////INICIO PARTE MODIFICABLE

/* Function type. */
typedef double (func_t) (double);
typedef void (command_t) (int argc, char** argv);


typedef char* tipoclave;

typedef struct
{
  char* name;
  int type;
  int lvalue;
  union {
    double var;
    func_t *fun;
    command_t *comm;
  } value;
} tipoelem;

//////////////////////////////////////////FIN PARTE MODIFICABLE

//TIPO OPACO, no sabemos como esta construido celda
// https://es.wikipedia.org/wiki/Puntero_opaco
typedef struct celda *abb;
//typedef void* abb;
// Si no tuviesemos importado abb.h en abb.c podriamos
// lograr mas opacidad usando esta definicion para el arbol:
// typedef void *abb;
// Y teniendo en el abb.c la definicion typedef struct celda *abb;
// Tenemos que decidir que preferimos mayor opacidad o menos
// codigo repetido, en este caso hemos optado por lo segundo.
//

///////////////////////// GLOBAL VARIABLES EXPORTED BY THIS MODULE

//We declare the symbol table to be used in the calculator
extern abb sym_table;
//Depending on this flag, result of evaluating expressions will be shown
extern int printFlag;

/////////////////////////////// FUNCIONES

/**
 * Imprime el arbol seguiend un recorrido inorder
 * @param A Puntero al arbol. Debe estar inicializado.
 */
void inorden(abb A, int type);

void inordenClean(abb* A, abb B, int type);

/**
 * Crea el arbol vacio.
 * @param A Puntero al arbol. Debe estar inicializado.
 */
void crear_arbol(abb *A);

/**
 * Destruye el arbol recursivamente
 * @param A El arbol que queremos destruir
 */
void destruir_arbol(abb *A);

/**
 * Comprueba si el arbol esta vacio
 * @param A El arbol binario
 */
unsigned es_vacio(abb A);

/**
 * Devuelve el subarbol izquierdo de A
 * @param A - Arbol original
 */
abb izq(abb A);
/**
 * Devuelve el subarbol derecho de A
 * @param A - Arbol original
 */
abb der(abb A);

/**
 * Inserta un nuevo nodo en el arbol para el elemento E
 * del que toma su clave. Esta clave no debe existir en
 * el arbol.
 * @param A Arbol binario
 * @param E Informacion del nuevo nodo.
 */
void insertar(abb *A, tipoelem E);

/**
 * Suprime el nodo del arbol <A>
 * @param A
 * @param cl
 */
void suprimir(abb *A, tipoelem E);

/**
 * Comprueba si el elemento con clave <cl> existe en el arbol <A>
 * @param A
 * @param cl
 */
unsigned es_miembro(abb A, tipoelem E);
unsigned es_miembro_clave(abb A, tipoclave cl);

/**
 * Busca un nodo con clave <cl> en el arbol y, si existe
 * modifica el puntero <nodo> para que lo apunte.
 * @param A Arbol binario en el que se busca el nodo.
 * @param cl Clave que se buscara.
 * @param nodo Puntero a un tipoelem.
 */
void buscar_nodo(abb A, tipoclave cl, tipoelem *nodo);

/**
 * Busca el nodo con clave la del nodo y lo modifica.
 * De esta forma nos aseguramos que no puede modificarse
 * la clave.
 * @param A
 * @param nodo
 */
void modificar(abb *A, tipoelem nodo);

/**
 * Recupera la informacion de la celda de la raiz del arbol
 * @param A
 * @param E Puntero al nodo que apuntara a la informacion
 */
void info(abb A, tipoelem *E);

#endif	/* __ABB_LIB */
