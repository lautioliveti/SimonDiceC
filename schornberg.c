#include "menu.h"
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "jugador.h"
#include "Schornberg.h"
#include "sonido.h"

#define N 0 // Negro
#define A 1 // Amarillo
#define B 2 // Blanco
#define V 3 // Verde
#define R 4 // Rojo
#define T 5 // Transparente
#define AZ 6 // Azul
#define VI 7 // Violeta
#define TRANSPARENCIA_INICIAL 80
#define CAPACIDAD_INICIAL_HISTORIAL 2
#define tamanioMatriz 20


Uint32 apagarColorCallback(Uint32 intervalo, void* parametro)
{
    ColorObj *color = (ColorObj *)parametro;
    color->activado = 0;
    printf("\nColor apagado");
    return 0;
}

void inicializarHistorial(Secuencia *secuencia)
{
//    secuencia->arrayPtr = malloc(CAPACIDAD_INICIAL_HISTORIAL * sizeof(*ColorObj));
//    secuencia->capacidad = CAPACIDAD_INICIAL_HISTORIAL ;
//    secuencia->ce = 0;
}
void presentarEscena(SDL_Renderer *renderer)
{
    SDL_RenderPresent(renderer);
}
void registrarEntradas(NotasApp *app, int duracionMS)
{
    int tamPixelFinal = TAM_PIXEL +5;
    int tamBloque = tamPixelFinal*tamanioMatriz;
    int ce = sizeof(app->arrayColores) / sizeof(app->arrayColores[0]);
    SDL_Event e;

    while (SDL_PollEvent(&e))
    {
        for(int i = 0; i < ce; i++)
        {


//            if (e.type == SDL_MOUSEMOTION)
//            {
//                int mouseX = e.motion.x;
//                int mouseY = e.motion.y;
//                int ratioX = app->arrayColores[i]->offsetX;
//                int ratioY = app->arrayColores[i]->offsetY;
//                int xInicial = (ANCHO_VENTANA*ratioX -tamanioMatriz*tamPixelFinal*ratioX)/100;
//                int yInicial = (ALTO_VENTANA*ratioY-tamanioMatriz*tamPixelFinal*ratioY)/100;
//                if(
//                    mouseX > xInicial&&
//                    mouseX < xInicial+tamBloque &&
//                    mouseY > yInicial &&
//                    mouseY < yInicial +tamBloque
//                ) {
//                    if(app->arrayColores[i]->activado == 0) {
//                            //ACA ES CUANDO ENTRA POR PRIMERA VEZ - MOUSE_ENTER
//                            //printf("\nEntro por primera vez");
//                            charReproducirTono("do");
//                    }
//                    app->arrayColores[i]->activado = 1;
//                }
//                else {
//                    if(app->arrayColores[i]->activado == 1) {
//                        //ACA ES CUANDO SALE POR PRIMERA VEZ MOUSE_LEAVE
//                        //printf("\nSalio por primera vez");
//                        charReproducirTono("re");
//                    }
//                        app->arrayColores[i]->activado = 0;
//                }
//
//            }
            //EL IF PREVIO ES POR SI QUIEREN AGREGAR ANIMACION, DETECTA ENTRADA Y SALIDA DENTRO DE UN OBJETO
            if (e.type == SDL_MOUSEBUTTONDOWN)
            {
                int mouseX = e.button.x;
                int mouseY = e.button.y;
                int ratioX = app->arrayColores[i]->offsetX;
                int ratioY = app->arrayColores[i]->offsetY;
                int xInicial = (ANCHO_VENTANA*ratioX -tamanioMatriz*tamPixelFinal*ratioX)/100;
                int yInicial = (ALTO_VENTANA*ratioY-tamanioMatriz*tamPixelFinal*ratioY)/100;
                if(
                    mouseX > xInicial&&
                    mouseX < xInicial+tamBloque &&
                    mouseY > yInicial &&
                    mouseY < yInicial +tamBloque
                )
                {
                    if(app->arrayColores[i]->activado == 0)
                    {
                        printf("\ntono: %s", app->arrayColores[i]->nota);
                        charReproducirTono(app->arrayColores[i]->nota, duracionMS);
                        SDL_AddTimer(duracionMS, apagarColorCallback, app->arrayColores[i]);
                    }
                    app->arrayColores[i]->activado = 1;

                }

            }
            //EL IF PREVIO ES PARA LA DETECCION DE CLICKS SOBRE OBJETOS



        } //FIN DEL FOR


    }




}
void prepararEscena(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}
void renderMatriz(SDL_Renderer *renderer, ColorObj *colorobj, int tamPixelFinal)
{
    SDL_Color colores[] =
    {
        {0,   0,   0,   255}, // N[0] - Negro
        {255, 255, 0,   255}, // A[1] - Amarillo
        {255, 255, 255, 255}, // B[2] - Blanco
        {0,   150, 60,  255}, // V[3] - Verde
        {255,   0,  0,  255}, // R[4] - Rojo
        {0,   0,    0,    0}, // T[5] - Transparente
        {0, 0, 255, 255},     // AZ[6] - Azul
        {155, 0, 238, 255}         // VI[7] - Violeta
    };
    int transparencia = colorobj->activado? 255 : TRANSPARENCIA_INICIAL;
    int ratioX = colorobj->offsetX;
    int ratioY = colorobj->offsetY;
    int xInicial = (ANCHO_VENTANA*ratioX -tamanioMatriz*tamPixelFinal*ratioX)/100;
    int yInicial = (ALTO_VENTANA*ratioY-tamanioMatriz*tamPixelFinal*ratioY)/100;

    for (int y = 0; y < 20; y++)
    {
        for (int x = 0; x < 20; x++)
        {
            SDL_SetRenderDrawColor(renderer,
                                   colores[colorobj->dibujo[y][x]].r,
                                   colores[colorobj->dibujo[y][x]].g,
                                   colores[colorobj->dibujo[y][x]].b,
                                   colores[colorobj->dibujo[y][x]].a == 0 ? 0 : transparencia);
            SDL_Rect pixel = {x*tamPixelFinal+xInicial, y*tamPixelFinal+yInicial, tamPixelFinal, tamPixelFinal};
            SDL_RenderFillRect(renderer, &pixel);
        }
    }

}

