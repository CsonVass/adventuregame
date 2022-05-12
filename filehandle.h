#ifndef FILEHANDLE_H_INCLUDED
#define FILEHANDLE_H_INCLUDED
#include <stdbool.h>
#include "game.h"
#include "datahandle.h"

//FÜGGVÉNYEK
bool has_txt_extension(char const *name);
void mentesek_listaz(Lista **lista);

void jatek_betolt(Allapot *allapot);
void mentes_betolt(char *fajlnev, Allapot *allapot);
void mentes_letrehoz(Allapot *allapot);

#endif // FILEHANDLE_H_INCLUDED
