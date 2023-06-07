#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

struct pregunta{
   char preg[100]; //pregunta
   char rep1[50]; //respuestas posibles
   char rep2[50];
   char rep3[50];
   char rep4[50];
   int correctRep;// numero de la respuesta correcta
};

void mostrar(struct pregunta pr) {
  printf("Pregunta:%s\n",pr.preg);
  printf("Respuesta (1):%s\n",pr.rep1);
  printf("Respuesta (2):%s\n",pr.rep2);
  printf("Respuesta (3):%s\n",pr.rep3);
  printf("Respuesta (4):%s\n",pr.rep4);
}

void asignarDesdeArchivo(struct pregunta *preguntas, int numPreguntas, const char *nombreArchivo) {
    FILE *archivo = fopen(nombreArchivo, "r"); //abre el archivo
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n"); //revisa que se pueda abrir el archivo
        return;
    }

    char linea[200];
    int indice = 0;
    while (fgets(linea, sizeof(linea), archivo)) {
        char inttemp[10];
        if (indice >= numPreguntas) { //revisa si tomo el numero maximo de preguntas solicitadas por el usuario
            printf("Se alcanzó el número máximo de preguntas.\n");
            break;
        }

        linea[strcspn(linea, "\n")] = '\0'; // Eliminar el salto de línea

        // Asignar la pregunta y las respuestas a la estructura
        strcpy(preguntas[indice].preg, linea);

        fgets(linea, sizeof(linea), archivo); // Leer la primera respuesta
        linea[strcspn(linea, "\n")] = '\0';
        strcpy(preguntas[indice].rep1, linea);

        fgets(linea, sizeof(linea), archivo); // Leer la segunda respuesta
        linea[strcspn(linea, "\n")] = '\0';
        strcpy(preguntas[indice].rep2, linea);

        fgets(linea, sizeof(linea), archivo); // Leer la tercera respuesta
        linea[strcspn(linea, "\n")] = '\0';
        strcpy(preguntas[indice].rep3, linea);

        fgets(linea, sizeof(linea), archivo); // Leer la cuarta respuesta
        linea[strcspn(linea, "\n")] = '\0';
        strcpy(preguntas[indice].rep4, linea);

        fgets(linea, sizeof(linea), archivo); // Leer el numero de respusta correcta
        linea[strcspn(linea, "\n")] = '\0';
        strcpy(inttemp, linea);
        preguntas[indice].correctRep = atoi(inttemp);

        indice++;
    }

    fclose(archivo);
}

void Cuestionario(struct pregunta *preguntas, int numPreguntas) {
  int random = rand() % numPreguntas; // genera un rando, del 0-numPreguntas
  printf("----- Cuestionario -----\n");
  printf("Random %d:\n", random );
  char temp[10];
  printf("Pregunta %d:\n", random + 1);
  mostrar(preguntas[random]);
  printf("Su respuesta es?\n");
  fgets(temp, 10, stdin);
  if(atoi(temp) == preguntas[random].correctRep) printf("BIEN!\n");//compara la respuesta del usuario con el numero de la respuesta correcta
  else printf("MAL!\n");
}

int main(void){
  srand(time(NULL));
  int juego = 1;
  printf("Ingrese el numero de preguntas totales: ");
  scanf("%d", &numPreguntas);
  getchar(); // Limpiar el búfer del teclado
  int blacklist[numPreguntas];
  while (juego == 1) {
    int numPreguntas ;
    int decision;
    label:
    printf("MENU:\n");
    printf("(1)Jugar\n");
    printf("(2)Salir\n");
    printf("Respuesta:");
    scanf("%d", &decision);
    switch (decision) {
      default:
        printf("Numero invalido\n");
        system("cls");
        goto label;
      case 1:
        printf("Bien\n");
        break;
      case 2:
        return 0;

    }
    struct pregunta *preguntas = malloc(numPreguntas * sizeof(struct pregunta));
    asignarDesdeArchivo(preguntas, numPreguntas,"test.txt" );//llama funcuiones
    Cuestionario(preguntas, numPreguntas);

  }





  return 0;
}
