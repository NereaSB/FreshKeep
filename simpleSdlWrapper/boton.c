#include <SDL.h>

#include "boton.h"
#include <SDL_ttf.h>
#include <stdio.h>

Button submit = {{900, 600, 115, 55}, {225, 255, 198, SDL_ALPHA_OPAQUE}, 0};

void drawButton(SDL_Renderer *gRenderer, Button *button)
{
    SDL_SetRenderDrawColor(gRenderer, button->color.r, button->color.g, button->color.b, button->color.a);
    SDL_RenderFillRect(gRenderer, &button->rect);
}

void handleMouseClick(SDL_Event *ebentua, Button *button)
{
    if (ebentua->button.button == SDL_BUTTON_LEFT)
    {
        int mouseX = ebentua->button.x;
        int mouseY = ebentua->button.y;

        if (mouseX >= button->rect.x && mouseX <= button->rect.x + button->rect.w && mouseY >= button->rect.y &&
            mouseY <= button->rect.y + button->rect.h)
        {
            // El botón ha sido clicado
            button->isClicked = 1;
        }
    }
}

void drawSubmitButton(SDL_Renderer *gRenderer)
{
    SDL_SetRenderDrawColor(gRenderer, submit.color.r, submit.color.g, submit.color.b, submit.color.a);
    SDL_RenderFillRect(gRenderer, &submit.rect);
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(gRenderer, &submit.rect);

    TTF_Font *font = 0;
    SDL_Color kolorea = {0x00, 0x00, 0x00};
    TTF_Init();
    font = TTF_OpenFontIndex("OpenSans-Regular.ttf", 30, 0);
    SDL_Surface *textSurface = TTF_RenderText_Blended(font, "GORDE", kolorea); // Color del texto (negro)
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
    SDL_Rect textRect = {submit.rect.x + 5, submit.rect.y + 5, textSurface->w, textSurface->h};
    SDL_RenderCopy(gRenderer, textTexture, NULL, &textRect);
}

int handleSubmitButton(SDL_Event *ebentua)
{
    int sakatuta = 0;
    if (ebentua->button.button == SDL_BUTTON_LEFT)
    {
        int mouseX = ebentua->button.x;
        int mouseY = ebentua->button.y;

        if (mouseX >= submit.rect.x && mouseX <= submit.rect.x + submit.rect.w && mouseY >= submit.rect.y &&
            mouseY <= submit.rect.y + submit.rect.h)
        {
            sakatuta = 1;
        }
    }
    return sakatuta;
}