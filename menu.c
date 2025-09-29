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
    // Fondo negro
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Texto blanco centrado
    SDL_Color color = {255, 255, 255, 255};
    mostrarTexto(renderer, "Bienvenido a Anhedonia!", font, ANCHO_VENTANA/2 - 180, ALTO_VENTANA/2-30, color);   // el - del eje x y del eje y es para centrar el texto :)
    mostrarTexto(renderer, "Simon dice!", font, ANCHO_VENTANA/2 - 90, ALTO_VENTANA/2 +50, color);
    SDL_RenderPresent(renderer);

    SDL_Delay(2000);

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
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_Color color = {135, 246, 255}; // Celeste
    SDL_Color color2 = {240, 255, 255}; // Tipo de blanco

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
        mostrarTexto(renderer,"Ingresar nombre del jugador ENTER",font,ANCHO_VENTANA/2 - 300, ALTO_VENTANA/2-30,color);

        // Mostrar nombre ingresado
        if (strlen(nombreJugador) > 0) {
            mostrarTexto(renderer,nombreJugador,font, ANCHO_VENTANA/2 - 120, ALTO_VENTANA/2 +50 ,color2);
        }

        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);

    }

    crearJugador(jugador,nombreJugador); // usando un TDA_JUGADOR


    TTF_CloseFont(font);
    TTF_Quit();
    SDL_StopTextInput();
    //  desactiva entrada de texto
}

