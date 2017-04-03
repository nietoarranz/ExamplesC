
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sysexits.h>
#include "auxiliar.h"

//Metodo auxiliar para imprimir una linea al reves
void imprimir (char texto[],int ciclo){
	//calculamos el tamaño de la linea
	int i = 1;
	while (texto[i]!='\n'){
		i++;
	}
	if(ciclo==1){
		i--;
	}
	//Imprimimos al reves la linea
	int j;
	for(j = i;j>=0;j--){
		printf("%c",texto[j]);
	}
}

//Metodo principal
void main (int argc, char *argv[])
{

	argv0="delreves";
	
	//Caso en el que se llama al programa con "-h" para entrar en la ayuda
	if(argc==2 && strcmp(argv[1],"-h")==0){
	printf("delreves: Uso: delreves [ fichero... ]\n");
	printf("delreves: Invierte el contenido de las líneas de los ficheros (o de la entrada).\n");
	exit(EX_OK);
	}
	
	//Caso en el que se pasa el texto escrito por consola
	if(argc<2){
		char linea[2048];
		while(fgets (linea, 2048, stdin)){
			imprimir(linea,1);
			printf("\n");
		}
		exit(EX_OK);
	}
	
	//Resto de casos
	int i;
	i=1;
	//Bucle para imprimir todos los archivos
	for(i=1;i<argc;i++){
		FILE *fichero;
		fichero=fopen(argv[i],"r");
		//Error para cuando el fichero no existe o no puede ser leido
		if(fichero==NULL){
			Error(EX_NOINPUT, " El fichero \"%s\" no puede ser leído." , argv[i]);
		}
		char texto[2048];
		int j=1;
		while(fgets(texto,2048,fichero)){
			imprimir(texto,j);
			j++;
		}
		double tamanio=ftell(fichero);
		//Caso en el que el archivo esta vacio
		if(tamanio != 0){		
			printf("\n");
		}
		fclose(fichero);
	}
	exit(EX_OK);
}

