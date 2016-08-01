#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <strings.h>
#define INICIO_MBR 0
#define FIN_MBR 219
#define CURRENT_MBR 220
char *fh();
void crearMBR(int size_disco, char *path);
void crearParticionNormal(char status, char type, char fit, int size, char *name, char *path);
int actualizarMBR(char * nombre_particion, char *path);
int generar_random();
void contarSlash(char path[]);


int totalSlash=0;
struct PARTICION{
        char estado;//esta activa o no
        char tipo;//primario o extendida
        char fit;//best,first,worst
        char name[16];//nombre de la particion
        int start;//bin en q inicia
        int size;//tamaño particion        
};

typedef struct PARTICION*ptrParticion;
typedef struct PARTICION particion;
int buscaSiexiste(ptrParticion p, int seek);

struct MBR{
     int tamano;//tamaño de disco duro
     char fecha[100];//fecha de creacion
     int random;//cualkier numero random
     particion part1;
     particion part2;
     particion part3;
     particion part4;
};
typedef struct MBR*ptrMBR;
typedef struct MBR mbr;

struct EBR{
    char status;
    char fit;
    int start;
    int size;
    int next;
    char name [16];
};

typedef struct EBR ebr;


mbr leerMBR(char path[]);
int espacio_disponible1(mbr m);

char *fh(){
    time_t tiempo = time(0);
    struct tm *tlocal = localtime(&tiempo);
    char output[128];
    strftime(output,128,"%d/%m/%y %H:%M:%S",tlocal);
    printf("%s\n",output);
return  output;
}

void crearMBR(int size_disco,char*path){
    FILE * ptrfile;
    ptrfile = fopen(path,"rb+");
    if(fopen(path,"rb+")){
        fseek(ptrfile,0*sizeof(mbr),SEEK_SET);
        particion p;
        p.estado='0';
        p.fit ='0';
        strcpy(p.name,"vacio");
        p.size=0;
        p.start=0;
        p.tipo='0';
        mbr m;
        m.part1=p;
        m.part2=p;
        m.part3=p;
        m.part4=p;
        m.random=generar_random();
        m.tamano=size_disco;
        //strcpy(m.fecha,c);
        fwrite(&m,sizeof(mbr),1,ptrfile);
        fclose(ptrfile);
    }else{
        printf("no se puede abrir el archivo");
    }
}
//agregar el mètodo acturalizar mbr
mbr leerMBR(char path[]){
    FILE* ptrfile = fopen(path,"rb");
    mbr c ={0,"",0,0,0,0};
    if(ptrfile!=NULL){
        fseek(ptrfile,0,SEEK_SET);
        fread(&c,sizeof(mbr),1,ptrfile);
        fclose(ptrfile);
    }else{
      printf("an error has ocurred");
      printf("\n");
      printf("\n");
      return c;
    }
    return c;
}

int generar_random(){
    int num=0;
    num=rand()%10000;
    return num;
}


int existeParticion(char path [],char name []){
    mbr aux = leerMBR(path);
    if(strcmp(aux.part1.name,name)==0){
        return 1;
    }else if(strcmp(aux.part2.name,name)==0){
        return 1;
    }else if(strcmp(aux.part3.name,name)==0){
        return 1;
    }else if(strcmp(aux.part4.name,name)==0){
        return 1;
    }else{
        return 0;
    }
}


void impimeMBR(char*path){
  FILE* ptrfile;
  ptrfile = fopen(path,"rb");
  mbr c =leerMBR(path);
  if(fopen(path,"rb")){
  if(ptrfile!=NULL){
      fseek(ptrfile,0*sizeof(mbr),SEEK_SET);
      fread(&c,sizeof(mbr),1,ptrfile);
      printf("%-5d%-5d%-5s\n",c.tamano,c.random,c.fecha);
      printf("%-15s%-15s%-15s%-15s%-15s%-15s\n","fit","estado","tipo","name","tamaño","inicia");
      printf("%-15c%-15c%-15c%-15s%-15d%-15d\n",c.part1.fit,c.part1.estado,c.part1.tipo,c.part1.name,c.part1.size,c.part1.start);
      printf("%-15c%-15c%-15c%-15s%-15d%-15d\n",c.part2.fit,c.part2.estado,c.part2.tipo,c.part2.name,c.part2.size,c.part2.start);
      printf("%-15c%-15c%-15c%-15s%-15d%-15d\n",c.part3.fit,c.part3.estado,c.part3.tipo,c.part3.name,c.part3.size,c.part3.start);
      printf("%-15c%-15c%-15c%-15s%-15d%-15d\n",c.part4.fit,c.part4.estado,c.part4.tipo,c.part4.name,c.part4.size,c.part4.start);
  }

  fclose(ptrfile);
  }else{
       printf("no se puede abri ese disco, no existe\n");
  }
}


