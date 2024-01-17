#ifndef IMAGEN_H
#define IMAGEN_H
#include <SDL.h>

#define MAX_IMG 100

int irudiaKargatu(char *fileName);
void irudiaMugitu(int numImg, int x, int y);
void irudiakMarraztu(void);
void irudiaKendu(int id);
void irudiaMugitubateskuinera(int numImg);
void irudiaMugitubatezkerrera(int numImg);

#endif
