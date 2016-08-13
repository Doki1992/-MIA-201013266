#ifndef INSTRUCCIONES
#define INSTRUCCIONES
#include "instruccion.h"
struct Nodo{
    char tipo [40];
    disk * mk;
    ddisk *mr;
    fd * ffd;
    m*mou;
    um *umo;
    reporte *rr;
    ex *ee;
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
void iniciar_m(ptrnodo * This, m*mou);
void iniciar_um(ptrnodo * This, um*umo);
void iniciar_rep(ptrnodo * This, reporte*rr);
void iniciar_ex(ptrnodo * This, ex *ee);

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
    }else if(strcmp(tipo,"m")==0){
        m * mou = (m*)generico;
        iniciar_m(This,mou);
    }else if(strcmp(tipo,"um")==0){
        um * umo=(um*)generico;
        iniciar_um(This,umo);
    }else if(strcmp(tipo,"r")==0){
        reporte *rr = (reporte*)generico;
        iniciar_rep(This,rr);
    }else if(strcmp(tipo,"ex")==0){
        ex * ee = (ex *)generico;
        iniciar_ex(This,ee);
    }else{
        printf("Error instruccion no soportada instrucciones.h");
        printf(" linea 63");
        INSTRUTION_STATE=1;
    }
}

void iniciar_ex(ptrnodo *This, ex *ee){
    (*This)->ee=(ex *)malloc(sizeof(ex));
    strcpy((*This)->ee->path,ee->path);
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

void iniciar_m(ptrnodo *This, m *mou){
    (*This)->mou = (ptrm)malloc(sizeof(m));
    strcpy((*This)->mou->name,mou->name);
    strcpy((*This)->mou->path,mou->path);
}

void iniciar_um(ptrnodo *This, um *umo){
    int i;
    (*This)->umo = (ptrum)malloc(sizeof(um));
    (*This)->umo->hasta_donde = umo->hasta_donde;
    for(i=0;i<umo->hasta_donde;i++){
        strcpy((*This)->umo->cadenas[i].representacion_cad,umo->cadenas[i].representacion_cad);
    }
}

void iniciar_rep(ptrnodo *This, reporte *rr){
   (*This)->rr = (reporte*)malloc(sizeof(reporte));
   (*This)->rr->disco=rr->disco;
   (*This)->rr->particion=rr->particion;
   strcpy((*This)->rr->name,rr->name);
   strcpy((*This)->rr->path,rr->path);
   strcpy((*This)->rr->ruta,rr->ruta);
}


#endif // INSTRUCCIONES

