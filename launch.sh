flex --header-file=lex.yy.h mfcalc.l
bison -d mfcalc.y
gcc -shared -o sampleLibrary.so -fPIC sampleLibrary.c
gcc -Wall mfcalc.tab.c abb.c pila.c params.c errors.c commands.c initialization.c -lm -ldl -o mfcalc mfcalc.tab.h abb.h pila.h params.h errors.h commands.h initialization.h
