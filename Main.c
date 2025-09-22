#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "menu.h"
#include "jugador.h"


#define ALTO_VENTANA 768
#define ANCHO_VENTANA 1366
#define ERROR_VENTANA 1

int main(int argc, char *argv[])
{
    ////creo la ventana donde se interactúa con el juego
    Jugador jugador;
    char nombreVentana[100];
    sprintf(nombreVentana, "Simon");
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    /*
    if (TTF_Init() == -1) {
    printf("Error inicializando SDL_ttf: %s\n", TTF_GetError());
    return 1;
}*/

    SDL_Window *ventana = SDL_CreateWindow(nombreVentana,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,
                                           ANCHO_VENTANA,ALTO_VENTANA,SDL_WINDOW_SHOWN);
    if(!ventana)
    {
        printf("Error al crear ventana: %s\n", SDL_GetError());
        return ERROR_VENTANA;
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(ventana, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND); //justifica usarlo?

    // Pantalla de presentación
    mostrarPantallaPresentacion(renderer);

    // Solicitar nombre del jugador
    solicitarNombreJugador(renderer, &jugador);
/*
    // Mostrar menú y obtener configuración
    Configuracion config = mostrarMenuConfiguracion(renderer);

    // Loop principal del juego
    int corriendo = 1;
    while (corriendo) {
        corriendo = ejecutarJuego(renderer, &config, nombreJugador);
    }

    // Mostrar estadísticas
    mostrarEstadisticas(renderer, nombreJugador);

*/

// Liberar recursos
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(ventana);
    //TTF_Quit();
    SDL_Quit();
    return 0;
}

