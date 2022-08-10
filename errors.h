#ifndef __ERRORS_LIB
#define __ERRORS_LIB

/*
 * Code file was not provided as an argument
 */
void errorUnexpectedArguments();
/*
 * Left operand must be an lvalue
 */
void errorExpectedLValue();
/*
 * Impossible to open file
 */
void errorImpossibleOpenFile(char const *s);
/*
 * Impossible to load function
 */
void errorImpossibleLoadFunction(char const *s);
/*
 * Name is already declared
 */
void errorAlreadyDeclared(char const *s);
/*
 * A division by zero was encountered
 */
void errorDivisionByZero();

/*
 * A syntax error was found during parsing
 */
void errorSyntax(char const *s);


#endif	/* __ERRORS_LIB */
