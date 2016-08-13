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
void reportes(reporte *disco);
void reporteMbr(char path[], char disco, int partcion);
void reporteEbr(char comando[],char disco, int particion);
void reporteDisco(char path[], char disco, int particion);
void reporteDiscoEbr(char comando[],char disco, int particion);
void ejecu_e(ex *di);
void ejecutar();
void ejecutar1();
struct cadenas{
    char cadena[30];
};
typedef struct cadenas cade;


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
        }else if(strcmp(primero->tipo,"r")==0){
            reportes(primero->rr);
        }else if((strcmp(primero->tipo,"ex")==0)){
            ejecu_e(primero->ee);
        }
        eliminar_instruccion();
    }

}



void ejecutar1(){
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
        }else if(strcmp(primero->tipo,"r")==0){
            reportes(primero->rr);
        }else if((strcmp(primero->tipo,"ex")==0)){
            ejecu_e(primero->ee);
        }
        eliminar_instruccion();
    }

}
void ejecu_e(ex *di){
    char buffer[60000]={};
    leer(buffer,di->path);
    lexer1(buffer);
    ejecutar1();
}

void reportes (reporte *disco){
    if(strcmp(disco->name,"Mbr")==0||strcmp(disco->name,"\"Mbr\"")==0){
       reporteMbr(disco->path,disco->disco,disco->particion);
    }else if(strcmp(disco->name,"disk")==0||strcmp(disco->name,"\"disk\"")==0){
       reporteDisco(disco->path,disco->disco,disco->particion);
    }
}


void reporteDisco(char path[], char disco, int particion){
    char contenidodot [60000]={};
    char aux [500] ={};
    strcpy(aux,obtener_path(cabeza,disco,particion));
    mbr m = leerMBR(obtener_path(cabeza,disco,particion));
    cade vec [10] = {};
    char name_disco [400]={} ;
    strcat(name_disco,obtener_nombre_particion(cabeza,disco,particion)) ;
    int inicio=0;
    split(vec,path,&inicio);
    char nuevopath [400]={};
    char nombre [200] = {};
    char path_aux[500]={};
    int i;
    char exec [500]={};
    strcat(nuevopath,"\"");
    char tamano [30];
    for(i=0;i<inicio-1;i++){
        strcat(nuevopath,vec[i].cadena);
        strcat(nuevopath,"/");
    }
    strcpy(path_aux,nuevopath);
    strcat(nuevopath,"\"");
    strcat(exec,"mkdir -p ");
    strcat(exec,nuevopath);
    strcat(nuevopath,"\"");
    system(exec);
    strcpy(nombre,vec[inicio-1].cadena);
    strcat(contenidodot,"digraph uno { ");
    strcat(contenidodot,"nodo1") ;
    strcat(contenidodot,"[label = \"") ;
    strcat(contenidodot,"{");
    strcat(contenidodot,obtener_path(cabeza,disco,particion));
    strcat(contenidodot,"|");
    strcat(contenidodot,"{MBR |");
    if(m.part1.estado=='1'){
        if(m.part1.tipo=='p')
            strcat(contenidodot,"Primaria");
        else{
            strcat(contenidodot,"{Extendida | {");
            reporteDiscoEbr(contenidodot,disco,particion);

            strcat(contenidodot,"}");
        }

    }else if(m.part1.estado=='0'){
        strcat(contenidodot,"| Libre");
    }
    if(m.part2.estado=='1'){
        if(m.part2.tipo=='p')
            strcat(contenidodot,"| Primaria");
        else{
            strcat(contenidodot,"| {Extendida | {");
            reporteDiscoEbr(contenidodot,disco,particion);

            strcat(contenidodot,"}");
        }

    }else if(m.part2.estado=='0'){
        strcat(contenidodot,"| Libre");
    }
    if(m.part3.estado=='1'){
        if(m.part3.tipo=='p')
            strcat(contenidodot,"| Primaria");
        else{
            strcat(contenidodot,"| {Extendida |{");
            reporteDiscoEbr(contenidodot,disco,particion);

            strcat(contenidodot,"}");
        }

    }else if(m.part3.estado=='0'){
        strcat(contenidodot,"| Libre");
        reporteDiscoEbr(contenidodot,disco,particion);

        strcat(contenidodot,"}");
    }
    if(m.part4.estado=='1'){
        if(m.part4.tipo=='p')
            strcat(contenidodot,"| Primaria");
        else{
            strcat(contenidodot,"| {Extendida |{");
            reporteDiscoEbr(contenidodot,disco,particion);
            strcat(contenidodot,"}");
        }

    }else if(m.part4.estado=='0'){
        strcat(contenidodot,"| Libre");
    }
    strcat(contenidodot,"}");
    strcat(contenidodot,"}");
    strcat(contenidodot,"\"");
    strcat(contenidodot," shape=\"record\"];");
    strcat(contenidodot,"}");
    FILE *file =fopen("dot.txt","w");
    fprintf(file,contenidodot);
    fclose(file);
    char exe1 [1000]={};
    strcat(path_aux,nombre);
    strcat(exe1,"dot -Tjpg dot.txt -o ");
    strcat(path_aux,"\"");
    strcat(exe1,path_aux);
    system(exe1);
    char exe2 [1000]={};

    strcat(exe2,"gnome-open ");
    strcat(exe2,path_aux);
    system(exe2);

}


