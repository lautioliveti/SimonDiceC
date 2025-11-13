#include "menu.h"


void mostrarPantallaPresentacion(SDL_Renderer * renderer)
{
    TTF_Init();
    // Cargar fuente
    TTF_Font * font = TTF_OpenFont ("fnt/BitcountGridSingle_Cursive-Regular.ttf",32);
    if (!font)
    {
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
    char nombreJugador[30]="Usuario";


    SDL_StartTextInput(); //  habilita entrada de texto
    TTF_Init();
    TTF_Font * font = TTF_OpenFont ("fnt/BitcountGridSingle_Cursive-Regular.ttf",32);

    if (!font)
    {
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
            {
                corriendo = 0;
            }
            else
            {
                if (e.type == SDL_TEXTINPUT)
                {
                    if (cursor < TAM_NOMBRE - 1)
                    {
                        strcat(nombreJugador, e.text.text);
                        cursor += strlen(e.text.text);
                    }
                }

                else
                {
                    if (e.type == SDL_KEYDOWN)
                    {
                        if (e.key.keysym.sym == SDLK_BACKSPACE && cursor > 0)
                        {
                            nombreJugador[--cursor] = '\0';
                        }
                        else
                        {
                            if (e.key.keysym.sym == SDLK_RETURN && cursor > 0)
                            {
                                corriendo = 0;
                            }
                        }
                    }
                }
            }
        }

        // Mensaje de ayuda
        mostrarTexto(renderer,"Ingresar nombre del jugador ENTER",font,ANCHO_VENTANA/2 - 325, ALTO_VENTANA/2-30,color);

        // Mostrar nombre ingresado
        if (strlen(nombreJugador) > 0)
        {
            mostrarTexto(renderer,nombreJugador,font, ANCHO_VENTANA/2 - 120, ALTO_VENTANA/2 +50,color2);
        }

        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
    }

    crearJugador(jugador,nombreJugador);

    TTF_CloseFont(font);

    TTF_Quit();
    SDL_StopTextInput();//  desactiva entrada de texto
}

