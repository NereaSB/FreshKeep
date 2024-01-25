#ifndef BOTON_H
#define BOTON_H

#include <SDL.h>

typedef struct
{
    SDL_Rect rect;
    SDL_Color color;
    int isClicked;
} Button;

void drawButton(SDL_Renderer *gRenderer, Button *button);
void handleMouseClick(SDL_Event *ebentua, Button *button);
void drawSubmitButton(SDL_Renderer *gRenderer);
int handleSubmitButton(SDL_Event *ebentua);
void submiteguneratu(SDL_Window *Ventana, int menuairekita, int zerjarri, int pantailarentamaina);

#endif