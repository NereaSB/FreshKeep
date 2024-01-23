#include "./lib/game02.h"
#include "boton.h"
#include "ebentoak.h"
#include "graphics.h"
#include "imagen.h"
#include "ourTypes.h"
#include "soinua.h"
#include "text.h"

#include <SDL.h>
#include <stdio.h>
int pantailaHasi();
int Irudiakjarri(int zeregin);
void refrescarpagina(int zeregin);
int SDL_main(int argc, char *str[])
{
    char *cadenas[] = {"Hola", "Mundo", "en", "C"};
    for (int i = 0; i < sizeof(cadenas) / sizeof(cadenas[0]); i++) // kalkulatzen du arrayaren luzaera
    {
        SDL_Log("%s\n", cadenas[i]);
    }
    pantailaHasi();
    Irudiakjarri(0);

    return 0;
}
