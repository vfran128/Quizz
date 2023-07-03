#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <time.h>

char mensaje_advertencia[500] = "No hay ningun problema !";


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
            printf("Se alcanzo el numero maximo de preguntas.\n");
            break;
        }

        linea[strcspn(linea, "\n")] = '\0'; // Eliminar el salto de linea

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

int Cuestionario(struct pregunta *preguntas, int numPreguntas) {
  int random = rand() % numPreguntas; // genera un rando, del 0-numPreguntas
  printf("----- Cuestionario -----\n");
  printf("Random %d:\n", random );
  int temp;
  printf("Pregunta %d:\n", random + 1);
  mostrar(preguntas[random]);
  printf("Su respuesta es?\n");
  scanf("%d",&temp );
  if(temp == preguntas[random].correctRep) {
    printf("BIEN!\n");
    return 0;
}//compara la respuesta del usuario con el numero de la respuesta correcta
  else {printf("MAL!\n");
  return 1;}
}





struct piezas {
   int estado;// 1 = viva, 2 = muerta
   int equipo;// 1 = blanco 2 = negro
   int x_cord;
   int y_cord;
};


void asignarDesdeArchivoPiezas(struct piezas *piezas, int numPiezas, const char *nombreArchivo) {
    FILE *archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    char linea[500];
    int indice = 0;
    while (fgets(linea, sizeof(linea), archivo)) {
        char inttemp[10];
        if (indice >= numPiezas) {
            printf("Se alcanzó el número máximo de piezas.\n");
            break;
        }

        piezas[indice].estado = atoi(linea);

        fgets(linea, sizeof(linea), archivo);
        piezas[indice].equipo = atoi(linea);

        fgets(linea, sizeof(linea), archivo);
        piezas[indice].x_cord = atoi(linea);

        fgets(linea, sizeof(linea), archivo);
        piezas[indice].y_cord = atoi(linea);

        indice++;
    }

    fclose(archivo);
}


