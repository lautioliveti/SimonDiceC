//Apellido: Cardella, Octavio
//DNI: 44141070
//Entrega: Sí

//Apellido: Oliveti, Lautaro Nahuel
//DNI: 43863497
//Entrega: Sí

//Apellido: Valdevieso, Rocio Elizabeth
//DNI: 44588998
//Entrega: Sí

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "menu.h"
#include "jugador.h"
#include "interfaz_Juego.h"
#include "modos.h"

#define ERROR_VENTANA 1

int main(int argc, char *argv[])
{
    ////creo la ventana donde se interactua con el juego
    char nombreVentana[20];
    sprintf(nombreVentana, "Simon");
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    SDL_Window *ventana = SDL_CreateWindow(nombreVentana,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,ANCHO_VENTANA,ALTO_VENTANA,SDL_WINDOW_SHOWN);

    if(!ventana)
    {
        printf("Error al crear ventana: %s\n", SDL_GetError());
        return ERROR_VENTANA;
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(ventana, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND); //justifica usarlo?

    Jugador jugador;
    int corriendo = 1;

    mostrarPantallaPresentacion(renderer);
    solicitarNombreJugador(renderer,&jugador);

    int estadoActual=MENU;
    while(corriendo)
        {
            switch(estadoActual)
            {
                case MENU:
                    {
                        estadoActual= mostrarMenuInicial(renderer);
                        break;
                    }
                case SCHORNBERG:
                    {
                        ConfiguracionSch configSc;
                        estadoActual=mostrarMenuConfiguracionSchornberg(renderer,&configSc);
                        //(restaurar luego) printf("%s, %d, %d\n",jugador.nombre,configSc.cantNotas,configSc.duracionIni);
                        if(estadoActual==SCHORNBERG)
                        {
                            modoSchornberg(&jugador, &configSc, ventana, renderer);
                        }
                        esperarCierreModo();
                        estadoActual=MENU;
                        break;
                    }
                case DESAFIO:
                    {
                        ConfiguracionDes configDes;
                        estadoActual=mostrarMenuConfiguracionDes(renderer,&configDes);
                        //(restaurar luego) printf("%s, %d, %d\n",jugador.nombre,configDes.cantNotas, configDes.timbre);
                        if(estadoActual==DESAFIO)
                        {
                            modoDesafio(&jugador,&configDes,ventana,renderer);
                            //(restaurar luego) printf("jugando DESAFIO");
                        }
                        esperarCierreModo();
                        estadoActual=MENU;
                        break;
                    }
                case MOZART:
                    {
                        ConfiguracionMoz configMoz;
                        estadoActual=mostrarMenuConfiguracionMoz(renderer,&configMoz);
                        if(estadoActual==MOZART)
                        {
                            estadoActual=modoMozart(&jugador, &configMoz, ventana, renderer);
                            if(estadoActual==-1)
                            {
                                mostrarErrorMozart(renderer);
                            }
                            //(restaurar luego) printf("jugando MOZART");
                        }
                        esperarCierreModo();
                        estadoActual=MENU;
                        break;
                    }
                case ESTADISTICAS:
                    {
                        //Las estedisticas se manejan en menu.c
                        estadoActual = MENU;
                        break;
                    }
                case SALIR:
                    {
                        corriendo=0;
                        break;
                    }

            }
        }


// Liberar recursos
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(ventana);
    SDL_Quit();
    return 0;
}
