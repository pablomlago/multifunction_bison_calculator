#ifndef __COMMANDS_LIB
#define __COMMANDS_LIB

/*
 * Cleans variables in current workspace
 */
void comClean(int argc, char** argv);
/*
 * Enables output after evaluation of expressions
 */
void comEcho(int argc, char** argv);
/*
 * Shows help about the functionality of the calculator
 */
void comHelp(int argc, char** argv);
/*
 * Loads a function from a dynamic library
 */
void comLoad(int argc, char** argv);
/*
 * Reads a set of instructions from a file and executes them
 */
void comRead(int argc, char** argv);
/*
 * Outputs current workspace
 */
void comWorkspace(int argc, char** argv);

#endif	/* __COMMANDS_LIB */
