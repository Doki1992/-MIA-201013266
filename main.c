#include <stdio.h>
#include <stdlib.h>
#include "ejecutar.h"
extern void lexer(char path []);

int main()
{
    char cadena [12]={};

    crearlista();
    do {

        char comando [100]={};
        char buffer[20000]={};
        ejecutar();
        printf(".....Escriba un comando por favor.....\n");
        fgets(comando,100,stdin);
        lexer(comando);
        ejecutar();
        printf("para para escriba no.. \n");

    } while (strcmp(cadena,"no\n")!=0);


    return 0;
}
