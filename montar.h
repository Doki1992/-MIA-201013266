#ifndef MONTAR_H
#define MONTAR_H
#include "estructuras.h"
struct Montar{
   particion p;
   struct Montar * sig;
   char Disco;
   int part;

};

struct datos{
  int cuenta;
  char * path;
  char * name_part[51];
};



typedef struct datos dato;

typedef struct Montar * ptrmontar;
typedef struct Montar montar;
static char letrasID [] = {'a','b','c','d','e','f','g',
                  'h','i','j','k','l','n','m',
                  'o','p','q','r','s','t','u',
                  'v','w','x','y','z',
                  'A','B','C','D','E','F','G',
                  'H','I','J','K','L','N','O',
                  'P','M','Q','R','S','T','U'
                  ,'V','W','X','Y','Z'};

static int numerosID [30]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29};
static char * discos [51];
 dato  d[51]={};
static int discos_iniciados =0;
static int particiones_iniciadas=0;
int ya_esta_montada(char name[]);

void iniciarDiscos(){
  discos_iniciados=1;
  int i ;
  for(i=0;i<51;i++){
      discos[i]="vacio";
      d[i].path="libre";
    }
}

void iniciarPartiones(){
  int i ;
  int j;
  for(i=0;i<51;i++){
      for(j=0;j<51;j++){
          d[i].name_part[j]="vacio";
        }
    }
  particiones_iniciadas=1;
}

int ya_esta_montada(char name []){
    int si=0;
    int i ;
    int j;
    for(i=0; i<51;i++){
        for (j = 0;  i< 51; i++) {
            char bueno [20];
            strcpy(bueno,d[i].name_part[j]);
            if(strcmp(d[i].name_part[j],name)==0){
                printf("La particon con nombre: ");
                printf(name);
                printf(" ya esta montada\n");
                si=1;
                break;
            }
        }
    }
    return si;
}

void asignarDisco(char path [],int *pos){
    int i =0;
    for(;i<51;i++){
        if(strcmp(discos[i],path)==0||strcmp(discos[i],"vacio")==0){
            (*pos)=i;
            discos[i]=&path[0];
            d[i].path=&path[0];
            break;
          }
      }
}

int obtener_pos_disco(char part_name []){
  int i;
  int pos=-1;
  int contrado = 0;
  for(i=0;i<51;i++){
      if(strcmp(d[i].path,part_name)==0){
          pos=i;
          contrado=1;
          break;
        }
    }
  return pos;
}

int obtener_pos_part(char name [],char path []){
  int i,j,pos=-1;
  int encontrado=0;
  for(i=0;i<51;i++){
      if(strcmp(path,d[i].path)==0)
      for(j=0;j<51;j++){
          if(strcmp(d[i].name_part[j],name)==0){
              encontrado=1;
              pos=j;
              break;
            }
        }
      if(encontrado==1){
          break;
        }
    }
  return j;
}

void asignarId(char path [],int *pos,char name_part[]){
    int i =0;
    int pd = obtener_pos_disco(path);
    for(;i<51;i++){
        if(strcmp(d[pd].name_part[i],"vacio")==0){
            (*pos)=i;
            d[pd].name_part[i]=&name_part[0];
            d[pd].cuenta++;break;
          }
      }
}


void Montar_disco(ptrmontar * cabeza,char path [],char name_particion []){
    ptrmontar nuevo = (ptrmontar)malloc(sizeof(montar));
    if(discos_iniciados==0&&particiones_iniciadas==0){
        iniciarDiscos();
        iniciarPartiones();
      }
    if(nuevo!=NULL){
       if(ya_esta_montada(name_particion)==0){
           int existe = iniciarNuevo(path,&nuevo,name_particion);
           if(existe==1){
               nuevo->sig=(*cabeza);
              (*cabeza)=nuevo;
             }
       }
    }
}


void Desmontar_particion(ptrmontar *cabeza, char name_particion [],char path []){
  ptrmontar actual;
  ptrmontar anterior;
  actual = *cabeza;
  anterior=NULL;
  int cuenta=obtener_pos_disco(path);
  int encontrado=-1;
  while((actual!=NULL)&&(encontrado!=0)){
      encontrado = strcmp(name_particion,actual->p.name);
      if(encontrado!=0){
          anterior=actual;
          actual=actual->sig;
        }
    }
  if(actual!=NULL){
      if(cuenta!=-1){
          d[cuenta].cuenta--;
          if(d[cuenta].cuenta==0){
              d[cuenta].cuenta=0;
              d[cuenta].path="";
              discos[cuenta]="vacio";
            }
          int ppp=obtener_pos_part(name_particion,path);
          if(ppp!=-1)
          d[cuenta].name_part[ppp]="vacio";
        }
      if(actual==*cabeza){
          *cabeza=actual->sig;
        }else{
          anterior->sig=actual->sig;
        }
      free(actual);
      actual=NULL;
    }
}

