#include "tateti.h"

int main(int arg, char *argv[]) {
    if(arg != 3){
        printf("\033[33mCantidad de argumentos invalida\033[0m\n");
        return 1;
    }

    Jugador j1,j2,jActual;
    srand(time(NULL));
    completarEstructura(&j1,&j2,argv);
    
    if((rand() % 2 + 1) % 2 == 0)
        jActual = j1;
    else
        jActual = j2;

    char tableroGeneral[3][3], tablero[9][9];
    crearTablero(tablero);
    crearTableroG(tableroGeneral);
    imprimirTablero(tablero);

    printf("¡Bienvenidos al juego ultra-tateti! Se enfrenta %s contra %s\n\n", j1.nombre, j2.nombre);
    int nroTablero = escogerTableros(jActual),b=1;

    while (1) {
        system(limpiar);
        imprimirTablero(tablero);
        int resultadoGeneral = comprobarGeneral(tableroGeneral);
        
        if (comprobarPosibilidad(tablero, nroTablero)||resultadoGeneral==2) {
            
            if (resultadoGeneral==1) {
                printf("\n\nFelicitaciones %s, ganaste!\n", jActual.nombre);
                FILE *archivo2 = fopen(argv[2], "w");
                if (archivo2 != NULL) {
                    fprintf(archivo2, "Ganador: %s", jActual.nombre);
                    fclose(archivo2);
                } else {
                    printf("\n\033[33mError al abrir el archivo %s para imprimir el ganador\033[0m\n", argv[2]);
                }
                return 0;
            } else if (resultadoGeneral == 2) {
                printf("\n\nEmpate!");
                return 0;
            }

            if(!b)
                jActual = (jActual.ficha == j1.ficha) ? j2 : j1;
            else b=0;

            ponerFicha(tablero, jActual, &nroTablero, tableroGeneral);
            imprimirTablero(tablero);
        } else if (!resultadoGeneral) {
            printf("\033[33mEl tablero nro %d ya esta finalizado.\033[0m\n",nroTablero);
            jActual = (jActual.ficha == j1.ficha) ? j2 : j1;
            nroTablero = escogerTableros(jActual);
            if(!comprobarPosibilidad(tablero, nroTablero))
                jActual = (jActual.ficha == j1.ficha) ? j2 : j1;
            b=1;
        }
    }
    return 0;
}

void completarEstructura(Jugador *j1, Jugador *j2, char *argv[]){
    FILE *archivo = fopen(argv[1], "r");
    if (archivo == NULL) {
        printf("\033[33mError al abrir el archivo de jugadores\033[0m\n");
        exit(1);
    }

    char *nombres[2];
    nombres[0] = malloc(sizeof(char) * 30);
    nombres[1] = malloc(sizeof(char) * 30);

    if (fscanf(archivo,"%s",nombres[0]) != 1) {
        printf("\033[33mError al leer el nombre del primer jugador\033[0m\n");
        free(nombres[0]);
        free(nombres[1]);
        fclose(archivo);
        exit(1);
    }
    

    if (fscanf(archivo,"%s",nombres[1]) != 1) {
        printf("\033[33mError al leer el nombre del segundo jugador\033[0m\n");
        free(nombres[0]);
        free(nombres[1]);
        fclose(archivo);
        exit(1);
    }

    if((rand() % 2 + 1) % 2 == 0){
        j1->ficha = 'X';
        strcpy(j1->nombre, nombres[0]);
        j2->ficha = 'O';
        strcpy(j2->nombre, nombres[1]);
    }
    else{
        j1->ficha = 'X';
        strcpy(j1->nombre, nombres[1]);
        j2->ficha = 'O';
        strcpy(j2->nombre, nombres[0]);
    }
    

    free(nombres[0]);
    free(nombres[1]);
    fclose(archivo);
}

void crearTablero(char tablero[][9]){
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
            tablero[i][j]= '*';
}
void crearTableroG(char tablero[][3]){
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            tablero[i][j]= '*';
}

