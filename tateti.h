#ifndef TATETI_H
#define TATETI_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32_
  #define limpiar "cls"
#else
  #define limpiar "clear"
#endif

typedef struct {
    char ficha;
    char nombre[30];
}Jugador;

void crearTablero(char tablero[][9]);
void crearTableroG(char tablero[][3]);
void imprimirTablero(char tablero[][9]);
int escogerTableros(char tablero[][9]);
void ponerFicha(char tablero[][9], Jugador jActual, int *nroTablero, char tableroGeneral[][3]);
int comprobarPosicion(int fila, int columna, int *b, char tablero[][9]);
int comprobarGanador(char tablero[][9], int subTablero);
void rellenarTablero(char tablero[][9], int Ntablero, char ganador);
int comprobarPosibilidad(char tablero[][9], int nro);
int comprobarGeneral(char tG[][3]);

#endif
