#ifndef JUGADOR_H_INCLUDED
#define JUGADOR_H_INCLUDED

#define TAM_NOMBRE 30
#include <stdlib.h>

typedef struct {
    char nombre[TAM_NOMBRE];
    int puntaje;   // por si queres guardar mas info
} Jugador;

typedef struct{
    Jugador jugador;
    size_t cantNotas;

}Estadisticas;


// Crea un jugador inicializado
void crearJugador(Jugador* j,const char* nombre);
int cargarMejorEstadistica(const char *nombreJugador, size_t cantNotas, Estadisticas *mejor);
void guardarEstadistica(const Estadisticas *actual);
void mostrarTopEstadisticasSDL(SDL_Renderer *renderer, size_t cantNotasFiltrar);
int compararEstadisticas(const void *a, const void *b);

#endif // JUGADOR_H_INCLUDED
