#include <stdio.h>
#include <string.h>

typedef struct {
    char ficha;
    char nombre[20];
}Jugador;

void crearTablero(char tablero[][9]);
void imprimirTablero(char tablero[][9]);
int escogerTableros();
void ponerFicha(char tablero[][9],int nroTablero,Jugador jActual);
int comprobarPosicion(int fila,int columna, int *b,char tablero[][9]);



int main() {
//int main(int argc, char *argv[]) {
// if (argc != 3) {
// printf("Cantidad de argumentos invalida \n");
// return 1;
// }

// FILE *file1, *file2;
// file1 = fopen(argv[1], "r");

    //guardar en dos instancias de estructura el nombre y ficha de cada jugador
    Jugador j1;
    j1.ficha='X';
    strcpy(j1.nombre,"nombre1");
    j1.nombre[sizeof(j1.nombre)-1]='\0';
    Jugador j2;
    j2.ficha='O';
    strcpy(j2.nombre,"nombre2");
    j2.nombre[sizeof(j2.nombre)-1]='\0';
    
    

    char tablero[9][9];
    crearTablero(tablero);
    imprimirTablero(tablero);


    //int b=1;
    for(int i=0;i<5;i++){
        Jugador jActual;
        if(i%2==0) jActual=j1;
        else jActual=j2;
        ponerFicha(tablero,escogerTableros(),jActual);
        imprimirTablero(tablero);

        //b=0;
    }

    return 0;
}

void crearTablero(char tablero[][9]){
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
            tablero[i][j]= '*';
}

void imprimirTablero(char tablero[][9]){
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            if(tablero[i][j]=='X')printf("\033[34m%c\033[0m", tablero[i][j]);
            else if(tablero[i][j]=='O')printf("\033[1;31m%c\033[0m", tablero[i][j]);
            else printf("%c", tablero[i][j]);
            if(j==2||j==5)printf(" | ");
        }
        if(i==2||i==5){
            printf("\n");
            for(int p=0;p<15;p++)
            printf("-");
        }
        printf("\n");
    }
}

int escogerTableros(){
    int eleccion;
    printf("Ingrese el tablero en el que desee jugar: ");
    scanf("%d",&eleccion);
    return eleccion;
}

void ponerFicha(char tablero[][9],int nroTablero,Jugador jActual){
    int pos,b=1;
    while(b){
        printf("En que posicion desea poner la ficha: ");
        scanf("%d",&pos);
        int fila=((nroTablero-1)/3)*3 + (pos-1)/3;
        int columna=((nroTablero-1)%3)*3 + (pos-1)%3;
        if(comprobarPosicion(fila,columna,&b,tablero)) tablero[fila][columna]=jActual.ficha;
        else nroTablero=escogerTableros();
    }
}

int comprobarPosicion(int fila,int columna, int *b,char tablero[][9]){
    if(tablero[fila][columna]=='*'){
        *b=0;
        return 1;
    }
    printf("\n\033[31mYa esta usada la posicion que deseas jugar!\033[0m\n");
    return 0;
}