#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define DIM 11

#define MIN_X 0
#define MAX_X 9

#define MIN_Y 65
#define MAX_Y 74

typedef struct PLAYER{
   int x;
   char y;
   int puntaje;
   char **tablero;
}Jugador;


/*Prototipos de las funciones*/
void GotoXY(int x, int y);
void ImprimirTablero(char **tablero, int x);
char **Text2Mat(char *fp);
int char2int(char c);
int VerificaBarco(Jugador player, char **tabl, char *fp);
char **freeM(char **m);
void Inicio();


/*Función principal*/
int main(){
   Jugador Yo;
   Jugador CPU;

   char **Inicial = Text2Mat("TABLERO.txt");

   char **TablIniYo = Text2Mat("TableroInicialYo.txt");
   char **TablIniCPU = Text2Mat("TableroInicialYo.txt");

   Yo.tablero = Text2Mat("TableroJugador.txt");
   CPU.tablero = Text2Mat("TableroCPU.txt");

   Yo.puntaje = 0;
   CPU.puntaje = 0;

   int i=0, k=0;

   Inicio();

   while(Yo.puntaje != 20 && CPU.puntaje != 20){
        ImprimirTablero(TablIniYo, 0);
        ImprimirTablero(TablIniCPU, 24);

        GotoXY(11, 15);
        printf("%d", Yo.puntaje);
        GotoXY(37, 15);
        printf("%d", CPU.puntaje);

        GotoXY(1, 19);
        printf("Coordenada en x: ");
        scanf(" %d", &Yo.x);
        GotoXY(1, 20);
        printf("Coordenada en y: ");
        scanf(" %c", &Yo.y);

        i = VerificaBarco(Yo, TablIniYo, "TableroInicialYo.txt");
        if(i == 1) Yo.puntaje++;

        getchar();

        do{
           CPU.x = MIN_X + rand() % (MAX_X - MIN_X);
           CPU.y = (char) (MIN_Y + rand() % (MAX_Y - MIN_Y));
        }while(CPU.tablero[char2int(CPU.y)+1][CPU.x+1] != 'x' && CPU.tablero[char2int(CPU.y)+1][CPU.x+1] != '~');

        k = VerificaBarco(CPU, TablIniCPU, "TableroInicialCPU.txt");

        if(k == 1) CPU.puntaje++;

        GotoXY(1, 23);
        printf("%d %c", CPU.x, CPU.y);

        GotoXY(1, 19);
        printf("                             ");
        GotoXY(1, 20);
        printf("                             ");


   }

   getchar();

   if(Yo.puntaje == 20){
      GotoXY(15, 22);
      printf("GANASTE OWO");
   }

   else{
      GotoXY(15, 22);
      printf("PERDISTE UnU");
   }

   RegresarTablero(Inicial, "TableroInicialYo.txt");
   RegresarTablero(Inicial, "TableroInicialCPU.txt");

   freeM(TablIniCPU);
   freeM(TablIniYo);
   freeM(Yo.tablero);
   freeM(CPU.tablero);

   getchar();
   return 0;
}

void Inicio(){
   GotoXY(13, 12);
   printf("B A T T L E S H I P");

   GotoXY(1, 14);
   printf("Puntaje del Jugador");

   GotoXY(27, 14);
   printf("Puntaje del CPU");


   GotoXY(48, 1);
   printf("Instrucciones:");
   GotoXY(48, 2);
   printf("Si la coordenada dice 'x', le");
   GotoXY(48, 3);
   printf("has atinado a una parte del");
   GotoXY(48, 4);
   printf("barco oponente. De lo contrario,");
   GotoXY(48, 5);
   printf("le has atinado a pura agua.");
   GotoXY(48, 7);
   printf("Ganas hasta tener 20 de puntaje.");
}

void RegresarTablero(char **m, char *fp){
   FILE *tab = fopen(fp, "w");
   int i=0, j=0;

   for(i=0; i < DIM; i++){
      for(j=0; j < DIM; j++){
         fprintf(tab, "%c", m[i][j]);
      }
      fprintf(tab, "\n");
   }
   fclose(tab);
}

int VerificaBarco(Jugador player, char **tabl, char *fp){
   int y = char2int(player.y);
   FILE *txt = fopen(fp, "w");
   int i=0, j=0;

   if(txt == NULL){
      printf("Error al abrir archivo");
      return 0;
   }

   if(player.tablero[y+1][player.x+1] == 'x'){
      tabl[y+1][player.x+1] = 'x';

      for(i=0; i < DIM; i++){
         for(j=0; j < DIM; j++){
            fprintf(txt, "%c", tabl[i][j]);
         }
         fprintf(txt, "\n");
      }
      fclose(txt);
      return 1;
    }

   else {
      tabl[y+1][player.x+1] = 'o';
      return 0;
      for(i=0; i < DIM; i++){
         for(j=0; j < DIM; j++){
            fprintf(txt, "%c", tabl[i][j]);
         }
         fprintf(txt, "\n");
      }
      fclose(txt);
      return 0;
   }
}

char **freeM(char **m){
	int i=0;
	for(i ; i < DIM; i++) free(m[i]);

    free(m);
    return m;
}

int char2int(char c){
   int r;
   switch(c){
      case 'A':
         r = 0;
         break;
      case 'B':
         r=1;
         break;
      case 'C':
         r=2;
         break;
      case 'D':
         r=3;
         break;
      case 'E':
         r=4;
         break;
      case 'F':
         r=5;
         break;
      case 'G':
         r=6;
         break;
      case 'H':
         r=7;
         break;
      case 'I':
         r=8;
         break;
      case 'J':
         r=9;
         break;
   }

   return r;
}

char **Text2Mat(char *fp){
   char **m = NULL;
   FILE *tabl = fopen(fp, "r");
   int i=0, j=0;


   //Si el archivo no abre
   if(tabl == NULL){
      GotoXY(11, 6);
      printf("Error al abrir archivo");
      return m;
   }

   //Memoria dinámica para la matriz
   m = (char **) malloc(DIM * sizeof(char *));
      for (i = 0; i < DIM; i++) {
         m[i] = (char *) malloc(DIM * sizeof(char));
    }

   //Si no hay memoria
   if(m == NULL){
      GotoXY(11, 5);
      printf("Error de memoria");
      return m;
   }

   //Rellenar la matriz con el archivo txt
   for(i=0; i<DIM; i++){
      for(j=0; j<DIM; j++){
         m[i][j]=getc(tabl);
      }
      getc(tabl);
   }

   fclose(tabl);
   return m;
}

void ImprimirTablero(char **tablero, int x){
   int i=0, k=0, j=0;

   for(i=0; i < DIM; i++){
      for(k=0, j=0; k < 2*DIM; k+=2, j++){
         GotoXY(k + x, i);
         printf("%c ", tablero[i][j]);
      }
   }
}

void GotoXY(int x, int y){
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
