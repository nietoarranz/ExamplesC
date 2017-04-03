#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sysexits.h>
#include "auxiliar.h"

int main (int argc, char *argv[]){

argv0="secuencia";

//Proceso de adquirir el maximo numero de elementos a imprimir en la consola desde la variable de entorno MAX_OUTPUT
double maximo = 100.0;//Valor predefinido
char *maxoutput;//Char donde guardaremos lo que hay en la variable de entorno
maxoutput = getenv("MAX_OUTPUT");//Usamos getenv para obtener lo que hay en MAX_OUTPUT

if(maxoutput!=NULL && strcmp(maxoutput,"\0")!=0){
	char *auxmax;//Variable para comprobar si es entero
	double maxout;

	maxout = strtol(maxoutput, &auxmax, 10);
	
	//Comprobmos casos especiales
	if(maxout==0){
		Error(EX_NOPERM, "Se intentó superar el límite de salida establecido por MAX OUTPUT.");
	}

	if(strcmp(auxmax,"\0")==0 && maxout>0){
		maximo = maxout;
	}
}

//Casos de error
if(argc==4 && strcmp(argv[3],"\0")==0){
	Error(EX_USAGE, " El parámetro \"paso\" no es un número real válido.");
}

if(argc>=3 && strcmp(argv[2],"\0")==0){
	Error(EX_USAGE, " El parámetro \"desde\" no es un número real válido.");
}

if(argc>=2 && strcmp(argv[1],"\0")==0){
	Error(EX_USAGE, " El parámetro \"hasta\" no es un número real válido.");
}

if(argc==4 && strcmp(argv[3],"0")==0){
	Error(EX_USAGE, "El parámetro \"paso\" no puede valer 0.");
}

if(argc==4 && strtod(argv[3], NULL)<0 && strtod(argv[1], NULL)>strtod(argv[2], NULL)){
	Error(EX_USAGE, "El signo de \"paso\" no permite recorrer el intervalo en el sentido \"desde\" a \"hasta\".");
}

if(argc==4 && strtod(argv[3], NULL)>0 && strtod(argv[1], NULL)<strtod(argv[2], NULL)){
	Error(EX_USAGE, "El signo de \"paso\" no permite recorrer el intervalo en el sentido \"desde\" a \"hasta\".");
}

if(argc>4){
	Error(EX_USAGE, "El número de argumentos no es correcto");
}

if(argc==2 && strcmp(argv[1],"-h")==0){
	printf("secuencia: Uso: secuencia [ hasta [ desde [ paso ]]]\n");
	printf("secuencia: Genera la secuencia de números en el intervalo y paso indicado\n");
	exit(EX_OK);
}

//Proceso principal
double hasta,desde,paso;

//Valores predefinidos
hasta = 10.0;
desde = 1.0;
paso = 1.0;

char *aux;

//Casos dependiendo de el numero de elementos pasados como parametros
if(argc==2){
        hasta = strtod(argv[1], &aux);
	if(hasta<2){
		Error(EX_USAGE, "El signo de \"paso\" no permite recorrer el intervalo en el sentido \"desde\" a \"hasta\".");
	}
	if(strcmp(aux,"\0")!=0){
		Error(EX_USAGE, "El parámetro \"hasta\" no es un número real válido.");
	}
}

if(argc==3){
  	hasta = strtod(argv[1], &aux);
	if(strcmp(aux,"\0")!=0){
		Error(EX_USAGE, "El parámetro \"hasta\" no es un número real válido.");
	}
        desde = strtod(argv[2], &aux);
	if(strcmp(aux,"\0")!=0){
		Error(EX_USAGE, "El parámetro \"desde\" no es un número real válido.");
	}
}

if (argc==4){
        hasta = strtod(argv[1], &aux);
	if(strcmp(aux,"\0")!=0){
		Error(EX_USAGE, "El parámetro \"hasta\" no es un número real válido.");
	}
        desde = strtod(argv[2], &aux);
	if(strcmp(aux,"\0")!=0){
		Error(EX_USAGE, "El parámetro \"desde\" no es un número real válido.");
	}
        paso = strtod(argv[3], &aux);
	if(strcmp(aux,"\0")!=0){
		Error(EX_USAGE, "El parámetro \"paso\" no es un número real válido.");
	}
}

//Proceso de impresion

double i = desde;
int limite = 0;

//Diferentes casos dependiedo del signo de paso
if(paso>0){
	while(i <= hasta && limite<maximo){
		printf("\t%g\n",i);
		i = i + paso;
		limite++;
	}
}else{
	while(i >= hasta && limite<maximo){
		printf("\t%g\n",i);
		i = i + paso;
		limite++;
	}
}

//Casos de error cuando se spuera el maximo numero de elementos a imprimir
if(argc==2 && hasta>maximo){
	Error(EX_NOPERM, "Se intentó superar el límite de salida establecido por MAX OUTPUT.");
}

if(limite > maximo){
	Error(EX_NOPERM, "Se intentó superar el límite de salida establecido por MAX OUTPUT.");
}
exit(EX_OK);
}
