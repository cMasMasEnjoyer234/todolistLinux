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

bool todolistGeneral(const char *archivo_config,const char *dia){
	char opciones;
	char tarea1[100];
	snprintf(tarea1, sizeof(tarea1), "%s%s", "estudiar_C", dia);
	char tarea2[100];
	snprintf(tarea2, sizeof(tarea2), "%s%s", "todolist_emocional", dia);
	

	if(obtener_estado_tarea(archivo_config, tarea1) == 1 /*&& obtener_estado_tarea(archivo_config, tarea2) == 1 */&& obtener_estado_tarea(archivo_config, tarea2) == 1){
		//actualizar_estado_tarea(archivo_config, "listo", 1);
		return false;		
	}
	else{
	// ZONA DONDE ENTRA MENSAJE DE TAREAS Y PARA TACHARLAS	
		if(obtener_estado_tarea(archivo_config, tarea1) == 0){
			printf("\033[33m(1):Estudiar C!\033[33m\n");
		}

		if(obtener_estado_tarea(archivo_config, tarea2) == 0){
			printf("\033[33m(2):Hacer Todolist Emocional !\033[33m\n");
		}


		printf("\033[32mselecciona tarea para marcarla como hecho... \033[32m\n");
		opciones = getchar();
	
		
		//OPCIONES PARA QUE SE DEJEN DE MOSTRAR EN EL DIA	
		
		
		if(opciones  == '1'){
			actualizar_estado_tarea(archivo_config, tarea1, 1);
		}

		if(opciones == '2'){
			actualizar_estado_tarea(archivo_config, tarea2, 1);
		}
		
		else if(opciones == EOF){
			return false;
		}
			
	//OPCIONES PARA QUE SE DEJEN DE MOSTRAR EN EL DIA	
	}
	system("clear");
	return true;
}



int main() {
   	bool  continuar= true; 
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
	
    while(continuar){
     	switch(dia){
    		case DOMINGO:
			continuar = false;
			printf("Descansa noob");
			break;
     		case LUNES:                  
			continuar = todolistGeneral(archivo_config,"1");			
			break;            
    		case MARTES:
			actualizar_estado_tarea(archivo_config, "estudiar_C1", 0);
			actualizar_estado_tarea(archivo_config, "todolist_emocional1", 0);

	
			continuar = todolistGeneral(archivo_config,"2");			
		    	break;            
		case MIERCOLES:
			actualizar_estado_tarea(archivo_config, "estudiar_C2", 0);
			actualizar_estado_tarea(archivo_config, "todolist_emocional2", 0);


			continuar = todolistGeneral(archivo_config,"3");			
			break;            
		case JUEVES:
			actualizar_estado_tarea(archivo_config, "estudiar_C3", 0);
			actualizar_estado_tarea(archivo_config, "todolist_emocional3", 0);


			continuar = todolistGeneral(archivo_config,"4");			
			break;            	
	
		case VIERNES:
			actualizar_estado_tarea(archivo_config, "estudiar_C4", 0);
			actualizar_estado_tarea(archivo_config, "todolist_emocional4", 0);

			continuar = todolistGeneral(archivo_config,"5");			
			break;            
    		case SABADO:
			actualizar_estado_tarea(archivo_config, "estudiar_C5", 0);
			actualizar_estado_tarea(archivo_config, "todolist_emocional5", 0);

			continuar = false;
			printf("descansa noob"); 	
			break;            

    	}

	
    }

	return 0;
}

