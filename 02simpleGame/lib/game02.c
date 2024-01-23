#include "game02.h"
#include "boton.h"
#include "ebentoak.h"
#include "gorde.h"
#include "graphics.h"
#include "ikono.h"
#include "imagen.h"
#include "input.h"
#include "soinua.h"
#include "text.h"
#include <input.h>
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
TTF_Font *font;
SDL_Color laukizuzenarenKolorea = {255, 255, 198, SDL_ALPHA_OPAQUE};
SDL_Color NorGaraKolorea = {255, 255, 255, SDL_ALPHA_OPAQUE};

Button Hostoa_Botoia = {{6, 1, 100, 70}, {255, 0, 0, 255}, 0};
Button Soinua_Botoia = {{1460, 3, 70, 70}, {255, 0, 0, 255}, 0};
Button Hasiera_Botoia = {{10, 100, 160, 50}, {255, 0, 0, 255}, 0};
Button ListaOsoa_Botoia = {{10, 180, 160, 50}, {255, 0, 0, 255}, 0};
Button Gehitu_Botoia = {{10, 260, 160, 50}, {255, 0, 0, 255}, 0};
Button Osasuna_Botoia = {{10, 340, 160, 50}, {255, 0, 0, 255}, 0};
Button Donazioa_Botoia = {{10, 420, 160, 50}, {255, 0, 0, 255}, 0};
Button NorGara_Botoia = {{10, 500, 160, 50}, {255, 0, 0, 255}, 0};
Button Idatzi_Botoia = {{600, 100, 180, 50}, {255, 0, 0, 255}, 0}; // 300

Input inputak[10] = {{{600, 200, 180, 50}, "", 0},
                     {{500, 700, 180, 50}, "", 0},
                     {{100, 300, 180, 50}, "", 0},
                     {{300, 500, 180, 50}, "", 0}};

Input *inputAktiboa = &inputak[0];

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

    /////////
    SDL_Renderer *renderer = SDL_CreateRenderer(Ventana, -1, SDL_RENDERER_ACCELERATED);

    SDL_Rect buttonRect = {300, 200, 200, 100};
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Color rojo para el botón (RGBA)
    SDL_RenderFillRect(renderer, &buttonRect);

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

                /*else if (ebentua.key.keysym.sym == TECLA_0)
                {
                    if (!menuairekita)
                    {
                        menuairekita = 1;
                        //*tics = SDL_GetTicks();
                        irudiaMugitubateskuinera(0);
                        irudiaMugitubateskuinera(1);
                        refrescarpagina(1);
                    }
                    else if (menuairekita)
                    {
                        menuairekita = 0;
                        //tics = SDL_GetTicks();
                        irudiaMugitubatezkerrera(0);
                        irudiaMugitubatezkerrera(1);
                        refrescarpagina(1);
                    }
                }*/

                else if (ebentua.key.keysym.sym == TECLA_2)
                {
                    char a[100][100];
                    irakurri("fitxategia.txt", a);
                }

                /*else if (ebentua.key.keysym.sym == TECLA_1)
                {
                    if (soinuapiztutadago)
                    {

                        Mix_PauseMusic();
                        irudiaMugitu(3, 1150, 1);
                        irudiaMugitu(2, 3000, 0);
                        soinuapiztutadago = 0;
                        refrescarpagina(2);
                    }
                    else
                    {
                        Mix_ResumeMusic();
                        irudiaMugitu(2, 1150, 1);
                        irudiaMugitu(3, 3000, 0);
                        soinuapiztutadago = 1;
                        refrescarpagina(2);
                    }
                }*/

                else if (ebentua.key.keysym.sym == SDLK_BACKSPACE)
                {
                    if (SDL_strlen(inputAktiboa->inputText) > 0 && inputAktiboa != NULL)
                    {
                        char text[250];
                        SDL_strlcpy(text, inputAktiboa->inputText, 50);
                        text[SDL_strlen(text) - 1] = '\0';
                        SDL_strlcpy(inputAktiboa->inputText, text, 50);
                        inputMarraztu(gRenderer, inputAktiboa);
                    }
                }
                else if (ebentua.key.keysym.sym == SDLK_RETURN && inputAktiboa != NULL)
                {
                    SDL_Log("Enter");
                    int strlen = 0;
                    char datua[50] = "";
                    SDL_strlcpy(datua, inputAktiboa->inputText, 50);
                    strlen = SDL_strlcat(datua, ", \n", 50);
                    SDL_Log("%s", datua);
                    idatziFitxategian("fitxategia.txt", datua);
                    SDL_strlcpy(inputAktiboa->inputText, "", 250);
                    inputMarraztu(gRenderer, inputAktiboa);
                }
                break;

            case SDL_MOUSEBUTTONDOWN:
                handleMouseClick(&ebentua, &Hostoa_Botoia);
                handleMouseClick(&ebentua, &Soinua_Botoia);
                handleMouseClick(&ebentua, &Hasiera_Botoia);
                handleMouseClick(&ebentua, &ListaOsoa_Botoia);
                handleMouseClick(&ebentua, &Gehitu_Botoia);
                handleMouseClick(&ebentua, &Osasuna_Botoia);
                handleMouseClick(&ebentua, &Donazioa_Botoia);
                handleMouseClick(&ebentua, &NorGara_Botoia);
                handleMouseClick(&ebentua, &Idatzi_Botoia);
                if (inputAktiboa != NULL)
                {
                    int index;
                    // handleInputSelected(&ebentua, inputAktiboa, gRenderer);
                    index = searchSelectedInput(&ebentua, inputAktiboa, inputak, 4, gRenderer);
                    if (index < 4)
                    {
                        inputAktiboa = &inputak[index];
                    }
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
                    inputMarraztu(gRenderer, inputAktiboa);
                }
                break;

            case SDL_TEXTINPUT:
                if (SDL_strlen(inputAktiboa->inputText) < 12 && inputAktiboa != NULL)
                {
                    SDL_strlcat(inputAktiboa->inputText, ebentua.text.text, 50);
                    inputMarraztu(gRenderer, inputAktiboa);
                }
            }
        }
        if (Hostoa_Botoia.isClicked)
        {
            if (!menuairekita)
            {
                // Lógica cuando el botón es clicado por primera vez
                menuairekita = 1;
                /*tics = SDL_GetTicks();*/
                irudiaMugitubateskuinera(0);
                irudiaMugitubateskuinera(1);
                refrescarpagina(1);
                drawButton(gRenderer, &Hasiera_Botoia);
                drawButton(gRenderer, &ListaOsoa_Botoia);
                drawButton(gRenderer, &Gehitu_Botoia);
                drawButton(gRenderer, &Idatzi_Botoia);
                if (Gehitu_Botoia.isClicked)
                {
                    drawButton(gRenderer, &Idatzi_Botoia);
                    Gehitu_Botoia.isClicked = 0;
                }
                drawButton(gRenderer, &Osasuna_Botoia);
                drawButton(gRenderer, &Donazioa_Botoia);
                drawButton(gRenderer, &NorGara_Botoia);
            }
            else
            {
                // Lógica cuando el botón es clicado después de la primera vez
                menuairekita = 0;
                /*tics = SDL_GetTicks();*/
                irudiaMugitubatezkerrera(0);
                irudiaMugitubatezkerrera(1);
                refrescarpagina(1);
            }

            // Resetear la variable isClicked después de procesar el clic
            Hostoa_Botoia.isClicked = 0;
        }

        if (Soinua_Botoia.isClicked)
        {
            if (soinuapiztutadago)
            {

                Mix_PauseMusic();
                irudiaMugitu(3, 1150, 1);
                irudiaMugitu(2, 3000, 0);
                soinuapiztutadago = 0;
                refrescarpagina(2);
            }
            else
            {
                Mix_ResumeMusic();
                irudiaMugitu(2, 1150, 1);
                irudiaMugitu(3, 3000, 0);
                soinuapiztutadago = 1;
                refrescarpagina(2);
            }
            Soinua_Botoia.isClicked = 0;
        }
        if (NorGara_Botoia.isClicked)
        {
            laukiaMarraztu(gRenderer, 200, 500, 300, 60, NorGaraKolorea, font, "Markel Gomez");
            laukiaMarraztu(gRenderer, 535, 500, 300, 60, NorGaraKolorea, font, "Nerea Soares");
            laukiaMarraztu(gRenderer, 865, 500, 300, 60, NorGaraKolorea, font, "Mikel Landa");
            laukiaMarraztu(gRenderer, 1200, 500, 300, 60, NorGaraKolorea, font, "Izaro Matxain");
        }

        // Dibujar el botón
        drawButton(gRenderer, &Hostoa_Botoia);
        drawButton(gRenderer, &Soinua_Botoia);

        SDL_RenderPresent(gRenderer);
    }
    return 0;
}

