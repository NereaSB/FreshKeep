#ifndef INPUT_H
#define INPUT_H
#include <SDL.h>

typedef struct
{
    SDL_Rect inputBox;
    char inputText[13];
    int isClicked;
    char title[50];
} Input;

void inputMarraztu(SDL_Renderer *gRenderer, Input *input);
int handleInputSelected(SDL_Event *ebentua, Input *input, SDL_Renderer *gRenderer);
void inputakMarraztu(SDL_Renderer *gRenderer, Input inputak[], int zenbat);
int searchSelectedInput(SDL_Event *ebentua, Input *selektedInput, Input inputak[], int zenbat, SDL_Renderer *gRenderer);
void inputakGarbitu(Input inputak[], int zenbat, SDL_Renderer *gRenderer);
void inputakZentratu(Input inputak[], int zenbat, SDL_Renderer *gRenderer, SDL_Window *Ventana);

#endif
