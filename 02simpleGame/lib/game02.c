#include "game02.h"
#include "ebentoak.h" //para boton raton
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

#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>

int pantailaHasi();
int Irudiakjarri();

SDL_Window *Ventana = NULL;
SDL_Surface *Superficie = NULL;
SDL_Renderer *gRenderer;
SDL_Rect src, dst;
int fin = 0, id;
int screenWidth;
int screenHeight;

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

    SDL_Rect inputBox = {30, 30, 200, 30};
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(gRenderer, &inputBox);

    SDL_RenderDrawLine(gRenderer, 20, 20, 70, 70);
    SDL_Color kolor = {0x00, 0x00, 0x00};

    // soinua
    audioInit();
    loadTheMusic(JOKOA_SOUND);
    playMusic();

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
                    SDL_SetWindowFullscreen(Ventana, 0);
                }
                break;

            case SDL_QUIT: // Si hemos pulsado el cierre de la ventana
                fin = 1;
                SDL_DestroyWindow(Ventana);
                SDL_Quit(); // También acabamos
                break;

                /*case SDL_TEXTINPUT:
                    SDL_Log("%s", ebentua.text.text);
                    break;*/

            case SDL_WINDOWEVENT:
                // SDL_DisplayMode mode;
                if (ebentua.window.event == SDL_WINDOWEVENT_EXPOSED)
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

                    /*SDL_Rect inputBox = {100, 100, 200, 100};
                    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
                    SDL_RenderFillRect(gRenderer, &inputBox);
                    TTF_Font *font = 0;
                    TTF_Init();
                    font = TTF_OpenFontIndex("(Titulo)ChauPhilomeneOne-Regular.ttf", 40, 0);
                    SDL_Surface *textSurface = TTF_RenderText_Solid(font, "Kaixo", kolor); // Color del texto (negro)
                    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
                    SDL_Rect textRect = {inputBox.x + 5, inputBox.y + 5, textSurface->w, textSurface->h};
                    SDL_RenderCopy(gRenderer, textTexture, NULL, &inputBox);*/

                    // idatzi(gRenderer, 40, 40, "FreshKeep", kolor, 40, "OpenSans-Regular.ttf");
                    tituluaIdatzi("FRESHKEEP", kolor, Ventana, "(Titulo)ChauPhilomeneOne-Regular.ttf");
                    Irudiakjarri();
                    inputMarraztu(gRenderer);
                }
                break;
            }
        }
    }
    return 0;
}

int Irudiakjarri()
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
    id = irudiaKargatu(HOSTOA_IMG);
    irudiaMugitu(id, 6, 1); /* //252,30
     id = irudiaKargatu(FONDO_ABAJO_IMG);
     irudiaMugitu(id, 0, 599);
     id = irudiaKargatu(FONDO_ARRIBA_IMG);
     irudiaMugitu(id, 0, 0);*/
    irudiakMarraztu();
    pantailaBerriztu();
    return id;
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
