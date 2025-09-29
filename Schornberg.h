#ifndef SCHORNBERG_H_INCLUDED
#define SCHORNBERG_H_INCLUDED


typedef struct{
    int activado;
    int dibujo[20][20];
    int offsetX;
    int offsetY;
    char *nota;
} ColorObj;

typedef struct {
    ColorObj verde1;
    ColorObj verde2;
    ColorObj rojo1;
    ColorObj rojo2;
    ColorObj azul1;
    ColorObj azul2;
    ColorObj amarillo1;
    ColorObj amarillo2;
    ColorObj violeta;
    ColorObj *arrayColores[9];
    char **escalaActual;
    int cantidadNotasEscala;
} NotasApp;

typedef struct {
    ColorObj **arrayPtr;
    size_t ce;
    size_t capacidad;
} Secuencia;
void inicializarHistorial(Secuencia *secuencia);
void presentarEscena(SDL_Renderer *renderer);
void prepararEscena(SDL_Renderer *renderer);
void renderMatriz(SDL_Renderer *renderer, ColorObj *colorobj, int tamPixelFinal);


void render3Notas(Jugador *jugador, ConfiguracionSch *configSc, SDL_Renderer *renderer, NotasApp *app);
void render4Notas(Jugador *jugador, ConfiguracionSch *configSc, SDL_Renderer *renderer, NotasApp *app);
void render5Notas(Jugador *jugador, ConfiguracionSch *configSc, SDL_Renderer *renderer, NotasApp *app);
void render6Notas(Jugador *jugador, ConfiguracionSch *configSc, SDL_Renderer *renderer, NotasApp *app);
void render8Notas(Jugador *jugador, ConfiguracionSch *configSc, SDL_Renderer *renderer, NotasApp *app);

void inicializar3Notas(NotasApp *app);
void inicializar4Notas(NotasApp *app);
void inicializar5Notas(NotasApp *app);
void inicializar6Notas(NotasApp *app);
void inicializar8Notas(NotasApp *app);

void Innit_Schornberg(Jugador *jugador, ConfiguracionSch *configSc, SDL_Window *ventana, SDL_Renderer *renderer);

#endif // SCHORNBERG_H_INCLUDED