void esperarCierreModo()
{
    SDL_Event e;
    int duracion = 200;
    size_t inicio = SDL_GetTicks();
    while (SDL_GetTicks() - inicio < duracion)
        while (SDL_PollEvent(&e))
            {

            };
}
int mostrarMenuConfiguracionDes (SDL_Renderer* renderer, ConfiguracionDes *config)
{
    //ConfiguracionSch config = {0,0}; // INICIALIZO ENCASO DE ERROR DE FUENTE
    config->cantNotas=0;

    // Valores iniciales
    int cantidadNotas = 3;

    //  flechas (izq y der)
    const int flechaDer[7][7] = { {A,T,T,T,T,T,T},
        {A,A,T,T,T,T,T},
        {A,A,A,T,T,T,T},
        {A,A,A,A,T,T,T},
        {A,A,A,T,T,T,T},
        {A,A,T,T,T,T,T},
        {A,T,T,T,T,T,T}
    };
    const int flechaIzq[7][7] = { {T,T,T,T,T,T,A},
        {T,T,T,T,T,A,A},
        {T,T,T,T,A,A,A},
        {T,T,T,A,A,A,A},
        {T,T,T,T,A,A,A},
        {T,T,T,T,T,A,A},
        {T,T,T,T,T,T,A}
    };

    // Rectangulos para percibir el click donde creare las imagenes
    SDL_Rect flechaDerNotas = {1100, 250, 7*TAM_PIXEL, 7*TAM_PIXEL};
    SDL_Rect flechaIzqNotas = {900,  250, 7*TAM_PIXEL, 7*TAM_PIXEL};
    SDL_Rect flechaDerTimbre = {1100, 350, 7*TAM_PIXEL, 7*TAM_PIXEL};
    SDL_Rect flechaIzqTimbre = {900,  350, 7*TAM_PIXEL, 7*TAM_PIXEL};

    SDL_Rect btnGuardar = {700, 600, 200, 100};
    SDL_Rect btnVolver   = {400, 600, 200, 100}; // X,Y,ALTO , ANCHO DEL DIBUJO

    // creo las sombras de los botoncitos
    SDL_Rect sombraGuardar = {690, 590, 220, 120};
    SDL_Rect sombraVolver   = {390, 590, 220, 120};

    // cargo la fuente
    TTF_Init();
    TTF_Font * font = TTF_OpenFont("fnt/BitcountGridSingle_Cursive-Regular.ttf", 32);
    if (!font)
    {
        printf("Error cargando fuente: %s\n", TTF_GetError());
        return -1;
    }
    // loop de cfg.
    SDL_Event e;
    int corriendo = 1;
    int estadosiguiente;
    int timbre =PIANO;

    while (corriendo)
    {
        while (SDL_PollEvent(&e))
        {
            if(e.type==SDL_QUIT)
            {
                corriendo = 0;
                printf("Saliendo de SDL\n");
            }
            if(e.type == SDL_MOUSEBUTTONDOWN)
            {
                int x = e.button.x;
                int y = e.button.y;

                // Cantidad de Notas
                if (SDL_PointInRect(&(SDL_Point){x,y}, &flechaDerNotas))
                {
                    if (cantidadNotas < 8)   // tope maximo
                        cantidadNotas++;
                }
                if (SDL_PointInRect(&(SDL_Point){x,y}, &flechaIzqNotas))
                {
                    if (cantidadNotas > 3)   // tope manimo
                        cantidadNotas--;
                }
                // timbre
                if (SDL_PointInRect(&(SDL_Point){x,y}, &flechaDerTimbre))
                {
                    timbre= CP70; //piano
                }
                if (SDL_PointInRect(&(SDL_Point){x,y}, &flechaIzqTimbre))
                {
                    timbre= PIANO; //CP-70
                }

                if (SDL_PointInRect(&(SDL_Point){x,y}, &btnGuardar))
                {
                    // Accion de GUARDAR
                    //(restaurar luego) printf("Configuracion guardada!\n");
                    config->cantNotas = cantidadNotas;
                    config->timbre = timbre;
                    estadosiguiente=DESAFIO;
                    corriendo = 0; // salir despues de guardar
                }

                if (SDL_PointInRect(&(SDL_Point){x,y}, &btnVolver))
                {
                    // MODO DESAFIO
                    //(restaurar luego) printf("VOLVER AL MENU\n");
                    estadosiguiente=MENU;
                    corriendo = 0;
                }
            }
        }

        // Limpiar pantalla
        SDL_SetRenderDrawColor(renderer, 0,0,0,255);
        SDL_RenderClear(renderer);

        // Dibujar textos
        mostrarTexto(renderer,"CONFIGURACION",font,550,50,(SDL_Color){135, 246, 255,255});

        //  Cantidad de Notas
        dibujar(renderer,flechaDer,1100,250,7);
        dibujar(renderer,flechaIzq,900,250,7);
        mostrarTexto(renderer,"Cantidad de Notas",font,250,250,(SDL_Color){255,255,255,255});

        char Notas[10];
        sprintf(Notas, "%d", cantidadNotas); // paso el entero a un string
        mostrarTexto(renderer, Notas, font, 1000, 250,(SDL_Color){255,255,255,255});


        // Timbre
        dibujar(renderer, flechaDer, 1100, 350, 7);
        dibujar(renderer, flechaIzq, 900, 350, 7);
        mostrarTexto(renderer,"Timbre", font, 250, 350, (SDL_Color){255,255,255,255});

        if (timbre == 1)
        {
            mostrarTexto(renderer, "Piano", font, 970, 350, (SDL_Color){255,255,255,255});
        }
        else
        {
            mostrarTexto(renderer, "CP-70", font, 970, 350, (SDL_Color){255,255,255,255});
        }
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
int mostrarMenuInicial(SDL_Renderer *renderer)
{

    int modo;
    const int cruzSalir[7][7] =
    {
        {B, T, T, T, T, T, B},
        {T, B, T, T, T, B, T},
        {T, T, B, T, B, T, T},
        {T, T, T, B, T, T, T},
        {T, T, B, T, B, T, T},
        {T, B, T, T, T, B, T},
        {B, T, T, T, T, T, B}
    };

    TTF_Init();
    // Cargar fuente
    TTF_Font * font = TTF_OpenFont ("fnt/BitcountGridSingle_Cursive-Regular.ttf",32);
    if (!font)
    {
        printf("Error cargando fuente: %s\n", TTF_GetError());
        return -1;
    }


    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_Rect btnSchornberg = {ANCHO_VENTANA/2-150, ALTO_VENTANA/2-200, 300, 50};
    SDL_Rect btnDesafio   = {ANCHO_VENTANA/2-150, ALTO_VENTANA/2-50, 300, 50};
    SDL_Rect btnMozart   = {ANCHO_VENTANA/2-150, ALTO_VENTANA/2+100, 300, 50};
    SDL_Rect btnEstadisticas = {ANCHO_VENTANA/2-150, ALTO_VENTANA/2+250, 300, 50};
    SDL_Rect btnSalir = {ANCHO_VENTANA/2+500, ALTO_VENTANA/2+250, 50, 50};
    // sombra de botnes
    // creo las sombras de los botoncitos
    SDL_Rect sombraSchornberg = {ANCHO_VENTANA/2-160, ALTO_VENTANA/2-210, 320, 70};
    SDL_Rect sombraDesafio   = {ANCHO_VENTANA/2-160, ALTO_VENTANA/2-60, 320, 70};
    SDL_Rect sombraMozart   = {ANCHO_VENTANA/2-160, ALTO_VENTANA/2+90, 320, 70};
    SDL_Rect sombraEstadisticas = {ANCHO_VENTANA/2-160, ALTO_VENTANA/2+240, 320, 70};
    SDL_Rect sombraSalir = {ANCHO_VENTANA/2+490, ALTO_VENTANA/2+240, 70, 70};

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
                    //(restaurar luego) printf("MODO SCHORNBERG!\n");
                    modo=SCHORNBERG;
                    corriendo = 0; // salir despu�s de guardar
                }

                if (SDL_PointInRect(&(SDL_Point){x,y}, &btnDesafio))
                {
                    // MODO DESAFIO
                    //(restaurar luego) printf("ENTRASTE AL MODO DESAFIO\n");
                    modo=DESAFIO;
                    corriendo = 0;
                }
                if (SDL_PointInRect(&(SDL_Point){x,y}, &btnMozart))
                {
                    // MODO DESAFIO
                    //(restaurar luego) printf("ENTRASTE AL MODO MOZART\n");
                    modo=MOZART;
                    corriendo = 0;
                }
                if (SDL_PointInRect(&(SDL_Point){x,y}, &btnEstadisticas))
                {
                    // MODO DESAFIO
                    //(restaurar luego) printf("ENTRASTE AL MODO ESTADISITCAS\n");
                    mostrarMenuEstadisticas(renderer);
                    modo=ESTADISTICAS;
                    corriendo = 0;
                }
                if(SDL_PointInRect(&(SDL_Point){x,y},&btnSalir))
                {
                    //(restaurar luego) printf("SALIENDO DEL JUEGO\n");
                    modo=SALIR;
                    corriendo=0;
                }
            }
        }
        mostrarTexto(renderer,"MENU PRINCIPAL",font,490,50,(SDL_Color){135, 246, 255,255});
        // sombra
        SDL_SetRenderDrawColor(renderer, 11,127,143,255); // celeste oscuro
        SDL_RenderFillRect(renderer, &sombraSchornberg);
        SDL_SetRenderDrawColor(renderer, 11,127,143,255); // celeste oscuro
        SDL_RenderFillRect(renderer, &sombraDesafio);
        SDL_SetRenderDrawColor(renderer, 11,127,143,255); // celeste oscuro
        SDL_RenderFillRect(renderer, &sombraMozart);
        SDL_SetRenderDrawColor(renderer, 11,127,143,255); // celeste oscuro
        SDL_RenderFillRect(renderer, &sombraEstadisticas);
        SDL_SetRenderDrawColor(renderer, 100,0,0,255); // rojo oscuro
        SDL_RenderFillRect(renderer, &sombraSalir);

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

        SDL_SetRenderDrawColor(renderer, 255,0,0,255); // rojo
        SDL_RenderFillRect(renderer, &btnSalir);
        dibujar(renderer,cruzSalir,ANCHO_VENTANA/2+507, ALTO_VENTANA/2+257,5);



        // Mostrar
        SDL_RenderPresent(renderer);

    }

    TTF_CloseFont(font);
    TTF_Quit();
    return modo;


}
void mostrarErrorMozart(SDL_Renderer * renderer)
{
    TTF_Init();
    TTF_Font *font = TTF_OpenFont ("fnt/BitcountGridSingle_Cursive-Regular.ttf",32);

    prepararEscena(renderer);
    mostrarTexto(renderer, "No hay canciones registradas con ese nombre.", font, 200, ALTO_VENTANA/2, (SDL_Color){255,255,255,255});
    presentarEscena(renderer);
    SDL_Delay(2000);

    TTF_CloseFont(font);
}
void mostrarMenuEstadisticas(SDL_Renderer *renderer)
{

    TTF_Init();
    // Cargar fuente
    TTF_Font * font = TTF_OpenFont ("fnt/BitcountGridSingle_Cursive-Regular.ttf",32);
    if (!font)
    {
        printf("Error cargando fuente: %s\n", TTF_GetError());
    }


    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_Rect btn3Notas = {ANCHO_VENTANA/2-150, ALTO_VENTANA/2-240, 300, 50};
    SDL_Rect btn4Notas = {ANCHO_VENTANA/2-150, ALTO_VENTANA/2-140, 300, 50};
    SDL_Rect btn5Notas = {ANCHO_VENTANA/2-150, ALTO_VENTANA/2-40, 300, 50};
    SDL_Rect btn6Notas = {ANCHO_VENTANA/2-150, ALTO_VENTANA/2+60, 300, 50};
    SDL_Rect btn7Notas = {ANCHO_VENTANA/2-150, ALTO_VENTANA/2+160, 300, 50};
    SDL_Rect btn8Notas = {ANCHO_VENTANA/2-150, ALTO_VENTANA/2+260, 300, 50};
    SDL_Rect btnVolver = {ANCHO_VENTANA/2+400, ALTO_VENTANA/2+260, 150, 50};

    // sombra de botnes
    // creo las sombras de los botoncitos

    SDL_Rect sombra3 = {ANCHO_VENTANA/2-160, ALTO_VENTANA/2-250, 320, 70};
    SDL_Rect sombra4 = {ANCHO_VENTANA/2-160, ALTO_VENTANA/2-150, 320, 70};
    SDL_Rect sombra5 = {ANCHO_VENTANA/2-160, ALTO_VENTANA/2-50, 320, 70};
    SDL_Rect sombra6 = {ANCHO_VENTANA/2-160, ALTO_VENTANA/2+50, 320, 70};
    SDL_Rect sombra7 = {ANCHO_VENTANA/2-160, ALTO_VENTANA/2+150, 320, 70};
    SDL_Rect sombra8 = {ANCHO_VENTANA/2-160, ALTO_VENTANA/2+250, 320, 70};
    SDL_Rect sombraVolver = {ANCHO_VENTANA/2+390, ALTO_VENTANA/2+250, 170, 70};

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
                if (SDL_PointInRect(&(SDL_Point){x,y}, &btn3Notas))
                {

                    //(restaurar luego) printf("ESTADISTICAS 3\n");
                    mostrarTopEstadisticasSDL(renderer,3);
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                    SDL_RenderClear(renderer);


                }
                if (SDL_PointInRect(&(SDL_Point){x,y}, &btn4Notas))
                {

                    //(restaurar luego) printf("ESTADISTICAS 4\n");
                    mostrarTopEstadisticasSDL(renderer,4);
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                    SDL_RenderClear(renderer);


                }
                if (SDL_PointInRect(&(SDL_Point){x,y}, &btn5Notas))
                {

                    //(restaurar luego) printf("ESTADISTICAS 5\n");
                    mostrarTopEstadisticasSDL(renderer,5);
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                    SDL_RenderClear(renderer);


                }
                if (SDL_PointInRect(&(SDL_Point){x,y}, &btn6Notas))
                {

                    //(restaurar luego) printf("ESTADISTICAS 6\n");
                    mostrarTopEstadisticasSDL(renderer,6);
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                    SDL_RenderClear(renderer);

                }
                if(SDL_PointInRect(&(SDL_Point){x,y},&btn7Notas))
                {
                    //(restaurar luego) printf("ESTADISTICAS 7\n");
                    mostrarTopEstadisticasSDL(renderer,7);
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                    SDL_RenderClear(renderer);


                }
                if(SDL_PointInRect(&(SDL_Point){x,y},&btn8Notas))
                {
                    //(restaurar luego) printf("ESTADISTICAS 8\n");
                    mostrarTopEstadisticasSDL(renderer,8);
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                    SDL_RenderClear(renderer);

                }
                if(SDL_PointInRect(&(SDL_Point){x,y},&btnVolver))
                {
                    //(restaurar luego) printf("Volver al menu\n");

                    corriendo=0;
                }
            }
        }
        mostrarTexto(renderer,"ESTADISTICAS",font,510,50,(SDL_Color){135, 246, 255,255});
        // sombra
        SDL_SetRenderDrawColor(renderer, 11,127,143,255); // celeste oscuro
        SDL_RenderFillRect(renderer, &sombra3);
        SDL_SetRenderDrawColor(renderer, 11,127,143,255); // celeste oscuro
        SDL_RenderFillRect(renderer, &sombra4);
        SDL_SetRenderDrawColor(renderer, 11,127,143,255); // celeste oscuro
        SDL_RenderFillRect(renderer, &sombra5);
        SDL_SetRenderDrawColor(renderer, 11,127,143,255); // celeste oscuro
        SDL_RenderFillRect(renderer, &sombra6);
        SDL_SetRenderDrawColor(renderer, 11,127,143,255); // celeste oscuro
        SDL_RenderFillRect(renderer, &sombra7);
        SDL_SetRenderDrawColor(renderer, 11,127,143,255); // celeste oscuro
        SDL_RenderFillRect(renderer, &sombra8);
        SDL_SetRenderDrawColor(renderer, 100,0,0,255); // rojo oscuro
        SDL_RenderFillRect(renderer, &sombraVolver);



        // botones click
        SDL_SetRenderDrawColor(renderer, 17,168,189,255); // celeste {135, 246, 255}
        SDL_RenderFillRect(renderer, &btn3Notas);
        mostrarTexto(renderer, "3 Notas", font, btn3Notas.x +75, btn3Notas.y +5, (SDL_Color){255,255,255,255});

        SDL_SetRenderDrawColor(renderer, 17,168,189,255); // celeste {135, 246, 255}
        SDL_RenderFillRect(renderer, &btn4Notas);
        mostrarTexto(renderer, "4 Notas", font, btn4Notas.x +75, btn4Notas.y +5, (SDL_Color){255,255,255,255});

        SDL_SetRenderDrawColor(renderer, 17,168,189,255); // celeste {135, 246, 255}
        SDL_RenderFillRect(renderer, &btn5Notas);
        mostrarTexto(renderer, "5 Notas", font, btn5Notas.x +75, btn5Notas.y +5, (SDL_Color){255,255,255,255});

        SDL_SetRenderDrawColor(renderer, 17,168,189,255); // celeste {135, 246, 255}
        SDL_RenderFillRect(renderer, &btn6Notas);
        mostrarTexto(renderer, "6 Notas", font, btn6Notas.x +75, btn6Notas.y +5, (SDL_Color){255,255,255,255});

        SDL_SetRenderDrawColor(renderer, 17,168,189,255); // celeste {135, 246, 255}
        SDL_RenderFillRect(renderer, &btn7Notas);
        mostrarTexto(renderer, "7 Notas", font, btn7Notas.x +75, btn7Notas.y +5, (SDL_Color){255,255,255,255});

        SDL_SetRenderDrawColor(renderer, 17,168,189,255); // celeste {135, 246, 255}
        SDL_RenderFillRect(renderer, &btn8Notas);
        mostrarTexto(renderer, "8 Notas", font, btn8Notas.x +75, btn8Notas.y +5, (SDL_Color){255,255,255,255});

        SDL_SetRenderDrawColor(renderer, 255,0,0,255); // celeste {135, 246, 255}
        SDL_RenderFillRect(renderer, &btnVolver);
        mostrarTexto(renderer, "Volver", font, btnVolver.x +20, btnVolver.y +5, (SDL_Color){255,255,255,255});

        // Mostrar
        SDL_RenderPresent(renderer);

    }

    TTF_CloseFont(font);
    TTF_Quit();

}
int mostrarMenuConfiguracionMoz(SDL_Renderer* renderer, ConfiguracionMoz *config)
{
    int timbre;
    config->duracionIni=0;

    // Valores iniciales
    int duracionIni=500;

    //  flechas (izq y der)
    const int flechaDer[7][7] = { {A,T,T,T,T,T,T},
        {A,A,T,T,T,T,T},
        {A,A,A,T,T,T,T},
        {A,A,A,A,T,T,T},
        {A,A,A,T,T,T,T},
        {A,A,T,T,T,T,T},
        {A,T,T,T,T,T,T}
    };
    const int flechaIzq[7][7] = { {T,T,T,T,T,T,A},
        {T,T,T,T,T,A,A},
        {T,T,T,T,A,A,A},
        {T,T,T,A,A,A,A},
        {T,T,T,T,A,A,A},
        {T,T,T,T,T,A,A},
        {T,T,T,T,T,T,A}
    };
    // Rectangulos para percibir el click donde creare las imagenes
    SDL_Rect flechaDerFreq  = {1100, 250, 7*TAM_PIXEL, 7*TAM_PIXEL};
    SDL_Rect flechaIzqFreq  = {800,  250, 7*TAM_PIXEL, 7*TAM_PIXEL};
    SDL_Rect flechaDerTimbre = {1100, 350, 7*TAM_PIXEL, 7*TAM_PIXEL};
    SDL_Rect flechaIzqTimbre = {800,  350, 7*TAM_PIXEL, 7*TAM_PIXEL};

    SDL_Rect btnGuardar = {700, 600, 200,100};
    SDL_Rect btnVolver   = {400, 600, 200, 100}; // X,Y,ALTO , ANCHO DEL DIBUJO
    // creo las sombras de los botoncitos
    SDL_Rect sombraGuardar = {690, 590, 220, 120};
    SDL_Rect sombraVolver   = {390, 590, 220, 120};

    // cargo la fuente
    TTF_Init();
    TTF_Font * font = TTF_OpenFont("fnt/BitcountGridSingle_Cursive-Regular.ttf", 32);
    if (!font)
    {
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
            if(e.type==SDL_QUIT)
            {
                corriendo = 0;
                printf("Saliendo de SDL\n");
            }
            if(e.type == SDL_MOUSEBUTTONDOWN)
            {
                int x = e.button.x;
                int y = e.button.y;

                // Elegir cancion
                //Timbre
                if (SDL_PointInRect(&(SDL_Point){x,y}, &flechaDerTimbre))
                {
                    timbre= CP70; //piano
                }

                if (SDL_PointInRect(&(SDL_Point){x,y}, &flechaIzqTimbre))
                {
                    timbre= PIANO; //CP-70
                }
                // Frecuencia de Nota
                if (SDL_PointInRect(&(SDL_Point){x,y}, &flechaDerFreq))
                {
                    if(duracionIni<2000)
                    {
                        duracionIni= duracionIni + 100;
                    }
                }
                if(SDL_PointInRect(&(SDL_Point){x,y},&flechaIzqFreq))
                {
                    if(duracionIni>500)
                    {
                        duracionIni= duracionIni - 100;
                    }
                }

                if (SDL_PointInRect(&(SDL_Point){x,y}, &btnGuardar))
                {
                    //(restaurar luego) printf("Configuracion guardada moz!\n");
                    config->duracionIni = duracionIni;
                    estadosiguiente=MOZART;
                    corriendo = 0; // salir despues de guardar
                }

                if (SDL_PointInRect(&(SDL_Point){x,y}, &btnVolver))
                {
                    // MODO DESAFIO
                    //(restaurar luego) printf("VOLVER AL MENU\n");
                    estadosiguiente=MENU;
                    corriendo = 0;
                }
            }
        }
        // Limpiar pantalla
        SDL_SetRenderDrawColor(renderer, 0,0,0,255);
        SDL_RenderClear(renderer);

        // Dibujar textos
        mostrarTexto(renderer,"CONFIGURACION",font,550,50,(SDL_Color){135, 246, 255,255});

        //  Frecuencia
        dibujar(renderer,flechaDer,flechaDerFreq.x, flechaDerFreq.y,7);
        dibujar(renderer,flechaIzq, flechaIzqFreq.x, flechaIzqFreq.y,7);
        mostrarTexto(renderer,"Duracion inicial",font,250,250,(SDL_Color){255,255,255,255});

        char durIn[10];          // cad para armar el texto
        char num[5];              // cad para el numero
        sprintf(num, "%d", duracionIni);  // convierto el numero a string
        strcpy(durIn, num);             // copio el numero a bufFreq
        strcat(durIn, "ms");   // concateno

        mostrarTexto(renderer, durIn, font, 920, 250,(SDL_Color){255,255,255,255});

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

        // Timbre
        dibujar(renderer, flechaDer, flechaDerTimbre.x, flechaDerTimbre.y, 7);
        dibujar(renderer, flechaIzq, flechaIzqTimbre.x, flechaIzqTimbre.y, 7);
        mostrarTexto(renderer,"Timbre", font, 250, 350, (SDL_Color){255,255,255,255});

        if (timbre == 1)
        {
            mostrarTexto(renderer, "Piano", font, 925, 350, (SDL_Color){255,255,255,255});
        }
        else
        {
            mostrarTexto(renderer, "CP-70", font, 925, 350, (SDL_Color){255,255,255,255});
        }
        // Mostrar
        SDL_RenderPresent(renderer);
    }

    TTF_CloseFont(font);
    TTF_Quit();

    config->duracionIni = duracionIni;
    config->timbre = timbre;

    //free(config->archivo);

    return estadosiguiente;
}
void buscarNombreArchivo(SDL_Renderer* renderer, ConfiguracionMoz* config)
{
    TTF_Init();
    TTF_Font *fontGuardado= TTF_OpenFont ("fnt/BitcountGridSingle_Cursive-Regular.ttf",32);
    if(!fontGuardado)
    {
        printf("Error al cargar la fuente");
        return;
    }

    char nombreArchivo[TAMANIO_ARCHIVO_WINDOWS] = {0};
    int corriendo = 1;
    int cursor = 0;
    nombreArchivo[0] = '\0';
    SDL_Color color = {135, 246, 255};  // Celeste
    SDL_Color color2 = {240, 255, 255}; // Tipo de blanco
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // fondo negro

    SDL_Event e;
    SDL_StartTextInput();

    while (corriendo)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT) corriendo = 0;
            else if (e.type == SDL_TEXTINPUT && cursor < TAMANIO_ARCHIVO_WINDOWS - 1)
            {
                strcat(nombreArchivo, e.text.text);
                cursor += strlen(e.text.text);
            }
            else if (e.type == SDL_KEYDOWN && cursor > 0)
            {
                if (e.key.keysym.sym == SDLK_BACKSPACE )
                {
                    nombreArchivo[--cursor] = '\0';
                }

                else if (e.key.keysym.sym == SDLK_RETURN)
                {
                    corriendo = 0;
                }

            }
        }
        mostrarTexto(renderer,"- Ingrese nombre del archivo -",fontGuardado,340, ALTO_VENTANA/2-200,color);
        if (strlen(nombreArchivo) > 0)
        {
            mostrarTexto(renderer,nombreArchivo,fontGuardado, ANCHO_VENTANA/2-140, ALTO_VENTANA/2,color2);
        }

        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
    }

    strcat(nombreArchivo,".txt");
    config->archivo = malloc(strlen(nombreArchivo) +1);
    if(config->archivo == NULL) {
        printf("\nFallo en asignar memoria para nombre");
    }
    strcpy(config->archivo,nombreArchivo);
    //(restaurar luego) printf("Archivo final:%s", nombreArchivo);
    TTF_CloseFont(fontGuardado);
    TTF_Quit();
}
int mostrarMenuConfiguracionSchornberg(SDL_Renderer* renderer,ConfiguracionSch *config)
{
    //ConfiguracionSch config = {0,0}; // INICIALIZO ENCASO DE ERROR DE FUENTE
    config->cantNotas=0;
    config->duracionIni=0;

    // Valores iniciales
    int cantidadNotas = 3;
    int duracionIni = 500;

    //  flechas (izq y der)
    const int flechaDer[7][7] = { {A,T,T,T,T,T,T},
        {A,A,T,T,T,T,T},
        {A,A,A,T,T,T,T},
        {A,A,A,A,T,T,T},
        {A,A,A,T,T,T,T},
        {A,A,T,T,T,T,T},
        {A,T,T,T,T,T,T}
    };
    const int flechaIzq[7][7] = { {T,T,T,T,T,T,A},
        {T,T,T,T,T,A,A},
        {T,T,T,T,A,A,A},
        {T,T,T,A,A,A,A},
        {T,T,T,T,A,A,A},
        {T,T,T,T,T,A,A},
        {T,T,T,T,T,T,A}
    };

    // Rectangulos para percibir el click donde creare las imagenes
    SDL_Rect flechaDerNotas = {1100, 250, 7*TAM_PIXEL, 7*TAM_PIXEL};
    SDL_Rect flechaIzqNotas = {900,  250, 7*TAM_PIXEL, 7*TAM_PIXEL};
    SDL_Rect flechaDerTimbre = {1100, 350, 7*TAM_PIXEL, 7*TAM_PIXEL};
    SDL_Rect flechaIzqTimbre = {900,  350, 7*TAM_PIXEL, 7*TAM_PIXEL};
    SDL_Rect flechaDerFreq  = {1100, 450, 7*TAM_PIXEL, 7*TAM_PIXEL};
    SDL_Rect flechaIzqFreq  = {900,  450, 7*TAM_PIXEL, 7*TAM_PIXEL};
    SDL_Rect btnGuardar = {700, 600, 200, 100};
    SDL_Rect btnVolver   = {400, 600, 200, 100}; // X,Y,ALTO , ANCHO DEL DIBUJO

    // creo las sombras de los botoncitos
    SDL_Rect sombraGuardar = {690, 590, 220, 120};
    SDL_Rect sombraVolver   = {390, 590, 220, 120};

    // cargo la fuente
    TTF_Init();
    TTF_Font * font = TTF_OpenFont("fnt/BitcountGridSingle_Cursive-Regular.ttf", 32);
    if (!font)
    {
        printf("Error cargando fuente: %s\n", TTF_GetError());
        return -1;
    }
    // loop de cfg.
    SDL_Event e;
    int corriendo = 1;
    int estadosiguiente;
    int timbre =PIANO;

    while (corriendo)
    {
        while (SDL_PollEvent(&e))
        {
            if(e.type==SDL_QUIT)
            {
                corriendo = 0;
                printf("Saliendo de SDL\n");
            }
            if(e.type == SDL_MOUSEBUTTONDOWN)
            {
                int x = e.button.x;
                int y = e.button.y;

                // Cantidad de Notas
                if (SDL_PointInRect(&(SDL_Point){x,y}, &flechaDerNotas))
                {
                    if (cantidadNotas < 8)   // tope maximo
                        cantidadNotas++;
                }
                if (SDL_PointInRect(&(SDL_Point){x,y}, &flechaIzqNotas))
                {
                    if (cantidadNotas > 3)   // tope manimo
                        cantidadNotas--;
                }

                // Frecuencia de Nota
                if (SDL_PointInRect(&(SDL_Point){x,y}, &flechaDerFreq))
                {
                    if(duracionIni<2000)
                        duracionIni= duracionIni + 100;

                }
                if (SDL_PointInRect(&(SDL_Point){x,y}, &flechaIzqFreq))
                {
                    if (duracionIni > 500)
                        duracionIni= duracionIni - 100;
                }
                // timbre
                if (SDL_PointInRect(&(SDL_Point){x,y}, &flechaDerTimbre))
                {
                    timbre= CP70; //piano
                }
                if (SDL_PointInRect(&(SDL_Point){x,y}, &flechaIzqTimbre))
                {
                    timbre= PIANO; //CP-70
                }

                if (SDL_PointInRect(&(SDL_Point){x,y}, &btnGuardar))
                {
                    // Accion de GUARDAR
                    //(restaurar luego) printf("Configuracion guardada!\n");
                    config->cantNotas = cantidadNotas;
                    config->duracionIni = duracionIni;
                    config->timbre = timbre;
                    estadosiguiente=SCHORNBERG;
                    corriendo = 0; // salir despues de guardar
                }

                if (SDL_PointInRect(&(SDL_Point){x,y}, &btnVolver))
                {
                    // MODO DESAFIO
                    //(restaurar luego) printf("VOLVER AL MENU\n");
                    estadosiguiente=MENU;
                    corriendo = 0;
                }
            }
        }

        // Limpiar pantalla
        SDL_SetRenderDrawColor(renderer, 0,0,0,255);
        SDL_RenderClear(renderer);

        // Dibujar textos
        mostrarTexto(renderer,"CONFIGURACION",font,550,50,(SDL_Color){135, 246, 255,255});

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
        mostrarTexto(renderer,"Duracion inicial",font,250,450,(SDL_Color){255,255,255,255});


        char durIn[10];          // cad para armar el texto
        char num[5];              // cad para el n�mero
        sprintf(num, "%d", duracionIni);  // convierto el n�mero a string
        strcpy(durIn, num);             // copio el n�mero a bufFreq
        strcat(durIn, "ms");   // concateno

        mostrarTexto(renderer, durIn, font, 970, 450,(SDL_Color){255,255,255,255});
        // Timbre
        dibujar(renderer, flechaDer, 1100, 350, 7);
        dibujar(renderer, flechaIzq, 900, 350, 7);
        mostrarTexto(renderer,"Timbre", font, 250, 350, (SDL_Color){255,255,255,255});

        if (timbre == 1)
        {
            mostrarTexto(renderer, "Piano", font, 970, 350, (SDL_Color){255,255,255,255});
        }
        else
        {
            mostrarTexto(renderer, "CP-70", font, 970, 350, (SDL_Color){255,255,255,255});
        }

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


