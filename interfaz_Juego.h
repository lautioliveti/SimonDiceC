#ifndef INTERFAZ_JUEGO_H_INCLUDED
#define INTERFAZ_JUEGO_H_INCLUDED

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "menu.h"
#include "jugador.h"
#include "dibujo.h"

#define tamanioMatriz 20

typedef struct{
    int activado;
    int dibujo[20][20];
    int offsetX;
    int offsetY;
    char *nota;
} ColorObj;

typedef struct {
    ColorObj verde1;
    ColorObj verde2;
    ColorObj rojo1;
    ColorObj rojo2;
    ColorObj azul1;
    ColorObj azul2;
    ColorObj amarillo1;
    ColorObj amarillo2;
    ColorObj violeta;
    ColorObj *arrayColores[9];
    char **escalaActual;
    int cantidadNotasEscala;
} NotasApp;

void presentarEscena(SDL_Renderer *renderer);
void prepararEscena(SDL_Renderer *renderer);
void esperar(size_t duracion, int *juegoActivo);
void renderMatriz(SDL_Renderer *renderer, ColorObj *colorobj, int tamPixelFinal);


void render3Notas(Jugador *jugador, SDL_Renderer *renderer, NotasApp *app);
void render4Notas(Jugador *jugador, SDL_Renderer *renderer, NotasApp *app);
void render5Notas(Jugador *jugador, SDL_Renderer *renderer, NotasApp *app);
void render6Notas(Jugador *jugador, SDL_Renderer *renderer, NotasApp *app);
void render7Notas(Jugador *jugador, SDL_Renderer *renderer, NotasApp *app);
void render8Notas(Jugador *jugador, SDL_Renderer *renderer, NotasApp *app);
void renderNotasGenerico(Jugador *jugador, size_t cantNotas, SDL_Renderer *renderer, NotasApp *app);




void inicializar3Notas(NotasApp *app);
void inicializar4Notas(NotasApp *app);
void inicializar5Notas(NotasApp *app);
void inicializar6Notas(NotasApp *app);
void inicializar7Notas(NotasApp *app);
void inicializar8Notas(NotasApp *app);
void inicializarNotasGenerico(NotasApp *app, size_t cantNotas);


#endif // INTERFAZ_JUEGO_H_INCLUDED
