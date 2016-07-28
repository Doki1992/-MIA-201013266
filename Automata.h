#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "instrucciones.h"


struct objeto{
    char clave [300];
    char valor[300];
};

typedef struct objeto obj;
obj objetos [15];


static char letras [] = {'a','b','c','d','e','f','g',
                  'h','i','j','k','l','n','m',
                  'o','p','q','r','s','t','u',
                  'v','w','x','y','z',
                  'A','B','C','D','E','F','G',
                  'H','I','J','K','L','N','O',
                  'P','M','Q','R','S','T','U'
                  ,'V','W','X','Y','Z'};

static char * palabras [] = {"mkdisk","rmdisk","fdisk","mount","unmount","-size","exec",
                             "+unit","-path","-id","-type","-fit","-delete","-name","loss",
                             "-add","rep","mkfs","mkfile","cat","rem","edit","ren","-p",
                             "mkdir","cp","mv","find","-cont","-p","-dest","-iddest","recovery"};

static int numeros [] = {'0','1','2','3','4','5','6','7','8','9'};
static char simbolos []= {};
static int ESTADO=0;
static int salto_linea = (int)'\n';
static int comentario = (int)'#';
static int continua = (int)'/';
static int comilla = (int)'\"';
static int espacio_blanco = (int)' ';
static int Esletra(char letra);
static int Esreservada(char * palabra);
static int Esnumero(char numero);
static void minusculas(char *s);
void lexer(char buffer []);
void leer(char buffer[], char *path);
void crear_instruccion(obj ver[]);
void iniciar_obj();
void crear_mkd(obj ver [],int tam);
void crear_mrd(obj ver[], int tam );

void lexer(char buffer [] ){
    int  i =0;
    minusculas(&buffer[0]);
    strcat(buffer,"|");
    iniciar_obj();
    int tamano = strlen(&buffer[0]);
    char dato [100]={};
    int pos_vector =0;
    int pos_obj=0;
    ESTADO=0;
    int flag =0;
    crearlista();
    while(i<tamano){
        switch(ESTADO){
        case 0:
            if((int)(buffer[i])==salto_linea&&flag==0){
                strcpy(objetos[pos_obj++].valor,dato);
                pos_vector=0;
                ESTADO=0;
                limpiar_vector(dato);
                crear_instruccion(objetos);
                if(INSTRUTION_STATE==1){
                    return;
                }
                flag=1;
                pos_obj=0;
                iniciar_obj();
            }else if((int)(buffer[i])==espacio_blanco){
              ESTADO=0;
            }else if(Esletra(buffer[i])==1||Esnumero(buffer[i])){
                dato[pos_vector++]=buffer[i];
                ESTADO=1;
            }else if((int)buffer[i]==comentario){
                //ESTADO =?;
            }else if((int)buffer[i]==(int)'/'){
                ESTADO=0;
            }else if((int)buffer[i]==(int)'.'){
                dato[pos_vector++]=buffer[i];
                ESTADO=1;
            }else if((int)buffer[i]==(int)'-'||(int)buffer[i]==(int)'+'){
                dato[pos_vector++]=buffer[i];
                ESTADO=1;
            }else if((int)buffer[i]==(int)'|'){

            }

            break;
        case 1:
            if((int)(buffer[i])==espacio_blanco){

                if(Esreservada(&dato[0])==1 )
                  {
                    strcpy(objetos[pos_obj++].clave,dato);
                    pos_vector=0;
                    ESTADO=0;
                    limpiar_vector(dato);
                    flag=0;
                  }else{
                    printf("Error ");
                    printf("%s",dato);
                    printf(" no es un comando ");
                    printf("Escriba help para ver una lista de comandos.\n");
                    pos_vector=0;
                    ESTADO=0;
                    limpiar_vector(dato);
                    INSTRUTION_STATE=1;
                    return;
                  }

            }else if(Esletra((buffer[i]))==1||Esnumero(buffer[i])==1){
                dato[pos_vector++]=buffer[i];
            }else if((int)buffer[i]==(int)'\\'){
                //dato[pos_vector++]=buffer[i];
                pos_vector=0;
                ESTADO=0;
            }else if((int)buffer[i]==(int)'.'){
                dato[pos_vector++]=buffer[i];
            }else if((int)buffer[i]==(int)':'){
                if(Esreservada(&dato[0])==1)
                  {
                    strcpy(objetos[pos_obj].clave,dato);
                    pos_vector=0;
                    ESTADO=0;
                    limpiar_vector(dato);
                    ESTADO=2;
                  }else{
                    printf("Error ");
                    printf("%s",dato);
                    printf(" no es un comando ");
                    printf("Escriba help para ver una lista de comandos.\n");
                    pos_vector=0;
                    ESTADO=2;
                    limpiar_vector(dato);
                    INSTRUTION_STATE=1;
                    return;
                  }
            }else if((int)(buffer[i])==salto_linea){
                printf("Error muy pocos argumentos\n");
                INSTRUTION_STATE =1;
                return ;
            }
            break;
        case 2:
            if((int)buffer[i]==(int)':'){
                ESTADO=3;
            }else{
                printf("Error se ha obtenido un caracter inesperado ");
                printf("%c\n",buffer[i]);
                INSTRUTION_STATE=1;
                return;
            }
            break;
        case 3:
            if((int)(buffer[i])==espacio_blanco){
                    strcpy(objetos[pos_obj++].valor,dato);
                    pos_vector=0;
                    ESTADO=0;
                    limpiar_vector(dato);
                    flag=0;
            }else if(Esletra((buffer[i]))==1||Esnumero(buffer[i])==1){
                dato[pos_vector++]=buffer[i];
            }else if((int)buffer[i]==(int)'\\'){
                //dato[pos_vector++]=buffer[i];
                pos_vector=0;
                ESTADO=0;
            }else if((int)buffer[i]==(int)'.'){
                dato[pos_vector++]=buffer[i];
            }else if((int)(buffer[i])==salto_linea){
                strcpy(objetos[pos_obj++].valor,dato);
                pos_vector=0;
                ESTADO=0;
                limpiar_vector(dato);
                crear_instruccion(objetos);
                flag=1;
                pos_obj=0;
                iniciar_obj();
                if(INSTRUTION_STATE==1)
                    return;
            }else if((int)(buffer[i])==comilla){
                ESTADO=4;
            }
            break;

        case 4:
            if((int)(buffer[i])!=comilla){
                dato[pos_vector++]=buffer[i];
            }else{
                ESTADO=3;
            }
            break;
        case 5:

            break;
        }
        i++;
    }

}

