#include <stdio.h>
#include <stdlib.h>
#include "Automata.h"
#include "estructuras.h"
extern void lexer(char path []);

int main()
{
    char buffer[2000];
    leer(buffer,"/home/mike/hola.txt");
    lexer(buffer);
    return 0;
}
