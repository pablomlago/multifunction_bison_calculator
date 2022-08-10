#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "initialization.h"

#include "mfcalc.tab.h"
#include "abb.h"
#include "commands.h"

//Initializes the name of the symbol
void _initializeName(tipoelem* t, const char* name){
  size_t nameSize = strlen(name)+1;
  t->name = (char*)malloc(nameSize*sizeof(char));
  strncpy(t->name, name, nameSize);
}

/*
 * Initializes the symbol table of the calculator with a set of
 * commands, constants and functions.
 */
void initializeSymbolTable(abb* sym_table) {

  //Struct for initialization of functions
  struct init_fun
  {
    char const *name;
    func_t *fun;
  };
  //Functions which will be inserted in the symbol table
  struct init_fun const funs[] =
  {
    { "atan", atan },
    { "cos",  cos  },
    { "exp",  exp  },
    { "ln",   log  },
    { "sin",  sin  },
    { "sqrt", sqrt },
    { 0, 0 },
  };
  //Struct for initialization of commands
  struct init_com
  {
    char const *name;
    command_t *comm;
  };
  //Commands which will be inserted in the symbol table
  struct init_com const coms[] =
  {
    { "workspace", comWorkspace },
    { "clean",     comClean     },
    { "load",      comLoad      },
    { "read",      comRead      },
    { "help",      comHelp      },
    { "echo",      comEcho      },
    { 0, 0 }
  };
  //Struct for initialization of constants
  struct init_const
  {
    char const *name;
    double var;
  };
  //Constants which will be inserted in the symbol table
  struct init_const const consts[] =
  {
    { "pi",  M_PI   },
    { "e" ,  exp(1) },
    { 0, 0 }
  };

  /* Put functions in table. */
  for (int i = 0; funs[i].name; i++)
  {
    tipoelem t;
    _initializeName(&t, funs[i].name);
    t.type = FUN;
    t.lvalue = 0;
    t.value.fun = funs[i].fun;
    insertar(sym_table, t);
  }

  /* Put commands in table. */
  for (int i = 0; coms[i].name; i++)
  {
    tipoelem t;
    _initializeName(&t, coms[i].name);
    t.type = COM;
    t.lvalue = 0;
    t.value.comm = coms[i].comm;
    insertar(sym_table, t);
  }

  /* Put constants in table. */
  for (int i = 0; consts[i].name; i++)
  {
    tipoelem t;
    _initializeName(&t, consts[i].name);
    t.type = VAR;
    t.lvalue = 0;
    t.value.var = consts[i].var;
    insertar(sym_table, t);
  }
}
