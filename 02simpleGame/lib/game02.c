#include "game02.h"
#include "ebentoak.h"
#include "gorde.h"
#include "graphics.h"
#include "ikono.h"
#include "imagen.h"
#include "input.h"
#include "soinua.h"
#include "text.h"
#include <stdio.h>

#define NOR_GARA_IMG "./img/nor_gara.bmp"
#define DONAZIOA_IMG "./img/donazioa.bmp"
#define GEHITU_IMG "./img/gehitu.bmp"
#define HASIERA_IMG "./img/hasiera.bmp"
#define HOSTOA_IMG "./img/hostoa.bmp"
#define LISTA_IMG "./img/lista.bmp"
#define OSASUNA_IMG "./img/osasuna.bmp"
#define FONDO_ABAJO_IMG "./img/fondo_abajo.bmp"
#define FONDO_ARRIBA_IMG "./img/fondo_arriba.bmp"
#define JOKOA_SOUND "./sound/Audio fondo.mp3"
#define LOGO_ESCRITORIO_IMG "./img/icono.png"
#define BERDEILUNA "./img/MugitzenDena.bmp"
#define SOINUAPIZTUTA "./img/soinuapiztu.bmp"
#define SOINUAITZALITA "./img/soinuaitzali.bmp"

#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>

int pantailaHasi();
int Irudiakjarri(int zeregin);
void refrescarpagina(int zeregin);
void idatziFitxategian(char izena[], char testua[]);

char inputText[250] = "";
SDL_Window *Ventana = NULL;
SDL_Surface *Superficie = NULL;
SDL_Renderer *gRenderer;
SDL_Rect src, dst;
int fin = 0, id;
int screenWidth;
int screenHeight;
int kopuru, kop = 1, i;
int soinuapiztutadago = 1;
int lehenengoaldia = 1;
int menuairekita = 0;
int zeregin = 0;

int pantailaHasi()
{

    // Inicializa el subsistema de Video
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("ERROR: No se pudo inicializar SDL, Error SDL: %s\n", SDL_GetError());
    }
    else
    {
        // Se crea la ventana principal
        Ventana = SDL_CreateWindow("FreshKeep", 20, 20, 1980, 920, SDL_WINDOW_RESIZABLE);
        SDL_SetWindowFullscreen(Ventana, SDL_WINDOW_FULLSCREEN_DESKTOP);
    }
    gRenderer = SDL_CreateRenderer(Ventana, -1, SDL_RENDERER_ACCELERATED);
    SDL_GetWindowSize(Ventana, &screenWidth, &screenHeight);
    SDL_SetWindowSize(Ventana, screenWidth, screenHeight);
    SDL_SetRenderDrawColor(gRenderer, 225, 255, 198, SDL_ALPHA_OPAQUE);
    SDL_Rect background = {0, 0, 1980, 920};
    SDL_RenderFillRect(gRenderer, &background);

    SDL_RenderDrawLine(gRenderer, 20, 20, 70, 70);
    SDL_Color kolor = {0x00, 0x00, 0x00};

    kopuru = Irudiakjarri(0);

    // soinua
    audioInit();
    loadTheMusic(JOKOA_SOUND);
    playMusic();
    // idatziFitxategian("fitxategia.txt", "kaixo");

    // icono
    ikonoajarribehekobarran(Ventana, LOGO_ESCRITORIO_IMG);

    while (!fin)
    {
        SDL_Event ebentua; // Aquí almacenaremos los eventos que vamos sacando de la cola
                           // Con esto controlamos cuando queremos acabar el programa
        while (SDL_PollEvent(&ebentua))
        { // Miramos y sacamos el siguiente evento en cola
            switch (ebentua.type)
            {                                              // Comprobamos el tipo de evento
            case SDL_KEYDOWN:                              // Si es una pulsación de tecla
                if (ebentua.key.keysym.sym == SDLK_ESCAPE) // Si es la tecla Escape
                {
                    SDL_SetWindowFullscreen(Ventana, 0); // Ponemos fin a true para salir del bucle
                }
                else if (ebentua.key.keysym.sym == TECLA_0)
                {
                    if (!menuairekita)
                    {
                        menuairekita = 1;
                        /*tics = SDL_GetTicks();*/
                        irudiaMugitubateskuinera(0);
                        irudiaMugitubateskuinera(1);
                        refrescarpagina(1);
                    }
                    else if (menuairekita)
                    {
                        menuairekita = 0;
                        /*tics = SDL_GetTicks();*/
                        irudiaMugitubatezkerrera(0);
                        irudiaMugitubatezkerrera(1);
                        refrescarpagina(1);
                    }
                }
                else if (ebentua.key.keysym.sym == TECLA_1)
                {
                    if (soinuapiztutadago)
                    {

                        Mix_PauseMusic();
                        irudiaMugitu(3, 1150, 1);
                        irudiaMugitu(2, 3000, 0);
                        refrescarpagina(2);
                        soinuapiztutadago = 0;
                    }
                    else
                    {
                        Mix_ResumeMusic();
                        irudiaMugitu(2, 1150, 1);
                        irudiaMugitu(3, 3000, 0);
                        refrescarpagina(2);
                        soinuapiztutadago = 1;
                    }
                }
                else if (ebentua.key.keysym.sym == SDLK_BACKSPACE)
                {
                    if (SDL_strlen(inputText) > 0)
                    {
                        inputText[SDL_strlen(inputText) - 1] = '\0';
                        inputMarraztu(gRenderer, inputText);
                    }
                }
                else if (ebentua.key.keysym.sym == SDLK_RETURN)
                {
                    SDL_Log("Enter");
                    idatziFitxategian("fitxategia.txt", "KAixo");
                }
                break;

            case SDL_QUIT: // Si hemos pulsado el cierre de la ventana
                fin = 1;
                SDL_DestroyWindow(Ventana);
                SDL_Quit(); // También acabamos
                break;

            case SDL_WINDOWEVENT:
                // SDL_DisplayMode mode;
                if (ebentua.window.event == SDL_WINDOWEVENT_EXPOSED)
                {
                    refrescarpagina(0);
                    inputMarraztu(gRenderer, inputText);
                }
                break;

            case SDL_TEXTINPUT:
                if (SDL_strlen(inputText) < 12)
                {
                    strcat(inputText, ebentua.text.text);
                }
                inputMarraztu(gRenderer, inputText);
            }
        }
    }
    return 0;
}

