#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>

void idatziFitxategian(char izena[], char testua[]);
void irakurri(char izena[], char dest[]);

void idatziFitxategian(char izena[], char testua[])
{

    char database[300];
    FILE *fitxategia;
    irakurri(izena, database);
    fitxategia = fopen(izena, "w");
    SDL_strlcat(database, testua, 300);
    SDL_Log("datuak: %s", database);
    fprintf(fitxategia, "%s", database);
    fclose(fitxategia);
}

void irakurri(char izena[], char dest[])
{
    FILE *fitxategia;
    fitxategia = fopen(izena, "r");
    fgets(dest, 128, fitxategia);
    fclose(fitxategia);
}