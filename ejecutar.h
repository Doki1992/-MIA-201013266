#ifndef EJECUTAR
#define EJECUTAR
#include "Automata.h"
#include "estructuras.h"
char*itoa(int i, char b[]);
void eliminaDisco(ptrddisk di);
void elimnarParticion();
void ejecutar(){
tam;
    while(primero!=NULL){
        if(strcmp(primero->tipo,"mk")==0){
            creaDisco(primero->mk);
        }else if(strcmp(primero->tipo,"mr")==0){
            eliminaDisco(primero->mr);
        }else if(strcmp(primero->tipo,"fd")==0){
            crearParticion_primaria_extendida(primero->ffd);
        }
        eliminar_instruccion();
    }

}


void creaDisco(ptrdisk di){
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
    impimeMBR(di->path);
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
                actualizarMBR(f->name,f->path);
            }else if(strcmp(aux.name,"vacio")!=0){
                eliminar_ebr(f->path,f->name);
            }else{
                printf("ERROR LA PARTICION ESPECIFICADA NO EXISTE");
            }
    }else if((int)f->type==(int)'l'){
        crearParticonEBR('1',f->fit,obtener_apuntador_asiguiente(f->path),f->sise,-1,f->name,f->path);
    }else if((int)f->type==(int)'p'||(int)f->type==(int)'e'){
        crearParticionNormal('1',f->type,f->fit,f->sise,f->name,f->path);
    }
    impimeMBR(f->path);
    imprimir_ebr(f->path);

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

#endif // EJECUTAR