int iniciarNuevo(char path [],ptrmontar *nuevo,char name_particion []){
    particion p;
    int existe =fijar_particion(path,&p,name_particion);
    if(existe==1){
        int disco=0;
        int part=0;
        asignarDisco(path,&disco);
        asignarId(path,&part,name_particion);
        (*nuevo)->Disco=letrasID[disco];
        (*nuevo)->part=numerosID[part];
        (*nuevo)->p=p;
      }else{
        printf("ERROR no existe la particion en el Disco\n\n");
      }
    return existe;
}

int fijar_particion(char path [],ptrParticion p_montar,char name_partcion []){
    FILE * ptrfile;
    mbr m;
    ptrfile = fopen(path,"rb");
    int existe=0;
    if(ptrfile!=NULL){
        fseek(ptrfile,0,SEEK_SET);
        fread(&m,sizeof(mbr),1,ptrfile);
        if(strcmp(m.part1.name,name_partcion)==0){
            (*p_montar).estado=m.part1.estado;
            (*p_montar).fit=m.part1.fit;
            strcpy((*p_montar).name,m.part1.name);
            (*p_montar).size=m.part1.size;
            (*p_montar).start=m.part1.start;
            (*p_montar).tipo=m.part1.tipo;
            existe=1;
        }else if(strcmp(m.part2.name,name_partcion)==0){
            (*p_montar).estado=m.part2.estado;
            (*p_montar).fit=m.part2.fit;
            strcpy((*p_montar).name,m.part2.name);
            (*p_montar).size=m.part2.size;
            (*p_montar).start=m.part2.start;
            (*p_montar).tipo=m.part2.tipo;
            existe=1;
        }else if(strcmp(m.part3.name,name_partcion)==0){
            (*p_montar).estado=m.part3.estado;
            (*p_montar).fit=m.part3.fit;
            strcpy((*p_montar).name,m.part3.name);
            (*p_montar).size=m.part3.size;
            (*p_montar).start=m.part3.start;
            (*p_montar).tipo=m.part3.tipo;
            existe=1;
        }else if(strcmp(m.part4.name,name_partcion)==0){
            (*p_montar).estado=m.part4.estado;
            (*p_montar).fit=m.part4.fit;
            strcpy((*p_montar).name,m.part4.name);
            (*p_montar).size=m.part4.size;
            (*p_montar).start=m.part4.start;
            (*p_montar).tipo=m.part4.tipo;
            existe=1;
        }else{
            ebr aux = buscar_ebr(path,name_partcion);
            if(strcmp(aux.name,"vacio")!=0){
                (*p_montar).estado=aux.status;
                (*p_montar).fit=aux.fit;
                strcpy((*p_montar).name,aux.name);
                (*p_montar).size=aux.size;
                (*p_montar).start=aux.start;
                (*p_montar).tipo='l';
                existe=1;
            }
        }
        fclose(ptrfile);
    }else{
        printf("no existe el disco");
    }
    return existe;
}

void ver_particiones_montadas(ptrmontar cabeza){
  ptrmontar aux = cabeza;
   printf("%-25s%-25s%-25s\n","nombre de particion","codigo disco","codigo particion");
  while(aux!=NULL){
      printf("%-25s%-25c%-25d\n",aux->p.name,aux->Disco,aux->part);
      aux=aux->sig;
    }
}

char * obtener_nombre_particion(ptrmontar cabeza,char disco,int particion){
  ptrmontar aux =cabeza;
  d;
  char * aux1="xc";
  int band=0;
  while(aux!=NULL){
      if(((int)aux->Disco==(int)disco)&&(aux->part==particion)){
          aux1=aux->p.name;
          band=1;
          break;
        }
      aux = aux->sig;
    }
  if(band==0){

  }
  return aux1;
}

char *obtener_path(ptrmontar cabeza,char disco, int particion){
  char  aux1 [100]="";
  char  *aux2=calloc(30,sizeof(char));
  int encontrado =0;
  strcpy(aux1,obtener_nombre_particion(cabeza,disco,particion));
  if(discos_iniciados==1&&particiones_iniciadas==1){
      int i,j;

      for(i=0;i<51;i++){

          for(j=0;j<4;j++){
             if(strcmp(d[i].name_part[j],aux1)==0) {
                encontrado=1;
                aux2=d[i].path;
                break;
               }
            }
          if(encontrado==1){
            break;
          }else{
              strcpy(aux2,("noencontrado"));
          }
        }
    }

  return aux2;
}


#endif // MONTAR_H
