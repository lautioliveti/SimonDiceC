#ifndef SONIDO_H_INCLUDED
#define SONIDO_H_INCLUDED
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#define FREQ_MUESTREO 44100
#define VOLUMEN 1000
typedef struct {
    char *nombre;
    float freq;
}
sonidoDiccionario;
void charReproducirTono(char nombreNota[], int tiempoMS);
void liberarChunk(Mix_Chunk* tono);
void liberarSonido(int canal);
void inicializarAudio();
void crearTono(float frecuenciaNota, int tiempoMS);
#endif // SONIDO_H_INCLUDED
