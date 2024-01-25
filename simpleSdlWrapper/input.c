#include <SDL.h>
#include <SDL_ttf.h>
#include <input.h>

void inputMarraztu(SDL_Renderer *gRenderer, Input *input);
int handleInputSelected(SDL_Event *ebentua, Input *input, SDL_Renderer *gRenderer);
void inputakMarraztu(SDL_Renderer *gRenderer, Input inputak[], int zenbat);
int searchSelectedInput(SDL_Event *ebentua, Input *selektedInput, Input inputak[], int zenbat, SDL_Renderer *gRenderer);
void inputakGarbitu(Input inputak[], int zenbat, SDL_Renderer *gRenderer);
void inputakZentratu(Input inputak[], int zenbat, SDL_Renderer *gRenderer, SDL_Window *Ventana);

// Input inputak[10];
// Input Produktua = {{600, 200, 180, 50}, "", 0};

void inputMarraztu(SDL_Renderer *gRenderer, Input *input)
{
    SDL_Color kolor = {0x00, 0x00, 0x00};
    TTF_Font *font = 0;
    TTF_Init();
    font = TTF_OpenFontIndex("OpenSans-Regular.ttf", 30, 0);
    SDL_Surface *textSurface = TTF_RenderText_Blended(font, input->title, kolor); // Color del texto (negro)
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
    SDL_Rect textRect = {input->inputBox.x - textSurface->w - 20, input->inputBox.y, textSurface->w, textSurface->h};
    SDL_RenderCopy(gRenderer, textTexture, NULL, &textRect);
    TTF_CloseFont(font);

    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
    SDL_RenderFillRect(gRenderer, &input->inputBox);
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(gRenderer, &input->inputBox);
    if (strlen(input->inputText) > 0)
    {
        TTF_Font *font = 0;
        TTF_Init();
        font = TTF_OpenFontIndex("(Titulo)ChauPhilomeneOne-Regular.ttf", 30, 0);
        SDL_Surface *textSurface = TTF_RenderText_Blended(font, input->inputText, kolor); // Color del texto (negro)
        SDL_Texture *textTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
        SDL_Rect textRect = {input->inputBox.x + 5, input->inputBox.y + 5, textSurface->w, textSurface->h};
        SDL_Rect marker = {textRect.x + textSurface->w, textRect.y, 5, textSurface->h};
        SDL_RenderCopy(gRenderer, textTexture, NULL, &textRect);
        if (input->isClicked)
        {
            SDL_RenderFillRect(gRenderer, &marker);
        }
    }
    else if (input->isClicked)
    {
        SDL_Rect marker = {input->inputBox.x + 5, input->inputBox.y + 5, 5, 40};
        SDL_RenderFillRect(gRenderer, &marker);
    };

    SDL_RenderPresent(gRenderer);
}

int handleInputSelected(SDL_Event *ebentua, Input *input, SDL_Renderer *gRenderer)
{
    if (ebentua->button.button == SDL_BUTTON_LEFT)
    {
        int mouseX = ebentua->button.x;
        int mouseY = ebentua->button.y;

        if (mouseX >= input->inputBox.x && mouseX <= input->inputBox.x + input->inputBox.w &&
            mouseY >= input->inputBox.y && mouseY <= input->inputBox.y + input->inputBox.h)
        {
            // El botón ha sido clicado
            input->isClicked = 1;
            inputMarraztu(gRenderer, input);
        }
        else
        {
            input->isClicked = 0;
            inputMarraztu(gRenderer, input);
        }
        return input->isClicked;
    }
}

void inputakMarraztu(SDL_Renderer *gRenderer, Input inputak[], int zenbat)
{
    for (int i = 0; i < zenbat; i++)
    {
        inputMarraztu(gRenderer, &inputak[i]);
    }
}

int searchSelectedInput(SDL_Event *ebentua, Input *selektedInput, Input inputak[], int zenbat, SDL_Renderer *gRenderer)
{
    int aurkituta = 0, indexa = -1;
    for (int i = 0; i < zenbat; i++)
    {
        aurkituta = handleInputSelected(ebentua, &inputak[i], gRenderer);
        if (aurkituta)
        {
            indexa = i;
        }
    }
    return indexa;
}

void inputakGarbitu(Input inputak[], int zenbat, SDL_Renderer *gRenderer)
{
    for (int i = 0; i < zenbat; i++)
    {
        SDL_strlcpy(&inputak[i].inputText, "", 13);
        inputMarraztu(gRenderer, &inputak[i]);
    }
}

void inputakZentratu(Input inputak[], int zenbat, SDL_Renderer *gRenderer, SDL_Window *Ventana)
{
    int windowH, windowW, x;
    SDL_GetWindowSize(Ventana, &windowW, NULL);
    x = windowW / 2;

    for (int i = 0; i < zenbat; i++)
    {
        inputak[i].inputBox.x = x;
        SDL_strlcpy(&inputak[i].inputText, "", 13);
        inputMarraztu(gRenderer, &inputak[i]);
    }
}