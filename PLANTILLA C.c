#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//Declaracion del nodo Raiz
struct raiz {
    char conjunto[256];
    struct raiz *sig;
    struct raiz *elements;
};
struct raiz *raiz=NULL;
struct raiz *temp=NULL;
struct raiz *elementos=NULL;
struct raiz *temp2=NULL;
struct raiz *tempElementos=NULL;

//Insertar Conjuntos
void insertar(char const *cadena)
{
    struct raiz *nuevo;
    nuevo = malloc(sizeof(struct raiz));
    strcpy(nuevo->conjunto, cadena);
	nuevo->sig=NULL;
    if (raiz == NULL)
    {
        raiz = nuevo;
        temp = nuevo;
        nuevo->sig = NULL;
    }
    else
    {
        raiz->sig = nuevo;
        raiz = nuevo;
    }
}

//Insertar Elementos
void insertarElements(char const *cadena)
{
    struct raiz *nuevo;
    nuevo = malloc(sizeof(struct raiz));
    strcpy(nuevo->conjunto, cadena);
	nuevo->elements=NULL;
    if (elementos == NULL)
    {
        elementos = nuevo;
        temp2 = nuevo;
        nuevo->elements = NULL;
    }
    else
    {
        elementos->elements = nuevo;
        elementos = nuevo;
    }
}

//Reinicio puntero
void reset()
{
	raiz->elements = temp2;
	temp2 = NULL;
	elementos = NULL;
}

//imprimir conjuntos
void imprimir()
{
    struct raiz *reco=temp;
    printf("Arbol Raiz -> ");
    printf("\n");
    while (reco!=NULL)
    {
        printf("%s -> ",reco->conjunto);
        	tempElementos = reco->elements;
        	printf("Elementos del conjunto");
            while (tempElementos!=NULL)
		    {
		        printf(" -> %s",tempElementos->conjunto);
		        tempElementos=tempElementos->elements;
		    }
		    printf("\n");
        reco=reco->sig;
    }
    printf("\n");
}

//Funcion para leer el archivo de entrada
void leerArchivo(char const *ruta){
	
    FILE * file;
    int control = 0;
    char data;
	char cadena[256];
	
    if( access(ruta, F_OK) != -1){
    	
	    file = fopen(ruta, "r");
	    strcpy(cadena, "");
	    int espacios = 0;
	    while (1) {
	        data = fgetc(file);
	        if (feof(file))
	        break;
	        if(control == 0){
	        	if(data=='\0'||data==32){	
	        		espacios++;
				}else if(data==61){
					espacios++;
					insertar(cadena);
				}else if (data=='\n'){
					strcpy(cadena, "");
				}else if (data==123){
					strcpy(cadena, "");
					control = 1;
				}else{
					espacios++;
					strncat(cadena, &data, 1);
					if(espacios==5){
						control = 3;
					}
				}
			}else if(control == 3){
				strncat(cadena, &data, 1);
				if (data=='\n'){
								printf("Se detecto un conjunto con operacion \n");
					strcpy(cadena, "");
					control = 0;
					espacios = 0;
				}
			}else{
				if(data=='\0'||data==32){        	
				}else if (data==44){
					insertarElements(cadena);
					strcpy(cadena, "");
				}else if (data==125){
					insertarElements(cadena);
					reset();
					strcpy(cadena, "");
					control = 0;
					espacios = 0;
				}else{
					strncat(cadena, &data, 1);
				}
			}
	    }
	    fclose(file);
	    
    }else{
    	printf("El archivo no existe en esta ruta");
    }
}

//funcion main de ejecucion
int main()
{    
 	char ruta[256];
	printf("Ingrese la ruta del archivo: \n");
	scanf("%s", ruta); 
	
	leerArchivo(ruta);
	
	imprimir();
}
