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

void todolistGeneral(const char *archivo_config, int opciones,const char *dia, bool verdadero){
	char tarea1[100];
	snprintf(tarea1, sizeof(tarea1), "%s%s", "estudiar_C", dia);
	char tarea2[100];
	snprintf(tarea2, sizeof(tarea2), "%s%s", "avanzarProyecto", dia);
	char tarea3[100];
	snprintf(tarea3, sizeof(tarea3), "%s%s", "todolist_emocional", dia);
	

			if(obtener_estado_tarea(archivo_config, tarea1) == 1 && obtener_estado_tarea(archivo_config, tarea2) == 1 && obtener_estado_tarea(archivo_config, tarea3) == 1){
				actualizar_estado_tarea(archivo_config, "listo", 1);			
			}
			else{
		
			actualizar_estado_tarea(archivo_config, "listo", 0);			
		    	if(obtener_estado_tarea(archivo_config, tarea1) == 0){
		    		printf("\033[33m(1):Estudiar C!\033[33m\n");
		    	}


		    	if(obtener_estado_tarea(archivo_config, tarea2) == 0){
		    		printf("\033[33m(2):Avanzar Proyecto C!\033[33m\n");
		    	}



		    	if(obtener_estado_tarea(archivo_config, tarea3) == 0){
		    		printf("\033[33m(3):Hacer Todolist Emocional !\033[33m\n");
		    	}


		    	printf("\033[32mselecciona tarea para marcarla como hecho... \033[32m");
    		    	scanf("%d", &opciones);
			if(opciones == 1){
				actualizar_estado_tarea(archivo_config, tarea1, 1);
			}


			if(opciones == 2){
				actualizar_estado_tarea(archivo_config, tarea2, 1);
			}


			if(opciones == 3){
				actualizar_estado_tarea(archivo_config, tarea3, 1);
			}
			
			}
}



int main() {
   	bool verdadero = true; 
	int opciones; //se usara multiples veces, no modificar.
	time_t t;
    	struct tm *local_time;
	int salida; // para salir de la app
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
    	printf("\033[32mHoy es %s, %d de %s de %d.\033[32m\n",
           	dias[local_time->tm_wday],
          	 local_time->tm_mday,
           	meses[local_time->tm_mon],
           	local_time->tm_year + 1900);
    	printf("\033[32mHora actual: %02d:%02d:%02d\033[32m\n",
           	local_time->tm_hour,
           	local_time->tm_min,
           	local_time->tm_sec);

    	int dia = local_time->tm_wday;

    while(verdadero){
     	switch(dia){
    		case DOMINGO:
			printf("Descansa noob");
			break;
     		case LUNES:                  
			todolistGeneral(archivo_config, opciones,"1", verdadero);			
			break;            
    		case MARTES:
			actualizar_estado_tarea(archivo_config, "estudiar_C1", 0);
			actualizar_estado_tarea(archivo_config, "avanzarProyecto1", 0);
			actualizar_estado_tarea(archivo_config, "todolist_emocional1", 0);

	
			todolistGeneral(archivo_config, opciones, "2", verdadero);			
		    	break;            
		case MIERCOLES:
			actualizar_estado_tarea(archivo_config, "estudiar_C2", 0);
			actualizar_estado_tarea(archivo_config, "avanzarProyecto2", 0);
			actualizar_estado_tarea(archivo_config, "todolist_emocional2", 0);


			todolistGeneral(archivo_config, opciones, "3", verdadero);			
			break;            
		case JUEVES:
			actualizar_estado_tarea(archivo_config, "estudiar_C3", 0);
			actualizar_estado_tarea(archivo_config, "avanzarProyecto3", 0);
			actualizar_estado_tarea(archivo_config, "todolist_emocional3", 0);


			todolistGeneral(archivo_config, opciones, "4", verdadero);			
			break;            	
	
		case VIERNES:
			actualizar_estado_tarea(archivo_config, "estudiar_C4", 0);
			actualizar_estado_tarea(archivo_config, "avanzarProyecto4", 0);
			actualizar_estado_tarea(archivo_config, "todolist_emocional4", 0);

			todolistGeneral(archivo_config, opciones, "5", verdadero);			
			break;            
    		case SABADO:
			actualizar_estado_tarea(archivo_config, "estudiar_C5", 0);
			actualizar_estado_tarea(archivo_config, "avanzarProyecto5", 0);
			actualizar_estado_tarea(archivo_config, "todolist_emocional5", 0);


			printf("descansa noob"); 	
			break;            

    	}

   	if(obtener_estado_tarea(archivo_config, "listo") != 1){

		printf("\033[32mDesea Salir?. si(1), no(0)\033[32m");
		scanf("%d",&salida);
  		if(salida == 1){
			verdadero = false;
		}

	}else {
		break;
	} 
	
    }


	return 0;
}