//Cantidad de Particiones Primarias =cpp
int cpp=0;
//Cantidad de Particiones Extendidas =cpe
int cpe=0;
//si se crear una particion extendida se guarda su tamaño aqui
int tamano_extendida=0;
//se guarda el tamaño total de todas las particiones logicas
int tamano_logicas=0;
//guarda el seek actual para la ebr
int seek_ebr=0;

int actualizarMBR(char * nombre_particion,char*path){
mbr mbr_1 = leerMBR(path);
char  constante [120];
char  constante1 [120];
char  constante2 [120];
char  constante3 [120];
strcpy(constante,mbr_1.part1.name);
strcpy(constante1,mbr_1.part2.name);
strcpy(constante2,mbr_1.part3.name);
strcpy(constante3,mbr_1.part4.name);
if(strcmp(constante,nombre_particion)==0){
    mbr_1.part1.estado='0';
    mbr_1.part1.fit ='0';
    strcpy(mbr_1.part1.name,"vacio");
    mbr_1.part1.start=0;
    mbr_1.part1.tipo='0';
    mbr_1.part1.size=0;
    FILE * ptrfile;
    ptrfile = fopen(path,"rb+");
    if(ptrfile!=NULL){
        fseek(ptrfile,0*sizeof(mbr),SEEK_SET);
        fwrite(&mbr_1,sizeof(mbr),1,ptrfile);
        fclose(ptrfile);
    }
    return 1;
}else if(strcmp(constante1,nombre_particion)==0){
    mbr_1.part2.estado='0';
    mbr_1.part2.fit ='0';
    strcpy(mbr_1.part2.name,"vacio");
    mbr_1.part2.start=0;
    mbr_1.part2.tipo='0';
    mbr_1.part2.size=0;
    FILE * ptrfile;
    ptrfile = fopen(path,"rb+");
    if(ptrfile!=NULL){
        fseek(ptrfile,0*sizeof(mbr),SEEK_SET);
        fwrite(&mbr_1,sizeof(mbr),1,ptrfile);
        fclose(ptrfile);
    }
    return 1;
}else if(strcmp(constante2,nombre_particion)==0){
    mbr_1.part3.estado='0';
    mbr_1.part3.fit ='0';
    strcpy(mbr_1.part3.name,"vacio");
    mbr_1.part3.start=0;
    mbr_1.part3.tipo='0';
    mbr_1.part3.size=0;
    FILE * ptrfile;
    ptrfile = fopen(path,"rb+");
    if(ptrfile!=NULL){
        fseek(ptrfile,0*sizeof(mbr),SEEK_SET);
        fwrite(&mbr_1,sizeof(mbr),1,ptrfile);
        fclose(ptrfile);
    }
    return 1;
}else if(strcmp(constante3,nombre_particion)==0){
    mbr_1.part4.estado='0';
    mbr_1.part4.fit ='0';
    strcpy(mbr_1.part4.name,"vacio");
    mbr_1.part4.start=0;
    mbr_1.part4.tipo='0';
    mbr_1.part4.size=0;
    FILE * ptrfile;
    ptrfile = fopen(path,"rb+");
    if(ptrfile!=NULL){
        fseek(ptrfile,0*sizeof(mbr),SEEK_SET);
        fwrite(&mbr_1,sizeof(mbr),1,ptrfile);
        fclose(ptrfile);
    }
    return 1;
}
int c =0;
cpp--;
return 0;
}

