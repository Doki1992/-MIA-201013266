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
    char path[300];
    char type;
    char fit;
    char delet[300];
    char name [300];
    int  add;
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
    char exe [400] ={};
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
    char  exe [200] = {};
    if((int)path[0]==(int)'/'){
        strcat(exe,"mike");
    }else{
        strcat(exe,"mike/");
    }
    strcat(exe,path);

    strcpy((*disco)->path,exe);
}

void set_size_fd(int tam, fd ** disco){
    if(tam<=0){
        printf("Error el tamaño debe ser mayo que cero \n");
        INSTRUTION_STATE=1;
    }else{
        (*disco)->sise=tam;
    }
}

void set_name_fd(char name [], fd ** disco){
    strcpy((*disco)->name,name);
}

void set_path_fd(char path[], fd** disco){
    char exe [200]={};
    if((int)path[0]==(int)'/'){
        strcat(exe,"mike");
    }else{
        strcat(exe,"mike/");
    }
    strcat(exe,path);
    strcpy((*disco)->path,exe);
}

void set_unit_fd(char unit, fd ** disco){
    if((int)unit==(int)'b'){
        (*disco)->sise=(*disco)->sise*1;
    }else if((int)unit==(int)'k'){
        (*disco)->sise=(*disco)->sise*1024;
    }else if((int)unit==(int)'m'){
        (*disco)->sise=(*disco)->sise*1024*1024;
    }else{
        (*disco)->sise=(*disco)->sise*1024;
    }
}

void set_type_fd(char *typ, fd ** disco){
    char type = (*typ);
    if((int)type==(int)'p'){
        (*disco)->type='p';
    }else if((int)type==(int)'e'){
        (*disco)->type='e';
    }else if((int)type==(int)'l'){
        (*disco)->type='l';
    }else{
        (*disco)->type='p';
    }
}

void set_fit_fd(char fit[],fd ** disco){
    char aux = fit[0];
    /*if((int)aux!=(int)'b'||(int)aux!=(int)'f'||(int)aux!=(int)'w'||(int)aux!=(int)'a'){
        printf("Error formato de ajuste desconocido\n");
        INSTRUTION_STATE=1;
    }else*/ if((int)fit[0]==(int)'a'){
        (*disco)->fit='w';
    }else if((int)aux==(int)'b'){
        (*disco)->fit=fit[0];
    }else if((int)aux==(int)'w'){
        (*disco)->fit='w';
    }else if((int)aux==(int)'f'){
        (*disco)->fit='f';
    }else{
        (*disco)->fit=fit[0];
    }
}

void set_delete_fd(char delet [], fd ** disco){
    strcpy((*disco)->delet,delet);

}

void set_add_fd(int add, fd ** disco){
    (*disco)->add=add;

}
