#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>



#define DOMINGO 0
#define LUNES 1
#define MARTES 2
#define MIERCOLES 3
#define JUEVES 4
#define VIERNES 5
#define SABADO 6


// Función para obtener el estado de una tarea desde el archivo
int obtener_estado_tarea(const char *nombre_archivo, const char *tarea) {
    FILE *archivo = fopen(nombre_archivo, "r");
    if (archivo == NULL) {
        perror("No se puede abrir el archivo");
        return -1;
    }

    char linea[256];
    while (fgets(linea, sizeof(linea), archivo)) {
        char nombre[50];
        int valor;
        if (sscanf(linea, "%49[^=]=%d", nombre, &valor) == 2) {
            if (strcmp(nombre, tarea) == 0) {
                fclose(archivo);
                return valor;
            }
        }
    }

    fclose(archivo);
    return -1; // Si no se encuentra la tarea, retornar -1
}

// Función para actualizar el estado de una tarea en el archivo
void actualizar_estado_tarea(const char *nombre_archivo, const char *tarea, int nuevo_estado) {
    FILE *archivo = fopen(nombre_archivo, "r+");  // Abrir archivo para lectura y escritura
    if (archivo == NULL) {
        perror("No se puede abrir el archivo para modificar");
        return;
    }

    char linea[256];
    long posicion;
    while ((posicion = ftell(archivo)) != -1 && fgets(linea, sizeof(linea), archivo)) {
        char nombre[50];
        int valor;
        if (sscanf(linea, "%49[^=]=%d", nombre, &valor) == 2) {
            if (strcmp(nombre, tarea) == 0) {
                // Mover el puntero del archivo a la posición de la tarea encontrada
                fseek(archivo, posicion, SEEK_SET);
                // Escribir el nuevo valor de la tarea
                fprintf(archivo, "%s=%d\n", tarea, nuevo_estado);
                fclose(archivo);
                return;
            }
        }
    }

    fclose(archivo);
    printf("Tarea no encontrada para modificar.\n");
}


int main() {
   	bool verdadero = true; 
	int opciones; //se usara multiples veces, no modificar.
	int salida; // para salir de la app
	time_t t;
    	struct tm *local_time;
    	const char *archivo_config = "archivos/tareas.txt"; // abro pointer de el archivo  
    	// Obtener el tiempo actual
    	t = time(NULL);
    	if (t == -1) {
        	perror("Error obteniendo el tiempo");
        	return 1;
    	}

    	// Convertir el tiempo a la hora local
    	local_time = localtime(&t);
    	if (local_time == NULL) {
        	perror("Error convirtiendo el tiempo");
        	return 1;
    	}

    	// Array con los nombres de los días de la semana
    	const char *dias[] = {"Domingo", "Lunes", "Martes", "Miércoles", "Jueves", "Viernes", "Sábado"};

    	// Array con los nombres de los meses
    	const char *meses[] = {"Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio",
                           "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"};

    	// Mostrar la fecha y hora
    	printf("Hoy es %s, %d de %s de %d.\n",
           	dias[local_time->tm_wday],
          	 local_time->tm_mday,
           	meses[local_time->tm_mon],
           	local_time->tm_year + 1900);
    	printf("Hora actual: %02d:%02d:%02d\n",
           	local_time->tm_hour,
           	local_time->tm_min,
           	local_time->tm_sec);

    	int dia = local_time->tm_wday;

    while(verdadero){
     	switch(dia){
    		case DOMINGO:
			printf("pansa");
			break;
     		case LUNES:                  
 			printf("pansa");
 			break;            
    		case MARTES:
			printf("\nLA POLLA GENERAL\n");
		    	printf("toca cualquier tecla para apagar: ");
		    	break;            
     		case MIERCOLES:                  
 			printf("pansa");
 		    	printf("toca cualquier tecla para apagar: ");
			break;            
    		case JUEVES:
			printf("pansa");  	    
		    	printf("toca cualquier tecla para apagar: ");
			break;            	
	
    		case VIERNES:
		    	if(obtener_estado_tarea(archivo_config, "estudiar_C") == 0){
		    		printf("(1):Estudiar C!\n");
		    	}

		    	if(obtener_estado_tarea(archivo_config, "hacer_ejercicio") == 0){
		    		printf("(2):Hacer brazo !\n");
		    	}

		    	if(obtener_estado_tarea(archivo_config, "avanzarProyecto") == 0){
		    		printf("(3):Avanzar Proyecto C!\n");
		    	}

		    	printf("selecciona tarea para marcarla como hecho... ");
    		    	scanf("%d", &opciones);
			if(opciones == 1){
				actualizar_estado_tarea(archivo_config, "estudiar_C", 1);
			}

			else if(opciones == 2){
				actualizar_estado_tarea(archivo_config, "hacer_ejercicio", 1);
			}

			if(opciones == 3){
				actualizar_estado_tarea(archivo_config, "avanzarProyecto", 1);
			}


			break;            
    		case SABADO:
	  		actualizar_estado_tarea(archivo_config, "estudiar_C", 0);
			
	  		actualizar_estado_tarea(archivo_config, "hacer_ejercicio", 0);		    	
	  		actualizar_estado_tarea(archivo_config, "avanzarProyecto", 0);
			//cuando pase de viernes a domingo, las tareas anteriores volveran a estar
			//visibles.
			printf("toca cualquier tecla para apagar: ");
			break;            

    	}
	printf("Desea Salir?. si(1), no(0)");
	scanf("%d",&salida);
  	if(salida == 1){
		break;
	} 
    
    
    }


	return 0;
}

