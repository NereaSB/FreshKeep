#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>

void idatziFitxategian(char izena[], char testua[]);
void irakurri(char izena[], char dest[]);

void idatziFitxategian(char izena[], char testua[])
{

    char database[300] = "";
    FILE *fitxategia;
    fitxategia = fopen(izena, "a");
    if (fitxategia)
    {
        fprintf(fitxategia, "%s", testua);
    }

    fclose(fitxategia);
}

void irakurri(char izena[], char dest[][100])
{
    FILE *fitxategia;
    char linea[30];
    int i = 0;
    int amaituta = 0;
    fitxategia = fopen(izena, "r");
    if (fitxategia)
    {
        while (i < 100 && !amaituta)
        {
            fgets(linea, 125, fitxategia);
            if (strcmp(dest[i], linea))
            {
                amaituta = 1;
            }
            else
            {
                strcpy(dest[i], linea);
                i++;
            }
        }
    }
    fclose(fitxategia);
}