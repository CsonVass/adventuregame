#include <stdio.h>
#include "display.h"
#include "filehandle.h"
#include "game.h"
#include "datahandle.h"
#include "econio.h"
#include "debugmalloc.h"


void printf_formazott(Formatum formatum, char *str){
    switch(formatum){
    case sima:
        econio_textcolor(COL_DARKGRAY);
        printf("%s\n",str);
        break;
    case story:
        econio_textcolor(COL_LIGHTBLUE);
        printf("**%s**\n", str);
        break;
    case inventory:
        econio_textcolor(COL_LIGHTRED);
        printf("%s", str);
        break;
    case commands:
        econio_textcolor(COL_LIGHTGREEN);
        printf("Parancsok: %s\n", str);
        break;
    case listae:
        econio_textcolor(COL_YELLOW);
        printf("%s", str);
        break;
    case helytelen:
        econio_textcolor(COL_RED);
        printf("Hiba: %s\n", str);
        break;
    default:
        printf("%s\n", str);
        break;
    }
    econio_textcolor(COL_WHITE);
}