int Irudiakjarri(int zeregin)
{
    int id = -1;

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
            Hostoa_Botoia.rect.x = 6;
            Hostoa_Botoia.rect.y = 1;
        }
        else if (menuairekita)
        {
            irudiaMugitu(0, -152, 0);
            irudiaMugitu(1, 181, 1);
            Hostoa_Botoia.rect.x = 181;
            Hostoa_Botoia.rect.y = 1;
        }
    }
    else if ((zeregin == 0) || (zeregin == 2))
    {
        if (!soinuapiztutadago)
        {
            irudiaMugitu(2, -1150, 3);
            irudiaMugitu(3, 1150, 3);
        }
        else if (soinuapiztutadago)
        {
            irudiaMugitu(2, 1150, 3);
            irudiaMugitu(3, -1150, 3);
        }
    }

    if (soinuapiztutadago)
    {
        irudiaMugituPantailarekinEzkerrerantz(2, Ventana);
    }
    else if (!soinuapiztutadago)
    {

        irudiaMugituPantailarekinEzkerrerantz(3, Ventana);
    }
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

    inputMarraztu(gRenderer, inputAktiboa);
    Irudiakjarri(zeregin);
    if (menuairekita)
    {
        laukiaMarraztu(gRenderer, 10, 100, 160, 50, laukizuzenarenKolorea, font, "Hasiera");
        laukiaMarraztu(gRenderer, 10, 180, 160, 50, laukizuzenarenKolorea, font, "Lista osoa");
        laukiaMarraztu(gRenderer, 10, 260, 160, 50, laukizuzenarenKolorea, font, "Gehitu");
        laukiaMarraztu(gRenderer, 10, 340, 160, 50, laukizuzenarenKolorea, font, "Osasuna");
        laukiaMarraztu(gRenderer, 10, 420, 160, 50, laukizuzenarenKolorea, font, "Donazioa");
        laukiaMarraztu(gRenderer, 10, 500, 160, 50, laukizuzenarenKolorea, font, "Nor gara");
        SDL_RenderPresent(gRenderer);
    }

    SDL_Color kolor = {0x00, 0x00, 0x00};
    tituluaIdatzi("FRESHKEEP", kolor, Ventana, "(Titulo)ChauPhilomeneOne-Regular.ttf");
    Irudiakjarri(zeregin);
    inputakMarraztu(gRenderer, inputak, 4);
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