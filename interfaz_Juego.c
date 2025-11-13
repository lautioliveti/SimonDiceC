
#include "interfaz_Juego.h"





void presentarEscena(SDL_Renderer *renderer)
{
    SDL_RenderPresent(renderer);
}
void esperar(size_t duracion, int *juegoActivo)
{
    SDL_Event e;
    size_t inicio = SDL_GetTicks();
    while (SDL_GetTicks() - inicio < duracion)
    {

        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                *juegoActivo = 0;
                break;
            }
        }
    }
}
void renderNotasGenerico(Jugador *jugador,size_t cantNotas,SDL_Renderer *renderer, NotasApp *app)
{
    switch (cantNotas)
    {
    case 3:
        render3Notas(jugador, renderer, app);
        break;
    case 4:
        render4Notas(jugador, renderer, app);
        break;
    case 5:
        render5Notas(jugador, renderer, app);
        break;
    case 6:
        render6Notas(jugador, renderer, app);
        break;
    case 7:
        render7Notas(jugador, renderer, app);
        break;
    case 8:
        render8Notas(jugador, renderer, app);
        break;
    default:
        // fallback de seguridad
        render3Notas(jugador, renderer, app);
        break;
    }
}
void inicializarNotasGenerico(NotasApp *app, size_t cantNotas)
{
    switch (cantNotas)
    {
    case 3:
        inicializar3Notas(app);
        app->arrayColores[0] = &app->verde1;
        app->arrayColores[1] = &app->rojo1;
        app->arrayColores[2] = &app->amarillo1;
        break;

    case 4:
        inicializar4Notas(app);
        app->arrayColores[0] = &app->verde1;
        app->arrayColores[1] = &app->rojo1;
        app->arrayColores[2] = &app->azul1;
        app->arrayColores[3] = &app->amarillo1;
        break;

    case 5:
        inicializar5Notas(app);
        app->arrayColores[0] = &app->verde1;
        app->arrayColores[1] = &app->rojo1;
        app->arrayColores[2] = &app->azul1;
        app->arrayColores[3] = &app->amarillo1;
        app->arrayColores[4] = &app->violeta;
        break;

    case 6:
        inicializar6Notas(app);
        app->arrayColores[0] = &app->verde1;
        app->arrayColores[1] = &app->rojo1;
        app->arrayColores[2] = &app->amarillo1;
        app->arrayColores[3] = &app->verde2;
        app->arrayColores[4] = &app->azul1;
        app->arrayColores[5] = &app->amarillo2;
        break;

    case 7:
        inicializar7Notas(app);
        app->arrayColores[0] = &app->verde1;
        app->arrayColores[1] = &app->rojo1;
        app->arrayColores[2] = &app->amarillo1;
        app->arrayColores[3] = &app->verde2;
        app->arrayColores[4] = &app->rojo2;
        app->arrayColores[5] = &app->amarillo2;
        app->arrayColores[6] = &app->violeta;
        break;

    case 8:
        inicializar8Notas(app);
        app->arrayColores[0] = &app->verde1;
        app->arrayColores[1] = &app->rojo1;
        app->arrayColores[2] = &app->amarillo1;
        app->arrayColores[3] = &app->azul1;
        app->arrayColores[4] = &app->verde2;
        app->arrayColores[5] = &app->rojo2;
        app->arrayColores[6] = &app->amarillo2;
        app->arrayColores[7] = &app->azul2;
        break;

    default:
        inicializar3Notas(app);
        app->arrayColores[0] = &app->verde1;
        app->arrayColores[1] = &app->rojo1;
        app->arrayColores[2] = &app->amarillo1;
        break;
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
void render3Notas(Jugador *jugador, SDL_Renderer *renderer, NotasApp *app)
{

    int tamPixelFinal = TAM_PIXEL +5;


    renderMatriz(renderer, &(app->verde1), tamPixelFinal);
    renderMatriz(renderer, &(app->rojo1), tamPixelFinal);
    renderMatriz(renderer, &(app->amarillo1), tamPixelFinal);

}
void render4Notas(Jugador *jugador, SDL_Renderer *renderer, NotasApp *app)
{


    int tamPixelFinal = TAM_PIXEL +5;


    renderMatriz(renderer, &(app->verde1), tamPixelFinal);
    renderMatriz(renderer, &(app->rojo1), tamPixelFinal);
    renderMatriz(renderer, &(app->azul1), tamPixelFinal);
    renderMatriz(renderer, &(app->amarillo1), tamPixelFinal);
}
void render5Notas(Jugador *jugador, SDL_Renderer *renderer, NotasApp *app)
{

    int tamPixelFinal = TAM_PIXEL +5;


    renderMatriz(renderer, &(app->verde1), tamPixelFinal);
    renderMatriz(renderer, &(app->rojo1), tamPixelFinal);
    renderMatriz(renderer, &(app->azul1), tamPixelFinal);
    renderMatriz(renderer, &(app->amarillo1), tamPixelFinal);
    renderMatriz(renderer, &(app->violeta), tamPixelFinal);
}
void render6Notas(Jugador *jugador, SDL_Renderer *renderer, NotasApp *app)
{

    int tamPixelFinal = TAM_PIXEL +5;

    renderMatriz(renderer, &(app->verde1), tamPixelFinal);
    renderMatriz(renderer, &(app->rojo1), tamPixelFinal);
    renderMatriz(renderer, &(app->amarillo1), tamPixelFinal);
    renderMatriz(renderer, &(app->verde2), tamPixelFinal);
    renderMatriz(renderer, &(app->azul1), tamPixelFinal);
    renderMatriz(renderer, &(app->amarillo2), tamPixelFinal);
}
void render7Notas(Jugador *jugador, SDL_Renderer *renderer, NotasApp *app)
{

    int tamPixelFinal = TAM_PIXEL +5;


    renderMatriz(renderer, &(app->verde1), tamPixelFinal);
    renderMatriz(renderer, &(app->rojo1), tamPixelFinal);
    renderMatriz(renderer, &(app->amarillo1), tamPixelFinal);
    renderMatriz(renderer, &(app->verde2), tamPixelFinal);
    renderMatriz(renderer, &(app->rojo2), tamPixelFinal);
    renderMatriz(renderer, &(app->amarillo2), tamPixelFinal);
    renderMatriz(renderer, &(app->violeta), tamPixelFinal);
}
void render8Notas(Jugador *jugador, SDL_Renderer *renderer, NotasApp *app)
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
            {T, T, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, T, T, T},
            {T, T, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, T, T, T},
            {T, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, T, T},
            {T, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, T, T},
            {VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, T},
            {VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, T},
            {VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, T},
            {VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, T},
            {VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, T},
            {T, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, T, T},
            {T, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, T, T},
            {T, T, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, T, T, T},
            {T, T, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, T, T, T},
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

}
void inicializar7Notas(NotasApp *app)
{
    ColorObj amarillo = {0, {
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, A, A, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, A, A, A, A, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, A, A, A, A, A, A, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, A, A, A, A, A, A, A, A, T, T, T, T, T, T},
            {T, T, T, T, T, A, A, A, A, A, A, A, A, A, A, T, T, T, T, T},
            {T, T, T, T, A, A, A, A, A, A, A, A, A, A, A, A, T, T, T, T},
            {T, T, T, A, A, A, A, A, A, A, A, A, A, A, A, A, A, T, T, T},
            {T, T, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, T, T},
            {T, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, T},

            {T, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, T},
            {T, T, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, T, T},
            {T, T, T, A, A, A, A, A, A, A, A, A, A, A, A, A, A, T, T, T},
            {T, T, T, T, A, A, A, A, A, A, A, A, A, A, A, A, T, T, T, T},
            {T, T, T, T, T, A, A, A, A, A, A, A, A, A, A, T, T, T, T, T},
            {T, T, T, T, T, T, A, A, A, A, A, A, A, A, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, A, A, A, A, A, A, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, A, A, A, A, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, A, A, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T}
        }
    };

    ColorObj verde = {0, {
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, V, V, V, V, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, V, V, V, V, V, V, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, V, V, V, V, V, V, V, V, T, T, T, T, T, T},
            {T, T, T, T, T, V, V, V, V, V, V, V, V, V, V, T, T, T, T, T},
            {T, T, T, T, V, V, V, V, V, V, V, V, V, V, V, V, T, T, T, T},
            {T, T, T, V, V, V, V, V, V, V, V, V, V, V, V, V, V, T, T, T},
            {T, T, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, T, T},
            {T, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, T},
            {V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V},
            {V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V},
            {T, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, T},
            {T, T, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, T, T},
            {T, T, T, V, V, V, V, V, V, V, V, V, V, V, V, V, V, T, T, T},
            {T, T, T, T, V, V, V, V, V, V, V, V, V, V, V, V, T, T, T, T},
            {T, T, T, T, T, V, V, V, V, V, V, V, V, V, V, T, T, T, T, T},
            {T, T, T, T, T, T, V, V, V, V, V, V, V, V, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, V, V, V, V, V, V, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, V, V, V, V, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T}
        }
    };

    ColorObj rojo = {0, {
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, R, R, R, R, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, R, R, R, R, R, R, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, R, R, R, R, R, R, R, R, T, T, T, T, T, T},
            {T, T, T, T, T, R, R, R, R, R, R, R, R, R, R, T, T, T, T, T},
            {T, T, T, T, R, R, R, R, R, R, R, R, R, R, R, R, T, T, T, T},
            {T, T, T, R, R, R, R, R, R, R, R, R, R, R, R, R, R, T, T, T},
            {T, T, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, T, T},
            {T, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, T},
            {R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R},
            {R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R},
            {T, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, T},
            {T, T, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, T, T},
            {T, T, T, R, R, R, R, R, R, R, R, R, R, R, R, R, R, T, T, T},
            {T, T, T, T, R, R, R, R, R, R, R, R, R, R, R, R, T, T, T, T},
            {T, T, T, T, T, R, R, R, R, R, R, R, R, R, R, T, T, T, T, T},
            {T, T, T, T, T, T, R, R, R, R, R, R, R, R, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, R, R, R, R, R, R, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, R, R, R, R, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T}
        }
    };

    ColorObj violeta = {0, {
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, VI, VI, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, VI, VI, VI, VI, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, VI, VI, VI, VI, VI, VI, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, VI, VI, VI, VI, VI, VI, VI, VI, T, T, T, T, T, T},
            {T, T, T, T, T, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, T, T, T, T, T},
            {T, T, T, T, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, T, T, T, T},
            {T, T, T, T, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, T, T, T, T},
            {T, T, T, T, T, VI, VI, VI, VI, VI, VI, VI, VI, VI, VI, T, T, T, T, T},
            {T, T, T, T, T, T, VI, VI, VI, VI, VI, VI, VI, VI, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, VI, VI, VI, VI, VI, VI, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, VI, VI, VI, VI, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, VI, VI, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T}
        }
    };
    ColorObj amarillo2 = {0, {
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, A, A, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, A, A, A, A, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, A, A, A, A, A, A, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, A, A, A, A, A, A, A, A, T, T, T, T, T, T},
            {T, T, T, T, T, A, A, A, A, A, A, A, A, A, A, T, T, T, T, T},
            {T, T, T, T, A, A, A, A, A, A, A, A, A, A, A, A, T, T, T, T},
            {T, T, T, A, A, A, A, A, A, A, A, A, A, A, A, A, A, T, T, T},
            {T, T, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, T, T},
            {T, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, T},

            {T, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, T},
            {T, T, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, T, T},
            {T, T, T, A, A, A, A, A, A, A, A, A, A, A, A, A, A, T, T, T},
            {T, T, T, T, A, A, A, A, A, A, A, A, A, A, A, A, T, T, T, T},
            {T, T, T, T, T, A, A, A, A, A, A, A, A, A, A, T, T, T, T, T},
            {T, T, T, T, T, T, A, A, A, A, A, A, A, A, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, A, A, A, A, A, A, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, A, A, A, A, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, A, A, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T}
        }
    };

    ColorObj verde2 = {0, {
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, V, V, V, V, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, V, V, V, V, V, V, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, V, V, V, V, V, V, V, V, T, T, T, T, T, T},
            {T, T, T, T, T, V, V, V, V, V, V, V, V, V, V, T, T, T, T, T},
            {T, T, T, T, V, V, V, V, V, V, V, V, V, V, V, V, T, T, T, T},
            {T, T, T, V, V, V, V, V, V, V, V, V, V, V, V, V, V, T, T, T},
            {T, T, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, T, T},
            {T, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, T},
            {V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V},
            {V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V},
            {T, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, T},
            {T, T, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, T, T},
            {T, T, T, V, V, V, V, V, V, V, V, V, V, V, V, V, V, T, T, T},
            {T, T, T, T, V, V, V, V, V, V, V, V, V, V, V, V, T, T, T, T},
            {T, T, T, T, T, V, V, V, V, V, V, V, V, V, V, T, T, T, T, T},
            {T, T, T, T, T, T, V, V, V, V, V, V, V, V, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, V, V, V, V, V, V, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, V, V, V, V, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T}
        }
    };

    ColorObj rojo2 = {0, {
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, R, R, R, R, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, R, R, R, R, R, R, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, R, R, R, R, R, R, R, R, T, T, T, T, T, T},
            {T, T, T, T, T, R, R, R, R, R, R, R, R, R, R, T, T, T, T, T},
            {T, T, T, T, R, R, R, R, R, R, R, R, R, R, R, R, T, T, T, T},
            {T, T, T, R, R, R, R, R, R, R, R, R, R, R, R, R, R, T, T, T},
            {T, T, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, T, T},
            {T, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, T},
            {R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R},
            {R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R},
            {T, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, T},
            {T, T, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, T, T},
            {T, T, T, R, R, R, R, R, R, R, R, R, R, R, R, R, R, T, T, T},
            {T, T, T, T, R, R, R, R, R, R, R, R, R, R, R, R, T, T, T, T},
            {T, T, T, T, T, R, R, R, R, R, R, R, R, R, R, T, T, T, T, T},
            {T, T, T, T, T, T, R, R, R, R, R, R, R, R, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, R, R, R, R, R, R, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, R, R, R, R, T, T, T, T, T, T, T, T},
            {T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T}
        }
    };

    app->verde1 = verde;
    app->rojo1 = rojo;
    app->amarillo1 = amarillo;

    app->verde2 = verde2;
    app->rojo2 = rojo2;
    app->amarillo2 = amarillo2;
    app->violeta = violeta;

    //EL OFFSET ES UN PORCENTAJE DE PANTALLA 0-100, EMPEZANDO DESDE LA EZQUINA IZQ-ARRIBA
    app->amarillo1.offsetX = 55;
    app->amarillo1.offsetY = 0;

    app->rojo1.offsetX =  25;
    app->rojo1.offsetY = 20;

    app->verde1.offsetX = 85;
    app->verde1.offsetY = 20;

    app->violeta.offsetX=55;
    app->violeta.offsetY=50;

    app->amarillo2.offsetX = 55;
    app->amarillo2.offsetY = 100;

    app->verde2.offsetX = 25;
    app->verde2.offsetY = 80;

    app->rojo2.offsetX =  85;
    app->rojo2.offsetY = 80 ;


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
    app->rojo1.offsetX =  5;
    app->rojo1.offsetY = 20;

    app->verde1.offsetX = 35;
    app->verde1.offsetY = 20;

    app->azul1.offsetX = 5;
    app->azul1.offsetY = 80;

    app->amarillo1.offsetX = 35;
    app->amarillo1.offsetY = 80;

    /////linea 2

    app->verde2.offsetX = 95;
    app->verde2.offsetY = 20;

    app->rojo2.offsetX =  65;
    app->rojo2.offsetY = 20;

    app->amarillo2.offsetX = 95;
    app->amarillo2.offsetY = 80;

    app->azul2.offsetX = 65;
    app->azul2.offsetY = 80;
    //sonidos



}

