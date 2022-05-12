#ifndef DATAHANDLE_H_INCLUDED
#define DATAHANDLE_H_INCLUDED
#include <stdbool.h>
#include "game.h"
#include "filehandle.h"

void beolvas_string(char *str);
void beolvas_enterig(char *str);
void csonkit(char *szo, int levagando);
bool bemenet_ellenorzes(char *bemenet, Lista *elvart);
void listabatesz(char *mit, Lista **lista);
void listakiir(Lista *lista, Formatum forma);
void felszabadit_lista(Lista *lista);
void felszabadit_allapot(Allapot *allapot);

void hova_mehet(Allapot *allapot);
void info_feltetel(Allapot *allapot, int i, char* feltetel);
#endif // DATAHANDLE_H_INCLUDED