void piece_move(int equip, struct piezas *pz, int array_size, int numPiezas, struct pregunta *preguntas, char mensaje_advertencia[500], int numPreguntas) {
  int x, y, choice, pieza_actual;
  label:
  printf("Ingrese las coordenadas de la pieza que quiera mover(x y): \n");
  scanf("%d %d", &x, &y);

  //detecta que pieza eligio el usuario
  for (int i = 0; i < numPiezas; i++) {
    if(pz[i].x_cord == x && pz[i].y_cord == y && equip == pz[i].equipo) pieza_actual = i;
  }
  if(pz[pieza_actual].x_cord != x || pz[pieza_actual].y_cord != y || pz[pieza_actual].equipo != equip) {
    printf("\n");
    strcpy(mensaje_advertencia, "  La pieza que intenta elegir no existe o no pertenece al equipo que tiene que mover ahora.");
    printf("\n");
    return;
    //da error en caso de que no haya una ficha en la coordenada elegida
  }

  secondlabel:
  printf("Elija la direccion en la que quiere mover la pieza:\n");
  printf("1) Derecha\n" );
  printf("2) Izquierda\n");
  printf("3) Elegir otra pieza.\n");
  scanf("%d", &choice);//pregunta a que posicion quiere mover la ficha o si la quiere cambiar

  switch (choice) {

    case 1:
    if(pz[pieza_actual].x_cord + 1 > numPiezas) {
      printf("\n");
        printf("No se puede mover.\n");
        printf("Tal vez estes intentando mover una pieza a un lugar que ya ocupa otra pieza del mismo equipo.\n");
        printf("\n");
        printf("Elija de vuelta.\n");
      goto secondlabel;
    }

    if(equip == 1) {

      for (int i = 0; i < numPiezas; i++) {
        if (pz[pieza_actual].y_cord - 1 < 0 || pz[pieza_actual].equipo == pz[i].equipo && pz[pieza_actual].x_cord + 1 == pz[i].x_cord && pz[pieza_actual].y_cord - 1 == pz[i].y_cord && pz[i].estado == 1) {
          printf("\n");
          printf("No se puede mover.\n");
          printf("Tal vez estes intentando mover una pieza a un lugar que ya ocupa otra pieza del mismo equipo.\n");
          printf("Elija de vuelta.\n");
          printf("\n");
          goto secondlabel;//mensajes de error por si no se puede mover la ficha
        }
      }

      for (int i = 0; i < numPiezas; i++) {
        if(pz[pieza_actual].equipo != pz[i].equipo && pz[pieza_actual].x_cord + 1 == pz[i].x_cord && pz[pieza_actual].y_cord - 1 == pz[i].y_cord ) {
          int funcion_preguntas =  Cuestionario(preguntas, numPreguntas);
          if(funcion_preguntas == 0) {
            pz[i].estado = 2;
            pz[pieza_actual].x_cord++;
            pz[pieza_actual].y_cord--;
            return;
          }
          else if(funcion_preguntas == 1){
            pz[pieza_actual].estado = 2;// movimiento por si esta por comer a otra ficha, llama la pregunta si la responde bien avanzas y si no la perdes
          }
        }
      }
      pz[pieza_actual].x_cord++;
      pz[pieza_actual].y_cord--; //movimiento normal

    } else{

      for (int i = 0; i < numPiezas; i++) {
        if(pz[pieza_actual].y_cord +   1 > numPiezas || pz[pieza_actual].equipo == pz[i].equipo && pz[pieza_actual].x_cord + 1 == pz[i].x_cord && pz[pieza_actual].y_cord + 1 == pz[i].y_cord && pz[i].estado == 1) {
          printf("\n");
          printf("No se puede mover.\n");
          printf("Tal vez estes intentando mover una pieza a un lugar que ya ocupa otra pieza del mismo equipo.\n");
          printf("Elija de vuelta.\n");
          printf("\n");
          goto secondlabel;//mensaje de error por si no se puede mover la ficha
        }
      }

      for (int i = 0; i < numPiezas; i++) {
        if(pz[pieza_actual].equipo != pz[i].equipo && pz[pieza_actual].x_cord + 1 == pz[i].x_cord && pz[pieza_actual].y_cord + 1 == pz[i].y_cord ) {
          int funcion_preguntas = Cuestionario(preguntas, numPreguntas);
          if(funcion_preguntas == 0) {
            pz[i].estado = 2;
            pz[pieza_actual].x_cord++;
            pz[pieza_actual].y_cord++;
            return;
          }
          else if(funcion_preguntas == 1){
            pz[pieza_actual].estado = 2;// movimiento por si esta por comer a otra ficha, llama la pregunta si la responde bien avanzas y si no la perdes
          }
        }
      }

      pz[pieza_actual].x_cord++;
      pz[pieza_actual].y_cord++;//movimiento normal
    }

    break;
    case 2:

    if((pz[pieza_actual].x_cord - 1) < 0) {
      printf("\n");
      printf("No se puede mover.\n");
      printf("Tal vez estes intentando mover una pieza a un lugar que ya ocupa otra pieza del mismo equipo.\n");
      printf("Elija de vuelta.\n");
      printf("\n");
      goto secondlabel;
    }

    if (equip == 1) {

      for (int i = 0; i < numPiezas; i++) {
        if(pz[pieza_actual].y_cord - 1 < 0 || equip == pz[i].equipo && pz[pieza_actual].x_cord - 1 == pz[i].x_cord && pz[pieza_actual].y_cord - 1 == pz[i].y_cord && pz[i].estado == 1) {
          printf("\n");
          printf("No se puede mover.\n");
          printf("Tal vez estes intentando mover una pieza a un lugar que ya ocupa otra pieza del mismo equipo.\n");
          printf("\n");
          printf("Elija de vuelta.\n");
          goto secondlabel;//mensajes de error por si no se puede mover la ficha
        }
      }


      for (int i = 0; i < numPiezas; i++) {
        if(pz[pieza_actual].equipo != pz[i].equipo && pz[pieza_actual].x_cord - 1 == pz[i].x_cord && pz[pieza_actual].y_cord - 1 == pz[i].y_cord ) {
          int funcion_preguntas = Cuestionario(preguntas, numPreguntas);
          if(funcion_preguntas == 0) {
            pz[i].estado = 2;
            pz[pieza_actual].x_cord--;
            pz[pieza_actual].y_cord--;
            return;
          }
          else if(funcion_preguntas == 1){
            pz[pieza_actual].estado = 2;// movimiento por si esta por comer a otra ficha, llama la pregunta si la responde bien avanzas y si no la perdes
          }
        }
      }

      pz[pieza_actual].x_cord--;
      pz[pieza_actual].y_cord--;//movimiento normal

    } else {

      for (int i = 0; i < numPiezas; i++) {
        if (pz[pieza_actual].y_cord + 1 > numPiezas ||  pz[pieza_actual].equipo == pz[i].equipo && pz[pieza_actual].x_cord - 1 == pz[i].x_cord && pz[pieza_actual].y_cord + 1 == pz[i].y_cord && pz[i].estado == 1) {
          printf("\n");
          printf("No se puede mover.\n");
          printf("Tal vez estes intentando mover una pieza a un lugar que ya ocupa otra pieza del mismo equipo.\n");
          printf("Elija de vuelta.\n");
          printf("\n");
          goto secondlabel;//mensajes de error por si no se puede mover la ficha
        }
      }

      for (int i = 0; i < numPiezas; i++) {
        if(pz[pieza_actual].equipo != pz[i].equipo && pz[pieza_actual].x_cord - 1 == pz[i].x_cord && pz[pieza_actual].y_cord + 1 == pz[i].y_cord ) {
          int funcion_preguntas = Cuestionario(preguntas, numPreguntas);
          if(funcion_preguntas == 0) {
            pz[i].estado = 2;
            pz[pieza_actual].x_cord--;
            pz[pieza_actual].y_cord++;
            return;
          }
          else if(funcion_preguntas == 1){
            pz[pieza_actual].estado = 2;// movimiento por si esta por comer a otra ficha, llama la pregunta si la responde bien avanzas y si no la perdes
          }
        }
      }

      pz[pieza_actual].x_cord--;
      pz[pieza_actual].y_cord++;//movimiento normal

    }
    break;
    case 3:
    goto label;
    default:
    printf("Elija una de las opciones validas.\n");
    break;
  }
}



