#ifndef __PARAMS_LIB
#define __PARAMS_LIB
#include "pila.h"

//Parameters for commands will be extracted using this struct
typedef struct {
  int argc;
  char** argv;
} ParamStruct;

/*
 * Maps a stack of parameters to a char**
 */
ParamStruct processParamStack(pila* P);
/*
 * Frees the memory associated to the parameters passed to a command
 */
void removeParamStruct(ParamStruct paramStruct);

#endif	/* __PARAMS_LIB */
