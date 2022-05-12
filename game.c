#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "display.h"
#include "econio.h"
#include "filehandle.h"
#include "datahandle.h"
#include "game.h"
#include "debugmalloc.h"

void jatek(Allapot *allapot, bool *vege, char *parancsok){
     printf_formazott(sima, "\n------------------------------------------");
        char parancs[101];
        beolvas_string(parancs);
        if(strcmp(parancs, "megy")==0) {megy(allapot);printf_formazott(commands, parancsok);listakiir(allapot->inventory, inventory);}
            else if(strcmp(parancs, "keres")==0) {keres(allapot);;printf_formazott(commands, parancsok);listakiir(allapot->inventory, inventory);}
            else if(strcmp(parancs, "hasznal")==0) {hasznal(allapot);;printf_formazott(commands, parancsok);listakiir(allapot->inventory, inventory);}
            else if(strcmp(parancs, "beszel")==0) {beszel(allapot);;printf_formazott(commands, parancsok);listakiir(allapot->inventory, inventory);}
            else if(strcmp(parancs, "nyomok")==0) {nyomok(allapot);;printf_formazott(commands, parancsok);listakiir(allapot->inventory, inventory);}
            else if(strcmp(parancs, "vadol")==0) vadol(vege, allapot);
            else if(strcmp(parancs, "ment")==0) ment(allapot);
            else if(strcmp(parancs, "kilep")==0) kilep(vege, allapot);
            else {
                    printf_formazott(helytelen, "Nincs ilyen parancs!");
            }
        if(strcmp(parancs, "kilep") != 0 && strcmp(parancs, "ment") != 0 && strcmp(parancs, "vadol") != 0)
            hova_mehet(allapot);
}

void start(bool *vege, Allapot *allapot){
    printf_formazott(story, "Új játék vagy mentés betöltése?");
    printf_formazott(commands, "new_game   load");
    char parancs[10];
    beolvas_string(parancs);
    bool helyes = false;
    while(!helyes){
        if(strcmp(parancs, "new_game")==0){
            econio_clrscr();
            uj_jatek(&helyes, allapot);
        }

        else if(strcmp(parancs, "load")==0){
            econio_clrscr();
            betolt(&helyes, allapot);
        }
        else{
            printf_formazott(helytelen, "Nincs ilyen parancs");
            beolvas_string(parancs);
        }
    }
    //szoveg kiiratas
    *vege = false;
    printf("\n");
    for(int i = 0; i < allapot->szovegek_szama; i++)
        if(strcmp(allapot->story[i][0], "start") == 0)
            printf_formazott(story, allapot->story[i][3]);
    printf("\n");
    char temp[200] = "Jelenlegi hely: ";
    strcat(temp, allapot->hely);
    printf_formazott(story, temp);
    printf_formazott(story, "Innen mehetsz:");
    int oszlop;
    for(oszlop = 0; strcmp(allapot->palya[0][oszlop], allapot->hely) != 0; oszlop++)
        ;
    for(int i = 1; i < allapot->helyek_szama; i++)
            if(strcmp(allapot->palya[i][oszlop], "1") == 0){
                printf_formazott(listae, allapot->palya[i][0]);
                printf_formazott(listae, "  ");
            }
            printf("\n");
}

void uj_jatek(bool *helyes, Allapot *allapot){
    printf_formazott(story, "Válassz játékmódot!");
    printf_formazott(commands, "gm1 gm2 gm3");
    char temp[201];
    while(!*helyes){
        *helyes = true;
        beolvas_string(temp);
        if(strcmp(temp, "gm1")==0) printf_formazott(story, "Kezdő");
            else if(strcmp(temp, "gm2")==0) printf_formazott(story, "Középhaladó");
            else if(strcmp(temp, "gm3")==0) printf_formazott(story, "Haladó");
            else{
                *helyes = false;
                printf_formazott(helytelen, "nincs ilyen játékmód");
            }
    }
    allapot->jatekmod = (char*) malloc((strlen(temp)+1)*sizeof(char));
    strcpy(allapot->jatekmod, temp);
    printf_formazott(story, "Add meg a mentés nevét!");
    beolvas_enterig(temp);
    allapot->nev = (char*) malloc((strlen(temp)+1)* sizeof(char));
    strcpy(allapot->nev, temp);

    jatek_betolt(allapot);

    allapot->hely = (char*) malloc((strlen(allapot->palya[0][1])+1)*sizeof(char));
    strcpy(allapot->hely, allapot->palya[0][1]);
    allapot->eredmeny = false;
    econio_clrscr();
}

