#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>


struct cadena{
   char representacion_cad [12];
};
typedef struct cadena strring;

struct Exec{
    char path[400];
};

struct mkdisk {
int sise;
char unit;
char path [400];
char name [400];
};

struct rmdisk{
   char path [400];
};

struct fdisk{
    int sise;
    char unit;
    char path[400];
    char type;
    char fit;
    char delet[400];
    char name [400];
    int  add;
};

struct mount{
    char name[400];
    char path[400];
    int just_see;
};

struct unmount{
    char name[400];
    strring cadenas [50];
    int hasta_donde;
};

struct rep{
 char name[400];
 char path[400];
 char disco;
 int particion;
 char ruta[0];
};
typedef struct Exec ex;
typedef struct rep reporte;
typedef struct rep * ptreporte;
typedef struct unmount um;
typedef struct unmount *ptrum;
typedef struct mount m;
typedef struct mount *ptrm;
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
    char exe [600] ={};
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
    char  exe [600] = {};
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
    char exe [600]={};
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


void set_name_m(char name [], m**disco){
    strcpy((*disco)->name,name);
}

void set_path_m(char path [], m**disco){
    char exe [600]={};
    if((int)path[0]==(int)'/'){
        strcat(exe,"mike");
    }else{
        strcat(exe,"mike/");
    }
    strcat(exe,path);
    strcpy((*disco)->path,exe);
}

void iniciar_codigos_um(um**disco){
    int i;
    for(i=0;i<50;i++){
        strcpy((*disco)->cadenas[i].representacion_cad,"vacio");
    }
}

int no_tiene_codigos_um(um**disco){
    if(strcmp((*disco)->cadenas[1].representacion_cad,"vacio")==0){
        return 1;
    }
    return 0;
}

void set_name_rep(reporte **r,char name []){
   strcpy((*r)->name,name);
}

void set_path_rep(reporte **r,char path []){
    char exec [600]={};
    if((int)path[0]==(int)'/'){
      strcat(exec,"mike");
    }else{
      strcat(exec,"mike");
    }
    strcat(exec,path);

    strcpy((*r)->path,exec);
}

void set_id_rep(reporte **r,char disco,char particion){
    (*r)->disco =disco;
    (*r)->particion =(int)particion-48;
}

void set_ruta_rep(reporte **r,char ruta []){
    strcpy((*r)->ruta,ruta);
}


void set_path_exec(ex ** disco, char path []){
    strcpy((*disco)->path,path);
}
