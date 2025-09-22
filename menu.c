#include "menu.h"
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "jugador.h"

void mostrarPantallaPresentacion(SDL_Renderer * renderer)
{
    TTF_Init();
    // Cargar fuente
    TTF_Font * font = TTF_OpenFont ("fnt/BitcountGridSingle_Cursive-Regular.ttf",32);
    if (!font) {
        printf("Error cargando fuente: %s\n", TTF_GetError());
        return;
    }
    //color texto: blanco
    SDL_Color color = {255, 255, 255};
    // Crear superficie con el texto
    SDL_Surface *surface = TTF_RenderText_Solid(font, "Bienvenido al juego!", color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect dst = {200, 200, surface->w, surface->h}; // 100 y 200 son las coordenadas de la pantalla, w y h del surface son el ancho y alto del texto

    SDL_FreeSurface(surface); //libero el bit map que se creó en la ram, ya que se creó la textura que necesitaba

    // Dibujar fondo y texto
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, texture, NULL, &dst);
    SDL_RenderPresent(renderer);

    // Esperar unos segundos
    SDL_Delay(3000);
    SDL_RenderClear(renderer);

    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
    TTF_Quit();

}

void solicitarNombreJugador(SDL_Renderer * renderer, Jugador* jugador)
{
    char nombreJugador[30];

    SDL_StartTextInput(); //  habilita entrada de texto
    TTF_Init();
    TTF_Font * font = TTF_OpenFont ("fnt/SUSEMono-Medium.ttf",32);
    if (!font) {
        printf("Error cargando fuente: %s\n", TTF_GetError());
        return;
    }
    //color texto: celeste
    SDL_Color color = {135, 246, 255};
    SDL_Color color2 = {240, 255, 255};

    SDL_Event e;
    int corriendo = 1; //bandera del while
    int cursor = 0;
    nombreJugador[0] = '\0';

    while (corriendo)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                {corriendo = 0;}
            else {
                if (e.type == SDL_TEXTINPUT)
                    {
                        if (cursor < TAM_NOMBRE - 1)
                            {
                                strcat(nombreJugador, e.text.text);
                                cursor += strlen(e.text.text);
                            }
                    }

                else {
                    if (e.type == SDL_KEYDOWN)
                    {
                        if (e.key.keysym.sym == SDLK_BACKSPACE && cursor > 0)
                        {
                            nombreJugador[--cursor] = '\0';
                        } else {
                            if (e.key.keysym.sym == SDLK_RETURN && cursor > 0)
                            { corriendo = 0; }}
                    }}
            }
        }

        // Mensaje de ayuda
        SDL_Surface *ayudaSurface = TTF_RenderText_Solid(font, "-> Ingresá tu nombre y presioná Enter", color);
        SDL_Texture *ayudaTexture = SDL_CreateTextureFromSurface(renderer, ayudaSurface);
        SDL_Rect ayudaRect = {50, 10, ayudaSurface->w, ayudaSurface->h};
        SDL_RenderCopy(renderer, ayudaTexture, NULL, &ayudaRect);
        SDL_FreeSurface(ayudaSurface);
        SDL_DestroyTexture(ayudaTexture);

        // Mostrar nombre ingresado
        if (strlen(nombreJugador) > 0) {
            SDL_Surface *textoSurface = TTF_RenderText_Solid(font, nombreJugador, color2);
            SDL_Texture *textoTexture = SDL_CreateTextureFromSurface(renderer, textoSurface);
            SDL_Rect destino = {50, 50, textoSurface->w, textoSurface->h};
            SDL_RenderCopy(renderer, textoTexture, NULL, &destino);
            SDL_FreeSurface(textoSurface);
            SDL_DestroyTexture(textoTexture);
        }


        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);

    }

    crearJugador(jugador,nombreJugador);

    printf("%s",jugador->nombre);

    TTF_CloseFont(font);
    TTF_Quit();
    SDL_StopTextInput();
    //  desactiva entrada de texto
}

