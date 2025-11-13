#ifndef MODOS_H_INCLUDED
#define MODOS_H_INCLUDED

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "jugador.h"
#include "interfaz_Juego.h"
#include "menu.h"
#include "dibujo.h"
#include "modos.h"
#include "sonido.h"
#include <stdbool.h>


#define MAX_SECUENCIA 100
#define RETRASO_LUZ 400
#define RETRASO_ENTRE_LUCES 150


void modoSchornberg(Jugador *jugador, ConfiguracionSch *configSc, SDL_Window *ventana, SDL_Renderer *renderer);
bool verificarSecuenciaMaxima(SDL_Renderer *renderer, int longitudSecuencia, int maxSecuencia, TTF_Font *font);
void mostrarGameOver(SDL_Renderer *renderer, Jugador *jugador,TTF_Font *font);
void mostrarPuntajeActual(SDL_Renderer *renderer, Jugador *jugador, TTF_Font *font);
void mostrarSecuenciaDesafio(SDL_Renderer *renderer, int secuencia[], int longitud, int cantNotas, TTF_Font *font);

int modoDesafio(Jugador *jugador, ConfiguracionDes *configDes, SDL_Window *ventana, SDL_Renderer *renderer);
char* obtenerNombreNota(int indice, int cantNotas);
void guardarMelodiaDesafio(const char *nombreArchivo, int *secuencia, int longitud, int cantNotas);

int modoMozart(Jugador *jugador, ConfiguracionMoz *configSc, SDL_Window *ventana, SDL_Renderer *renderer);
int obtenerIntNota(char notaString[], int cantidadNotas) ;
void obtenerArrayNotas(ConfiguracionMoz *config, int *largoSecuencia, int secuencia[],FILE* ptrCancionTxt);
void buscarNombreArchivo(SDL_Renderer* renderer, ConfiguracionMoz* config);


#endif // MODOS_H_INCLUDED
