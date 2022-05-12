#include <time.h>
#include "display.h"
#include "filehandle.h"
#include "game.h"
#include "debugmalloc.h"
#ifdef _WIN32
    #include <windows.h>
#endif


int main(void) {
#ifdef _WIN32
    SetConsoleCP(1250);
    SetConsoleOutputCP(65001);
#endif

    bool vege = true;
    Allapot allapot = {NULL};
    start(&vege, &allapot);
    char parancsok[80] = "megy <szoba>, keres, hasznal <targy>, beszel, nyomok, vadol <nev>, ment, kilep";
    printf_formazott(commands, parancsok);
    listakiir(allapot.inventory, inventory);
    while(!vege){
       jatek(&allapot, &vege, parancsok);
    }
    return 0;
}
