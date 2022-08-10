#include <stdlib.h>
#include "params.h"

/*
 * Maps a stack of parameters to a char**
 */
ParamStruct processParamStack(pila* P) {
  ParamStruct ps;
  tipoelemPila t;
  //Auxiliar stack to process the parameters contained in the stack
  pila aux;
  //Count variable
  int i = 0;
  //We initialize the auxiliar stack
  crearPila(&aux);
  //We will be increasing the number of parameters in each iterations
  ps.argc = 0;
  //We pop all the elements from the stack
  while(!esVaciaPila(*P)) {
    //And we add each of them to the auxiliar stack
    t = tope(*P);
    pop(P);
    push(&aux, t);
    ps.argc++;
  }
  //We allocate memory for the parameters now that we know its number
  ps.argv = (char**)malloc(ps.argc*sizeof(char*));
  //We extract the parameters from the auxiliar stack
  for(i = 0; i < ps.argc; i++) {
    t = tope(aux);
    pop(&aux);
    ps.argv[i] = t.value.name;
  }
  //We free the memory associated to both stacks
  destruirPila(&aux);
  destruirPila(P);
  //We return the struct of parameters to be used by a command
  return ps;
}
/*
 * Frees the memory associated to the parameters passed to a command
 */
void removeParamStruct(ParamStruct ps) {
  //Count variable
  int i;
  //We free the memory associated to every parameter
  for(i = 0; i < ps.argc; i++) {
    free(ps.argv[i]);
    ps.argv[i] = NULL;
  }
  //And finally, the memory associated to the vector of parameters
  free(ps.argv);
  ps.argv = NULL;
}