void reporteDiscoEbr(char comando[], char disco, int particion){
    int seek_ebr;
    fijar_puntero_ebr(leerMBR(obtener_path(cabeza,disco,particion)),&seek_ebr,"");
    if(seek_ebr!=0){
       int next =0;
       ebr primera ;
       FILE * ptrfile;
       char path [400];
       strcpy(path,obtener_path(cabeza,disco,particion));
       ptrfile = fopen(path,"rb");
       char l [30];
       while(next!=-1){
           fseek(ptrfile,seek_ebr,SEEK_SET);
           fread(&primera,sizeof(ebr),1,ptrfile);
           next = primera.next;
           seek_ebr=primera.start+primera.size+32;
           strcat(comando,"EBR |");
           if(primera.status=='1'){
               if(next!=-1){
                   strcat(comando,"Logica |");
               }else{
                   strcat(comando,"Logica ");
               }
           }else{
               if(next!=-1){
                   strcat(comando,"Libre |");
               }else{
                   strcat(comando,"Libre ");
               }
           }
       }
       strcat(comando,"}");
    }

}

void desmontar(ptrum disco){
    int i;
    for(i=0;i<disco->hasta_donde;i++){
        int numero = (int)disco->cadenas[i].representacion_cad[1]-48;
        char diss = disco->cadenas[i].representacion_cad[0];
        char path [400];
        char name [400];
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

}

void creaDisco(ptrdisk di){
    printf("Creando disco con nombre: ");
    printf(di->name);
    printf("....\n");
    char exe [500]={};
    char size_m [500]={};
    char exe1[500]={};
    strcat(exe1,"mkdir -p ");
    strcat(exe1,"\"");
    strcat(exe1,di->path);
    strcat(exe1,"\"");
    system(exe1);
    strcpy(size_m,itoa(di->sise,size_m));
    strcat(exe,"dd if=/dev/zero of=");
    strcat(exe,"\"");
    strcat(exe,di->path);
    strcat(exe,di->name);
    strcat(exe,"\"");
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
    char path_nuevo [500]={};
    strcat(path_nuevo,"\"");
    strcat(path_nuevo,di->path);
    strcat(path_nuevo,"\"");
    printf("  ");
    printf("s/n\n");
    char *con = (char*)malloc(sizeof(char));
    fgets(con,10,stdin);
    if(strcmp(con,"s\n")==0){
        char exe [600]={};
        strcat(exe,"rm ");
        strcat(exe,path_nuevo);
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
       ver_particiones_montadas(cabeza);
    }

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


void split(cade vec [],char cad [],int *ini){
    int k=strlen(cad);
    strcat(cad,"|");
    int j = 0;
    char vec1 [30];
    int i;
    int pos_vec=0;
    char d[30]={};
    int tam=0;
    for(i=0;i<k+1;i++){
        if((int)cad[i]==(int)'/'||(int)cad[i]==(int)'|'){
            strcpy(vec[j].cadena,d);
            j++;
            for(tam=0;tam<30;tam++){
             d[tam]='\0';
            }
            pos_vec=0;
            continue;
        }
        d[pos_vec++]=cad[i];
    }
    (*ini)=j;
}

void reporteMbr(char path[], char disco, int partcion){
    char contenidodot [50000]={};
    mbr m = leerMBR(obtener_path(cabeza,disco,partcion));
    cade vec [10] = {};
    char name_disco [300] ={};
    strcat(name_disco,obtener_nombre_particion(cabeza,disco,partcion)) ;
    int inicio=0;
    split(vec,path,&inicio);
    char nuevopath [500]={};
    char nombre [300] = {};
    char path_aux[600]={};
    int i;
    char exec [650]={};
    strcat(nuevopath,"\"");
    char tamano [400]={};
    for(i=0;i<inicio-1;i++){
        strcat(nuevopath,vec[i].cadena);
        strcat(nuevopath,"/");
    }
    strcpy(path_aux,nuevopath);
    strcat(nuevopath,"\"");
    strcat(exec,"mkdir -p ");
    strcat(exec,nuevopath);
    strcat(nuevopath,"\"");
    system(exec);
    strcpy(nombre,vec[inicio-1].cadena);
    strcat(contenidodot,"digraph uno { ");
    strcat(contenidodot,"nodo1") ;
    strcat(contenidodot,"[label = \"") ;
    strcat(contenidodot,"{") ;
    strcat(contenidodot,obtener_path(cabeza,disco,partcion)) ;
    strcat(contenidodot,"|") ;
    strcat(contenidodot,"{NOMBRE | VALOR}") ;
    strcat(contenidodot,"|") ;
    strcat(contenidodot,"{mbr_tamano|") ;
    strcat(contenidodot,itoa(m.tamano,tamano)) ;
    strcat(contenidodot,"}") ;
    strcat(contenidodot,"|") ;
    strcat(contenidodot,"{mbr_fecha|") ;
    strcat(contenidodot,"no :=)");
    strcat(contenidodot,"}") ;
    strcat(contenidodot,"|") ;
    strcat(contenidodot,"{mbr_disk_signature|") ;
    strcat(contenidodot,itoa(m.random,tamano));
    strcat(contenidodot,"}") ;
    if(m.part1.estado=='1'){
        strcat(contenidodot,"|") ;
        strcat(contenidodot,"{part_status_1|") ;
        char ve1 [1]={};
        strcat(contenidodot,"activa");
        strcat(contenidodot,"}") ;
        strcat(contenidodot,"|") ;
        strcat(contenidodot,"{part_type_1|") ;
        if(m.part1.tipo =='p'){
         strcat(contenidodot,"primaria");
        }else{
         strcat(contenidodot,"extendida");
        }

        strcat(contenidodot,"}") ;
        strcat(contenidodot,"|") ;
        strcat(contenidodot,"{part_fit_1|") ;
        ve1[0]=m.part1.fit;
        if(m.part1.fit=='f'){
         strcat(contenidodot,"primer ajuste");
        }else if(m.part1.fit=='b'){
         strcat(contenidodot,"mejor ajuste");
        }else{
         strcat(contenidodot,"peor ajuste");
        }

        strcat(contenidodot,"}") ;
        strcat(contenidodot,"|") ;
        strcat(contenidodot,"{part_start_1|") ;
        strcat(contenidodot,itoa(m.part1.start,tamano));
        strcat(contenidodot,"}") ;

        strcat(contenidodot,"|") ;
        strcat(contenidodot,"{part_size_1|") ;
        strcat(contenidodot,itoa(m.part1.size,tamano));
        strcat(contenidodot,"}") ;

        strcat(contenidodot,"|") ;
        strcat(contenidodot,"{part_name_1|") ;
        strcat(contenidodot,m.part1.name);
        strcat(contenidodot,"}") ;

    }
    if(m.part2.estado=='1'){
        strcat(contenidodot,"|") ;
        strcat(contenidodot,"{part_status_2|") ;
        char ve1 [1]={};
        strcat(contenidodot,"activa");
        strcat(contenidodot,"}") ;
        strcat(contenidodot,"|") ;
        strcat(contenidodot,"{part_type_2|") ;
        if(m.part2.tipo =='p'){
         strcat(contenidodot,"primaria");
        }else{
         strcat(contenidodot,"extendida");
        }

        strcat(contenidodot,"}") ;
        strcat(contenidodot,"|") ;
        strcat(contenidodot,"{part_fit_2|") ;
        ve1[0]=m.part2.fit;
        if(m.part2.fit=='f'){
         strcat(contenidodot,"primer ajuste");
        }else if(m.part2.fit=='b'){
         strcat(contenidodot,"mejor ajuste");
        }else{
         strcat(contenidodot,"peor ajuste");
        }

        strcat(contenidodot,"}") ;
        strcat(contenidodot,"|") ;
        strcat(contenidodot,"{part_start_2|") ;
        strcat(contenidodot,itoa(m.part2.start,tamano));
        strcat(contenidodot,"}") ;

        strcat(contenidodot,"|") ;
        strcat(contenidodot,"{part_size_2|") ;
        strcat(contenidodot,itoa(m.part2.size,tamano));
        strcat(contenidodot,"}") ;

        strcat(contenidodot,"|") ;
        strcat(contenidodot,"{part_name_2|") ;
        strcat(contenidodot,m.part2.name);
        strcat(contenidodot,"}") ;


    }

    if(m.part3.estado=='1'){
        strcat(contenidodot,"|") ;
        strcat(contenidodot,"{part_status_3|") ;
        char ve1 [1]={};
        strcat(contenidodot,"activa");
        strcat(contenidodot,"}") ;
        strcat(contenidodot,"|") ;
        strcat(contenidodot,"{part_type_3|") ;
        if(m.part3.tipo =='p'){
         strcat(contenidodot,"primaria");
        }else{
         strcat(contenidodot,"extendida");
        }

        strcat(contenidodot,"}") ;
        strcat(contenidodot,"|") ;
        strcat(contenidodot,"{part_fit_3|") ;
        ve1[0]=m.part3.fit;
        if(m.part3.fit=='f'){
         strcat(contenidodot,"primer ajuste");
        }else if(m.part3.fit=='b'){
         strcat(contenidodot,"mejor ajuste");
        }else{
         strcat(contenidodot,"peor ajuste");
        }

        strcat(contenidodot,"}") ;
        strcat(contenidodot,"|") ;
        strcat(contenidodot,"{part_start_3|") ;
        strcat(contenidodot,itoa(m.part3.start,tamano));
        strcat(contenidodot,"}") ;

        strcat(contenidodot,"|") ;
        strcat(contenidodot,"{part_size_3|") ;
        strcat(contenidodot,itoa(m.part3.size,tamano));
        strcat(contenidodot,"}") ;

        strcat(contenidodot,"|") ;
        strcat(contenidodot,"{part_name_3|") ;
        strcat(contenidodot,m.part3.name);
        strcat(contenidodot,"}") ;


    } if(m.part4.estado=='1'){
        strcat(contenidodot,"|") ;
        strcat(contenidodot,"{part_status_4|") ;
        char ve1 [1]={};
        strcat(contenidodot,"activa");
        strcat(contenidodot,"}") ;
        strcat(contenidodot,"|") ;
        strcat(contenidodot,"{part_type_4|") ;
        if(m.part4.tipo =='p'){
         strcat(contenidodot,"primaria");
        }else{
         strcat(contenidodot,"extendida");
        }

        strcat(contenidodot,"}") ;
        strcat(contenidodot,"|") ;
        strcat(contenidodot,"{part_fit_4|") ;
        ve1[0]=m.part4.fit;
        if(m.part4.fit=='f'){
         strcat(contenidodot,"primer ajuste");
        }else if(m.part4.fit=='b'){
         strcat(contenidodot,"mejor ajuste");
        }else{
         strcat(contenidodot,"peor ajuste");
        }

        strcat(contenidodot,"}") ;
        strcat(contenidodot,"|") ;
        strcat(contenidodot,"{part_start_4|") ;
        strcat(contenidodot,itoa(m.part4.start,tamano));
        strcat(contenidodot,"}") ;

        strcat(contenidodot,"|") ;
        strcat(contenidodot,"{part_size_4|") ;
        strcat(contenidodot,itoa(m.part4.size,tamano));
        strcat(contenidodot,"}") ;

        strcat(contenidodot,"|") ;
        strcat(contenidodot,"{part_name_4|") ;
        strcat(contenidodot,m.part4.name);
        strcat(contenidodot,"}") ;


    }
    strcat(contenidodot,"}") ;
    strcat(contenidodot,"\"");
    strcat(contenidodot," shape = \"record\"];");
    if(m.part1.tipo=='e'||m.part2.tipo=='e'||m.part3.tipo=='e'||m.part4.tipo=='e'){
        reporteEbr(contenidodot,disco,partcion);
    }
    strcat(contenidodot,"}") ;
    FILE *file =fopen("dot.txt","w");
    fprintf(file,contenidodot);
    fclose(file);
    char exe1 [600]={};
    strcat(path_aux,nombre);
    strcat(exe1,"dot -Tjpg dot.txt -o ");
    strcat(path_aux,"\"");
    strcat(exe1,path_aux);
    system(exe1);
    char exe2 [600]={};

    strcat(exe2,"gnome-open ");
    strcat(exe2,path_aux);
    system(exe2);


}

void reporteEbr(char comando[], char disco, int particion){
    int seek_ebr;
    fijar_puntero_ebr(leerMBR(obtener_path(cabeza,disco,particion)),&seek_ebr,"");
    if(seek_ebr!=0){
       int next =0;
       ebr primera ;
       FILE * ptrfile;
       char path [600]={};
       strcpy(path,obtener_path(cabeza,disco,particion));
       ptrfile = fopen(path,"rb");
       int node =0;
       char l [30];
       while(next!=-1){
           char ll[20]={};
           char node1 [25]="node";
           strcat(node1,itoa(node,ll));
           fseek(ptrfile,seek_ebr,SEEK_SET);
           fread(&primera,sizeof(ebr),1,ptrfile);
           strcat(comando,node1);
           strcat(comando,"[ label = \"{");
           strcat(comando,"{NOMBRE |VALOR } |");
           strcat(comando,"{part_status |");
           if(primera.status=='1'){
            strcat(comando,"activa} |");
           }else{
            strcat(comando,"espacio libre} |");
           }
           strcat(comando,"{part_fit|");
           if(primera.fit=='f'){
            strcat(comando,"primer ajuste");
           }else if(primera.fit=='b'){
            strcat(comando,"mejor ajuste");
           }else{
            strcat(comando,"peor ajuste");
           }
           strcat(comando,"}|");
           strcat(comando,"{part_start|");
           strcat(comando,itoa(primera.start,ll));
           strcat(comando,"}|");
           strcat(comando,"{part_size |");
           strcat(comando,itoa(primera.size,ll));
           strcat(comando,"}|");
           strcat(comando,"{part_next |");
           strcat(comando,itoa(primera.next,ll));
           strcat(comando,"}|");
           strcat(comando,"{part_name |");
           strcat(comando,primera.name);
           strcat(comando,"}}\" shape = \"record\"];");
           next=primera.next;
           seek_ebr=primera.start+primera.size+sizeof(ebr);
           node++;
       }

    }

}

#endif // EJECUTAR