void render3Notas(Jugador *jugador, ConfiguracionSch *configSc, SDL_Renderer *renderer, NotasApp *app)
{

    int tamPixelFinal = TAM_PIXEL +5;


    renderMatriz(renderer, &(app->verde1), tamPixelFinal);
    renderMatriz(renderer, &(app->rojo1), tamPixelFinal);
    renderMatriz(renderer, &(app->amarillo1), tamPixelFinal);

}
void render4Notas(Jugador *jugador, ConfiguracionSch *configSc, SDL_Renderer *renderer, NotasApp *app)
{


    int tamPixelFinal = TAM_PIXEL +5;


    renderMatriz(renderer, &(app->verde1), tamPixelFinal);
    renderMatriz(renderer, &(app->rojo1), tamPixelFinal);
    renderMatriz(renderer, &(app->azul1), tamPixelFinal);
    renderMatriz(renderer, &(app->amarillo1), tamPixelFinal);
}
void render5Notas(Jugador *jugador, ConfiguracionSch *configSc, SDL_Renderer *renderer, NotasApp *app)
{

    int tamPixelFinal = TAM_PIXEL +5;


    renderMatriz(renderer, &(app->verde1), tamPixelFinal);
    renderMatriz(renderer, &(app->rojo1), tamPixelFinal);
    renderMatriz(renderer, &(app->azul1), tamPixelFinal);
    renderMatriz(renderer, &(app->amarillo1), tamPixelFinal);
    renderMatriz(renderer, &(app->violeta), tamPixelFinal);
}
void render6Notas(Jugador *jugador, ConfiguracionSch *configSc, SDL_Renderer *renderer, NotasApp *app)
{

    int tamPixelFinal = TAM_PIXEL +5;

    renderMatriz(renderer, &(app->verde1), tamPixelFinal);
    renderMatriz(renderer, &(app->rojo1), tamPixelFinal);
    renderMatriz(renderer, &(app->amarillo1), tamPixelFinal);
    renderMatriz(renderer, &(app->verde2), tamPixelFinal);
    renderMatriz(renderer, &(app->azul1), tamPixelFinal);
    renderMatriz(renderer, &(app->amarillo2), tamPixelFinal);
}
void render8Notas(Jugador *jugador, ConfiguracionSch *configSc, SDL_Renderer *renderer, NotasApp *app)
{


    int tamPixelFinal = TAM_PIXEL +5;


    renderMatriz(renderer, &(app->verde1), tamPixelFinal);
    renderMatriz(renderer, &(app->rojo1), tamPixelFinal);
    renderMatriz(renderer, &(app->amarillo1), tamPixelFinal);
    renderMatriz(renderer, &(app->azul1), tamPixelFinal);

    renderMatriz(renderer, &(app->verde2), tamPixelFinal);
    renderMatriz(renderer, &(app->rojo2), tamPixelFinal);
    renderMatriz(renderer, &(app->amarillo2), tamPixelFinal);
    renderMatriz(renderer, &(app->azul2), tamPixelFinal);
}
void inicializar3Notas(NotasApp *app)
{
    ColorObj amarillo = {0, {
            {T, T, T, T, T, T, T, T, T, A, A, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, A, A, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, A, A, A, A, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, A, A, A, A, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, A, A, A, A, A, A, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, A, A, A, A, A, A, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, A, A, A, A, A, A, A, A, T, T, T, T, T, T},
            {T, T, T, T, T, T, A, A, A, A, A, A, A, A, T, T, T, T, T, T},
            {T, T, T, T, T, A, A, A, A, A, A, A, A, A, A, T, T, T, T, T},
            {T, T, T, T, T, A, A, A, A, A, A, A, A, A, A, T, T, T, T, T},
            {T, T, T, T, T, A, A, A, A, A, A, A, A, A, A, T, T, T, T, T},
            {T, T, T, T, A, A, A, A, A, A, A, A, A, A, A, A, T, T, T, T},
            {T, T, T, T, A, A, A, A, A, A, A, A, A, A, A, A, T, T, T, T},
            {T, T, T, A, A, A, A, A, A, A, A, A, A, A, A, A, A, T, T, T},
            {T, T, T, A, A, A, A, A, A, A, A, A, A, A, A, A, A, T, T, T},
            {T, T, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, T, T},
            {T, T, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, T, T},
            {T, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, T},
            {T, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, T},
            {A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A}
        }
    };

    ColorObj verde = {0, {
            {T, T, T, T, T, T, T, T, T, V, V, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, V, V, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, V, V, V, V, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, V, V, V, V, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, V, V, V, V, V, V, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, V, V, V, V, V, V, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, V, V, V, V, V, V, V, V, T, T, T, T, T, T},
            {T, T, T, T, T, T, V, V, V, V, V, V, V, V, T, T, T, T, T, T},
            {T, T, T, T, T, V, V, V, V, V, V, V, V, V, V, T, T, T, T, T},
            {T, T, T, T, T, V, V, V, V, V, V, V, V, V, V, T, T, T, T, T},
            {T, T, T, T, T, V, V, V, V, V, V, V, V, V, V, T, T, T, T, T},
            {T, T, T, T, V, V, V, V, V, V, V, V, V, V, V, V, T, T, T, T},
            {T, T, T, T, V, V, V, V, V, V, V, V, V, V, V, V, T, T, T, T},
            {T, T, T, V, V, V, V, V, V, V, V, V, V, V, V, V, V, T, T, T},
            {T, T, T, V, V, V, V, V, V, V, V, V, V, V, V, V, V, T, T, T},
            {T, T, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, T, T},
            {T, T, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, T, T},
            {T, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, T},
            {T, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, T},
            {V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V}
        }
    };

    ColorObj rojo = {0, {
            {R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R},
            {T, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, T},
            {T, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, T},
            {T, T, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, T, T},
            {T, T, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, T, T},
            {T, T, T, R, R, R, R, R, R, R, R, R, R, R, R, R, R, T, T, T},
            {T, T, T, R, R, R, R, R, R, R, R, R, R, R, R, R, R, T, T, T},
            {T, T, T, T, R, R, R, R, R, R, R, R, R, R, R, R, T, T, T, T},
            {T, T, T, T, R, R, R, R, R, R, R, R, R, R, R, R, T, T, T, T},
            {T, T, T, T, T, R, R, R, R, R, R, R, R, R, R, T, T, T, T, T},
            {T, T, T, T, T, R, R, R, R, R, R, R, R, R, R, T, T, T, T, T},
            {T, T, T, T, T, R, R, R, R, R, R, R, R, R, R, T, T, T, T, T},
            {T, T, T, T, T, T, R, R, R, R, R, R, R, R, T, T, T, T, T, T},
            {T, T, T, T, T, T, R, R, R, R, R, R, R, R, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, R, R, R, R, R, R, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, R, R, R, R, R, R, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, R, R, R, R, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, R, R, R, R, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, R, R, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, R, R, T, T, T, T, T, T, T, T, T}
        }
    };


    app->verde1 = verde;
    app->rojo1 = rojo;
    app->amarillo1 = amarillo;

    //EL OFFSET ES UN PORCENTAJE DE PANTALLA 0-100, EMPEZANDO DESDE LA EZQUINA IZQ-ARRIBA
    app->verde1.offsetX = 25;
    app->verde1.offsetY = 50;

    app->rojo1.offsetX =  50;
    app->rojo1.offsetY = 50;

    app->amarillo1.offsetX = 75;
    app->amarillo1.offsetY = 50;

    app->verde1.nota = app->escalaActual[0];
    app->rojo1.nota = app->escalaActual[1];
    app->amarillo1.nota = app->escalaActual[2];


}
void inicializar4Notas(NotasApp *app)
{
    ColorObj verde = {0, {
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, V, V, V, V},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, V, V, V, V, V, V, V},
            {T, T, T, T, T, T, T, T, T, T, T, T, V, V, V, V, V, V, V, V},
            {T, T, T, T, T, T, T, T, T, T, T, V, V, V, V, V, V, V, V, V},
            {T, T, T, T, T, T, T, T, T, T, V, V, V, V, V, V, V, V, V, V},
            {T, T, T, T, T, T, T, T, T, V, V, V, V, V, V, V, V, V, V, V},
            {T, T, T, T, T, T, T, T, V, V, V, V, V, V, V, V, V, V, V, V},
            {T, T, T, T, T, T, T, V, V, V, V, V, V, V, V, V, V, V, V, V},
            {T, T, T, T, T, T, V, V, V, V, V, V, V, V, V, V, V, V, V, V},
            {T, T, T, T, T, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V},
            {T, T, T, T, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V},
            {T, T, T, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V},
            {T, T, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V},
            {T, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, T, T},
            {T, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, T, T, T, T},
            {V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, T, T, T, T, T},
            {V, V, V, V, V, V, V, V, V, V, V, V, V, V, T, T, T, T, T, T},
            {V, V, V, V, V, V, V, V, V, V, V, V, V, T, T, T, T, T, T, T},
            {V, V, V, V, V, V, V, V, V, V, V, V, V, T, T, T, T, T, T, T},
            {V, V, V, V, V, V, V, V, V, V, V, V, V, T, T, T, T, T, T, T}
        }
    };
    ColorObj rojo = {0, {
            {R, R, R, R, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {R, R, R, R, R, R, R, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {R, R, R, R, R, R, R, R, T, T, T, T, T, T, T, T, T, T, T, T},
            {R, R, R, R, R, R, R, R, R, T, T, T, T, T, T, T, T, T, T, T},
            {R, R, R, R, R, R, R, R, R, R, T, T, T, T, T, T, T, T, T, T},
            {R, R, R, R, R, R, R, R, R, R, R, T, T, T, T, T, T, T, T, T},
            {R, R, R, R, R, R, R, R, R, R, R, R, T, T, T, T, T, T, T, T},
            {R, R, R, R, R, R, R, R, R, R, R, R, R, T, T, T, T, T, T, T},
            {R, R, R, R, R, R, R, R, R, R, R, R, R, R, T, T, T, T, T, T},
            {R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, T, T, T, T, T},
            {R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, T, T, T, T},
            {R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, T, T, T},
            {R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, T, T},
            {T, T, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, T},
            {T, T, T, T, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, T},
            {T, T, T, T, T, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R},
            {T, T, T, T, T, T, R, R, R, R, R, R, R, R, R, R, R, R, R, R},
            {T, T, T, T, T, T, T, R, R, R, R, R, R, R, R, R, R, R, R, R},
            {T, T, T, T, T, T, T, R, R, R, R, R, R, R, R, R, R, R, R, R},
            {T, T, T, T, T, T, T, R, R, R, R, R, R, R, R, R, R, R, R, R}
        }
    };
    ColorObj azul = {0,
        {
            {T, T, T, T, T, T, T, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ},
            {T, T, T, T, T, T, T, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ},
            {T, T, T, T, T, T, T, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ},
            {T, T, T, T, T, T, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ},
            {T, T, T, T, T, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ},
            {T, T, T, T, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, T},
            {T, T, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, T},
            {AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, T, T},
            {AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, T, T, T},
            {AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, T, T, T, T},
            {AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, T, T, T, T, T},
            {AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, T, T, T, T, T, T},
            {AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, T, T, T, T, T, T, T},
            {AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, T, T, T, T, T, T, T, T},
            {AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, T, T, T, T, T, T, T, T, T},
            {AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, T, T, T, T, T, T, T, T, T, T},
            {AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, T, T, T, T, T, T, T, T, T, T, T},
            {AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, T, T, T, T, T, T, T, T, T, T, T, T},
            {AZ, AZ, AZ, AZ, AZ, AZ, AZ, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {AZ, AZ, AZ, AZ, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T}
        }
    };
    ColorObj amarillo = {0,
        {
            {A, A, A, A, A, A, A, A, A, A, A, A, A, T, T, T, T, T, T, T},
            {A, A, A, A, A, A, A, A, A, A, A, A, A, T, T, T, T, T, T, T},
            {A, A, A, A, A, A, A, A, A, A, A, A, A, T, T, T, T, T, T, T},
            {A, A, A, A, A, A, A, A, A, A, A, A, A, A, T, T, T, T, T, T},
            {A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, T, T, T, T, T},
            {T, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, T, T, T, T},
            {T, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, T, T},
            {T, T, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A},
            {T, T, T, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A},
            {T, T, T, T, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A},
            {T, T, T, T, T, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A},
            {T, T, T, T, T, T, A, A, A, A, A, A, A, A, A, A, A, A, A, A},
            {T, T, T, T, T, T, T, A, A, A, A, A, A, A, A, A, A, A, A, A},
            {T, T, T, T, T, T, T, T, A, A, A, A, A, A, A, A, A, A, A, A},
            {T, T, T, T, T, T, T, T, T, A, A, A, A, A, A, A, A, A, A, A},
            {T, T, T, T, T, T, T, T, T, T, A, A, A, A, A, A, A, A, A, A},
            {T, T, T, T, T, T, T, T, T, T, T, A, A, A, A, A, A, A, A, A},
            {T, T, T, T, T, T, T, T, T, T, T, T, A, A, A, A, A, A, A, A},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, A, A, A, A, A, A, A},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, A, A, A, A}
        }
    };
    app->verde1 = verde;
    app->rojo1 = rojo;
    app->azul1 = azul;
    app->amarillo1 = amarillo;

    //EL OFFSET ES UN PORCENTAJE DE PANTALLA 0-100, EMPEZANDO DESDE LA EZQUINA IZQ-ARRIBA
    app->verde1.offsetX = 30;
    app->verde1.offsetY = 12;

    app->rojo1.offsetX =  70;
    app->rojo1.offsetY = 12;

    app->azul1.offsetX = 70;
    app->azul1.offsetY = 88;

    app->amarillo1.offsetX = 30;
    app->amarillo1.offsetY = 88;

    app->verde1.nota = app->escalaActual[0];
    app->rojo1.nota = app->escalaActual[1];
    app->azul1.nota = app->escalaActual[2];
    app->amarillo1.nota = app->escalaActual[3];

}
void inicializar5Notas(NotasApp *app)
{
    ColorObj amarillo = {0, {
            {A, A, A, A, A, A, A, A, A, A, A, A, A, T, T, T, T, T, T, T},
            {A, A, A, A, A, A, A, A, A, A, A, A, A, T, T, T, T, T, T, T},
            {A, A, A, A, A, A, A, A, A, A, A, A, A, T, T, T, T, T, T, T},
            {A, A, A, A, A, A, A, A, A, A, A, A, A, A, T, T, T, T, T, T},
            {A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, T, T, T, T, T},
            {T, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, T, T, T, T},
            {T, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, T, T},
            {T, T, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A},
            {T, T, T, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A},
            {T, T, T, T, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A},
            {T, T, T, T, T, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A},
            {T, T, T, T, T, T, A, A, A, A, A, A, A, A, A, A, A, A, A, A},
            {T, T, T, T, T, T, T, A, A, A, A, A, A, A, A, A, A, A, A, A},
            {T, T, T, T, T, T, T, T, A, A, A, A, A, A, A, A, A, A, A, A},
            {T, T, T, T, T, T, T, T, T, A, A, A, A, A, A, A, A, A, A, A},
            {T, T, T, T, T, T, T, T, T, T, A, A, A, A, A, A, A, A, A, A},
            {T, T, T, T, T, T, T, T, T, T, T, A, A, A, A, A, A, A, A, A},
            {T, T, T, T, T, T, T, T, T, T, T, T, A, A, A, A, A, A, A, A},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, A, A, A, A, A, A, A},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, A, A, A, A}
        }
    };

    ColorObj verde = {0, {
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, V, V, V, V},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, V, V, V, V, V, V, V},
            {T, T, T, T, T, T, T, T, T, T, T, T, V, V, V, V, V, V, V, V},
            {T, T, T, T, T, T, T, T, T, T, T, V, V, V, V, V, V, V, V, V},
            {T, T, T, T, T, T, T, T, T, T, V, V, V, V, V, V, V, V, V, V},
            {T, T, T, T, T, T, T, T, T, V, V, V, V, V, V, V, V, V, V, V},
            {T, T, T, T, T, T, T, T, V, V, V, V, V, V, V, V, V, V, V, V},
            {T, T, T, T, T, T, T, V, V, V, V, V, V, V, V, V, V, V, V, V},
            {T, T, T, T, T, T, V, V, V, V, V, V, V, V, V, V, V, V, V, V},
            {T, T, T, T, T, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V},
            {T, T, T, T, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V},
            {T, T, T, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V},
            {T, T, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V},
            {T, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, T, T},
            {T, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, T, T, T, T},
            {V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, T, T, T, T, T},
            {V, V, V, V, V, V, V, V, V, V, V, V, V, V, T, T, T, T, T, T},
            {V, V, V, V, V, V, V, V, V, V, V, V, V, T, T, T, T, T, T, T},
            {V, V, V, V, V, V, V, V, V, V, V, V, V, T, T, T, T, T, T, T},
            {V, V, V, V, V, V, V, V, V, V, V, V, V, T, T, T, T, T, T, T}
        }
    };

    ColorObj rojo = {0, {
            {R, R, R, R, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {R, R, R, R, R, R, R, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {R, R, R, R, R, R, R, R, T, T, T, T, T, T, T, T, T, T, T, T},
            {R, R, R, R, R, R, R, R, R, T, T, T, T, T, T, T, T, T, T, T},
            {R, R, R, R, R, R, R, R, R, R, T, T, T, T, T, T, T, T, T, T},
            {R, R, R, R, R, R, R, R, R, R, R, T, T, T, T, T, T, T, T, T},
            {R, R, R, R, R, R, R, R, R, R, R, R, T, T, T, T, T, T, T, T},
            {R, R, R, R, R, R, R, R, R, R, R, R, R, T, T, T, T, T, T, T},
            {R, R, R, R, R, R, R, R, R, R, R, R, R, R, T, T, T, T, T, T},
            {R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, T, T, T, T, T},
            {R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, T, T, T, T},
            {R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, T, T, T},
            {R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, T, T},
            {T, T, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, T},
            {T, T, T, T, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, T},
            {T, T, T, T, T, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R},
            {T, T, T, T, T, T, R, R, R, R, R, R, R, R, R, R, R, R, R, R},
            {T, T, T, T, T, T, T, R, R, R, R, R, R, R, R, R, R, R, R, R},
            {T, T, T, T, T, T, T, R, R, R, R, R, R, R, R, R, R, R, R, R},
            {T, T, T, T, T, T, T, R, R, R, R, R, R, R, R, R, R, R, R, R}
        }
    };

    ColorObj azul = {0, {
            {T, T, T, T, T, T, T, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ},
            {T, T, T, T, T, T, T, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ},
            {T, T, T, T, T, T, T, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ},
            {T, T, T, T, T, T, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ},
            {T, T, T, T, T, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ},
            {T, T, T, T, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, T},
            {T, T, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, T},
            {AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, T, T},
            {AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, T, T, T},
            {AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, T, T, T, T},
            {AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, T, T, T, T, T},
            {AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, T, T, T, T, T, T},
            {AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, T, T, T, T, T, T, T},
            {AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, T, T, T, T, T, T, T, T},
            {AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, T, T, T, T, T, T, T, T, T},
            {AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, T, T, T, T, T, T, T, T, T, T},
            {AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, T, T, T, T, T, T, T, T, T, T, T},
            {AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, T, T, T, T, T, T, T, T, T, T, T, T},
            {AZ, AZ, AZ, AZ, AZ, AZ, AZ, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {AZ, AZ, AZ, AZ, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T}
        }
    };

    ColorObj violeta = {0, {
            {T, T, T, T, T, T, T, VI, VI, VI, VI, VI, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, VI, VI, VI, VI, VI, VI, VI, VI, VI, T, T, T, T, T, T},
            {T, T, T, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, T, T, T, T},
            {T, T, VI, VI, VI, VI, VI, T, T, T, T, T, VI, VI, VI, VI, VI, T, T, T},
            {T, T, VI, VI, VI, VI, T, VI, VI, VI, VI, VI, T, VI, VI, VI, VI, T, T, T},
            {T, VI, VI, VI, VI, T, VI, VI, VI, VI, VI, VI, VI, T, VI, VI, VI, VI, T, T},
            {T, VI, VI, VI, T, VI, VI, VI, VI, VI, VI, VI, VI, VI, T, VI, VI, VI, T, T},
            {VI, VI, VI, T, VI, VI, VI, VI, T, T, T, VI, VI, VI, VI, T, VI, VI, VI, T},
            {VI, VI, VI, T, VI, VI, VI, T, VI, VI, VI, T, VI, VI, VI, T, VI, VI, VI, T},
            {VI, VI, VI, T, VI, VI, VI, T, VI, T, VI, T, VI, VI, VI, T, VI, VI, VI, T},
            {VI, VI, VI, T, VI, VI, VI, T, VI, VI, VI, T, VI, VI, VI, T, VI, VI, VI, T},
            {VI, VI, VI, T, VI, VI, VI, VI, T, T, T, VI, VI, VI, VI, T, VI, VI, VI, T},
            {T, VI, VI, VI, T, VI, VI, VI, VI, VI, VI, VI, VI, VI, T, VI, VI, VI, T, T},
            {T, VI, VI, VI, VI, T, VI, VI, VI, VI, VI, VI, VI, T, VI, VI, VI, VI, T, T},
            {T, T, VI, VI, VI, VI, T, VI, VI, VI, VI, VI, T, VI, VI, VI, VI, T, T, T},
            {T, T, VI, VI, VI, VI, VI, T, T, T, T, T, VI, VI, VI, VI, VI, T, T, T},
            {T, T, T, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, T, T, T, T},
            {T, T, T, T, T, VI, VI, VI, VI, VI, VI, VI, VI, VI, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, VI, VI, VI, VI, VI, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T}
        }
    };




    app->verde1 = verde;
    app->rojo1 = rojo;
    app->azul1 = azul;
    app->amarillo1 = amarillo;
    app->violeta = violeta;

    //EL OFFSET ES UN PORCENTAJE DE PANTALLA 0-100, EMPEZANDO DESDE LA EZQUINA IZQ-ARRIBA
    app->verde1.offsetX = 25;
    app->verde1.offsetY = 8;

    app->rojo1.offsetX =  75;
    app->rojo1.offsetY = 8;

    app->azul1.offsetX = 75;
    app->azul1.offsetY = 92;

    app->amarillo1.offsetX = 25;
    app->amarillo1.offsetY = 92;

    app->violeta.offsetX = 50;
    app->violeta.offsetY = 50;

    app->verde1.nota = app->escalaActual[0];
    app->rojo1.nota = app->escalaActual[1];
    app->azul1.nota = app->escalaActual[2];
    app->amarillo1.nota = app->escalaActual[3];
    app->violeta.nota = app->escalaActual[4];
}

void inicializar6Notas(NotasApp *app)
{
    ColorObj amarillo = {0, {
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, T},
            {T, A, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, A, T},
            {T, A, T, A, A, A, A, A, A, A, A, A, A, A, A, A, A, T, A, T},
            {T, A, T, A, A, A, A, A, A, A, A, A, A, A, A, A, A, T, A, T},
            {T, A, T, A, A, A, A, A, A, A, A, A, A, A, A, A, A, T, A, T},
            {T, A, T, A, A, A, A, A, A, A, A, A, A, A, A, A, A, T, A, T},
            {T, A, T, A, A, A, A, A, A, A, A, A, A, A, A, A, A, T, A, T},
            {T, A, T, A, A, A, A, A, T, T, T, T, A, A, A, A, A, T, A, T},
            {T, A, T, A, A, A, A, A, T, A, A, T, A, A, A, A, A, T, A, T},
            {T, A, T, A, A, A, A, A, T, A, A, T, A, A, A, A, A, T, A, T},
            {T, A, T, A, A, A, A, A, T, T, T, T, A, A, A, A, A, T, A, T},
            {T, A, T, A, A, A, A, A, A, A, A, A, A, A, A, A, A, T, A, T},
            {T, A, T, A, A, A, A, A, A, A, A, A, A, A, A, A, A, T, A, T},
            {T, A, T, A, A, A, A, A, A, A, A, A, A, A, A, A, A, T, A, T},
            {T, A, T, A, A, A, A, A, A, A, A, A, A, A, A, A, A, T, A, T},
            {T, A, T, A, A, A, A, A, A, A, A, A, A, A, A, A, A, T, A, T},
            {T, A, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, A, T},
            {T, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T}
        }
    };

    ColorObj verde = {0, {
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, T},
            {T, V, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, V, T},
            {T, V, T, V, V, V, V, V, V, V, V, V, V, V, V, V, V, T, V, T},
            {T, V, T, V, V, V, V, V, V, V, V, V, V, V, V, V, V, T, V, T},
            {T, V, T, V, V, V, V, V, V, V, V, V, V, V, V, V, V, T, V, T},
            {T, V, T, V, V, V, V, V, V, V, V, V, V, V, V, V, V, T, V, T},
            {T, V, T, V, V, V, V, V, V, V, V, V, V, V, V, V, V, T, V, T},
            {T, V, T, V, V, V, V, V, T, T, T, T, V, V, V, V, V, T, V, T},
            {T, V, T, V, V, V, V, V, T, V, V, T, V, V, V, V, V, T, V, T},
            {T, V, T, V, V, V, V, V, T, V, V, T, V, V, V, V, V, T, V, T},
            {T, V, T, V, V, V, V, V, T, T, T, T, V, V, V, V, V, T, V, T},
            {T, V, T, V, V, V, V, V, V, V, V, V, V, V, V, V, V, T, V, T},
            {T, V, T, V, V, V, V, V, V, V, V, V, V, V, V, V, V, T, V, T},
            {T, V, T, V, V, V, V, V, V, V, V, V, V, V, V, V, V, T, V, T},
            {T, V, T, V, V, V, V, V, V, V, V, V, V, V, V, V, V, T, V, T},
            {T, V, T, V, V, V, V, V, V, V, V, V, V, V, V, V, V, T, V, T},
            {T, V, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, V, T},
            {T, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T}
        }
    };

    ColorObj rojo = {0, {
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, T},
            {T, R, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, R, T},
            {T, R, T, R, R, R, R, R, R, R, R, R, R, R, R, R, R, T, R, T},
            {T, R, T, R, R, R, R, R, R, R, R, R, R, R, R, R, R, T, R, T},
            {T, R, T, R, R, R, R, R, R, R, R, R, R, R, R, R, R, T, R, T},
            {T, R, T, R, R, R, R, R, R, R, R, R, R, R, R, R, R, T, R, T},
            {T, R, T, R, R, R, R, R, R, R, R, R, R, R, R, R, R, T, R, T},
            {T, R, T, R, R, R, R, R, T, T, T, T, R, R, R, R, R, T, R, T},
            {T, R, T, R, R, R, R, R, T, R, R, T, R, R, R, R, R, T, R, T},
            {T, R, T, R, R, R, R, R, T, R, R, T, R, R, R, R, R, T, R, T},
            {T, R, T, R, R, R, R, R, T, T, T, T, R, R, R, R, R, T, R, T},
            {T, R, T, R, R, R, R, R, R, R, R, R, R, R, R, R, R, T, R, T},
            {T, R, T, R, R, R, R, R, R, R, R, R, R, R, R, R, R, T, R, T},
            {T, R, T, R, R, R, R, R, R, R, R, R, R, R, R, R, R, T, R, T},
            {T, R, T, R, R, R, R, R, R, R, R, R, R, R, R, R, R, T, R, T},
            {T, R, T, R, R, R, R, R, R, R, R, R, R, R, R, R, R, T, R, T},
            {T, R, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, R, T},
            {T, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T}
        }
    };
    ColorObj azul = {0, {
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, T},
            {T, AZ, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, AZ, T},
            {T, AZ, T, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, T, AZ, T},
            {T, AZ, T, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, T, AZ, T},
            {T, AZ, T, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, T, AZ, T},
            {T, AZ, T, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, T, AZ, T},
            {T, AZ, T, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, T, AZ, T},
            {T, AZ, T, AZ, AZ, AZ, AZ, AZ, T, T, T, T, AZ, AZ, AZ, AZ, AZ, T, AZ, T},
            {T, AZ, T, AZ, AZ, AZ, AZ, AZ, T, AZ, AZ, T, AZ, AZ, AZ, AZ, AZ, T, AZ, T},
            {T, AZ, T, AZ, AZ, AZ, AZ, AZ, T, AZ, AZ, T, AZ, AZ, AZ, AZ, AZ, T, AZ, T},
            {T, AZ, T, AZ, AZ, AZ, AZ, AZ, T, T, T, T, AZ, AZ, AZ, AZ, AZ, T, AZ, T},
            {T, AZ, T, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, T, AZ, T},
            {T, AZ, T, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, T, AZ, T},
            {T, AZ, T, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, T, AZ, T},
            {T, AZ, T, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, T, AZ, T},
            {T, AZ, T, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, T, AZ, T},
            {T, AZ, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, AZ, T},
            {T, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T}
        }
    };

    app->verde1 = verde;
    app->rojo1 = rojo;
    app->amarillo1 = amarillo;
    app->verde2 = verde;
    app->azul1 = azul;
    app->amarillo2 = amarillo;

    //EL OFFSET ES UN PORCENTAJE DE PANTALLA 0-100, EMPEZANDO DESDE LA EZQUINA IZQ-ARRIBA
    app->verde1.offsetX = 20;
    app->verde1.offsetY = 20;

    app->rojo1.offsetX =  50;
    app->rojo1.offsetY = 20;

    app->amarillo1.offsetX = 80;
    app->amarillo1.offsetY = 20;

    app->verde2.offsetX = 80;
    app->verde2.offsetY = 88;

    app->azul1.offsetX =  50;
    app->azul1.offsetY = 88;

    app->amarillo2.offsetX = 20;
    app->amarillo2.offsetY = 88;

    app->verde1.nota = app->escalaActual[0];
    app->rojo1.nota = app->escalaActual[1];
    app->amarillo1.nota = app->escalaActual[2];
    app->verde2.nota = app->escalaActual[3];
    app->azul1.nota = app->escalaActual[4];
    app->amarillo2.nota = app->escalaActual[5];
}
void inicializar8Notas(NotasApp *app)
{
    ColorObj amarillo = {0, {
            {A, A, A, A, A, A, A, A, A, T, T, T, T, T, T, T, T, T, T, T},
            {A, A, A, A, A, A, A, A, A, A, T, T, T, T, T, T, T, T, T, T},
            {A, A, A, A, A, A, A, A, A, A, A, T, T, T, T, T, T, T, T, T},
            {A, A, A, A, A, A, A, A, A, A, A, T, T, T, T, T, T, T, T, T},
            {A, A, A, A, A, A, A, A, A, A, A, T, T, T, T, T, T, T, T, T},
            {A, A, A, A, A, A, A, A, A, A, T, T, T, T, T, T, T, T, T, T},
            {A, A, A, A, A, A, A, A, A, T, T, T, T, T, T, T, T, T, T, T},
            {A, A, A, A, A, A, A, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {A, A, A, A, A, A, A, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, A, A, A, A, A, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, T, A, A, A, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T}
        }
    };

    ColorObj verde = {0, {
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, T, V, V, V, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, V, V, V, V, V, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {V, V, V, V, V, V, V, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {V, V, V, V, V, V, V, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {V, V, V, V, V, V, V, V, V, T, T, T, T, T, T, T, T, T, T, T},
            {V, V, V, V, V, V, V, V, V, V, T, T, T, T, T, T, T, T, T, T},
            {V, V, V, V, V, V, V, V, V, V, V, T, T, T, T, T, T, T, T, T},
            {V, V, V, V, V, V, V, V, V, V, V, T, T, T, T, T, T, T, T, T},
            {V, V, V, V, V, V, V, V, V, V, V, T, T, T, T, T, T, T, T, T},
            {V, V, V, V, V, V, V, V, V, V, T, T, T, T, T, T, T, T, T, T},
            {V, V, V, V, V, V, V, V, V, T, T, T, T, T, T, T, T, T, T, T}
        }
    };

    ColorObj rojo = {0, {
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, R, R, R, T, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, R, R, R, R, R, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, R, R, R, R, R, R, R},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, R, R, R, R, R, R, R},
            {T, T, T, T, T, T, T, T, T, T, T, R, R, R, R, R, R, R, R, R},
            {T, T, T, T, T, T, T, T, T, T, R, R, R, R, R, R, R, R, R, R},
            {T, T, T, T, T, T, T, T, T, R, R, R, R, R, R, R, R, R, R, R},
            {T, T, T, T, T, T, T, T, T, R, R, R, R, R, R, R, R, R, R, R},
            {T, T, T, T, T, T, T, T, T, R, R, R, R, R, R, R, R, R, R, R},
            {T, T, T, T, T, T, T, T, T, T, R, R, R, R, R, R, R, R, R, R},
            {T, T, T, T, T, T, T, T, T, T, T, R, R, R, R, R, R, R, R, R}
        }
    };

    ColorObj azul = {0, {
            {T, T, T, T, T, T, T, T, T, T, T, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ},
            {T, T, T, T, T, T, T, T, T, T, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ},
            {T, T, T, T, T, T, T, T, T, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ},
            {T, T, T, T, T, T, T, T, T, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ},
            {T, T, T, T, T, T, T, T, T, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ},
            {T, T, T, T, T, T, T, T, T, T, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ},
            {T, T, T, T, T, T, T, T, T, T, T, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, AZ, AZ, AZ, AZ, AZ, AZ, AZ},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, AZ, AZ, AZ, AZ, AZ, AZ, AZ},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, AZ, AZ, AZ, AZ, AZ, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, AZ, AZ, AZ, T, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T}
        }
    };

    ColorObj amarillo2 = {0, {
            {A, A, A, A, A, A, A, A, A, T, T, T, T, T, T, T, T, T, T, T},
            {A, A, A, A, A, A, A, A, A, A, T, T, T, T, T, T, T, T, T, T},
            {A, A, A, A, A, A, A, A, A, A, A, T, T, T, T, T, T, T, T, T},
            {A, A, A, A, A, A, A, A, A, A, A, T, T, T, T, T, T, T, T, T},
            {A, A, A, A, A, A, A, A, A, A, A, T, T, T, T, T, T, T, T, T},
            {A, A, A, A, A, A, A, A, A, A, T, T, T, T, T, T, T, T, T, T},
            {A, A, A, A, A, A, A, A, A, T, T, T, T, T, T, T, T, T, T, T},
            {A, A, A, A, A, A, A, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {A, A, A, A, A, A, A, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, A, A, A, A, A, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, T, A, A, A, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T}
        }
    };

    ColorObj verde2 = {0, {
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, T, V, V, V, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, V, V, V, V, V, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {V, V, V, V, V, V, V, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {V, V, V, V, V, V, V, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {V, V, V, V, V, V, V, V, V, T, T, T, T, T, T, T, T, T, T, T},
            {V, V, V, V, V, V, V, V, V, V, T, T, T, T, T, T, T, T, T, T},
            {V, V, V, V, V, V, V, V, V, V, V, T, T, T, T, T, T, T, T, T},
            {V, V, V, V, V, V, V, V, V, V, V, T, T, T, T, T, T, T, T, T},
            {V, V, V, V, V, V, V, V, V, V, V, T, T, T, T, T, T, T, T, T},
            {V, V, V, V, V, V, V, V, V, V, T, T, T, T, T, T, T, T, T, T},
            {V, V, V, V, V, V, V, V, V, T, T, T, T, T, T, T, T, T, T, T}
        }
    };

    ColorObj rojo2 = {0, {
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, R, R, R, T, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, R, R, R, R, R, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, R, R, R, R, R, R, R},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, R, R, R, R, R, R, R},
            {T, T, T, T, T, T, T, T, T, T, T, R, R, R, R, R, R, R, R, R},
            {T, T, T, T, T, T, T, T, T, T, R, R, R, R, R, R, R, R, R, R},
            {T, T, T, T, T, T, T, T, T, R, R, R, R, R, R, R, R, R, R, R},
            {T, T, T, T, T, T, T, T, T, R, R, R, R, R, R, R, R, R, R, R},
            {T, T, T, T, T, T, T, T, T, R, R, R, R, R, R, R, R, R, R, R},
            {T, T, T, T, T, T, T, T, T, T, R, R, R, R, R, R, R, R, R, R},
            {T, T, T, T, T, T, T, T, T, T, T, R, R, R, R, R, R, R, R, R}
        }
    };

    ColorObj azul2 = {0, {
            {T, T, T, T, T, T, T, T, T, T, T, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ},
            {T, T, T, T, T, T, T, T, T, T, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ},
            {T, T, T, T, T, T, T, T, T, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ},
            {T, T, T, T, T, T, T, T, T, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ},
            {T, T, T, T, T, T, T, T, T, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ},
            {T, T, T, T, T, T, T, T, T, T, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ},
            {T, T, T, T, T, T, T, T, T, T, T, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ, AZ},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, AZ, AZ, AZ, AZ, AZ, AZ, AZ},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, AZ, AZ, AZ, AZ, AZ, AZ, AZ},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, AZ, AZ, AZ, AZ, AZ, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, AZ, AZ, AZ, T, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T}
        }
    };


    app->verde1 = verde;
    app->rojo1 = rojo;
    app->amarillo1 = amarillo;
    app->azul1= azul;

    app->verde2 = verde2;
    app->rojo2 = rojo2;
    app->amarillo2 = amarillo2;
    app->azul2= azul2;

    //EL OFFSET ES UN PORCENTAJE DE PANTALLA 0-100, EMPEZANDO DESDE LA EZQUINA IZQ-ARRIBA
    app->rojo1.offsetX =  15;
    app->rojo1.offsetY = 5;

    app->verde1.offsetX = 45;
    app->verde1.offsetY = 5;

    app->azul1.offsetX = 15;
    app->azul1.offsetY = 70;

    app->amarillo1.offsetX = 45;
    app->amarillo1.offsetY = 70;

    /////linea 2

    app->verde2.offsetX = 95;
    app->verde2.offsetY = 5;

    app->rojo2.offsetX =  65;
    app->rojo2.offsetY = 5;

    app->amarillo2.offsetX = 95;
    app->amarillo2.offsetY = 70;

    app->azul2.offsetX = 65;
    app->azul2.offsetY = 70;
    //sonidos
    app->rojo1.nota = app->escalaActual[0];
    app->verde1.nota = app->escalaActual[1];
    app->azul1.nota = app->escalaActual[2];
    app->amarillo1.nota = app->escalaActual[3];

    app->verde2.nota = app->escalaActual[4];
    app->rojo2.nota = app->escalaActual[5];
    app->amarillo2.nota = app->escalaActual[6];
    app->azul2.nota = app->escalaActual[7];


}

