#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "interfaz_Juego.h"
#include "jugador.h"
#include <string.h>
#include <stdio.h>

void crearJugador(Jugador* j,const char* nombre)
{
    strncpy(j->nombre, nombre, TAM_NOMBRE - 1);
    j->nombre[TAM_NOMBRE - 1] = '\0'; // seguridad
    j->puntaje = 0;
}
int cargarMejorEstadistica(const char *nombreJugador, size_t cantNotas, Estadisticas *mejor)
{
    FILE *f = fopen("stats.dat", "rb");
    if (!f)
        return 0; // No hay archivo todavía

    Estadisticas temp;
    int encontrado = 0;

    while (fread(&temp, sizeof(Estadisticas), 1, f) == 1)
    {
        if (strcmp(temp.jugador.nombre, nombreJugador) == 0 &&
                temp.cantNotas == cantNotas)
        {
            if (!encontrado || temp.jugador.puntaje > mejor->jugador.puntaje)
            {
                *mejor = temp;
                encontrado = 1;
            }
        }
    }
    fclose(f);
    return encontrado; // 1 si encontró algo
}

void guardarEstadistica(const Estadisticas *actual)
{
    Estadisticas mejorPrevio;
    int existe = cargarMejorEstadistica(actual->jugador.nombre, actual->cantNotas, &mejorPrevio);

    if (existe && mejorPrevio.jugador.puntaje >= actual->jugador.puntaje)
    {
        //printf("No se guardo: puntaje anterior %d >= actual %d\n", mejorPrevio.jugador.puntaje, actual->jugador.puntaje);
        return;
    }

    FILE *f = fopen("stats.dat", "ab");
    if (!f)
    {
        printf("Error: no se pudo abrir stats.dat para escritura.\n");
        return;
    }

    fwrite(actual, sizeof(Estadisticas), 1, f);
    fclose(f);

    //printf("Nueva mejor estadística guardada: %s - Puntaje %d - Notas %zu\n",actual->jugador.nombre, actual->jugador.puntaje, actual->cantNotas);

}

int compararEstadisticas(const void *a, const void *b)
{
    const Estadisticas *ea = (const Estadisticas *)a;
    const Estadisticas *eb = (const Estadisticas *)b;
    return eb->jugador.puntaje - ea->jugador.puntaje; // descendente
}

void mostrarTopEstadisticasSDL(SDL_Renderer *renderer, size_t cantNotasFiltrar)
{
    FILE *f = fopen("stats.dat", "rb");
    TTF_Init();
    TTF_Font *font = TTF_OpenFont("fnt/BitcountGridSingle_Cursive-Regular.ttf", 32);
    if (!f)
    {
        prepararEscena(renderer);
        mostrarTexto(renderer, "No hay estadisticas con registradas con esta cantidad.", font, 100, ALTO_VENTANA / 2, (SDL_Color){255,255,255,255});
        presentarEscena(renderer);
        SDL_Delay(2000);
        esperarCierreModo();
        if (font)
            TTF_CloseFont(font);
        return;
    }

    Estadisticas *lista = NULL;
    size_t cantidad = 0;
    Estadisticas temp;

    SDL_Rect sombraVolver = {ANCHO_VENTANA/2+390, ALTO_VENTANA/2+250, 170, 70};
    SDL_Rect btnVolver = {ANCHO_VENTANA/2+400, ALTO_VENTANA/2+260, 150, 50};


    // lee solo las que coincidan con el filtro
    while (fread(&temp, sizeof(Estadisticas), 1, f) == 1)
    {
        if (temp.cantNotas == cantNotasFiltrar)
        {
            lista = realloc(lista, (cantidad + 1) * sizeof(Estadisticas));
            if (!lista)
            {
                printf("Error de memoria.\n");
                fclose(f);
                return;
            }
            lista[cantidad++] = temp;
        }
    }
    fclose(f);
    if(cantidad==0)
    {
        prepararEscena(renderer);
        mostrarTexto(renderer, "No hay estadisticas con registradas con esta cantidad.", font, 100, ALTO_VENTANA / 2, (SDL_Color){255,255,255,255});
        presentarEscena(renderer);
        SDL_Delay(2000);
        esperarCierreModo();
        if (font)
            TTF_CloseFont(font);
        return;

    }


    // ordena
    qsort(lista, cantidad, sizeof(Estadisticas), compararEstadisticas);

    TTF_Font *fontTitulo = TTF_OpenFont("fnt/BitcountGridSingle_Cursive-Regular.ttf", 32);
    TTF_Font *fontFila   = TTF_OpenFont("fnt/BitcountGridSingle_Cursive-Regular.ttf", 24);

    SDL_Color colorTitulo = {17, 168, 189, 255};
    SDL_Color colorTexto  = {255, 255, 255, 255};

    int corriendo = 1;
    SDL_Event e;



    while (corriendo)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                corriendo = 0;
            }
            if(e.type==SDL_MOUSEBUTTONDOWN)
            {
                int x = e.button.x;
                int y = e.button.y;
                if(SDL_PointInRect(&(SDL_Point){x,y},&btnVolver))
                {
                        //printf("Volver al menu estadisticas\n");
                        corriendo=0;
                }
            }

        }
        prepararEscena(renderer);

        mostrarTexto(renderer, "TOP 20 ESTADISTICAS", fontTitulo, 435, 60, colorTitulo);

        size_t limite = cantidad < 20 ? cantidad : 20;
        int startY = 150;

        for (size_t i = 0; i < limite; i++)
        {
            char linea[128];
            snprintf(linea, sizeof(linea), "%2zu. %-17s Puntaje: %-4d ",i + 1,lista[i].jugador.nombre,lista[i].jugador.puntaje);

            mostrarTexto(renderer, linea, fontFila, ANCHO_VENTANA / 2 - 250, startY + (int)(i * 30), colorTexto);
        }

        SDL_SetRenderDrawColor(renderer, 100,0,0,255); // rojo oscuro
        SDL_RenderFillRect(renderer, &sombraVolver);

        SDL_SetRenderDrawColor(renderer, 255,0,0,255); // celeste {135, 246, 255}
        SDL_RenderFillRect(renderer, &btnVolver);
        mostrarTexto(renderer, "Volver", font, btnVolver.x +20, btnVolver.y +5, (SDL_Color){255,255,255,255});

        presentarEscena(renderer);
        SDL_Delay(16);
    }

    if (fontTitulo) TTF_CloseFont(fontTitulo);
    if (fontFila) TTF_CloseFont(fontFila);
    free(lista);
    TTF_Quit();

}
