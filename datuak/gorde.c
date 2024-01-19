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
            if (fgets(linea, 125, fitxategia) != NULL) // Konprobatu lerroa hutsik badago
            {
                strcpy(dest[i], linea);
                i++;
            }
            else
            {
                amaituta = 1;
            }
        }
    }
    fclose(fitxategia);
}