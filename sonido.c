#include "sonido.h"
#include <SDL2/SDL_mixer.h>
#include <stdlib.h>
#include <stdio.h>

// Variables globales dinámicas


Mix_Chunk **inicializarAudio(int cantNotas,int timbre)
{


    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        printf("Error al inicializar SDL_mixer: %s\n", Mix_GetError());
        return NULL;
    }

    // Reservamos según cantidad de notas
    Mix_Chunk **sonidos = malloc(sizeof(Mix_Chunk *) * cantNotas);
    if (!sonidos)
    {
        printf("Error reservando memoria para sonidos.\n");
        return NULL;
    }

    // Cargar sonidos según cantidad
    if(timbre==PIANO)
    {
        timbrePiano(sonidos,cantNotas);
    }
    else
    {
        timbreCP70(sonidos,cantNotas);
    }

    // Verificar carga
    for (int i = 0; i < cantNotas; i++)
    {
        if (!sonidos[i])
            printf("Error cargando sonido %d: %s\n", i, Mix_GetError());
    }
    return sonidos;
}
void timbreCP70(Mix_Chunk **sonidos,int cantNotas)
{
    switch (cantNotas)
    {
    case 3: // c mayor
        sonidos[0] = Mix_LoadWAV("snd/docp.wav");
        sonidos[1] = Mix_LoadWAV("snd/micp.wav");
        sonidos[2] = Mix_LoadWAV("snd/solcp.wav");
        break;

    case 4: // C6: DO MI SOL LA
        sonidos[0] = Mix_LoadWAV("snd/docp.wav");
        sonidos[1] = Mix_LoadWAV("snd/micp.wav");
        sonidos[2] = Mix_LoadWAV("snd/solcp.wav");
        sonidos[3] = Mix_LoadWAV("snd/lacp.wav");
        break;

    case 5: // Penta
        sonidos[0] = Mix_LoadWAV("snd/docp.wav");
        sonidos[1] = Mix_LoadWAV("snd/recp.wav");
        sonidos[2] = Mix_LoadWAV("snd/micp.wav");
        sonidos[3] = Mix_LoadWAV("snd/solcp.wav");
        sonidos[4] = Mix_LoadWAV("snd/lacp.wav");
        break;

    case 6: // Hexatonal
        sonidos[0] = Mix_LoadWAV("snd/docp.wav");
        sonidos[1] = Mix_LoadWAV("snd/recp.wav");
        sonidos[2] = Mix_LoadWAV("snd/micp.wav");
        sonidos[3] = Mix_LoadWAV("snd/fa#cp.wav");
        sonidos[4] = Mix_LoadWAV("snd/sol#cp.wav");
        sonidos[5] = Mix_LoadWAV("snd/la#cp.wav");
        break;

    case 7: // Escala menor armonica
        sonidos[0] = Mix_LoadWAV("snd/docp.wav");
        sonidos[1] = Mix_LoadWAV("snd/recp.wav");
        sonidos[2] = Mix_LoadWAV("snd/re#cp.wav");
        sonidos[3] = Mix_LoadWAV("snd/facp.wav");
        sonidos[4] = Mix_LoadWAV("snd/solcp.wav");
        sonidos[5] = Mix_LoadWAV("snd/sol#cp.wav");
        sonidos[6] = Mix_LoadWAV("snd/sicp.wav");
        break;

    case 8: // escala mayor + 8va
        sonidos[0] = Mix_LoadWAV("snd/docp.wav");
        sonidos[1] = Mix_LoadWAV("snd/recp.wav");
        sonidos[2] = Mix_LoadWAV("snd/micp.wav");
        sonidos[3] = Mix_LoadWAV("snd/facp.wav");
        sonidos[4] = Mix_LoadWAV("snd/solcp.wav");
        sonidos[5] = Mix_LoadWAV("snd/lacp.wav");
        sonidos[6] = Mix_LoadWAV("snd/sicp.wav");
        sonidos[7] = Mix_LoadWAV("snd/do8cp.wav");
        break;
    }
}

void timbrePiano(Mix_Chunk **sonidos,int cantNotas)
{
    switch (cantNotas)
    {

    case 3: // c mayor
        sonidos[0] = Mix_LoadWAV("snd/do.wav");
        sonidos[1] = Mix_LoadWAV("snd/mi.wav");
        sonidos[2] = Mix_LoadWAV("snd/sol.wav");
        break;

    case 4: // C6: DO MI SOL LA
        sonidos[0] = Mix_LoadWAV("snd/do.wav");
        sonidos[1] = Mix_LoadWAV("snd/mi.wav");
        sonidos[2] = Mix_LoadWAV("snd/sol.wav");
        sonidos[3] = Mix_LoadWAV("snd/la.wav");
        break;

    case 5: // Penta
        sonidos[0] = Mix_LoadWAV("snd/do.wav");
        sonidos[1] = Mix_LoadWAV("snd/re.wav");
        sonidos[2] = Mix_LoadWAV("snd/mi.wav");
        sonidos[3] = Mix_LoadWAV("snd/sol.wav");
        sonidos[4] = Mix_LoadWAV("snd/la.wav");
        break;

    case 6: // Hexatonal
        sonidos[0] = Mix_LoadWAV("snd/do.wav");
        sonidos[1] = Mix_LoadWAV("snd/re.wav");
        sonidos[2] = Mix_LoadWAV("snd/mi.wav");
        sonidos[3] = Mix_LoadWAV("snd/fa#.wav");
        sonidos[4] = Mix_LoadWAV("snd/sol#.wav");
        sonidos[5] = Mix_LoadWAV("snd/la#.wav");
        break;

    case 7: // Escala menor armonica
        sonidos[0] = Mix_LoadWAV("snd/do.wav");
        sonidos[1] = Mix_LoadWAV("snd/re.wav");
        sonidos[2] = Mix_LoadWAV("snd/re#.wav");
        sonidos[3] = Mix_LoadWAV("snd/fa.wav");
        sonidos[4] = Mix_LoadWAV("snd/sol.wav");
        sonidos[5] = Mix_LoadWAV("snd/sol#.wav");
        sonidos[6] = Mix_LoadWAV("snd/si.wav");
        break;

    case 8: // escala mayor + 8va
        sonidos[0] = Mix_LoadWAV("snd/do.wav");
        sonidos[1] = Mix_LoadWAV("snd/re.wav");
        sonidos[2] = Mix_LoadWAV("snd/mi.wav");
        sonidos[3] = Mix_LoadWAV("snd/fa.wav");
        sonidos[4] = Mix_LoadWAV("snd/sol.wav");
        sonidos[5] = Mix_LoadWAV("snd/la.wav");
        sonidos[6] = Mix_LoadWAV("snd/si.wav");
        sonidos[7] = Mix_LoadWAV("snd/do8.wav");
        break;

    }
}

void reproducirSonido(Mix_Chunk **sonidos,int indice,size_t cantNotas)
{
    if (indice >= 0 && indice < cantNotas && sonidos && sonidos[indice])
        Mix_PlayChannel(-1, sonidos[indice], 0);
}

void destruirAudio(Mix_Chunk **sonidos,size_t cantNotas)
{
    if (sonidos)
    {
        for (int i = 0; i < cantNotas; i++)
        {
            if (sonidos[i])
                Mix_FreeChunk(sonidos[i]);
        }

        free(sonidos);
        sonidos = NULL;
    }

    Mix_CloseAudio();
}
