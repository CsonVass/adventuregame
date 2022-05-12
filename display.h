#ifndef DISPLAY_H_INCLUDED
#define DISPLAY_H_INCLUDED

typedef enum Formatum{
    sima,
    story,
    inventory,
    commands,
    listae,
    helytelen
}Formatum;

void printf_formazott(Formatum formatum, char *str);

#endif // DISPLAY_H_INCLUDED