int wincheck(struct piezas *pz, int numPiezas, int equip) {
  int count = 0;
  for (int i = 0; i < numPiezas; i++) {
    if(pz[i].equipo == equip && pz[i].estado == 1) count++;
  }
  if(count == 0) return 1;
  else return 0;//chequea que equipo se queda sin fichas primero y gano el que le quedan
}





void printarray(struct piezas *pz, int array_size, char array[array_size][array_size], int numPiezas, char mensaje_advertencia[500]) {
  int i, j;
  //limpia la terminal
  system("cls");
  printf("Equipo 1: X\nEquipo 2: O\n");//aclaracion de los equipos de las piezas
  printf("\n");
  printf("\n");
  printf("Mensaje de advertencia: \n");
  //imprime el mensaje de advertencia actual e inmediatamente despues lo elimina.
  for (int i = 0; i < 500; i++) {
    printf("%c", mensaje_advertencia[i]);
    mensaje_advertencia[i] = ' ';
  }
  printf("\n");
  printf("\n");
  printf("\n");
  printf("   0 1 2 3 4 5 6 7 8 9 X\n");
  printf("  --------------------\n");
  // Inicializar la matriz con '-'
  for (i = 0; i < array_size; i++) {
    for (j = 0; j < array_size; j++) {
      array[i][j] = '-';
    }
  }

  // Asignar los valores a la matriz basados en las coordenadas
  for (int indice = 0; indice < numPiezas; indice++) {
    int x = pz[indice].x_cord;
    int y = pz[indice].y_cord;
    // printf("%d %d %d %d\n", pz[indice].estado, pz[indice].equipo, x, y);
    if (x >= 0 && x < array_size && y >= 0 && y < array_size) {
      if (pz[indice].equipo == 1 && pz[indice].estado == 1) array[y][x] = 'X';
      if (pz[indice].equipo == 2 && pz[indice].estado == 1) array[y][x] = 'O';
    }
  }

  // Imprimir la matriz
  for (i = 0; i < array_size; i++) {
    printf("%d |",  i);
    for (j = 0; j < array_size; j++) {
      printf("%c ", array[i][j]);
    }
    printf("\n");
  }
  printf("Y\n");
  printf("\n");
}


