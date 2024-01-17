
#include "./lib/game02.h"
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
    pantailaHasi();
    Irudiakjarri(0);

    return 0;
}