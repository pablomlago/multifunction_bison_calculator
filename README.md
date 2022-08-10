# EtseCalc
Multifunction Calculator made with Bison and Flex for the second  exercise of the subject Compilers and Interpreters taught at the University of Santiago de Compostela.

------------

**Table of Contents**

[TOC]

#Introduction
This is the third exercise of the subject Compiler and Interpreters  taught at the University of Santiago de Compostela.

It consists in an interpreter for mathematical expressions, using Flex and Bison for lexical and syntax parsing respectively.

#Files
Following, we provide a brief description of the files contained in the project.
- **abb.c:** Implementation of the binary tree used for the symbol table.
- **commands.c:** Implementation of the functions that extend the capabilities of the calculator.
- **errors.c:** Specific messages for every type of error detected.
- **initialization.c**: Allows the initialization of the symbol table with some predefined functions, commands and constants.
- **instructions1, instructions2: **Sample set of instructions to demonstrate the behaviour of the command *read*.
- **launch.sh:** Shell script to generate the executable for the calculator.
- **mfcalc.l:** Flex lexical specification file.
- **mfcalc.y:** Bison grammar specification file.
- **params.c:** Provides functions that allow the extraction of the parameters for the commands.
- **pila.c: **Implementation of an stack.
- **sampleLIbrary.c:** Sample library to demonstrate how to load a function dinamically using *load*.

Every file has its correspondign header file associated.

#Operators
The interpreter supports the following operators.
- **+ :** Sumation.
- **- :** Substraction.
- *** :** Multiplication.
- **^: ** Exponentation.
- **Parenthesis (): ** Allow altering the order of evaluation.
- **= : **Assignation.

#Commands
The interpreter offers a set of commands that extend its basic functionality.
- **clean:** clean variables in the current workspace.
- **echo $(on|off):** enables/disables the output of the evaluation of mathematical expressions. Its behaviour is the same as adding **;** at the end of an expression.
w- **help:** Provides the user with information on how to use the calculator.
- **load $library $function:** Loads a function from a dynamic library and adds it to the current workspace.
- **read $file:** Evaluates the expressions in a file supplied as parameter.
- **workspace ($all): ** Shows current workspace.

Note that every parameter supplied to the command is preceeded by **$**.

#Dependecies
The calculator was built and tested in *Ubuntu 20.04.2 LTS*. The following programs were used for its development and testing:
- gcc (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0
- flex 2.6.4
- bison (GNU Bison) 3.5.1
- valgrind-3.15.0

#Execution instructions
The parser was built and tested in *Ubuntu 20.04.2 LTS*. For demonstration, the following instructions should be followed:
- Open a terminal and navigate to the directory with the code.
- Input the following comands:

```shell
sh launch.sh
./mfcalc
```

And interactive command line interface will be provided allowing the evaluation of mathematical expressions.

#Sample output
Following, we show an example of the execution of the calculator:


```
EtseCalc 1.0.0
Type "help" for more information.
>>> workspace
	(const) e=2.71828
	(const) pi=3.14159
>>> pi+2-e    
2.423310825
>>> load $./sampleLibrary.so $square
>>> square(e)    
7.389056099
>>> a = 2
2
>>> workspace
	(var) a=2
	(const) e=2.71828
	(const) pi=3.14159
>>> a = pi + 2
5.141592654
>>> workspace
	(var) a=5.14159
	(const) e=2.71828
	(const) pi=3.14159

```

#Future improvements
Following, we list some possible improvements for our calculator.
1. Extend the functionality of the commands allowing a finer-grained control (remove one variable, load several functions at once...).
2. Allow mathematical functions taking more than one parameter (e.g. max, min...).

#References
**[1]** Aho, A. V., Sethi, R., & Ullman, J. D. (1985). Compilers: Principles, Techniques, and Tools.
