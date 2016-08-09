#ifndef EJECUTAR
#define EJECUTAR
#include "Automata.h"
#include "montar.h"
char*itoa(int i, char b[]);
void eliminaDisco(ptrddisk di);
void elimnarParticion();
void montar_partcion(ptrm m);
static ptrmontar cabeza=NULL;
void iniciarMontarcabeza(ptrmontar * cabeza);
void desmontar(ptrum disco);

void ejecutar(){
tam;
    while(primero!=NULL){
        if(strcmp(primero->tipo,"mk")==0){
            creaDisco(primero->mk);
        }else if(strcmp(primero->tipo,"mr")==0){
            eliminaDisco(primero->mr);
        }else if(strcmp(primero->tipo,"fd")==0){
            crearParticion_primaria_extendida(primero->ffd);
        }else if(strcmp(primero->tipo,"m")==0){
            montar_partcion(primero->mou);
        }else if(strcmp(primero->tipo,"um")==0){
            desmontar(primero->umo);
        }
        eliminar_instruccion();
    }

}

void desmontar(ptrum disco){
    int i;
    for(i=0;i<disco->hasta_donde;i++){
        int numero = (int)disco->cadenas[i].representacion_cad[1]-48;
        char diss = disco->cadenas[i].representacion_cad[0];
        char path [40];
        char name [40];
        strcpy(path,obtener_path(cabeza,diss,numero));
        strcpy(name,obtener_nombre_particion(cabeza,diss,numero));
        printf("desmontando partcion con nombre: ");
        printf(name);
        printf(".....\n");
        if(strcmp(name,"xc")==0)
            printf("Error en id solicitado no ha sido montado....\n");
        else
            Desmontar_particion(&cabeza,name,path);

    }
    ver_particiones_montadas(cabeza);
}

void creaDisco(ptrdisk di){
    printf("Creando disco con nombre: ");
    printf(di->name);
    printf("....\n");
    char exe [500]={};
    char size_m [500]={};
    char exe1[500]={};
    strcat(exe1,"mkdir -p ");
    strcat(exe1,di->path);
    system(exe1);
    strcpy(size_m,itoa(di->sise,size_m));
    strcat(exe,"dd if=/dev/zero of=");
    strcat(exe,di->path);
    strcat(exe,di->name);
    strcat(exe," ");
    strcat(exe," bs=");
    strcat(exe,size_m);
    strcat(exe," count=1");
    system(exe);
    char cad [500]={};
    strcat(cad,di->path);
    strcat(cad,di->name);
    crearMBR(di->sise,cad);
    strcat(di->path,di->name);
}

void eliminaDisco(ptrddisk di){
    printf("Desea borrar el disco con direccion: ");
    printf(di->path);
    printf("  ");
    printf("s/n\n");
    char *con = (char*)malloc(sizeof(char));
    fgets(con,10,stdin);
    if(strcmp(con,"s\n")==0){
        char exe [500]={};
        strcat(exe,"rm ");
        strcat(exe,di->path);
        system(exe);
    }
}

void crearParticion_primaria_extendida(ptrfd f){

    if(strcmp(f->delet,"fast")==0||strcmp(f->delet,"full")==0){
            ebr aux = buscar_ebr(f->path,f->name);
            if(existeParticion(f->path,f->name)==1){
                printf("Eliminando particion con nombre ");
                printf(f->name);
                printf("....\n");
                actualizarMBR(f->name,f->path);
            }else if(strcmp(aux.name,"vacio")!=0){
                printf("Eliminando particion con nombre ");
                printf(f->name);
                printf("....\n");
                eliminar_ebr(f->path,f->name);
            }else{
                printf("Error la particion que desea borrar no exist...\n");
            }
    }else if((int)f->type==(int)'l'){
        printf("creando particion ");
        printf("con nombre: ");
        printf(f->name);
        printf("......\n");
        crearParticonEBR('1',f->fit,obtener_apuntador_asiguiente(f->path),f->sise,-1,f->name,f->path);
    }else if((int)f->type==(int)'p'||(int)f->type==(int)'e'){
        printf("creando particion ");
        printf("con nombre: ");
        printf(f->name);
        printf("......\n");
        crearParticionNormal('1',f->type,f->fit,f->sise,f->name,f->path);
    }
}

void montar_partcion(ptrm m){
    if(m->just_see==0){
        printf("Montando particion con nombre: ");
        printf(m->name);
        printf(".....\n");
        Montar_disco(&cabeza,m->path,m->name);
    }else{

    }
    ver_particiones_montadas(cabeza);
}

void elimnarParticion(){

}

char* itoa(int i, char b[]){
    char const digit[] = "0123456789";
    char* p = b;
    if(i<0){
        *p++ = '-';
        i *= -1;
    }
    int shifter = i;
    do{ //Move to where representation ends
        ++p;
        shifter = shifter/10;
    }while(shifter);
    *p = '\0';
    do{ //Move back, inserting digits as u go
        *--p = digit[i%10];
        i = i/10;
    }while(i);
    return b;
}


void iniciarMontarcabeza(ptrmontar *cabeza){
    (*cabeza)=(ptrmontar)malloc(sizeof(montar));
}

#endif // EJECUTAR

