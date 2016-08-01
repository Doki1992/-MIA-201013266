#include <stdio.h>
#include <stdlib.h>
#include "ejecutar.h"
extern void lexer(char path []);

int main()
{
    char buffer[20000];
    leer(buffer,"/home/mike/build-mia1-Desktop_Qt_5_5_1_GCC_32bit-Debug/hola.txt");
    lexer(buffer);
    ejecutar();
    printf("%d\n",sizeof(mbr));
    //printf("%d",sizeof(ebr));
    return 0;
}