void crearParticionNormal(char status, char type, char fit  , int size,char * name,char*path){
    mbr m = leerMBR(path);
    cpp=cpe=0;
    obtener_numero_particiones(&cpp,&cpe,m);
    FILE * ptrfile;
    ptrfile = fopen(path,"rb+");
    if(fopen(path,"rb+")){
    if(ptrfile!=NULL&&((cpe==1&&cpp<=3&&(int)type!=(int)'e')||(cpe==0&&cpp<=4))){
        fseek(ptrfile,0*sizeof(mbr),SEEK_SET);
        int espacio_disponible=espacio_disponible1(m);
        if(size<=espacio_disponible){
       //     if((strcmp(m.part1.name,name)==0)||(strcmp(m.part2.name,name)==0)||(strcmp(m.part3.name,name)==0)||(strcmp(m.part4.name,name)==0)){//agregado x mi
            if((int)m.part1.estado!=(int)'1'&&verificaAgujero(size,m.part1.size)==1){
                m.part1.estado=status;
                m.part1.fit=fit;
                strcpy(m.part1.name,name);
                m.part1.size=size;
                m.part1.start=sizeof(mbr);
                m.part1.tipo=type;
                if((int)type==(int)'e'){
                    creaEBR(path,m.part1.start);
                    tamano_extendida=size;
                    obtener_tamano_extendida(m,&tamano_extendida);
                  }

              }else if((int)m.part2.estado!=(int)'1'&&verificaAgujero(size,m.part2.size)==1){
                m.part2.estado=status;
                m.part2.fit=fit;
                strcpy(m.part2.name,name);
                m.part2.size=size;
                m.part2.start=sizeof(mbr)+m.part1.size;
                m.part2.tipo=type;
                if((int)type==(int)'e'){
                    creaEBR(path,m.part2.start);
                    tamano_extendida=size;
                    obtener_tamano_extendida(m,&tamano_extendida);
                  }
              }else if((int)m.part3.estado!=(int)'1'&&verificaAgujero(size,m.part3.size)==1){
                m.part3.estado=status;
                m.part3.fit=fit;
                strcpy(m.part3.name,name);
                m.part3.size=size;
                m.part3.start=sizeof(mbr)+m.part1.size+m.part2.size;
                m.part3.tipo=type;
                if((int)type==(int)'e'){
                    creaEBR(path,m.part3.start);
                    tamano_extendida=size;
                    obtener_tamano_extendida(m,&tamano_extendida);
                  }
              }else if((int)m.part4.estado!=(int)'1'&&verificaAgujero(size,m.part4.size)==1){
                m.part4.estado=status;
                m.part4.fit=fit;
                strcpy(m.part4.name,name);
                m.part4.size=size;
                m.part4.start=sizeof(mbr)+m.part1.size+m.part2.size+m.part3.size;
                m.part4.tipo=type;
                if((int)type==(int)'e'){
                    creaEBR(path,m.part4.start);
                    tamano_extendida=size;
                    obtener_tamano_extendida(m,&tamano_extendida);
                  }
              }else{
                printf("error, the size is bigger than the free space in the disc\n");
              }
        //  }else{//agregado x mi
          //        printf("error, el nombre ya es usado por otra particion\n");//agregado x mi
          // }//agregado x mi
          }else{
            printf("ERROR EL TAMAÑO DE LA PARTICION A CREAR ES MENOR QUE EL ESPACIO LIBRE EN EL DISCO\n");
            printf("EL ESPACIO LIBRE EN EL DISCO ES: ");
            printf("%d",espacio_disponible);
            printf(" Y EL TAMAÑO DE LA PARTICION HA CREAR ES DE: ");
            printf("%d",size);

          }

    }else{
        printf("ERROR NO PUEDEN EXISTIR MAS DE UNA PARTICION EXTENDIDA EN EL MISMO DISCO\n");
    }

    fwrite(&m,sizeof(mbr),1,ptrfile);
    fclose(ptrfile);
    }else{
         printf("no hay disco con esa direcicon y nombre\n\n");
    }
}

int espacio_disponible1(mbr m){
  int espacio=m.tamano-220;
  if((int)m.part1.estado==(int)'1'){
      espacio-=m.part1.size;
    }if((int)m.part2.estado==(int)'1'){
      espacio-=m.part2.size;
    }if((int)m.part3.estado==(int)'1'){
      espacio-=m.part3.size;
    }if((int)m.part4.estado==(int)'1'){
      espacio-=m.part4.size;
    }
  return espacio;
}

