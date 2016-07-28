#include <stdio.h>
#include <stdlib.h>
#include "ejecutar.h"
extern void lexer(char path []);

int main()
{
    char buffer[2000];
    leer(buffer,"/home/mike/hola.txt");
    lexer(buffer);
    ejecutar();
    printf("%d\n",sizeof(mbr));
    printf("%d",sizeof(ebr));
    return 0;
}
