#include <stdio.h>
#include <time.h>

#define DOMINGO 0
#define LUNES 1
#define MARTES 2
#define MIERCOLES 3
#define JUEVES 4
#define VIERNES 5
#define SABADO 6

int main() {
    // Crear variables para guardar el tiempo
    time_t t;
    struct tm *local_time;
    FILE *ejercicios;
   
    char linea[256]; 
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
    int entero = 0;
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
		    scanf("%d", &entero); 
		    break;            
     	case MIERCOLES:                  
 		printf("pansa");
 		    printf("toca cualquier tecla para apagar: ");
     		    scanf("%d", &entero);                           	
		break;            
    	case JUEVES:
		printf("pansa");  	    
		    printf("toca cualquier tecla para apagar: ");
    		    scanf("%d", &entero);
		break;            	
	
    	case VIERNES:
		    
	            ejercicios = fopen("archivos/ejercicios.txt", "r");
	    	    if(ejercicios == NULL){
		    	printf("Error al Abrir archivo.\n");
			return 1;
		    }	    
		    while(fgets(linea, sizeof(linea), ejercicios)){
		  	printf("%s", linea);  
		    }
		    fclose(ejercicios);
		    printf("toca cualquier tecla para apagar: ");
    		    scanf("%d", &entero);
		break;            
    	case SABADO:
		printf("pansa");
		    printf("toca cualquier tecla para apagar: ");
    		    scanf("%d", &entero);
		break;            

    }



	return 0;
}

