#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>

int pantailaHasi();

SDL_Window *Ventana = NULL;
SDL_Surface *Superficie = NULL;
SDL_Renderer *gRenderer;
int fin = 0;
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
        Ventana = SDL_CreateWindow("FreshKeep", 20, 20, 640, 480, SDL_WINDOW_SHOWN);
    }
    gRenderer = SDL_CreateRenderer(Ventana, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(gRenderer, 230, 200, 200, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLine(gRenderer, 20, 20, 70, 70);
    SDL_RenderPresent(gRenderer);
    TTF_Init();

    while (!fin)
    {
        SDL_Event mi_evento; // Aquí almacenaremos los eventos que vamos sacando de la cola
                             // Con esto controlamos cuando queremos acabar el programa
        while (SDL_PollEvent(&mi_evento))
        { // Miramos y sacamos el siguiente evento en cola
            switch (mi_evento.type)
            {                                                // Comprobamos el tipo de evento
            case SDL_KEYDOWN:                                // Si es una pulsación de tecla
                if (mi_evento.key.keysym.sym == SDLK_ESCAPE) // Si es la tecla Escape
                {
                    fin = 1; // Ponemos fin a true para salir del bucle
                }
                break;
            case SDL_QUIT: // Si hemos pulsado el cierre de la ventana
                fin = 1;
                SDL_DestroyWindow(Ventana);
                SDL_Quit(); // También acabamos
                break;
            }
        }
    }

    return 0;
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
            SDL_UpdateWindowSurface(Ventana);*/