void imprimirTablero(char tablero[][9]){
    printf("\n");
    for(int i = 0; i < 9; i ++){
        for(int j = 0; j < 9; j ++){
            if(tablero[i][j] == 'O')
                printf("\033[34m%c\033[0m", tablero[i][j]);
            else if(tablero[i][j] == 'X')
                printf("\033[1;31m%c\033[0m", tablero[i][j]);
            else if(tablero[i][j] == 'E')
                printf("\033[1;35m%c\033[0m", tablero[i][j]);
            else 
                printf("%c", tablero[i][j]);
            if(j == 2 || j == 5)
                printf(" | ");
        }
        if(i == 2 || i == 5){
            printf("\n");
            for(int p = 0; p < 15; p ++)
                printf("-");
        }
        printf("\n");
    }
}

int escogerTableros(Jugador jActual) {
    int eleccion;
    while (1) {
        if (jActual.ficha == 'O') {
            printf("\033[34m%s - O: \033[0m", jActual.nombre);
        } else {
            printf("\033[31m%s - X: \033[0m", jActual.nombre);
        }
        printf("Ingrese el tablero en el que desee jugar (1-9): ");
        int rango = scanf("%d", &eleccion);

        if (rango != 1) {
            printf("\033[33mEntrada no valida. Por favor, ingrese un numero entre 1 y 9.\033[0m\n");
        } else if (eleccion < 1 || eleccion > 9) {
            printf("\033[33mNumero de tablero invalido, intente de nuevo.\033[0m\n");
        } else {
            return eleccion;
        }

        // Descartar en caso de ser una entrada inválida
        while (getchar() != '\n');
    }
}

void ponerFicha(char tablero[][9], Jugador jActual, int *nroTablero, char tableroGeneral[][3]) {
    int pos, b = 1;
    while (b) {
        if (jActual.ficha == 'O')
            printf("\033[34m%s - O: \033[0m", jActual.nombre);
        else
            printf("\033[31m%s - X: \033[0m", jActual.nombre);
        printf("¿En que posicion del tablero %d desea poner la ficha?: ", *nroTablero);
        int resultado = scanf("%d", &pos);
        if (resultado != 1) {
            // Aca tambien, para descartar valores no validos
            while (getchar() != '\n');
            printf("\n\033[33mValor no valido. Por favor, ingrese un numero entre 1 y 9.\033[0m\n");
        } else if (pos > 9 || pos < 1) {
            printf("\n\033[33mNumero fuera de rango. Por favor, ingrese un numero entre 1 y 9.\033[0m\n");
        } else {
            int fila = ((*nroTablero - 1) / 3) * 3 + (pos - 1) / 3;
            int columna = ((*nroTablero - 1) % 3) * 3 + (pos - 1) % 3;

            if (comprobarPosicion(fila, columna, &b, tablero)) {
                tablero[fila][columna] = jActual.ficha;
                if (comprobarGanador(tablero, *nroTablero) == 1) {
                    rellenarTablero(tablero, *nroTablero, jActual.ficha);
                    tableroGeneral[(fila - (pos - 1) / 3) / 3][(columna - (pos - 1) % 3) / 3] = jActual.ficha;
                } else if (comprobarGanador(tablero, *nroTablero) == 2) {
                    rellenarTablero(tablero, *nroTablero, 'E');
                    tableroGeneral[(fila - (pos - 1) / 3) / 3][(columna - (pos - 1) % 3) / 3] = 'E';
                }
                b = 0;
            }
        }
    }
    *nroTablero = pos;
}

int comprobarPosicion(int fila, int columna, int *b, char tablero[][9]){
    if(tablero[fila][columna] == '*'){
        *b = 0;
        return 1;
    }
    printf("\033[33mYa esta ocupada la posicion que deseas jugar!\033[0m\n");
    return 0;
}

