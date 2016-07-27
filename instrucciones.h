#ifndef INSTRUCCIONES
#define INSTRUCCIONES
#include "instruccion.h"
struct Nodo{
    char tipo [40];
    disk * mk;
    struct Nodo * sig;
};

typedef struct Nodo nodo;
typedef struct Nodo *ptrnodo;
int tam =0 ;
ptrnodo primero;
ptrnodo ultimo;
void crearlista();
void insertar(ptrnodo *primero, void *mk, ptrnodo *ultimo,char *tipo);
void iniciar_mk(ptrnodo * This, disk * mk);
void iniciar(ptrnodo * This,void *generico, char * tipo);

void crearlista(){
    primero = NULL;
    ultimo = NULL;
}

void insertar(ptrnodo *primero, void *generico, ptrnodo* ultimo,char * tipo){
    ptrnodo nuevo = (ptrnodo)malloc(sizeof(nodo));
    if(nuevo!=NULL){
        tam++;
        iniciar(&nuevo,generico,tipo);
        if((*primero)==NULL&&(*ultimo)==NULL){
           nuevo->sig=NULL;
           (*primero)=nuevo;
           (*ultimo)=nuevo;
        }else{
            nuevo->sig=NULL;
            (*ultimo)->sig=nuevo;
            (*ultimo)=nuevo;
        }

    }
}

void iniciar(ptrnodo *This, void *generico, char * tipo){
    strcpy((*This)->tipo,tipo);
    if(strcmp(tipo,"mk")==0){
        disk * mk = (disk*)generico;
        iniciar_mk(This,mk);
    }else{
        printf("Error instruccion no soportada instrucciones.h");
        printf(" linea 49");
        INSTRUTION_STATE=1;
    }
}

void iniciar_mk(ptrnodo *This, disk *mk){
    (*This)->mk = (ptrdisk)malloc(sizeof(disk));
    strcpy((*This)->mk->name,mk->name);
    strcpy((*This)->mk->path,mk->path);
    (*This)->mk->sise=mk->sise;
    (*This)->mk->unit=mk->unit;
}


#endif // INSTRUCCIONES

