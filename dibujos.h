#ifndef DIBUJOS_H_INCLUDED
#define DIBUJOS_H_INCLUDED
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>


#define TAM_PIXEL 10
#define TAM_GRILLA 4
#define PX_PADDING 4

#define N 0 // Negro
#define A 1 // Amarillo
#define B 2 // Blanco
#define V 3 // Verde
#define R 4 // Rojo
#define T 5 // Transparente
#define COL 7
void dibujar(SDL_Renderer *renderer, const int[][COL], int oX, int oY,size_t tam_pixel);
void borrarPantalla(SDL_Renderer *renderer, SDL_Color color);
void mostrarTexto(SDL_Renderer *renderer, const char* texto ,TTF_Font *font, int oX, int oY, SDL_Color color);

#endif // DIBUJOS_H_INCLUDED
