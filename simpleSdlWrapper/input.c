#include <SDL.h>
#include <SDL_ttf.h>

void inputMarraztu(SDL_Renderer *gRenderer);

void inputMarraztu(SDL_Renderer *gRenderer)
{
    char testua[250];
    int fin = 0;
    SDL_Color kolor = {0x00, 0x00, 0x00};
    SDL_Rect inputBox = {100, 100, 200, 100};
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
    SDL_RenderFillRect(gRenderer, &inputBox);
    TTF_Font *font = 0;
    TTF_Init();
    font = TTF_OpenFontIndex("(Titulo)ChauPhilomeneOne-Regular.ttf", 40, 0);
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, "Kaixo", kolor); // Color del texto (negro)
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
    SDL_Rect textRect = {inputBox.x + 5, inputBox.y + 5, textSurface->w, textSurface->h};
    SDL_RenderCopy(gRenderer, textTexture, NULL, &inputBox);
    SDL_Event ebentua;
    SDL_RenderPresent(gRenderer); // Aquí almacenaremos los eventos que vamos sacando de la cola
    while (!fin)
    {
        while (SDL_PollEvent(&ebentua))
        {
            if (ebentua.type == SDL_TEXTINPUT)
            {
                SDL_RenderFillRect(gRenderer, &inputBox);
                TTF_Font *font = 0;
                TTF_Init();
                font = TTF_OpenFontIndex("(Titulo)ChauPhilomeneOne-Regular.ttf", 40, 0);
                textSurface = TTF_RenderText_Solid(font, ebentua.text.text, kolor); // Color del texto (negro)
                SDL_Texture *textTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
                SDL_Rect textRect = {inputBox.x + 5, inputBox.y + 5, textSurface->w, textSurface->h};
                SDL_RenderCopy(gRenderer, textTexture, NULL, &inputBox);
                SDL_RenderPresent(gRenderer);
            }
        }
    }
}
