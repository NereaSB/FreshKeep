#include <SDL.h>
#include <SDL_ttf.h>

void inputMarraztu(SDL_Renderer *gRenderer, char str[]);

void inputMarraztu(SDL_Renderer *gRenderer, char str[])
{
    char testua[250];
    int fin = 0;
    SDL_Color kolor = {0x00, 0x00, 0x00};
    SDL_Rect inputBox = {600, 200, 180, 50};
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
    SDL_RenderFillRect(gRenderer, &inputBox);
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(gRenderer, &inputBox);
    if (strlen(str) > 0)
    {
        TTF_Font *font = 0;
        TTF_Init();
        font = TTF_OpenFontIndex("(Titulo)ChauPhilomeneOne-Regular.ttf", 30, 0);
        SDL_Surface *textSurface = TTF_RenderText_Blended(font, str, kolor); // Color del texto (negro)
        SDL_Texture *textTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
        SDL_Rect textRect = {inputBox.x + 5, inputBox.y + 5, textSurface->w, textSurface->h};
        SDL_Rect marker = {textRect.x + textSurface->w, textRect.y, 10, textSurface->h};
        SDL_RenderFillRect(gRenderer, &marker);

        SDL_RenderCopy(gRenderer, textTexture, NULL, &textRect);
    }
    else
    {
        SDL_Rect marker = {inputBox.x + 5, inputBox.y + 5, 10, 40};
        SDL_RenderFillRect(gRenderer, &marker);
    };

    SDL_RenderPresent(gRenderer);
}
