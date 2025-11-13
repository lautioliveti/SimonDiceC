#include "dibujo.h"
SDL_Color colores[] =
{
    {0,   0,   0,   255}, // N[0] - Negro
    {255, 255, 0,   255}, // Y[1] - Amarillo
    {255, 255, 255, 255}, // B[2] - Blanco
    {0,   150, 60,  255}, // V[3] - Verde
    {255,   0,  0,  255}, // R[4] - Rojo
    {0,   0,    0,    0}  // T[5] - Transparente
};


void dibujar(SDL_Renderer *renderer, const int   dibujo[][COL], int oX, int oY,size_t tam_pixel)
{
    for (int y = 0; y < COL; y++)
    {
        for (int x = 0; x < COL; x++)
        {
            SDL_SetRenderDrawColor(renderer,
                                   colores[dibujo[y][x]].r,
                                   colores[dibujo[y][x]].g,
                                   colores[dibujo[y][x]].b,
                                   colores[dibujo[y][x]].a);
            SDL_Rect pixel = {oX + x * tam_pixel,oY + y * tam_pixel, tam_pixel, tam_pixel};
            SDL_RenderFillRect(renderer, &pixel);
        }
    }
}
void mostrarTexto(SDL_Renderer *renderer,const char* texto, TTF_Font *font, int oX, int oY, SDL_Color color)
{
    SDL_Surface *ayudaSurface = TTF_RenderText_Solid(font, texto,color);
    SDL_Texture *ayudaTexture = SDL_CreateTextureFromSurface(renderer, ayudaSurface);
    SDL_Rect ayudaRect = {oX, oY, ayudaSurface->w, ayudaSurface->h};
    SDL_RenderCopy(renderer, ayudaTexture, NULL, &ayudaRect);
    SDL_FreeSurface(ayudaSurface);
    SDL_DestroyTexture(ayudaTexture);

    // No hago el SDL_RenderPresent aca por que me genera un titileo en el ingreso del nombre c;

}
void borrarPantalla(SDL_Renderer *renderer, SDL_Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}