void obtener_numero_particiones(int *cpp, int *cpe,mbr m){
    if((int)m.part1.tipo==(int)'e'){
        (*cpe)++;
      } else if((int)m.part1.tipo==(int)'p'){
        (*cpp)++;
      }
    if((int)m.part2.tipo==(int)'e'){
        (*cpe)++;
      } else if((int)m.part2.tipo==(int)'p'){
        (*cpp)++;
      }
    if((int)m.part3.tipo==(int)'e'){
        (*cpe)++;
      }else if((int)m.part3.tipo==(int)'p'){
        (*cpp)++;
      }
    if((int)m.part4.tipo==(int)'e'){
        (*cpe)++;
      }else if((int)m.part4.tipo==(int)'p'){
        (*cpp)++;
      }
}

void obtener_tamano_extendida(mbr m,int *te){
    if((int)m.part1.tipo==(int)'e'){
        (*te)=m.part1.size;
      }
    if((int)m.part2.tipo==(int)'e'){
        (*te)=m.part2.size;;
      }
    if((int)m.part3.tipo==(int)'e'){
        (*te)=m.part3.size;;
      }
    if((int)m.part4.tipo==(int)'e'){
        (*te)==m.part4.size;;
      }
}

void fijar_puntero_ebr(mbr m,int *seek_eb,char path []){
    if((int)m.part1.tipo==(int)'e'){
        (*seek_eb)=m.part1.start;
      }else
    if((int)m.part2.tipo==(int)'e'){
       (*seek_eb)=m.part2.start;
      }else
    if((int)m.part3.tipo==(int)'e'){
        (*seek_eb)=m.part3.start;
      }else
    if((int)m.part4.tipo==(int)'e'){
        (*seek_eb)=m.part4.start;
      }else{
        (*seek_eb)=0;
      }

}

int verificaAgujero(int size, int size_disponible){
  if(size_disponible==0){
      return 1;
    }else if(size<=size_disponible){
      return 1;
    }else{
      return 0;
    }

}


int obtener_apuntador_asiguiente(char path []){
    ebr primera;
    FILE * ptrfile;
    int p=0;
    ptrfile = fopen(path,"rb");
    if(ptrfile!=NULL){
        int next =0;
        seek_ebr=0;
        cpe=0;
        cpp=0;
        obtener_numero_particiones(&cpp,&cpe,leerMBR(path));
        fijar_puntero_ebr(leerMBR(path),&seek_ebr,path);
        if(cpe!=0)
        while(next!=-1){
            fseek(ptrfile,seek_ebr,SEEK_SET);
            fread(&primera,sizeof(ebr),1,ptrfile);
            next = primera.next;
            seek_ebr=primera.start+32+primera.size;
            p=seek_ebr;
          }
        fclose(ptrfile);
      }
    return p;
}

int factor_de_cambio_EBR(char path []){
  ebr primera;
  FILE * ptrfile;
  int p=0;
  ptrfile = fopen(path,"rb");
  if(ptrfile!=NULL){
      int next =0;
      seek_ebr=0;
      cpp=0;
      cpe=0;
      obtener_numero_particiones(&cpp,&cpe,leerMBR(path));
      fijar_puntero_ebr(leerMBR(path),&seek_ebr,path);
      if(cpe!=0)
      while(next!=-1){
          fseek(ptrfile,seek_ebr,SEEK_SET);
          fread(&primera,sizeof(ebr),1,ptrfile);
          next = primera.next;
          seek_ebr=primera.start+32+primera.size;
          if((int)primera.status!=(int)'0')
          p++;
        }
      fclose(ptrfile);
    }
  return p;
}

ebr obtenerAnterior(char path [],int size){
  ebr primera;
  FILE * ptrfile;
  int p=0;
  ptrfile = fopen(path,"rb");
  if(ptrfile!=NULL){
      int next =0;
      seek_ebr=0;
      fijar_puntero_ebr(leerMBR(path),&seek_ebr,path);
      while(next!=-1){
          fseek(ptrfile,seek_ebr,SEEK_SET);
          fread(&primera,sizeof(ebr),1,ptrfile);
          next = primera.next;
          seek_ebr=primera.start+primera.size+32;
          p++;
          if((int)primera.status==(int)'0'&&size<=primera.size){
              if(size<primera.size){
                correrEBR(path,seek_ebr-primera.size-32,primera.size-size);
              }

              if(primera.next!=-1){
                 primera.next=primera.next-(primera.size-size);
              }
              break;
            }

        }
      fclose(ptrfile);
    }
  return primera;
}

