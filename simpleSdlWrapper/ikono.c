#include <SDL.h>

#include "ikono.h"
#include <stdio.h>

void ikonoajarribehekobarran(SDL_Window *Ventana, char *izenaikono);

void ikonoajarribehekobarran(SDL_Window *Ventana, char *izenaikono)
{
    SDL_Surface *icon = IMG_Load(izenaikono);
    SDL_SetWindowIcon(Ventana, icon);
}