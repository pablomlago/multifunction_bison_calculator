#include <stdlib.h>
#include <dlfcn.h>
#include <string.h>

#include "mfcalc.tab.h"
#include "lex.yy.h"

#include "abb.h"
#include "errors.h"

/*
 * Cleans variables in current workspace
 */
void comClean(int argc, char** argv) {
  //We delete elements of type VAR
  inordenClean(&sym_table, sym_table, VAR);
}
/*
 * Enables output after evaluation of expressions
 */
void comEcho(int argc, char** argv) {
  if(argc != 1) {
    //The arguments provided are not those expected
    errorUnexpectedArguments();
  } else {
    // -on option was provided
    if( strcmp(argv[0], "on") == 0) {
      //We enable output of result of evaluations
      printFlag = 1;
    // -off option was provided
    } else if( strcmp(argv[0], "off") == 0) {
      //We disable output of result of evaluations
      printFlag = 0;
    } else {
      //The arguments provided are not those expected
      errorUnexpectedArguments();
    }
  }
}
/*
 * Shows help about the functionality of the calculator
 */
void comHelp(int argc, char** argv) {
  printf(
    "============ COMMANDS ============\n"
    "\t clean: Cleans current workspace.\n"
    "\t echo $(on|off): Enables verbose output.\n"
    "\t help: Shows information about the commands.\n"
    "\t load $library $function: Loads a function from a dynamic library.\n"
    "\t read $file: Processes the instructions in a file.\n"
    "\t workspace ($all): Shows current workspace.\n"
    "============ OPERATORS ============\n"
    "\t +: Sum.\n"
    "\t -: Substraction.\n"
    "\t *: Product.\n"
    "\t /: Division\n"
    "\t ^: Exponentiation\n"
  );
}
/*
 * Loads a function from a dynamic library
 */
void comLoad(int argc, char** argv) {
  if(argc != 2)  {
    //The arguments provided are not those expected
    errorUnexpectedArguments();
    return;
  }
  //We open a dynamic library whose path is provided in argv[0]
  FILE* handle = dlopen(argv[0], RTLD_LAZY);
  char* error = NULL;
  tipoelem t;
  tipoelemPila tp;
  //In case the libray could not be opened we show and error
  if (handle == NULL) {
    errorImpossibleOpenFile(argv[0]);
    return;
  }
  //We load the function from the library whose name matches argv[1]
  t.value.fun = (func_t*) dlsym(handle, argv[1]);
  //We check if there was an error loading the file
  error = dlerror();
  if (error != NULL) {
      errorImpossibleLoadFunction(argv[1]);
      dlclose(handle);
      return;
  }
  //We store the descriptor to close it when finishing the program
  tp.value.desc = handle;
  push(&stackDinamic, tp);
  //We close the descriptor to the dynamic library
  //dlclose(handle);
  //We check if the function is already present in the symbol table
  if(es_miembro_clave(sym_table, argv[1])) {
    //In that case we show an indicative message
    errorAlreadyDeclared(argv[1]);
  } else {
    //Otherwise, we add it to the symbol table
    //We initialize the fields for inserting in our symbol table
    size_t nameSize = strlen(argv[1])+1;
    t.name = (char*)malloc(nameSize*sizeof(char));
    strncpy(t.name, argv[1], nameSize);
    t.type = FUN;
    insertar(&sym_table, t);
  }
}
/*
 * Reads a set of instructions from a file and executes them
 */
void comRead(int argc, char** argv) {
  if(argc != 1)  {
    //The arguments provided are not those expected
    errorUnexpectedArguments();
    return;
  }
  tipoelemPila t;
  //We open the file whose instructions will be read
  t.value.desc = fopen(argv[0], "r");
  //In case the file could not be opened a message is printed
  if(t.value.desc == NULL) {
    errorImpossibleOpenFile(argv[0]);
    return;
  }
  //Otherwise, we push the descriptor to the stack
  push(&stackInput, t);
  //And change flex input
  yyin = t.value.desc;
}
/*
 * Outputs current workspace
 */
void comWorkspace(int argc, char** argv) {
  if(argc > 0) {
    if( strcmp(argv[0], "all") == 0) {
      //We output all the elements in our workspace
      inorden(sym_table, FUN);
      inorden(sym_table, VAR);
      inorden(sym_table, COM);
    } else {
      //The arguments provided are not those expected
      errorUnexpectedArguments();
    }
  } else {
    //We only output varaibles in our workspace
    inorden(sym_table, VAR);
  }
}
