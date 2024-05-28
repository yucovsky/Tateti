Juego creado por Julian Vaccari y Francisco Yucovsky

Estructura del Juego
Jugador: Estructura con la ficha ('X' o 'O') y el nombre del jugador.
Tablero Grande: Matriz 9x9 que representa el área de juego.
Tablero General: Matriz 3x3 que guarda el estado de cada sub-tablero (ganado o empatado).


Funciones:

completarEstructura: Accede al archivo dado como argumento con los nombres, comprueba que esten ambos y los asigna a las estructuras de los jugadores usando memoria dinamica.

Crear Tableros:
crearTablero: Inicializa el tablero grande con asteriscos.
crearTableroG: Inicializa el tablero general con asteriscos.

Imprimir Tablero:
imprimirTablero: Muestra el tablero grande en la consola.

Interacción del Jugador:
escogerTableros: Permite al jugador elegir un sub-tablero.
ponerFicha: Coloca la ficha del jugador en la posición seleccionada.

Verificación de Juego:
comprobarPosicion: Verifica si una posición está libre.
comprobarGanador: Verifica si hay un ganador en un sub-tablero.
comprobarGeneral: Verifica el estado del tablero general.
comprobarPosibilidad: Verifica si hay movimientos posibles en un sub-tablero.
rellenarTablero: Marca un sub-tablero completo con la ficha del ganador o 'E' para empate.

Cómo Ejecutar:
Compilar:
gcc main.c -o tateti

Ejecutar:
./tateti (archivo_entrada) (archivo_salida)
(archivo_entrada): Archivo con los nombres de los jugadores. Este archivo debe contener los nombres de los dos jugadores, uno por línea.
(archivo_salida): Archivo donde se guardará el nombre del ganador.