ebr  aux [100]={};

void correrEBR(char path [],int seek_eb,int tamano){
  ebr primera;
  FILE * ptrfile;
  int p=0;
  ptrfile = fopen(path,"rb");
  if(ptrfile!=NULL){
      int next =0;
      int seek=seek_eb;
      while(next!=-1){
          int pp =(next==0)?seek:next;
          fseek(ptrfile,pp,SEEK_SET);
          fread(&primera,sizeof(ebr),1,ptrfile);
          next=primera.next;
          if(primera.next!=-1&&seek_eb!=seek){
              primera.next-=tamano;
              primera.start-=tamano;
            }
          if(primera.next!=-1&&seek_eb==seek){
              primera.next-=tamano;
            }
          seek_eb=primera.start+primera.size+32;
          aux[p]=primera;
          p++;
        }
      escribe(path,seek,aux ,p);
      fclose(ptrfile);
    }
}

void escribe(char path [], int seek,ebr primera [],int t_pr){
  FILE * ptrfile;
  ptrfile=fopen(path,"rb+");
  if(ptrfile!=NULL){
      int i;
      for( i=0; i<t_pr;i++){
          fseek(ptrfile,seek,SEEK_SET);
          fwrite(&primera[i],sizeof(ebr),1,ptrfile);
          seek=primera[i].next;
        }
      fclose(ptrfile);
    }
}

ebr buscar_ebr(char path [],char name []){
  ebr primera={};
  ebr segunda={};
  strcpy(primera.name,"vacio");
  strcpy(segunda.name,"vacio");
  FILE * ptrfile;
  ptrfile = fopen(path,"rb");
  if(ptrfile!=NULL){
      int next =0;
      seek_ebr=0;
      fijar_puntero_ebr(leerMBR(path),&seek_ebr,path);
      if(seek_ebr!=0)
      while(next!=-1){
          fseek(ptrfile,seek_ebr,SEEK_SET);
          fread(&primera,sizeof(ebr),1,ptrfile);
          next = primera.next;
          seek_ebr=primera.start+primera.size+32;
          if(strcmp(primera.name,name)==0){
              return primera;
            }
        }
      fclose(ptrfile);
    }
  return segunda;
}



void eliminar_ebr(char path[],char name []){
  ebr partcion_a_eliminar = buscar_ebr(path,name);
  FILE * ptrfile ;
  ptrfile= fopen(path,"rb+");
  if(ptrfile!=NULL){
      fseek(ptrfile,partcion_a_eliminar.start,SEEK_SET);
      partcion_a_eliminar.fit='0';
      strcpy(partcion_a_eliminar.name,"");
      partcion_a_eliminar.status='0';
      fwrite(&partcion_a_eliminar,sizeof(ebr),1,ptrfile);
      fclose(ptrfile);
    }else{
      printf("Error desde el metodo con nombre: void elminar_ebr(char path[],char name[]),linea: 440\n");
    }
}

void imprimir_ebr(char path []){
  ebr primera;
  FILE * ptrfile;
  ptrfile = fopen(path,"rb");
  if(ptrfile!=NULL){
      int next =0;
      seek_ebr=0;
      fijar_puntero_ebr(leerMBR(path),&seek_ebr,path);
      printf("%-15s%-15s%-15s%-15s%-15s%-15s\n","fit","nombre","siguiente","tamano","inicio","estatus");
      if(seek_ebr!=0)
      while(next!=-1){
          fseek(ptrfile,seek_ebr,SEEK_SET);
          fread(&primera,sizeof(ebr),1,ptrfile);
          next = primera.next;
          seek_ebr=primera.start+primera.size+32;
          printf("%-15c%-15s%-15d%-15d%-15d%-15c\n",primera.fit,primera.name,primera.next,primera.size,primera.start,primera.status);
        }
      fclose(ptrfile);
    }

}

//siguiente
ebr NewEbr(char status,char fit,int start,int size,int next,char name[]){
  ebr aux;
  aux.fit=fit;
  strcpy(aux.name,name);
  aux.next=-1;
  aux.size=size;
  aux.start=start;
  aux.status=status;
  return aux;
}

