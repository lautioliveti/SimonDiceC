#ifndef SONIDO_H_INCLUDED
#define SONIDO_H_INCLUDED

#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include "menu.h"

Mix_Chunk **inicializarAudio(int cantNotas,int timbre);
void reproducirSonido(Mix_Chunk **sonidos,int indice,size_t cantNotas);
void destruirAudio(Mix_Chunk **sonidos,size_t cantNotas);
void timbreCP70(Mix_Chunk **sonidos,int cantNotas);
void timbrePiano(Mix_Chunk **sonidos,int cantNotas);


#endif // SONIDO_H_INCLUDED
