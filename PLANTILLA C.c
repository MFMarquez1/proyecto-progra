#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//Funcion para leer el archivo de entrada
void leerArchivo(char const *ruta){
	
    FILE * file;
    int data;
 
    if( access(ruta, F_OK) != -1){
    	
	    file = fopen(ruta, "r");
	    while (1) {
	        data = fgetc(file);
	        if (feof(file))
	            break;
	        printf("%c", data);
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
}