static int Esletra(char letra){
    int tamano  = strlen(letras);
    int i =0;
    for(i=0; i<tamano; i++){
        if((int)letras[i]==(int)letra){
            return 1;
        }
    }
    return 0;
}

static int Esnumero(char  numero){
    int tamano = 10;
    int i =0;
    for(i=0; i<tamano; i++){
        if((int)numero==(int)numeros[i]){
            return 1;
        }
    }
    return 0;
}

static void minusculas(char *s)
{
    char com='\"';
    while(*s!='\0')
    {
        if(*s>='A' && *s<='Z')
            if((*s)==com){
                while(*s==com){
                    *s+=(char)32;
                    s++;
                }
            }else{
            *s+=(char)32;
            } if((*s)==com){
            s++;
               while(*s!=com){
                   s++;
               }
        }
        s++;
    }
}

void limpiar_vector(char v []){
  int tamano = strlen(v);
  int i =0;
  for(i=0; i<tamano; i++){
      v[i]='\0';
    }
}

static int Esreservada(char *palabra){
  int tamano = 33;
  int i =0;
  for(;i<tamano; i++){
      if(strcmp(palabra,palabras[i])==0){
          return 1;
        }
    }
  return 0;
}

void leer(char buffer[],char *path){
    FILE *ptrCf;
    char hola[10000];
    if ( ( ptrCf = fopen(path, "r" ) ) == NULL ) {
    printf( "No pudo abrirse el archivo.\n");
    }
    else {
    while (!feof(ptrCf)) {
    fgets(hola,10000,ptrCf);
    strcat(buffer,hola);
    }
    fclose( ptrCf ); /* fclose cierra el archivo */
    }
}

void crear_instruccion(obj ver[]){
    int  i;
    for(i=0;i<15;i++){
        if(strcmp(objetos[i].clave,"vacio")!=0){
            if(strcmp(objetos[i].clave,"mkdisk")==0){
                crear_mkd(ver ,5);
                break;
            }
            if(strcmp(objetos[i].clave,"rmdisk")==0){
                crear_mrd(ver,2);
                break;
            }
            if(strcmp(objetos[i].clave,"fdisk")==0){

            }
        }
    }

}

void crear_mrd(obj ver[], int tam){
    int  i;
    ptrddisk di = (ptrddisk)malloc(sizeof(ddisk));
    strcpy(di->path,"vacio");
    for(i=0;i<tam;i++){
        if(strcmp(ver[i].clave,"-path")==0){
            set_path_delete_disk(ver[i].valor,&di);
        }
    }
    if(strcmp(di->path,"vacio")==0){
        INSTRUTION_STATE=1;
        printf("Muy pocos parametros para instruccion mrdisk (path) son obligatorios\n");
        return ;
    }

    printf("Se ha eliminado el disco ");
    printf("%s\n",di->path);
    insertar(&primero,di,&ultimo,"mr");

}

void crear_mkd(obj ver[], int tam){
    int  i;
    ptrdisk di = (ptrdisk)malloc(sizeof(disk));
    strcpy(di->name,"vacio");
    strcpy(di->path,"vacio");
    di->sise =-1;
    di->unit='v';
    for(i=0;i<tam;i++){
        if(strcmp(ver[i].clave,"-name")==0){
            set_name(ver[i].valor,&di);
        }
        if(strcmp(ver[i].clave,"-path")==0){
            set_path(ver[i].valor,&di);
        }
        if(strcmp(ver[i].clave,"-size")==0){
            set_size(atoi(ver[i].valor),&di);
        }
        if(strcmp(ver[i].clave,"+unit")==0){
           di->unit=ver[i].valor[0];
        }
    }
    set_unit(di->unit,&di);
    if(strcmp(di->name,"vacio")==0||strcmp(di->path,"vacio")==0||di->sise==-1){
        INSTRUTION_STATE=1;
        printf("Muy pocos parametros para instruccion mkdisk (name, path, size) son obligatorios\n");
        return ;
    }
    printf("Se ha acreado el disco ");
    printf("%s\n",di->name);
    insertar(&primero,di,&ultimo,"mk");
}

void iniciar_obj(){
    int  i;
    for(i=0;i<15;i++){
        strcpy(objetos[i].clave,"vacio");
    }
}
