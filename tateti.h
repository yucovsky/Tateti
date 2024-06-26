#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef _WIN32
    #define limpiar "cls"
#else
    #define limpiar "clear"
#endif

typedef struct {
    char ficha;
    char nombre[30];
}Jugador;

void completarEstructura(Jugador *p, Jugador *q, char *argv[]);
void crearTablero(char tablero[][9]);
void crearTableroG(char tablero[][3]);
void imprimirTablero(char tablero[][9]);
int escogerTableros(Jugador jActual);
void ponerFicha(char tablero[][9],Jugador jActual,int *nroTablero,char tableroGeneral[][3]);
int comprobarPosicion(int fila,int columna, int *b,char tablero[][9]);
int comprobarGanador(char tablero[][9],int subTablero);
void rellenarTablero(char tablero[][9],int Ntablero,char ganador);
int comprobarPosibilidad(char tablero[][9],int nro);
int comprobarGeneral(char tG[][3],Jugador *jActual,Jugador j1,Jugador j2);
