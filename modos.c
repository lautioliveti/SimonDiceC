#include "modos.h"

int modoDesafio(Jugador *jugador, ConfiguracionDes *configDes, SDL_Window *ventana, SDL_Renderer *renderer)
{


    NotasApp app;
    inicializarNotasGenerico(&app, configDes->cantNotas);

    Mix_Chunk **sonidos = inicializarAudio(configDes->cantNotas, configDes->timbre);
    if (!sonidos)
    {
        printf("Error: No se pudieron cargar los sonidos\n");
        return MENU;
    }

    if (TTF_Init() == -1)
    {
        printf("Error iniciando TTF: %s\n", TTF_GetError());
        destruirAudio(sonidos, configDes->cantNotas);
        return MENU;
    }

    TTF_Font *font = TTF_OpenFont("fnt/BitcountGridSingle_Cursive-Regular.ttf", 20);
    if (!font)
    {
        printf("Error cargando fuente: %s\n", TTF_GetError());
        destruirAudio(sonidos, configDes->cantNotas);
        TTF_Quit();
        return MENU;
    }
    TTF_Font *fontGuardado = TTF_OpenFont("fnt/BitcountGridSingle_Cursive-Regular.ttf", 40);
    if (!fontGuardado)
    {
        printf("Error cargando fuente: %s\n", TTF_GetError());
        destruirAudio(sonidos, configDes->cantNotas);
        TTF_Quit();
        return MENU;
    }

    int secuenciaDesafio[100] = {0};
    int longitudSecuenciaDesafio = 0;

    SDL_Rect btnDeshacer = {10, 200, 120, 50};
    SDL_Rect btnVolver   = {10, 400, 120, 50};
    SDL_Rect btnTerminar = {10, 300, 120, 50};

    int juegoActivo = 1;
    int estadoFinal = MENU;
    SDL_Event e;

    while (juegoActivo == 1)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                juegoActivo = 0;
                estadoFinal = SALIR;
            }

            if (e.type == SDL_MOUSEBUTTONDOWN)
            {
                int mouseX = e.button.x;
                int mouseY = e.button.y;

                if (SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &btnDeshacer))
                {
                    if (longitudSecuenciaDesafio > 0)
                    {
                        longitudSecuenciaDesafio--;
                    }
                }
                else if (SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &btnVolver))
                {
                    //(restaurar luego) printf("VOLVER AL MENU\n");
                    estadoFinal = MENU;
                    juegoActivo = 0;
                }
                else if (SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &btnTerminar))
                {
                    //(restaurar luego) printf("TERMINAR MODO DESAFIO\n");
                    mostrarTexto(renderer, "Desafio Terminado!", font, ANCHO_VENTANA / 2 - 100, ALTO_VENTANA / 2,(SDL_Color){255,255,255,255});
                    presentarEscena(renderer);
                    esperar(1000, &juegoActivo);
                    estadoFinal = MENU;
                    juegoActivo = 2;
                }
                else
                {
                    for (int i = 0; i < configDes->cantNotas; i++)
                    {
                        ColorObj *c = app.arrayColores[i];
                        int tamPixelFinal = TAM_PIXEL + 5;
                        int ancho = 20 * tamPixelFinal;
                        int alto = 20 * tamPixelFinal;
                        int xIni = (ANCHO_VENTANA * c->offsetX - ancho * c->offsetX) / 100;
                        int yIni = (ALTO_VENTANA * c->offsetY - alto * c->offsetY) / 100;

                        SDL_Rect zona = {xIni, yIni, ancho, alto};
                        if (SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &zona))
                        {
                            if (longitudSecuenciaDesafio < 100)
                                secuenciaDesafio[longitudSecuenciaDesafio++] = i;

                            c->activado = 1;
                            prepararEscena(renderer);
                            renderNotasGenerico(jugador, configDes->cantNotas, renderer, &app);
                            mostrarSecuenciaDesafio(renderer, secuenciaDesafio, longitudSecuenciaDesafio,configDes->cantNotas, font);

                            reproducirSonido(sonidos, i, configDes->cantNotas);

                            SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
                            SDL_RenderFillRect(renderer, &btnDeshacer);
                            mostrarTexto(renderer, "Deshacer", font, btnDeshacer.x + 15,btnDeshacer.y + 15, (SDL_Color){255,255,255,255});

                            SDL_SetRenderDrawColor(renderer, 224, 0, 0, 255);
                            SDL_RenderFillRect(renderer, &btnVolver);
                            mostrarTexto(renderer, "Volver", font, btnVolver.x + 25, btnVolver.y + 15, (SDL_Color){255,255,255,255});


                            SDL_SetRenderDrawColor(renderer, 17,168,189,255);
                            SDL_RenderFillRect(renderer, &btnTerminar);
                            mostrarTexto(renderer, "Terminar", font, btnTerminar.x + 15, btnTerminar.y + 15, (SDL_Color){255,255,255,255});
                            presentarEscena(renderer);

                            esperar(200, &juegoActivo);
                            c->activado = 0;
                            //printf("\nSeq: ");

                            break;
                        }
                    }
                }
            }
        }

        prepararEscena(renderer);
        renderNotasGenerico(jugador, configDes->cantNotas, renderer, &app);
        mostrarSecuenciaDesafio(renderer, secuenciaDesafio, longitudSecuenciaDesafio,configDes->cantNotas, font);


        SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
        SDL_RenderFillRect(renderer, &btnDeshacer);
        mostrarTexto(renderer, "Deshacer", font, btnDeshacer.x + 15, btnDeshacer.y + 15, (SDL_Color){255,255,255,255});

        SDL_SetRenderDrawColor(renderer, 224, 0, 0, 255);
        SDL_RenderFillRect(renderer, &btnVolver);
        mostrarTexto(renderer, "Volver", font, btnVolver.x + 25, btnVolver.y + 15,(SDL_Color){255,255,255,255});

        SDL_SetRenderDrawColor(renderer, 17,168,189,255);
        SDL_RenderFillRect(renderer, &btnTerminar);
        mostrarTexto(renderer, "Terminar", font, btnTerminar.x + 15, btnTerminar.y + 15,(SDL_Color){255,255,255,255});

        presentarEscena(renderer);
        SDL_Delay(16);
    }

    if (juegoActivo == 2)
    {
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
            mostrarTexto(renderer,"- Ingrese nombre del archivo -",fontGuardado,ANCHO_VENTANA/2-380, ALTO_VENTANA/2-200,color);
            if (strlen(nombreArchivo) > 0)
            {
                mostrarTexto(renderer,nombreArchivo,fontGuardado, ANCHO_VENTANA/2-140, ALTO_VENTANA/2,color2);
            }

            SDL_RenderPresent(renderer);
            SDL_RenderClear(renderer);
        }
        strcat(nombreArchivo,".txt");
        guardarMelodiaDesafio(nombreArchivo, secuenciaDesafio, longitudSecuenciaDesafio,configDes->cantNotas);
    }

    destruirAudio(sonidos, configDes->cantNotas);
    TTF_CloseFont(font);
    TTF_CloseFont(fontGuardado);
    TTF_Quit();
    return estadoFinal;
}
void guardarMelodiaDesafio(const char *nombreArchivo, int *secuencia, int longitud, int cantNotas)
{
    FILE *archivo = fopen(nombreArchivo, "w");
    if (!archivo)
    {
        printf("Error al crear el archivo de melodía.\n");
        return;
    }

    fprintf(archivo, "%d\n", cantNotas);


    for (int i = 0; i < longitud; i++)
    {
        char *nombreNota = obtenerNombreNota(secuencia[i], cantNotas);
        fprintf(archivo, "%s ", nombreNota ? nombreNota : "ERR");
    }

    fprintf(archivo, "\n");
    fclose(archivo);
    //(restaurar luego) printf("Melodia guardada en %s\n", nombreArchivo);
}
bool verificarSecuenciaMaxima(SDL_Renderer *renderer, int longitudSecuencia, int maxSecuencia,TTF_Font *font)
{
    if (longitudSecuencia < maxSecuencia)
        return false; // no se alcanzo el límite

    //(restaurar luego) printf("Secuencia maxima alcanzada (%d pasos)\n", maxSecuencia);


    if (font)
    {

        mostrarTexto(renderer, "SAY NO MORE", font, ANCHO_VENTANA / 2 -50, ALTO_VENTANA / 2, (SDL_Color){0, 255, 0, 255}); // verde
        presentarEscena(renderer);
        SDL_Delay(3000);
    }

    return true; // se alcanzó la secuencia máxima 100
}
void mostrarGameOver(SDL_Renderer *renderer, Jugador *jugador,TTF_Font *font)
{
    mostrarTexto(renderer, "GAME OVER", font, ANCHO_VENTANA / 2-50, ALTO_VENTANA / 2, (SDL_Color){255, 0, 0, 255}); // rojito
    presentarEscena(renderer);
    SDL_Delay(3000);

}
void mostrarPuntajeActual(SDL_Renderer *renderer, Jugador *jugador, TTF_Font *font)
{
    char texto[15];
    sprintf(texto, "Puntaje: %d", jugador->puntaje);
    mostrarTexto(renderer, texto, font, 20, 20,(SDL_Color){255, 255, 255, 255});
}
char* obtenerNombreNota(int indice, int cantNotas)
{

    char* escalas[6][8] =
    {
        {"DO", "MI", "SOL"},  // C Mayor
        {"DO", "MI", "SOL", "LA"},  // C6
        {"DO", "RE", "MI", "SOL", "LA"},  // penta
        {"DO", "RE", "MI", "FA#", "SOL#", "LA#"},  //  Hexatonal
        {"DO", "RE", "RE#", "FA", "SOL", "SOL#", "SI"},  //  Escala menor armónica
        {"DO", "RE", "MI", "FA", "SOL", "LA", "SI", "DO8"}  // Escala mayor + 8va
    };

    if (cantNotas >= 3 && cantNotas <= 8 && indice >= 0 && indice < cantNotas)
    {
        return escalas[cantNotas - 3][indice];
    }
    return escalas [0][0];
}
void mostrarSecuenciaDesafio(SDL_Renderer *renderer, int secuencia[], int longitud, int cantNotas, TTF_Font *font)
{
    char texto[50] = "Melodia: ";
    int inicio = 0;
    if (longitud > 8)
    {
        strcat(texto, "... ");
        inicio = longitud - 8;
    }

    for (int i = inicio; i < longitud; i++)
    {
        strcat(texto, obtenerNombreNota(secuencia[i], cantNotas));
        strcat(texto, " ");
    }
    mostrarTexto(renderer, texto, font, 0, 0, (SDL_Color){17,168,189,255});
}
void modoSchornberg(Jugador *jugador, ConfiguracionSch *configSc, SDL_Window *ventana, SDL_Renderer *renderer)
{
    srand(time(NULL));

    NotasApp app;

    const int tilde[7][7] =
    {
        {T, T, T, T, T, T, T},
        {T, T, T, T, T, T, V},
        {T, T, T, T, T, V, T},
        {T, T, T, T, V, T, T},
        {V, T, T, V, T, T, T},
        {T, V, V, T, T, T, T},
        {T, T, T, T, T, T, T}
    };


    // Inicializa cantidad de notas
    inicializarNotasGenerico(&app, configSc->cantNotas);
    Mix_Chunk **sonidos = inicializarAudio(configSc->cantNotas,configSc->timbre);

    if (!sonidos)
    {
        return; // ERROR AL CARGAR SONIDO
    }

    TTF_Init();
    TTF_Font *font = TTF_OpenFont("fnt/BitcountGridSingle_Cursive-Regular.ttf", 24);
    if (!font)
    {
        destruirAudio(sonidos, configSc->cantNotas); // destruyo el sonido q cree antes
        printf("Error cargando fuente para puntaje: %s\n", TTF_GetError());
    }


    // --- Variables de juego ---
    int secuencia[MAX_SECUENCIA];
    int longitudSecuencia = 0;
    int juegoActivo = 1;
    size_t duracion = configSc->duracionIni;

    SDL_Event e;

    // Loop principal
    while (juegoActivo)
    {
        //
        if (verificarSecuenciaMaxima(renderer, longitudSecuencia, MAX_SECUENCIA,font))
        {
            juegoActivo = 0;
            break;
        }

        //  Agrega nueva nota a la secuencia
        secuencia[longitudSecuencia] = rand() % configSc->cantNotas;
        longitudSecuencia++;

        // Mostrar secuencia
        for (int i = 0; i < longitudSecuencia; i++)
        {
            app.arrayColores[secuencia[i]]->activado = 1;
            prepararEscena(renderer);

            renderNotasGenerico(jugador, configSc->cantNotas, renderer, &app);
            mostrarPuntajeActual(renderer, jugador, font);
            presentarEscena(renderer);
            reproducirSonido(sonidos, secuencia[i], configSc->cantNotas);


            esperar(duracion, &juegoActivo);
            // repito dos veces por que debo DESILUMINAR el boton.

            app.arrayColores[secuencia[i]]->activado = 0;
            prepararEscena(renderer);

            renderNotasGenerico(jugador, configSc->cantNotas, renderer, &app);
            mostrarPuntajeActual(renderer, jugador, font);
            presentarEscena(renderer);

            SDL_Delay(RETRASO_ENTRE_LUCES);
        }

        // 3. Turno del jugador
        int indiceJugador = 0;
        int turnoJugador = 1;
        while (turnoJugador)
        {
            while (SDL_PollEvent(&e))
            {
                if (e.type == SDL_QUIT)
                {
                    juegoActivo = 0;
                    turnoJugador = 0;
                    break;
                }

                if (e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_KEYDOWN)
                {
                    int mouseX = e.button.x;
                    int mouseY = e.button.y;

                    for (int i = 0; i < configSc->cantNotas; i++)
                    {
                        ColorObj *c = app.arrayColores[i];
                        int tamPixelFinal = TAM_PIXEL + 5;
                        int ancho = 20 * tamPixelFinal;
                        int alto = 20 * tamPixelFinal;
                        int xIni = (ANCHO_VENTANA * c->offsetX - ancho * c->offsetX) / 100;
                        int yIni = (ALTO_VENTANA * c->offsetY - alto * c->offsetY) / 100;

                        SDL_Rect zona = {xIni, yIni, ancho, alto};
                        if(e.key.keysym.sym == SDLK_c)
                        {
                            indiceJugador=longitudSecuencia;
                            turnoJugador=0;

                            mostrarTexto(renderer,"CHEAT ACTIVADO",font,20,40,(SDL_Color){255,255,255,255});
                            presentarEscena(renderer);
                            esperar(1000,&juegoActivo);
                        }
                        if (SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &zona))
                        {
                            // Efecto visual
                            c->activado = 1;
                            prepararEscena(renderer);

                            renderNotasGenerico(jugador, configSc->cantNotas, renderer, &app);
                            mostrarPuntajeActual(renderer, jugador, font);
                            presentarEscena(renderer);

                            reproducirSonido(sonidos, i, configSc->cantNotas);

                            esperar(duracion, &juegoActivo);
                            // DESILUMINO LO QUE CLIKIE
                            c->activado = 0;
                            prepararEscena(renderer);

                            renderNotasGenerico(jugador, configSc->cantNotas, renderer, &app);
                            mostrarPuntajeActual(renderer, jugador, font);

                            presentarEscena(renderer);

                            // Validación
                            if (i == secuencia[indiceJugador])
                            {
                                indiceJugador++;
                                if (indiceJugador == longitudSecuencia)
                                {
                                    turnoJugador = 0;


                                }
                            }
                            else
                            {
                                mostrarGameOver(renderer,jugador,font);
                                juegoActivo = 0;
                                turnoJugador = 0;
                            }
                            break;
                        }
                    }
                    if(!turnoJugador)
                        break;
                }
            }
        }

        if (!juegoActivo)
            break;

        // Dibujar tilde en el centro de la pantalla
        dibujar(renderer, tilde, (ANCHO_VENTANA - 7 * 20) / 2, (ALTO_VENTANA - 7 * 20) / 2, 30);
        mostrarPuntajeActual(renderer, jugador, font);
        presentarEscena(renderer);

        esperar(duracion, &juegoActivo);

        duracion=duracion*0.97;
        if (duracion < 100)// por que hago esto? por que en el caso de que estemos por la ronda 90 y nuestra dur incial sea de 500 ms , nos quedara un tiempo de nota de 33 ms, casi incheaqueable la iluminacion para el ojo humano
            duracion = 100;
        jugador->puntaje++;
        //(restaurar luego) printf("Ronda superada! Puntaje: %d\n", jugador->puntaje);

        SDL_Delay(1000);
    }


    destruirAudio(sonidos, configSc->cantNotas);

    TTF_CloseFont(font);
    TTF_Quit();

    Estadisticas estadistica;

    strcpy(estadistica.jugador.nombre, jugador->nombre);
    estadistica.jugador.puntaje = jugador->puntaje;
    estadistica.cantNotas = configSc->cantNotas;
    guardarEstadistica(&estadistica);

    jugador->puntaje=0; // reseteo los puntajes. ANTES DEBERIA GUARDARLO EN LAS STATS. ??? o reseteo dsps en el main
}
int obtenerIntNota(char notaString[], int cantidadNotas)
{

    char* escalas[6][8] =
    {
        {"DO", "MI", "SOL"},  // C Mayor
        {"DO", "MI", "SOL", "LA"},  // C6
        {"DO", "RE", "MI", "SOL", "LA"},  // penta
        {"DO", "RE", "MI", "FA#", "SOL#", "LA#"},  //  Hexatonal
        {"DO", "RE", "RE#", "FA", "SOL", "SOL#", "SI"},  //  Escala menor armónica
        {"DO", "RE", "MI", "FA", "SOL", "LA", "SI", "DO8"}  // Escala mayor + 8va
    };
    for(int i = 0; i < cantidadNotas; i++)
    {
        if( strcmp(escalas[cantidadNotas-3][i], notaString) == 0 )
        {
            return i;
        }
    }
    return -1;
}
void obtenerArrayNotas(ConfiguracionMoz *config, int *largoSecuencia, int secuencia[],FILE* ptrCancionTxt)
{
    int notasLeidas = 0;
    char notaActual[20] = {0};
    char cantidadNotas[10] = {0};

    fgets(cantidadNotas, sizeof(cantidadNotas), ptrCancionTxt);
    //(restaurar luego) printf("Cantidad Notas: %c\n", cantidadNotas[0]);

    if(cantidadNotas[0] < 51 || cantidadNotas[0] > 56) {
        printf("Error cantidad de notas invalida %s\n", cantidadNotas);
        fclose(ptrCancionTxt);
        return;
    }
//  Obtengo la string de la segunda linea, son las notas de la melodia

    while (fscanf(ptrCancionTxt, "%19s\n", notaActual) == 1) {
        secuencia[notasLeidas] = obtenerIntNota(notaActual, cantidadNotas[0]-'0');
        notasLeidas++;
    }
//    printf("\n>>Cantidad notas validas: %d", notasLeidas);
    *largoSecuencia = notasLeidas;
    config->cantNotas = cantidadNotas[0] - '0';
}
int modoMozart(Jugador *jugador, ConfiguracionMoz *config, SDL_Window *ventana, SDL_Renderer *renderer)
{
    //(restaurar luego) printf("Archivo seleccionado: %s\n", config->archivo);
    int largoSecuencia = 0;
    int seq[500] = {0};
    buscarNombreArchivo(renderer,config);
    FILE *ptrCancionTxt = fopen(config->archivo, "r");

//  Obtengo el primer caracter, modo de cantidad de notas

    if(ptrCancionTxt == NULL)
    {
        //printf("\No se encontro el archivo\n");
        return -1;
    }
    obtenerArrayNotas(config, &largoSecuencia, seq, ptrCancionTxt);
    fclose(ptrCancionTxt);

    //(restaurar luego) printf(" Timbre: %d, Archivo: %s, Notas: %d, Duracion: %d\n", config->timbre, config->archivo, config->cantNotas, config->duracionIni);
    //(restaurar luego) printf("\nMelodia: ");
    for(int i = 0; i < largoSecuencia; i++)
    {
        //(restaurar luego) printf(" %d", seq[i]);
    }
    //(restaurar luego) printf("\n");

    srand(time(NULL));
    NotasApp app;
    const int tilde[7][7] =
    {
        {T, T, T, T, T, T, T},
        {T, T, T, T, T, T, V},
        {T, T, T, T, T, V, T},
        {T, T, T, T, V, T, T},
        {V, T, T, V, T, T, T},
        {T, V, V, T, T, T, T},
        {T, T, T, T, T, T, T}
    };


    // Inicializa cantidad de notas
    inicializarNotasGenerico(&app, config->cantNotas);
    Mix_Chunk **sonidos = inicializarAudio(config->cantNotas,config->timbre);
    if (!sonidos)
    {
        return -1; // ERROR AL CARGAR SONIDO
    }

    TTF_Init();
    TTF_Font *font = TTF_OpenFont("fnt/BitcountGridSingle_Cursive-Regular.ttf", 24);


    if (!font)
    {
        destruirAudio(sonidos, config->cantNotas); // destruyo el sonido q cree antes
        printf("Error cargando fuente para puntaje: %s\n", TTF_GetError());
    }




    // --- Variables de juego ---
    int secuencia[MAX_SECUENCIA];
    int longitudSecuencia = 0;
    int juegoActivo = 1;
    size_t duracion = config->duracionIni;

    SDL_Event e;

    // Loop principal
    while (juegoActivo)
    {
        //
        if (verificarSecuenciaMaxima(renderer, longitudSecuencia, largoSecuencia,font))
        {
            juegoActivo = 0;
            break;
        }
        //  Agrega nueva nota a la secuencia
        secuencia[longitudSecuencia] = seq[longitudSecuencia];
        longitudSecuencia++;

        // Mostrar secuencia
        for (int i = 0; i < longitudSecuencia; i++)
        {
            app.arrayColores[secuencia[i]]->activado = 1;
            prepararEscena(renderer);

            renderNotasGenerico(jugador, config->cantNotas, renderer, &app);
            mostrarPuntajeActual(renderer, jugador, font);
            presentarEscena(renderer);
            reproducirSonido(sonidos, secuencia[i], config->cantNotas);

            esperar(duracion, &juegoActivo);
            // repito dos veces por que debo DESILUMINAR el boton.
            app.arrayColores[secuencia[i]]->activado = 0;
            prepararEscena(renderer);

            renderNotasGenerico(jugador, config->cantNotas, renderer, &app);
            mostrarPuntajeActual(renderer, jugador, font);
            presentarEscena(renderer);
            SDL_Delay(RETRASO_ENTRE_LUCES);
        }

        // 3. Turno del jugador
        int indiceJugador = 0;
        int turnoJugador = 1;
        while (turnoJugador)
        {
            while (SDL_PollEvent(&e))
            {
                if (e.type == SDL_QUIT)
                {
                    juegoActivo = 0;
                    turnoJugador = 0;
                    break;
                }

                if (e.type == SDL_MOUSEBUTTONDOWN || e.type== SDL_KEYDOWN)
                {
                    int mouseX = e.button.x;
                    int mouseY = e.button.y;
                    if(e.key.keysym.sym == SDLK_c)
                        {
                            indiceJugador=longitudSecuencia;
                            turnoJugador=0;

                            mostrarTexto(renderer,"CHEAT ACTIVADO",font,20,40,(SDL_Color){255,255,255,255});
                            presentarEscena(renderer);
                            esperar(1000,&juegoActivo);
                        }
                    for (int i = 0; i < config->cantNotas; i++)
                    {
                        ColorObj *c = app.arrayColores[i];
                        int tamPixelFinal = TAM_PIXEL + 5;
                        int ancho = 20 * tamPixelFinal;
                        int alto = 20 * tamPixelFinal;
                        int xIni = (ANCHO_VENTANA * c->offsetX - ancho * c->offsetX) / 100;
                        int yIni = (ALTO_VENTANA * c->offsetY - alto * c->offsetY) / 100;

                        SDL_Rect zona = {xIni, yIni, ancho, alto};

                        if (SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &zona))
                        {
                            // Efecto visual
                            c->activado = 1;
                            prepararEscena(renderer);

                            renderNotasGenerico(jugador, config->cantNotas, renderer, &app);
                            mostrarPuntajeActual(renderer, jugador, font);
                            presentarEscena(renderer);

                            reproducirSonido(sonidos, i, config->cantNotas);

                            esperar(duracion, &juegoActivo);
                            // DESILUMINO LO QUE CLIKIE
                            c->activado = 0;
                            prepararEscena(renderer);

                            renderNotasGenerico(jugador, config->cantNotas, renderer, &app);
                            mostrarPuntajeActual(renderer, jugador, font);

                            presentarEscena(renderer);

                            // Validación
                            if (i == secuencia[indiceJugador])
                            {
                                indiceJugador++;
                                if (indiceJugador == longitudSecuencia)
                                {
                                    turnoJugador = 0;
                                }
                            }
                            else
                            {
                                mostrarGameOver(renderer,jugador,font);
                                juegoActivo = 0;
                                turnoJugador = 0;
                            }
                            break;
                        }
                    }
                    if(!turnoJugador) break;
                }
            }
        }

        if (!juegoActivo)
            break;


        // Dibujar tilde en el centro de la pantalla
        dibujar(renderer, tilde, (ANCHO_VENTANA - 7 * 20) / 2, (ALTO_VENTANA - 7 * 20) / 2, 30);
        mostrarPuntajeActual(renderer, jugador, font);
        presentarEscena(renderer);

        esperar(duracion, &juegoActivo);

        duracion=duracion*0.97;
        if (duracion < 100)// por que hago esto? por que en el caso de que estemos por la ronda 90 y nuestra dur incial sea de 500 ms , nos quedara un tiempo de nota de 33 ms, casi incheaqueable la iluminacion para el ojo humano
            duracion = 100;
        jugador->puntaje++;
        //(restaurar luego) printf("Ronda superada! Puntaje: %d\n", jugador->puntaje);

        SDL_Delay(1000);
    }


    destruirAudio(sonidos, config->cantNotas);

    TTF_CloseFont(font);
    TTF_Quit();

    jugador->puntaje=0; // reseteo los puntajes. ANTES DEBERIA GUARDARLO EN LAS STATS. ??? o reseteo dsps en el main
    free(config->archivo);
    return MENU;
}


