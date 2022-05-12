#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

//STRUKTURAK


typedef struct Lista{
    char *adat;
    struct Lista *kov;
}Lista;
typedef struct Allapot{
    char *nev, *hely, *jatekmod, ***palya, ***story, *tettes;
    int helyek_szama, szovegek_szama;
    bool eredmeny;
    Lista *inventory, *nyom, *info;
}Allapot;

//FUGGVENYEK
void jatek(Allapot *allapot, bool *vege, char *parancsok);
void start(bool *vege, Allapot *allapot);
void uj_jatek(bool *helyes, Allapot *allapot);
void betolt (bool *helyes, Allapot *allapot);
    //játékkommandok
void megy(Allapot *allapot);
void keres(Allapot *allapot);
void hasznal(Allapot *allapot);
void beszel(Allapot *allapot);
void nyomok(Allapot *allapot);
void vadol(bool *vege, Allapot *allapot);
void ment(Allapot *allapot);
void kilep(bool *vege, Allapot *allapot);


#endif // GAME_H_INCLUDED