//funcion del juego

void juego(struct piezas *pz, int numPiezas, int array_size, char array[array_size][array_size],struct pregunta *preguntas, int numPreguntas) {
  //hasta que gane algun equipo, se repiten los movimientos de cada equipo
  while (1) {
    printarray(pz, array_size, array,numPiezas, mensaje_advertencia);
    printf("Mueve equipo 1:\n");
    piece_move(1, pz, array_size, numPiezas, preguntas, mensaje_advertencia, numPreguntas);
    //chequea si gana el Equipo 1
    if(wincheck(pz, numPiezas, 2)) {
      printf("Gano el equipo 1.\n");
      break;
    }
    strcpy(mensaje_advertencia, " ");
    printarray(pz, array_size, array,numPiezas, mensaje_advertencia);
    printf("Mueve equipo 2:\n");
    piece_move(2, pz, array_size, numPiezas, preguntas, mensaje_advertencia, numPreguntas);
    //chequea si gana el Equipo 2
    if (wincheck(pz, numPiezas, 1)) {
      printf("Gano el equipo 1.\n");
      break;
    }
  }
}


//funcion del menu
void game(int *numPreguntas, char **arshivo) {
    int game;
    int k;

    menu:
    printf("Bienvenido a las damas nashe!\n");
    printf("1- Jugar\n");
    printf("2- Elegir con cuantas preguntas jugar\n");
    printf("3- Salir\n");
    scanf("%d", &game);

    switch (game) {
        case 1:
            return;
            break;

        case 2:
            printf("1- 4 preguntas\n");
            printf("2- 20 preguntas\n");
            printf("3- 30 preguntas\n");
            printf("4- Metal Gear c:\n");
            scanf("%d", &k);

            switch (k) {
                case 1:
                    *numPreguntas = 4;
                    break;
                case 2:
                    *numPreguntas = 20;
                    break;
                case 3:
                    *numPreguntas = 30;
                    break;
                case 4:
                    *arshivo = "metalgear.txt";
                    *numPreguntas = 1;
                    break;
            }

            system("cls");
            goto menu;
            break;

        case 3:
            return;
            break;
    }
}


int main(void) {

  srand(time(NULL));
  char *arshivo = "preguntas.txt";
  int numPreguntas;
  int array_size = 10;
  char array[array_size][array_size];
  int numPiezas = 40;
  game(&numPreguntas, &arshivo);
  struct pregunta *preguntas = malloc(numPreguntas * sizeof(struct pregunta));
  struct piezas *pz = malloc(numPiezas * sizeof(struct piezas));
  asignarDesdeArchivo(preguntas, numPreguntas,arshivo );
  asignarDesdeArchivoPiezas(pz,numPiezas,"pieza.txt");
  juego(pz, numPiezas, array_size, array, preguntas, numPreguntas);

  return 0;

  	return 0;
}