void Innit_Schornberg(Jugador *jugador, ConfiguracionSch *configSc, SDL_Window *ventana, SDL_Renderer *renderer)
{
    //configSc->duracionIni = 800; // OCTAVIO - BORRAR
    inicializarAudio();
    NotasApp app;
    Secuencia historial;
    inicializarHistorial(&historial);
    //ESCALAS
     char* acordeMayor[] = {"do", "mi", "sol"};
     char* acordeMayorSexta[] = {"do", "mi", "sol", "la"};
     char* escalaPentatonica[] = {"do", "re", "mi", "sol", "la"};
     char* escalaHexatonal[] = {"do", "re", "mi", "fa#", "sol#", "la#"};
     char* escalaMenorArmonica[] = {"do", "re", "mib", "fa", "sol", "lab", "si"};
     char* escalaMayor[] = {"do", "re", "mi", "fa", "sol", "la", "si", "doAgudo"};

    //printf("\nJugando Schornberg - Usuario %s - Puntaje %d\nCantidad Notas: %d / Duracion Inicial: %d", jugador->nombre, jugador->puntaje, configSc->cantNotas, configSc->duracionIni);
    //Self estatico, con esto podemos iterar
    app.arrayColores[0] = &app.amarillo1,
    app.arrayColores[1] = &app.amarillo2;
    app.arrayColores[2] = &app.azul1;
    app.arrayColores[3] = &app.azul2;
    app.arrayColores[4] = &app.rojo1;
    app.arrayColores[5] = &app.rojo2;
    app.arrayColores[6] = &app.verde1;
    app.arrayColores[7] = &app.verde2;
    app.arrayColores[8] = &app.violeta;
    //configSc->cantNotas = 5;
    void (*renderActual)(Jugador *jugador, ConfiguracionSch *configSc, SDL_Renderer *renderer, NotasApp *app) = NULL;
//
//    char **sonidosDisponibles;
//    int cantidadSonidos;
    switch(configSc->cantNotas)
    {
    case 3:
    {
        renderActual = &render3Notas;
        app.cantidadNotasEscala = 3;
        app.escalaActual = acordeMayor;
        inicializar3Notas(&app);
        break;
    }
    case 4:
    {
        app.cantidadNotasEscala = 4;
        app.escalaActual = acordeMayorSexta;
        inicializar4Notas(&app);
        renderActual = &render4Notas;
        break;
    }
    case 5:
    {
        app.cantidadNotasEscala = 5;
        app.escalaActual = escalaPentatonica;
        inicializar5Notas(&app);
        renderActual = &render5Notas;
        break;
    }
    case 6:
    {
        app.cantidadNotasEscala = 6;
        app.escalaActual = escalaHexatonal;
        inicializar6Notas(&app);
        renderActual = &render6Notas;
        break;
    }
    case 7:
    {
        app.cantidadNotasEscala = 7;
        app.escalaActual = escalaMenorArmonica;
    }
    case 8:
    {
        app.cantidadNotasEscala = 8;
        app.escalaActual = escalaMayor;
        inicializar8Notas(&app);
        renderActual = &render8Notas;
        break;
    }

    }
    while(1)
    {
        prepararEscena(renderer);
        registrarEntradas(&app, configSc->duracionIni); // detecta la posicion de mouse y entradas
        renderActual(jugador, configSc, renderer, &app);
        presentarEscena(renderer);
    }


}