void betolt (bool *helyes, Allapot *allapot){
    Lista *mentesek = NULL;
    mentesek_listaz(&mentesek);
    if(mentesek == NULL){
        printf_formazott(story, "Nincsenek mentett jatekallasok! Kezdj uj jatekot!");
        felszabadit_lista(mentesek);
        uj_jatek(helyes, allapot);
    }else{
    printf_formazott(story, "Válaszd ki a mentést!");
    listakiir(mentesek, sima);

    char nev[41];
    while(!*helyes){
        *helyes = true;
        beolvas_enterig(nev);
        if(!bemenet_ellenorzes(nev, mentesek)){
            printf_formazott(helytelen,"Helytelen bemenet");
            *helyes = false;
        }
    }
    felszabadit_lista(mentesek);

    mentes_betolt(nev,allapot);
    jatek_betolt(allapot);
    econio_clrscr();
    printf_formazott(story, "Jelenlegi állás:");
    printf_formazott(sima, "Tárgyak:");
    listakiir(allapot->inventory, sima);
    printf_formazott(sima, "Nyomok:");
    listakiir(allapot->nyom, listae);
    printf_formazott(sima, "Infomációk:");
    listakiir(allapot->info, listae);
}
}


void megy(Allapot *allapot){
    char hova[31];
    int oszlop, sor;
    beolvas_string(hova);
    for(sor = 1; strcmp(allapot->palya[sor][0], allapot->hely) != 0;sor++)
        ;
    for(oszlop = 1; oszlop < allapot->helyek_szama && strcmp(allapot->palya[0][oszlop], hova) != 0; oszlop++)
        ;
    if(oszlop == allapot -> helyek_szama){
        printf_formazott(helytelen, "Ninc ilyen hely.");
    }else{
    if(strcmp(allapot->palya[sor][oszlop], "1") == 0){
        for(int i = 0; i < allapot->szovegek_szama; i++)
        if(strcmp(allapot->story[i][0], "megy") == 0 && strcmp(allapot->story[i][1], hova)==0)
            printf_formazott(story, allapot->story[i][3]);
        printf("\n");
        free(allapot->hely);
        allapot->hely = (char*) malloc((strlen(hova)+1)*sizeof(char));
        strcpy(allapot->hely, hova);
    }else{
        printf_formazott(helytelen, "Jelenlegi helyedről ide nem mehetsz!");
    }
    }
}

 void keres(Allapot *allapot){
    char feltetel[201] = "NULL";
    bool talalt = false;
    for(int i = 0; i < allapot->szovegek_szama; i++){
        if(strcmp(allapot->story[i][0], "keres") == 0 && strcmp(allapot->story[i][1], allapot->hely) == 0){
            if(strcmp(allapot->story[i][6], "info") == 0)
                    info_feltetel(allapot,i,feltetel);
            if(strcmp(feltetel, "NULL") == 0 || bemenet_ellenorzes(feltetel, allapot->info)){
                    if(bemenet_ellenorzes(allapot->story[i][5], allapot->inventory))
                        ;
                    else{
                        printf("\n");
                        printf_formazott(story, allapot->story[i][3]);
                        printf("\n");
                        if(strcmp(allapot->story[i][4], "inventory") == 0)
                            if(!(bemenet_ellenorzes(allapot->story[i][5], allapot->inventory)))
                                listabatesz(allapot->story[i][5], &(allapot->inventory));
                        if(strcmp(allapot->story[i][4], "nyom") == 0)
                            if(!(bemenet_ellenorzes(allapot->story[i][5], allapot->nyom)))
                                listabatesz(allapot->story[i][5], &(allapot->nyom));
                        }

                    talalt = true;
                }
        }
    }
    if(!talalt) printf_formazott(sima, "Nem talaltal semmit.");
 }
 void hasznal(Allapot *allapot){
     char eszkoz[31];
     int i; bool helyes = false;
     scanf(" ");
     beolvas_enterig(eszkoz);
     for(i = 0; i < allapot->szovegek_szama; i++)
        if(strcmp(allapot->story[i][0], "hasznal") == 0 && strcmp(allapot->story[i][1], allapot->hely) == 0 && strcmp(allapot->story[i][2], eszkoz) == 0){
            if(bemenet_ellenorzes(eszkoz, allapot->inventory)){
                if(strcmp(allapot->story[i][5], "inventory")==0){
                    helyes = true;
                    if(bemenet_ellenorzes(allapot->story[i][4], allapot->inventory))
                        printf_formazott(sima, "Már felhasznaltad ezt a tartgyat itt!");
                    else{
                        printf_formazott(story, allapot->story[i][3]);
                        listabatesz(allapot->story[i][4], &(allapot->inventory));
                    }

                }else if(strcmp(allapot->story[i][5], "info")==0){
                        helyes = true;
                        char temp[201];
                        strcpy(temp, allapot->story[i][4]);
                        strcat(temp, ": ");
                        strcat(temp, allapot->story[i][3]);
                        if(bemenet_ellenorzes(temp, allapot->info))
                            printf_formazott(sima, "Már felhasznaltad ezt a tartgyat itt!");
                        else{
                            printf_formazott(story,temp);
                            listabatesz(temp, &(allapot->info));
                        }
            }


        }else
            printf_formazott(helytelen, "Some unexpecter error."); //ha egyik if sem teljesül, de jol hasznalna

     }
     if(!helyes)
            printf_formazott(helytelen, "Nincs ilyen tárgy a birtokodban vagy itt nem hasznalhatod.");

 }
 void beszel(Allapot *allapot){
    char temp[201];
    bool beszelt = false ;
     for(int i = 0; i < allapot->szovegek_szama; i++){
        if(strcmp(allapot->story[i][0], "beszel") == 0 && strcmp(allapot->story[i][1], allapot->hely) == 0){
            char feltetel[201] = "NULL";
            if(strcmp(allapot->story[i][6], "info") == 0)
                info_feltetel(allapot,i,feltetel);
            if(bemenet_ellenorzes(feltetel, allapot->info) || strcmp(feltetel, "NULL") == 0){
                strcpy(temp, allapot->story[i][4]);
                strcat(temp, ": ");
                strcat(temp, allapot->story[i][3]);
                printf("\n");
                printf_formazott(story, temp);
                printf("\n");
                beszelt = true;
                if(!(bemenet_ellenorzes(temp, allapot->info)))
                    listabatesz(temp, &(allapot->info));
                break;
            }

        }
    }
    if(!beszelt) printf_formazott(sima, "Nem tudsz itt kivel beszelni.");
 }


 void nyomok(Allapot *allapot){
     printf_formazott(story, "Nyomok:");
     listakiir(allapot->nyom, sima);
     printf_formazott(story, "Infmorációk:");
     listakiir(allapot->info, listae);
 }


 void vadol(bool *vege, Allapot *allapot){
        char vadlott[31];
        beolvas_string(vadlott);

            if(strcmp(vadlott, allapot->tettes) == 0){
                econio_textbackground(COL_GREEN);
                for(int i = 0; i < 6; i++){
                    for(int k = 0; k < 3; k++){
                        for(int j = 0; j < 8; j++){
                            if(j == -3 + i||j == 7-i)
                                printf("X");
                                else printf(" ");
                        }
                        printf(" ");
                    }
                    printf("\n");
                }
                econio_textbackground(COL_BLACK);
                printf_formazott(story, "Helyes megfejtés! A játék véget ért!");
                allapot->eredmeny = true;
                kilep(vege, allapot);
            }else{
                econio_textbackground(COL_RED);
                for(int i = 0; i < 7; i++){
                    for(int k = 0; k < 3; k++){
                        for(int j = 0; j < 7; j++){
                            if(j == i || 6-j == i)
                                printf("X");
                                else printf(" ");
                        }
                        printf(" ");
                    }
                    printf("\n");
                }
                econio_textbackground(COL_BLACK);
                printf_formazott(helytelen, "Rossz megfejtés! Próbáld újra!");
            }
     }


 void ment(Allapot *allapot){
     mentes_letrehoz(allapot);
     printf_formazott(story, "Játékállás mentve");
     }


 void kilep(bool *vege, Allapot *allapot){
     printf_formazott(story, "Szeretnéd menteni a játékállást? (I/N)");
     char c;
     while(c != 'I' && c != 'N'){
         scanf(" %c%*[^\n]%*c", &c);
         switch(c){
         case 'I': ment(allapot); break;
         case 'N': printf_formazott(sima, "Kilépés mentés nélkül."); break;
         default: printf_formazott(helytelen, "Érvénytelen bemenet."); break;
     }
     }
     felszabadit_allapot(allapot);
     *vege = true;
     printf_formazott(story, "A játék véget ért.");
 }
