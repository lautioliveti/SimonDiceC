#include "jugador.h"
#include <string.h>

void crearJugador(Jugador* j,const char* nombre) {
    strncpy(j->nombre, nombre, TAM_NOMBRE - 1);
    j->nombre[TAM_NOMBRE - 1] = '\0'; // seguridad
    j->puntaje = 0;
}


