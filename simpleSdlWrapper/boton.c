#include <SDL.h>

#include "boton.h"
#include <stdio.h>

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