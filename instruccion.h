#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>

struct mkdisk {
int sise;
char unit;
char path [200];
char name [200];
};

struct rmdisk{
   char path [200];
};

struct fdisk{
    int sise;
    char unit;
    char path[200];

};

typedef struct fdisk fd;
typedef struct fdisk *ptrfd;
typedef struct rmdisk ddisk;
typedef struct rmdisk *ptrddisk;
typedef struct mkdisk   disk;
typedef struct mkdisk * ptrdisk;

/*ESTA VARIABLE MUESTRA SI HA OCURRIDO UN ERROR ESTA O NO 1 SI*/
int INSTRUTION_STATE =0;


void set_size(int sise, disk ** disco){
    if(sise<0){
        printf("Error el tamaño del disco debe ser mayor que 0\n");
        printf("linea 14 archivo instrucion.h");
        INSTRUTION_STATE=1;
    }else{
        (*disco)->sise=sise;
    }
}

void set_unit(char unit, disk ** disco){
    if((int)unit==(int)'m'){
        (*disco)->sise=1024*1024*(*disco)->sise;
    }else if((int)unit==(int)'k'){
        (*disco)->sise=1024*(*disco)->sise;
    }else if((int)unit==(int)'v'){
        (*disco)->sise=1024*1024*(*disco)->sise;
    }else{
        printf("Error el parametro del tamaño no es correcto\n");
        printf("Linea 30 archvio instruccion.h");
        INSTRUTION_STATE=1;
        return;
    }
}

void set_path(char path[], disk ** disco){
    char * exe = (char*)calloc(400,sizeof(char));
    if((int)path[0]==(int)'/'){
        strcat(exe,"mike");
    }else{
        strcat(exe,"mike/");
    }
    strcat(exe,path);

    strcpy((*disco)->path,exe);
}

void set_name(char name[],disk ** disco){
    strcpy((*disco)->name,name);
}

void set_path_delete_disk(char path[], ddisk ** disco){
    char * exe = (char*)malloc(sizeof(char));
    if((int)path[0]==(int)'/'){
        strcat(exe,"mike");
    }else{
        strcat(exe,"mike/");
    }
    strcat(exe,path);

    strcpy((*disco)->path,exe);
}
