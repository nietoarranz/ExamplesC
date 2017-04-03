#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sysexits.h>
#include "auxiliar.h"

typedef struct TPila{
  char* top;
  struct TPila* resto;
}Pila;

Pila* newPila(){
  Pila* pila = (Pila*) malloc(sizeof(Pila));
  if(pila==NULL){
	Error(EX_OSERR, "No se pudo ubicar la memoria din´amica necesaria.");
  }
  pila->top = NULL;
  pila->resto = NULL;
  return pila;
}


char* pop(Pila** pila){
  char* res = (*pila)->top;
  *pila =(* pila)->resto;
  return res;
}
void push(Pila** pila, char* elem){
  Pila* nuevaPila = (Pila*) malloc(sizeof(Pila));
  if(nuevaPila==NULL){
	Error(EX_OSERR, "No se pudo ubicar la memoria din´amica necesaria.");
  }
  nuevaPila->top = elem;
  nuevaPila->resto = *pila;
  *pila = nuevaPila;
}
void imprimirPila(Pila* pila){
  while(pila->top){
    printf("%s",pop(&pila));
  }
}



int main(int argc, char *argv[]){

	argv0="bocabajo";

	if(argc==2 && strcmp(argv[1],"-h")==0){
	printf("bocabajo: Uso: bocabajo [ fichero... ]\n");
	printf("bocabajo: Invierte el orden de las l´ıneas de los ficheros (o de la entrada).\n");
	exit(EX_OK);
	}

	

	if(argc<2){
		Pila* pila = newPila();
		char linea[2048];
		while(fgets (linea, 2048, stdin)){
			push(&pila,strdup(linea));
		}
		imprimirPila(pila);
		exit(EX_OK);
	}
	Pila* pila = newPila();
	int i;
	for(i=1;i<argc;i++){
		FILE *fichero;
		fichero=fopen(argv[i],"rt");
		if(fichero==NULL){
			Error(EX_NOINPUT, " El fichero \"%s\" no puede ser leído." , argv[i]);
		}
		char fila[2048];
		while(fgets(fila,2048,fichero)){
			push(&pila,strdup(fila));
		}

	  	
		fclose(fichero);
	}
	imprimirPila(pila);
	exit(EX_OK);
}