int Irudiakjarri(int zeregin)
{
    int id = -1;
    /*id = irudiaKargatu(HASIERA_IMG); // 1
    irudiaMugitu(id, 0, 100);
    id = irudiaKargatu(LISTA_IMG); // 2
    irudiaMugitu(id, 0, 178);
    id = irudiaKargatu(GEHITU_IMG); // 3
    irudiaMugitu(id, 0, 268);
    id = irudiaKargatu(OSASUNA_IMG); // 4
    irudiaMugitu(id, 0, 350);
    id = irudiaKargatu(DONAZIOA_IMG); // 5
    irudiaMugitu(id, 0, 435);
    id = irudiaKargatu(NOR_GARA_IMG); // 6
    irudiaMugitu(id, 0, 510);*/

    if (lehenengoaldia)
    {
        id = irudiaKargatu(BERDEILUNA);     // 0
        id = irudiaKargatu(HOSTOA_IMG);     // 1
        id = irudiaKargatu(SOINUAPIZTUTA);  // 2
        id = irudiaKargatu(SOINUAITZALITA); // 3
        irudiaMugitu(0, -327, 0);
        irudiaMugitu(1, 6, 1);
        irudiaMugitu(2, 1150, 3);
        irudiaMugitu(3, -1150, 5);
        lehenengoaldia = 0;
    }
    if ((zeregin == 0) || (zeregin == 1))
    {
        if (!menuairekita)
        {
            irudiaMugitu(0, -327, 0);
            irudiaMugitu(1, 6, 1);
        }
        else if (menuairekita)
        {
            irudiaMugitu(0, -152, 0);
            irudiaMugitu(1, 181, 1);
        }
    }
    else if ((zeregin == 0) || (zeregin == 2))
    {
        if (soinuapiztutadago)
        {
            irudiaMugitu(2, -1150, 3);
            irudiaMugitu(3, 1150, 3);
        }
        else if (!soinuapiztutadago)
        {
            irudiaMugitu(2, 1150, 3);
            irudiaMugitu(3, -1150, 3);
        }
    }
    /* //252,30
    id = irudiaKargatu(FONDO_ABAJO_IMG);
    irudiaMugitu(id, 0, 599);
    id = irudiaKargatu(FONDO_ARRIBA_IMG);
    irudiaMugitu(id, 0, 0);*/
    irudiakMarraztu();
    pantailaBerriztu();
    return id;
}
void refrescarpagina(int zeregin)
{
    SDL_GetWindowSize(Ventana, &screenWidth, &screenHeight);
    SDL_Log("h: %d, w: %d", screenHeight, screenWidth);
    SDL_SetWindowSize(Ventana, screenWidth, screenHeight);
    SDL_SetRenderDrawColor(gRenderer, 225, 255, 198, SDL_ALPHA_OPAQUE);
    SDL_Rect background = {0, 0, screenWidth, screenHeight};
    SDL_RenderFillRect(gRenderer, &background);

    SDL_RenderDrawLine(gRenderer, 20, 20, 70, 70);
    SDL_RenderPresent(gRenderer);
    SDL_Color kolor = {0x00, 0x00, 0x00};
    // idatzi(gRenderer, 40, 40, "FreshKeep", kolor, 40, "OpenSans-Regular.ttf");
    tituluaIdatzi("FRESHKEEP", kolor, Ventana, "(Titulo)ChauPhilomeneOne-Regular.ttf");
    Irudiakjarri(zeregin);
}

/* if (Ventana == NULL)
        {
            printf("ERROR: No se pudo crear la ventana, SDL_Error: %s\n", SDL_GetError());
        }
        else
        {
            // Se crea la superficie para la ventana principal
            Superficie = SDL_GetWindowSurface(Ventana);

            // Se actualiza la superficie
            SDL_UpdateWindowSurface(Ventana);
        }*/

// Testua
/*TTF_Init();
SDL_Texture *texture;
TTF_Font *letra = TTF_OpenFont("../Debug/OpenSans-Regular.ttf", 28);
SDL_Color kolorea = {0, 0, 0};
SDL_Surface *testuarenAzalera = TTF_RenderText_Solid(letra, "FreshKeep", kolorea);
texture = SDL_CreateTextureFromSurface(gRenderer, testuarenAzalera);
src.x = 0;
dst.x = 0;
src.y = 0;
dst.y = 0;
src.w = dst.w = testuarenAzalera->w;
src.h = dst.h = testuarenAzalera->h;
SDL_RenderCopy(gRenderer, texture, &src, &dst);
SDL_RenderPresent(gRenderer);*/