void copiarEBR(ebr *copia, ebr *original){
  (*copia).fit=(*original).fit;
  strcpy((*copia).name,(*original).name);
  (*copia).size=(*original).size;
  (*copia).status=(*original).status;
}

int obtenerTamanoLogicas(char path []){
  ebr primera;
  FILE * ptrfile;
  int tamano = 0;
  ptrfile = fopen(path,"rb");
  if(ptrfile!=NULL){
      int next =0;
      seek_ebr=0;
      cpe=0;
      cpp=0;
      obtener_numero_particiones(&cpp,&cpe,leerMBR(path));
      fijar_puntero_ebr(leerMBR(path),&seek_ebr,path);
      if(cpe!=0)
      while(next!=-1){
          fseek(ptrfile,seek_ebr,SEEK_SET);
          fread(&primera,sizeof(ebr),1,ptrfile);
          next = primera.next;
          seek_ebr=primera.start+primera.size+32;
          if((int)primera.status!=(int)'0'){
              tamano+=primera.size;
            }
        }
      fclose(ptrfile);
    }
  return tamano;
}

void crearParticonEBR(char status, char fit, int start, int size, int next, char name [], char path[]){
  //existe particion extendida 1 no 0
  int tam_ex;
  obtener_tamano_extendida(leerMBR(path),&tam_ex);
  int disponible = tam_ex-obtenerTamanoLogicas(path)-32*factor_de_cambio_EBR(path);
  FILE * ptrfile;
  ptrfile= fopen(path,"rb+");
  cpp=cpe=0;
  obtener_numero_particiones(&cpp,&cpe,leerMBR(path));
  if(cpe==1){
      //buscar la siguiente poscion libre para insertar ebr
      //verificar el tamaño disponible
      if(size+32<= disponible){
          if(ptrfile!=NULL){
              ebr nueva = NewEbr(status,fit,start,size,next,name);
              ebr anterior= obtenerAnterior(path,size);
              if((int)anterior.status==(int)'0'){
                  copiarEBR(&anterior,&nueva);
                  fseek(ptrfile,anterior.start,SEEK_SET);
                  fwrite(&anterior,sizeof(ebr),1,ptrfile);
                }else if((int)anterior.status==(int)'1'){
                  anterior.next=obtener_apuntador_asiguiente(path);
                  fseek(ptrfile,anterior.next-32-anterior.size,SEEK_SET);
                  fwrite(&anterior,sizeof(ebr),1,ptrfile);
                  fseek(ptrfile,anterior.next,SEEK_SET);
                  fwrite(&nueva,sizeof(ebr),1,ptrfile);
                }else{
                  printf("Error estatus no reconocido\n");
                }
              fclose(ptrfile);
            }else{
              printf("El archivo no existe\n");
            }
        }else{
          printf("NO HAY ESPACIO SUFICIENTE PARA CREAR LA PARTICION LOGICA EN ESTA PARTCION EXTENDIDA\n");
        }
    }else{
      printf("Aun no ha sido creada una particion extendia\n");
    }

}



void creaEBR(char path[], int start){
  mbr b=leerMBR(path);
  ebr primera;
  primera.fit='b';
  strcpy(primera.name,"vacio");
  primera.next=-1;
  primera.size=0;
  primera.start=start;
  primera.status='0';
  FILE * ptrfile1=(FILE*)malloc(sizeof(FILE));
  ptrfile1 = fopen(path,"rb+");
  if(ptrfile1!=NULL){
      //antes verificar si hay espacio disponible en la particion extendida para
      //insertar la logica
      fseek(ptrfile1,start,SEEK_SET);
      fwrite(&primera,sizeof(ebr),1,ptrfile1);
      fclose(ptrfile1);
    }

}

void contarSlash(char path[]){
    char*auxT=path;
    char slash='/';
    totalSlash=0;
    while((*auxT)!='\0'){
        if((*auxT)==slash){
            totalSlash++;
        }
        auxT++;
    }

}
int existe_punto(char palabra[]){
    char*auxT=palabra;
    char punto='.';
    totalSlash=0;
    while((*auxT)!='\0'){
        if((*auxT)==punto){
           return 1;
        }
        auxT++;
    }
    return 0;

}
#endif // ESTRUCTURAS_H
