#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#define TAM_NOMBRE 30
#include "jugador.h"

void mostrarPantallaPresentacion(SDL_Renderer * renderer);
void solicitarNombreJugador(SDL_Renderer * renderer, Jugador* jugador);

#endif // MENU_H_INCLUDED

/*
                    SDL_Window: Representa una ventana del sistema operativo.
                    Flags (resizable, fullscreen, borderless, etc.)

SDL_Window* SDL_CreateWindow(const char* title, int x, int y, int w, int h, Uint32 flags);
void SDL_DestroyWindow(SDL_Window* window);
void SDL_ShowWindow(SDL_Window* window);
void SDL_HideWindow(SDL_Window* window);

                    SDL_Renderer:Representa el motor de renderizado (dibujado) de una ventana. Es el intermediario entre tu código y la GPU.

SDL_Renderer* SDL_CreateRenderer(SDL_Window* window, int index, Uint32 flags);
void SDL_DestroyRenderer(SDL_Renderer* renderer);
void SDL_SetRenderDrawColor(SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
void SDL_RenderClear(SDL_Renderer* renderer);
void SDL_RenderPresent(SDL_Renderer* renderer);  // Muestra lo que dibujaste



*/
