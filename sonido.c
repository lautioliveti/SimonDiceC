#include "sonido.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <math.h>
Mix_Chunk* canalesArray[8] = {NULL};
void liberarChunk(Mix_Chunk* tono) {
free(tono->abuf);
free(tono);
}
void liberarSonido(int canal) {
    liberarChunk(canalesArray[canal]);
    canalesArray[canal] = NULL;
    printf("\nHa dejado de sonar la nota");
}
void charReproducirTono(char nombreNota[],  int tiempoMS) {
    static const sonidoDiccionario sonidos[] = {
        {"do", 261.63}, {"do#", 277.18}, {"reb", 277.18},
        {"re", 293.66}, {"re#", 311.13}, {"mib", 311.13},
        {"mi", 329.63},
        {"fa", 349.23}, {"fa#", 369.99}, {"solb", 369.99},
        {"sol", 392.00}, {"sol#", 415.30}, {"lab", 415.30},
        {"la", 440.00}, {"la#", 466.16}, {"sib", 466.16},
        {"si", 493.88},
        {"doAgudo", 523.26}
    };
    for(int i = 0; i < sizeof(sonidos) / sizeof(sonidos[0]); i++)
    if(strcmp(nombreNota, sonidos[i].nombre) == 0) {
            printf("\nSonando la nota: %s -> %f HZ", sonidos[i].nombre, sonidos[i].freq);
            crearTono(sonidos[i].freq, tiempoMS);
    }
}


void crearTono(float frecuenciaNota, int tiempoMS) {
    Mix_Chunk* tono;
    int canalUsado = 0;

    int tiempo = tiempoMS * 2; // tiempo en milisegundos (MS)
    int cantidadMuestras = (tiempo * FREQ_MUESTREO)/1000; //cuantas fotos totales vamos a tomar, se parte por mil para que sea todo en MS
    int tamBuffer = cantidadMuestras * sizeof(short); // en bytes
    short *buffer = malloc(tamBuffer);

    for(int i = 0; i < cantidadMuestras; i++) {
        buffer[i] = VOLUMEN * sin( 2 * M_PI * frecuenciaNota * i / FREQ_MUESTREO);
    }

    tono = malloc(sizeof(Mix_Chunk));
    tono->alen = tamBuffer; // cantidad de bytes del buffer de audio
    tono->abuf = (unsigned char*)buffer;
    tono->volume = MIX_MAX_VOLUME;

    canalUsado = Mix_PlayChannel(-1, tono, 0);
    if(canalUsado != -1) canalesArray[canalUsado] = tono;
    else liberarChunk(tono);

}

void inicializarAudio() {
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 1, 2048);
    Mix_AllocateChannels(8);
    Mix_ChannelFinished(liberarSonido);
    }
