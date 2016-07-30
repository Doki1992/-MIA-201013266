#ifndef INSTRUCCIONES
#define INSTRUCCIONES
#include "instruccion.h"
struct Nodo{
    char tipo [40];
    disk * mk;
    ddisk *mr;
    fd * ffd;
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
void iniciar_mr(ptrnodo * This, ddisk * mr);
void iniciar(ptrnodo * This,void *generico, char * tipo);
void iniciar_fd(ptrnodo*This,fd *ffd);

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

void eliminar_instruccion(){
    if(primero!=NULL){
        ptrnodo aux = primero;
        primero=primero->sig;
        free(aux);
        tam--;
    }
}

void iniciar(ptrnodo *This, void *generico, char * tipo){
    strcpy((*This)->tipo,tipo);
    if(strcmp(tipo,"mk")==0){
        disk * mk = (disk*)generico;
        iniciar_mk(This,mk);
    }else if(strcmp(tipo,"mr")==0){
        ddisk *mr = (ddisk*)generico;
        iniciar_mr(This,mr);
    }else if(strcmp(tipo,"fd")==0){
        fd * ffd =(ptrfd)generico;
        iniciar_fd(This,ffd);
    }else{
        printf("Error instruccion no soportada instrucciones.h");
        printf(" linea 63");
        INSTRUTION_STATE=1;
    }
}

void iniciar_mr(ptrnodo* This,ddisk *mr){
    (*This)->mr=(ptrddisk)malloc(sizeof(ddisk));
    strcpy((*This)->mr->path,mr->path);
}

void iniciar_mk(ptrnodo *This, disk *mk){
    (*This)->mk = (ptrdisk)malloc(sizeof(disk));
    strcpy((*This)->mk->name,mk->name);
    strcpy((*This)->mk->path,mk->path);
    (*This)->mk->sise=mk->sise;
    (*This)->mk->unit=mk->unit;
}

void iniciar_fd(ptrnodo *This, fd *ffd){
    (*This)->ffd = (ptrfd)malloc(sizeof(fd));
    strcpy((*This)->ffd->name,ffd->name);
    strcpy((*This)->ffd->delet,ffd->delet);
    strcpy((*This)->ffd->path,ffd->path);
    (*This)->ffd->sise=ffd->sise;
    (*This)->ffd->unit=ffd->unit;
    (*This)->ffd->type=ffd->type;
    (*This)->ffd->fit=ffd->fit;
    (*This)->ffd->add=ffd->add;
}


#endif // INSTRUCCIONES