int mostrarMenuInicial(SDL_Renderer *renderer)
{

    int modo;

    TTF_Init();
    // Cargar fuente
    TTF_Font * font = TTF_OpenFont ("fnt/SUSEMono-Medium.ttf",32);
    if (!font) {
        printf("Error cargando fuente: %s\n", TTF_GetError());
        return -1;
    }


    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_Rect btnSchornberg = {ANCHO_VENTANA/2-150, ALTO_VENTANA/2-200, 300, 50};
    SDL_Rect btnDesafio   = {ANCHO_VENTANA/2-150, ALTO_VENTANA/2-50, 300, 50};
    SDL_Rect btnMozart   = {ANCHO_VENTANA/2-150, ALTO_VENTANA/2+100, 300, 50};
    SDL_Rect btnEstadisticas = {ANCHO_VENTANA/2-150 , ALTO_VENTANA/2+250, 300, 50};
    // sombra de botnes
    // creo las sombras de los botoncitos
    SDL_Rect sombraSchornberg = {ANCHO_VENTANA/2-160, ALTO_VENTANA/2-210, 320, 70};
    SDL_Rect sombraDesafio   = {ANCHO_VENTANA/2-160, ALTO_VENTANA/2-60, 320, 70};
    SDL_Rect sombraMozart   = {ANCHO_VENTANA/2-160, ALTO_VENTANA/2+90, 320, 70};
    SDL_Rect sombraEstadisticas ={ANCHO_VENTANA/2-160, ALTO_VENTANA/2+240, 320, 70};

    SDL_Event e;
    int corriendo = 1;

    while(corriendo)
        {
            while(SDL_PollEvent(&e))
            {
                if(e.type==SDL_QUIT)
                {
                    corriendo = 0;
                    printf("Saliendo de SDL\n");
                }
                if(e.type==SDL_MOUSEBUTTONDOWN)
                {
                    int x = e.button.x;
                    int y = e.button.y;
                    if (SDL_PointInRect(&(SDL_Point){x,y}, &btnSchornberg))
                    {
                        // MODO SCHRONBERG
                        printf("MODO SCHORNBERG!\n");
                        modo=SCHORNBERG;
                        corriendo = 0; // salir después de guardar
                    }

                    if (SDL_PointInRect(&(SDL_Point){x,y}, &btnDesafio))
                    {
                        // MODO DESAFIO
                        printf("ENTRASTE AL MODO DESAFIOr\n");
                        modo=DESAFIO;
                        corriendo = 0;
                    }
                    if (SDL_PointInRect(&(SDL_Point){x,y}, &btnMozart))
                    {
                        // MODO DESAFIO
                        printf("ENTRASTE AL MODO DESAFIOr\n");
                        modo=MOZART;
                        corriendo = 0;
                    }
                    if (SDL_PointInRect(&(SDL_Point){x,y}, &btnEstadisticas))
                    {
                        // MODO DESAFIO
                        printf("ENTRASTE AL MODO DESAFIOr\n");
                        modo=ESTADISTICAS;
                        corriendo = 0;
                    }
                }
            }
        mostrarTexto(renderer,"MENU PRINCIPAL",font,550,50,(SDL_Color){135, 246, 255,255});
        // sombra
        SDL_SetRenderDrawColor(renderer, 11,127,143,255); // celeste oscuro
        SDL_RenderFillRect(renderer, &sombraSchornberg);
        SDL_SetRenderDrawColor(renderer, 11,127,143,255); // celeste oscuro
        SDL_RenderFillRect(renderer, &sombraDesafio);
        SDL_SetRenderDrawColor(renderer, 11,127,143,255); // celeste oscuro
        SDL_RenderFillRect(renderer, &sombraMozart);
        SDL_SetRenderDrawColor(renderer, 11,127,143,255); // celeste oscuro
        SDL_RenderFillRect(renderer, &sombraEstadisticas);
        // botones click
        SDL_SetRenderDrawColor(renderer, 17,168,189,255); // celeste {135, 246, 255}
        SDL_RenderFillRect(renderer, &btnSchornberg);
        mostrarTexto(renderer, "Schornberg", font, btnSchornberg.x +45, btnSchornberg.y +5, (SDL_Color){255,255,255,255});

        SDL_SetRenderDrawColor(renderer, 17,168,189,255); // celeste {135, 246, 255}
        SDL_RenderFillRect(renderer, &btnDesafio);
        mostrarTexto(renderer, "Desafio", font, btnDesafio.x +75, btnDesafio.y +5, (SDL_Color){255,255,255,255});


        SDL_SetRenderDrawColor(renderer, 17,168,189,255); // celeste {135, 246, 255}
        SDL_RenderFillRect(renderer, &btnMozart);
        mostrarTexto(renderer, "Mozart", font, btnMozart.x +75, btnMozart.y +5, (SDL_Color){255,255,255,255});

        SDL_SetRenderDrawColor(renderer, 17,168,189,255); // celeste {135, 246, 255}
        SDL_RenderFillRect(renderer, &btnEstadisticas);
        mostrarTexto(renderer, "Estadisticas", font, btnEstadisticas.x +35, btnEstadisticas.y +5, (SDL_Color){255,255,255,255});

         // Mostrar
        SDL_RenderPresent(renderer);

        }

    TTF_CloseFont(font);
    TTF_Quit();
    return modo;


}
int mostrarMenuConfiguracionSchornberg(SDL_Renderer* renderer,ConfiguracionSch *config)
{
    //ConfiguracionSch config = {0,0}; // INICIALIZO ENCASO DE ERROR DE FUENTE
    config->cantNotas=0;
    config->duracionIni=0;

    // Valores iniciales
    int cantidadNotas = 3;
    int duracionIni = 2000;

    // Definir flechas (izq y der) igual que vos
    const int flechaDer[7][7] = { {A,T,T,T,T,T,T},
                                {A,A,T,T,T,T,T},
                                {A,A,A,T,T,T,T},
                                {A,A,A,A,T,T,T},
                                {A,A,A,T,T,T,T},
                                {A,A,T,T,T,T,T},
                                {A,T,T,T,T,T,T} };
    const int flechaIzq[7][7] = { {T,T,T,T,T,T,A},
                                 {T,T,T,T,T,A,A},
                                 {T,T,T,T,A,A,A},
                                 {T,T,T,A,A,A,A},
                                 {T,T,T,T,A,A,A},
                                 {T,T,T,T,T,A,A},
                                 {T,T,T,T,T,T,A} };

    // Rectangulos para percibir el click donde creare las imagenes
    SDL_Rect flechaDerNotas = {1100, 250, 7*TAM_PIXEL, 7*TAM_PIXEL};
    SDL_Rect flechaIzqNotas = {900,  250, 7*TAM_PIXEL, 7*TAM_PIXEL};
    SDL_Rect flechaDerFreq  = {1100, 450, 7*TAM_PIXEL, 7*TAM_PIXEL};
    SDL_Rect flechaIzqFreq  = {900,  450, 7*TAM_PIXEL, 7*TAM_PIXEL};
    SDL_Rect btnGuardar = {700, 600, 200, 100};
    SDL_Rect btnVolver   = {400, 600, 200, 100}; // X,Y,ALTO , ANCHO DEL DIBUJO
    // creo las sombras de los botoncitos
    SDL_Rect sombraGuardar = {690, 590, 220, 120};
    SDL_Rect sombraVolver   = {390, 590, 220, 120};

    // cargo la fuente
    TTF_Init();
    TTF_Font * font = TTF_OpenFont("fnt/SUSEMono-Medium.ttf", 32);
    if (!font) {
        printf("Error cargando fuente: %s\n", TTF_GetError());
        return -1;
    }
    // loop de cfg.
    SDL_Event e;
    int corriendo = 1;
    int estadosiguiente;

    while (corriendo)
    {
        while (SDL_PollEvent(&e))
        {
            if(e.type==SDL_QUIT) {
                corriendo = 0;
                printf("Saliendo de SDL\n");
            }
            if(e.type == SDL_MOUSEBUTTONDOWN) {
                int x = e.button.x;
                int y = e.button.y;

                // Cantidad de Notas
                if (SDL_PointInRect(&(SDL_Point){x,y}, &flechaDerNotas)) {
                    if (cantidadNotas < 8)   // tope máximo
                        cantidadNotas++;
                }
                if (SDL_PointInRect(&(SDL_Point){x,y}, &flechaIzqNotas)) {
                    if (cantidadNotas > 3)   // tope mínimo
                        cantidadNotas--;
                }

                // Frecuencia de Nota
                if (SDL_PointInRect(&(SDL_Point){x,y}, &flechaDerFreq)) {
                    if(duracionIni<2000)
                        duracionIni= duracionIni + 100;

                }
                if (SDL_PointInRect(&(SDL_Point){x,y}, &flechaIzqFreq)) {
                    if (duracionIni > 500)
                        duracionIni= duracionIni - 100;
                }
                if (SDL_PointInRect(&(SDL_Point){x,y}, &btnGuardar)) {
                    // Acción de GUARDAR
                    printf("Configuración guardada!\n");
                    config->cantNotas = cantidadNotas;
                    config->duracionIni = duracionIni;
                    estadosiguiente=SCHORNBERG;
                    corriendo = 0; // salir después de guardar
                }

                if (SDL_PointInRect(&(SDL_Point){x,y}, &btnVolver)) {
                    // MODO DESAFIO
                    printf("VOLVER AL MENU\n");
                    estadosiguiente=MENU;
                    corriendo = 0;
                }
            }
        }

        // Limpiar pantalla
        SDL_SetRenderDrawColor(renderer, 0,0,0,255);
        SDL_RenderClear(renderer);

        // Dibujar textos
        mostrarTexto(renderer,"CONFIGURACIÓN",font,550,50,(SDL_Color){135, 246, 255,255});

        //  Cantidad de Notas
        dibujar(renderer,flechaDer,1100,250,7);
        dibujar(renderer,flechaIzq,900,250,7);
        mostrarTexto(renderer,"Cantidad de Notas",font,250,250,(SDL_Color){255,255,255,255});

        char Notas[10];
        sprintf(Notas, "%d", cantidadNotas); // paso el entero a un string
        mostrarTexto(renderer, Notas, font, 1000, 250,(SDL_Color){255,255,255,255});

        //  Frecuencia

        dibujar(renderer,flechaDer,1100,450,7);
        dibujar(renderer,flechaIzq,900,450,7);
        mostrarTexto(renderer,"Duración inicial",font,250,450,(SDL_Color){255,255,255,255});


        char durIn[10];          // cad para armar el texto
        char num[5];              // cad para el número
        sprintf(num, "%d", duracionIni);  // convierto el número a string
        strcpy(durIn, num);             // copio el número a bufFreq
        strcat(durIn, "ms");   // concateno

        mostrarTexto(renderer, durIn, font, 970, 450,(SDL_Color){255,255,255,255});

///// creacion de los dibujos de los botones////

        SDL_SetRenderDrawColor(renderer, 11,127,143,255); // celeste oscuro
        SDL_RenderFillRect(renderer, &sombraGuardar);

        SDL_SetRenderDrawColor(renderer, 140,0,0,255); // rojo oscuro
        SDL_RenderFillRect(renderer, &sombraVolver);

        SDL_SetRenderDrawColor(renderer, 17,168,189,255); // celeste {135, 246, 255}

        SDL_RenderFillRect(renderer, &btnGuardar);
        mostrarTexto(renderer, "Guardar", font, btnGuardar.x +35, btnGuardar.y +30, (SDL_Color){255,255,255,255});

        SDL_SetRenderDrawColor(renderer, 224,0,0,255); // rojo

        SDL_RenderFillRect(renderer, &btnVolver);
        mostrarTexto(renderer, "Volver", font, btnVolver.x + 30, btnVolver.y + 30, (SDL_Color){255,255,255,255});

        // Mostrar
        SDL_RenderPresent(renderer);
    }


    TTF_CloseFont(font);
    TTF_Quit();

    return estadosiguiente;
}
