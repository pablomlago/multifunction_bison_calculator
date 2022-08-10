%{
#include <math.h>
#include <stdlib.h>
#include "abb.h"
#include "pila.h"
%}

/*Integer literals*/
INTEGER {DECINTEGER}|{BININTEGER}|{OCTINTEGER}|{HEXINTEGER}
DECINTEGER {DIGIT}+
BININTEGER "0"("b"|"B"){BINDIGIT}*
OCTINTEGER "0"("o"|"O"){OCTDIGIT}*
HEXINTEGER "0"("x"|"X"){HEXDIGIT}*
NONZERODIGIT [1-9]
DIGIT [0-9]
BINDIGIT [0-1]
OCTDIGIT [0-7]
HEXDIGIT {DIGIT}|[a-fA-F]
/*Floating point literals*/
FLOATNUMBER {POINTFLOAT}|{EXPONENTFLOAT}
POINTFLOAT {DIGITPART}?{FRACTION}|({DIGITPART}".")
EXPONENTFLOAT ({DIGITPART}|{POINTFLOAT}){EXPONENT}
DIGITPART {DIGIT}+
FRACTION "."{DIGITPART}
EXPONENT [eE][+-]?{DIGITPART}
/*Same treatment for floats and integers*/
NUMBER {INTEGER}|{FLOATNUMBER}
/*Identifiers*/
IDENTIFIER [_a-zA-Z][_a-zA-Z0-9]*
/*Arguments*/
ARGUMENT ${SHORTSTRINGITEM}+
SHORTSTRINGITEM {SHORTSTRINGCHAR}|{STRINGESCAPESEQ}
SHORTSTRINGCHAR [^"\\\n ]
STRINGESCAPESEQ \\.
/*Comment*/
COMMENT \#[^\n]*$

%%
{NUMBER} {
yylval.NUM = atof(yytext);
return NUM;
}
"exit" {
  return YYEOF;
}
{IDENTIFIER} {
tipoelem t;
t.name = NULL;
//First, we check if the identifier is in the symbol table
buscar_nodo(sym_table, yytext, &t);
if(t.name == NULL) {
  //If not, we add it as a variable
  size_t nameSize = yyleng+1;
  t.name = (char*)malloc(nameSize*sizeof(char));
  strncpy(t.name, yytext, nameSize);
  //We initialize the variable to 0
  t.type = VAR;
  //Variables are lvalues, they can be assigned a value
  t.lvalue = 1;
  t.value.var = 0;
  //We add the new variable to the symbol table
  insertar(&sym_table, t);
}
yylval.VAR = t;
return t.type;
}
{ARGUMENT} {
  tipoelemPila t;
  size_t nameSize = yyleng;
  t.value.name = (char*)malloc(nameSize*sizeof(char));
  //We ignore the character - in yytext
  strncpy(t.value.name, yytext+1, nameSize);
  yylval.ARG = t;
  return ARG;
}
<<EOF>> {
  return EOF;
}
"="|"("|")"|"+"|"-"|"*"|"/"|"^"|","|";" {
  return (yytext[0]);
}
"\n" {
  return (yytext[0]);
}
{COMMENT}
.
%%

int yywrap () {
  //When we get to the end of the file, we move to the next input stream
  tipoelemPila t = tope(stackInput);
  //We close the already processed descriptor
  fclose(t.value.desc);
  //We remove the descriptor from the stack
  pop(&stackInput);
  //We move on to the next file to be processed
  t = tope(stackInput);
  //And we start processing it
  yyin = t.value.desc;
  //We show and indicative message when we finish processing files
  if(yyin == stdin) printf("[INFO] Instructions from files were executed succesfully.\n" PROMPT);
  //We indicate that there is still input to be procesed
  return 0;
}
