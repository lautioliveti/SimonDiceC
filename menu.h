#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#define ALTO_VENTANA 720
#define ANCHO_VENTANA 1240

#define SALIR 0
#define MENU 1
#define SCHORNBERG 2
#define DESAFIO 3
#define MOZART 4
#define ESTADISTICAS 5
#define TAM_NOMBRE 30
#define MAX_ARCH 5
#define TAMANIO_ARCHIVO_WINDOWS 21

#define PIANO 1
#define CP70 2

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>


#include "jugador.h"
#include "dibujo.h"
#include "interfaz_Juego.h"





typedef struct {
    int cantNotas;
    int duracionIni;
    int timbre;
} ConfiguracionSch;

typedef struct{
    int cantNotas;
    int duracionIni;
    int timbre;
    char* archivo;
}ConfiguracionMoz;

typedef struct{
    int cantNotas;
    int timbre;
}ConfiguracionDes;

int mostrarMenuConfiguracionSchornberg(SDL_Renderer* renderer,ConfiguracionSch *config);
int mostrarMenuConfiguracionMoz (SDL_Renderer* renderer, ConfiguracionMoz *config);
int mostrarMenuConfiguracionDes (SDL_Renderer* renderer, ConfiguracionDes *config);
void mostrarErrorMozart(SDL_Renderer * renderer);


void mostrarMenuEstadisticas(SDL_Renderer *renderer);
int mostrarMenuInicial(SDL_Renderer* renderer);
void mostrarPantallaPresentacion(SDL_Renderer * renderer);
void solicitarNombreJugador(SDL_Renderer * renderer, Jugador* jugador);
void esperarCierreModo();

#endif // MENU_H_INCLUDED
