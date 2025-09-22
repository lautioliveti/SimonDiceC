#ifndef JUGADOR_H_INCLUDED
#define JUGADOR_H_INCLUDED
#define TAM_NOMBRE 30

typedef struct {
    char nombre[TAM_NOMBRE];
    int puntaje;   // por si querés guardar más info
} Jugador;

// Crea un jugador inicializado
void crearJugador(Jugador* j,const char* nombre);

// Setea el nombre del jugador


#endif // JUGADOR_H_INCLUDED