int comprobarGanador(char tablero[][9], int NsubTablero){
    int f = ((NsubTablero - 1) / 3) * 3, c = ((NsubTablero - 1) % 3) * 3;
    //comprobar filas
    for(int i = 0; i < 3; i ++)
        if(tablero[i + f][c] == tablero[i + f][c + 1] && tablero[i + f][c] == tablero[i + f][c + 2] && tablero[f + i][c] != '*')
            return 1;
    //comprobar columnas
    for(int i = 0; i < 3; i ++)
        if(tablero[f][i + c] == tablero[f + 1][i + c] && tablero[f][i + c] == tablero[f + 2][i + c] && tablero[f][c + i] != '*')
            return 1;
    //comprobar diagonales
    if(tablero[f][c] == tablero[f + 1][c + 1] && tablero[f][c] == tablero[f + 2][c + 2] && tablero[f][c] != '*')
        return 1;
    if(tablero[f][c + 2] == tablero[f + 1][c + 1] && tablero[f][c + 2] == tablero[f + 2][c] && tablero[f][c + 2] != '*')
        return 1;
    //comprobar empate
    if(!comprobarPosibilidad(tablero, NsubTablero))
        return 2;
    return 0;
}

void rellenarTablero(char tablero[][9], int Ntablero, char ganador){
    int fila = ((Ntablero - 1) / 3) * 3, columna = ((Ntablero - 1) % 3) * 3;
    for(int i = 0; i < 3; i ++)
        for(int j = 0; j < 3; j ++)
            tablero[i + fila][j + columna] = ganador;
}

int comprobarPosibilidad(char tablero[][9], int nro){
    int f = ((nro - 1) / 3) * 3, c = ((nro - 1) % 3) * 3;
    for(int i = 0; i < 3; i ++)
        for(int j = 0; j < 3; j ++)
            if(tablero[f + i][c + j] == '*')
                return 1;
    return 0;
}

int comprobarGeneral(char tG[][3]){
    //comprobar filas
    for (int i = 0; i < 3; i++)
        if ((tG[i][0] == tG[i][1] && tG[i][0] == tG[i][2] && tG[i][0] != '*') ||
            (tG[i][0] == 'E' && tG[i][1] == tG[i][2] && tG[i][1] != '*') ||
            (tG[i][1] == 'E' && tG[i][0] == tG[i][2] && tG[i][0] != '*') ||
            (tG[i][2] == 'E' && tG[i][0] == tG[i][1] && tG[i][0] != '*'))
            return 1;

    //comprobar columnas
    for (int i = 0; i < 3; i++)
        if ((tG[0][i] == tG[1][i] && tG[0][i] == tG[2][i] && tG[0][i] != '*') ||
            (tG[0][i] == 'E' && tG[1][i] == tG[2][i] && tG[1][i] != '*') ||
            (tG[1][i] == 'E' && tG[0][i] == tG[2][i] && tG[0][i] != '*') ||
            (tG[2][i] == 'E' && tG[0][i] == tG[1][i] && tG[0][i] != '*'))
            return 1;

    //comprobar diagonales
    if ((tG[0][0] == tG[1][1] && tG[0][0] == tG[2][2] && tG[0][0] != '*') ||
        (tG[0][0] == 'E' && tG[1][1] == tG[2][2] && tG[1][1] != '*') ||
        (tG[1][1] == 'E' && tG[0][0] == tG[2][2] && tG[0][0] != '*') ||
        (tG[2][2] == 'E' && tG[0][0] == tG[1][1] && tG[0][0] != '*') ||
        (tG[0][2] == tG[1][1] && tG[0][2] == tG[2][0] && tG[0][2] != '*') ||
        (tG[0][2] == 'E' && tG[1][1] == tG[2][0] && tG[1][1] != '*') ||
        (tG[1][1] == 'E' && tG[0][2] == tG[2][0] && tG[0][2] != '*') ||
        (tG[2][0] == 'E' && tG[0][2] == tG[1][1] && tG[0][2] != '*'))
        return 1;

    //comprobar empate
    for(int i = 0; i < 3; i ++)
        for(int j = 0; j < 3; j ++)
            if(tG[i][j] == '*')
                return 0;
    return 2;
}