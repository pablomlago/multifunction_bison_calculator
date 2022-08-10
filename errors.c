#include <stdio.h>
#include <stdlib.h>

#define CALC_NAME "etsecalc"

#define RESET   "\033[0m"
#define RED     "\033[31m"      /* Red */

#define FATAL_ERROR "fatal error"
#define FATAL_ERROR_CODE 402

#define NORMAL_ERROR "error"
#define NORMAL_ERROR_CODE 403

#define SYNTAX_ERROR "syntax error"
#define SYNTAX_ERROR_CODE 404

#include "errors.h"

/* Definition of the functions for fatal error treatment */

/*
 * Code file was not provided as an argument
 */
void errorUnexpectedArguments() {
  fprintf(stderr, CALC_NAME": "RED NORMAL_ERROR RESET ": Unexpected arguments. Check help for more information.\n");
}

/*
 * Left operand must be an lvalue
 */
void errorExpectedLValue() {
  fprintf(stderr, CALC_NAME": "RED NORMAL_ERROR RESET ": A lvalue was expected as left operand.\n");
}
/*
 * Impossible to open file
 */
void errorImpossibleOpenFile(char const *s) {
  fprintf(stderr, CALC_NAME": "RED NORMAL_ERROR RESET ": Impossible to open file %s.\n", s);
}
/*
 * Impossible to load function
 */
void errorImpossibleLoadFunction(char const *s) {
  fprintf(stderr, CALC_NAME": "RED NORMAL_ERROR RESET ": Impossible to load function %s.\n", s);
}
/*
 * Name is already declared
 */
void errorAlreadyDeclared(char const *s) {
  fprintf(stderr, CALC_NAME": "RED NORMAL_ERROR RESET ": Name %s is already declared.\n", s);
}
/*
 * A division by zero was encountered
 */
void errorDivisionByZero(char const *s) {
  fprintf(stderr, CALC_NAME": "RED NORMAL_ERROR RESET ": A division by zero cannot be evaluated.\n");
}
/*
 * A syntax error was found during parsing
 */
void errorSyntax(char const *s) {
  fprintf(stderr, CALC_NAME": "RED SYNTAX_ERROR RESET ": %s.\n", s);
}
