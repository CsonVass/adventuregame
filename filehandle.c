#include <dirent.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include "display.h"
#include "filehandle.h"
#include "datahandle.h"
#include "game.h"
#include "debugmalloc.h"


//https://stackoverflow.com/questions/12976733/how-can-i-get-only-txt-files-from-directory-in-c/12976897#12976897
bool has_txt_extension(char const *name){
    size_t len = strlen(name);
    return len > 4 && strcmp(name + len - 4, ".txt") == 0;
}

void mentesek_listaz(Lista **lista){
 DIR *d = opendir("gamefiles\\saves");  /* melyik mappát */
    if (d == NULL) {
        perror("Nem sikerült megnyitni");
    } else {
        struct dirent *de;
        while ((de = readdir(d)) != NULL) {
            if(has_txt_extension(de->d_name)){
                csonkit(de->d_name, 4);
                listabatesz(de->d_name,lista);
            }
        }
        closedir(d);
    }
}


void jatek_betolt(Allapot *allapot){
    char hely[64], temp[201], tab[2] = "\t", *token;
    int oszlop = 0, sor = 0;
    strcpy(hely, "gamefiles\\");
    strcat(hely, allapot->jatekmod);
    strcat(hely, "\\helyszinek.txt");
    FILE *helyszinek = fopen(hely, "r");
    if(helyszinek == NULL){
        perror("Nem sikerült megnyitni a helyszínek fájlt.");
    }else{
        while(fscanf(helyszinek, "%[^\n]", temp) == 1){
            token = strtok(temp, tab);
            for(oszlop = 0; token != NULL; oszlop++)
                token = strtok(NULL, tab);
            sor++;
            fscanf(helyszinek, "%*[\n]");

    }
    allapot->helyek_szama = sor;
    allapot->palya = (char***) malloc(sor * sizeof(char**));
    for(int y = 0; y < sor; y++)
        allapot->palya[y] = (char**) malloc(sor * sizeof(char*));

    rewind(helyszinek);

    for(int i = 0; i < sor; i++){
        fgets(temp, 200, helyszinek);
        csonkit(temp, 1);
        token = strtok(temp, tab);
        for(int j = 0; token != NULL; j++){

            allapot->palya[i][j] = (char*) malloc((strlen(token)+1)*sizeof(char));
            strcpy(allapot->palya[i][j], token);
            token = strtok(NULL, tab);

        }
    }
    }
    fclose(helyszinek);

    strcpy(hely, "gamefiles\\");
    strcat(hely, allapot->jatekmod);
    strcat(hely, "\\tortenet.txt");
    FILE *tortenet = fopen(hely, "r");
    if(tortenet == NULL){
        perror("Nem sikerült megnyitni a tortenet fájlt.");
    }else{
        sor = 0; oszlop = 0;
        fgets(temp, 200, tortenet);
        fscanf(tortenet, "%*[\n]");
        csonkit(temp, 1);
        allapot->tettes = (char*) malloc((strlen(temp)+1)*sizeof(char));
        strcpy(allapot->tettes, temp);
        while(fscanf(tortenet, "%[^\n]", temp) == 1){
            token = strtok(temp, tab);
            for(oszlop = 0; token != NULL; oszlop++)
                token = strtok(NULL, tab);
            sor++;
            fscanf(tortenet, "%*[\n]");

    }
    allapot->szovegek_szama = sor;
    allapot->story = (char***) malloc(sor * sizeof(char**));
    for(int y = 0; y < sor; y++)
        allapot->story[y] = (char**) malloc(oszlop * sizeof(char*));

    rewind(tortenet);
    fgets(temp, 200, tortenet);
    fscanf(tortenet, "%*[\n]");
    for(int i = 0; i < allapot->szovegek_szama; i++){
        fgets(temp, 200, tortenet);
        csonkit(temp, 1);
        token = strtok(temp, tab);
        for(int j = 0; j<7; j++){
            allapot->story[i][j] = (char*) malloc((strlen(token)+1)*sizeof(char));
            strcpy(allapot->story[i][j], token);
            token = strtok(NULL, tab);

        }
    }

    }
    fclose(tortenet);

}

void mentes_betolt(char *fajlnev, Allapot *allapot){
    char hely[64] = "gamefiles\\saves\\";
    char temp[201], tab[2] = "\t", *token;
    strcat(hely, fajlnev);
    strcat(hely, ".txt");
    FILE *f = fopen(hely, "r");
    if(f == NULL)
        printf_formazott(sima, "Nem sikerült megnyitni a fajlt.");
    else{
    //nev
    fgets(temp, 200,  f);
    csonkit(temp, 1);
    allapot->nev = (char*) malloc((strlen(temp)+1)*sizeof(char));
    strcpy(allapot->nev, temp);
    //ido atugras (nem kell)
    fgets(temp, 200,  f);
    //jatekallas
    fgets(temp, 200,  f);
    csonkit(temp, 1);
    if(strcmp(temp, "true") == true)
        allapot->eredmeny = true;
    else
        allapot->eredmeny = false;
    //jatekmod
    fgets(temp, 200,  f);
    csonkit(temp, 1);
    allapot->jatekmod = (char*) malloc((strlen(temp)+1)*sizeof(char));
    strcpy(allapot->jatekmod, temp);
    //hely
    fgets(temp, 200,  f);
    csonkit(temp, 1);
    allapot->hely = (char*) malloc((strlen(temp)+1)*sizeof(char));
    strcpy(allapot->hely, temp);
    //inventory
    fgets(temp, 200, f);
    csonkit(temp, 1);
    token = strtok(temp, tab);
    while(token != NULL){
        listabatesz(token, &(allapot->inventory));
        token = strtok(NULL, tab);
    }
    //nyomok
    fgets(temp, 200, f);
    csonkit(temp, 1);
    token = strtok(temp, tab);
    while(token != NULL){
        listabatesz(token, &(allapot->nyom));
        token = strtok(NULL, tab);
    }
    //infok
    while(fscanf(f, "%[^\n]", temp) == 1){
        listabatesz(temp, &(allapot->info));
        fscanf(f, "%*[\n]");
    }

    fclose(f);
    }
}

void mentes_letrehoz(Allapot *allapot){
    //mentesi fajl eleresi helye
    int meret = 18 + strlen(allapot->nev)+4+1;
    char *fajl = (char*) malloc(meret*sizeof(char));
    strcpy(fajl, "gamefiles\\saves\\");
    strcat(fajl, allapot->nev);
    strcat(fajl, ".txt");
    //uj fajl letrehozasa, ezzel a korabbi felulirasa
    FILE *f = fopen(fajl, "w");
    //elso sor, nev beirasa
    fprintf(f, "%s\n",allapot->nev);
    //masodik sor, mentes ideje
    time_t rawtime;
    struct tm * timeinfo; //https://stackoverflow.com/questions/5141960/get-the-current-time-in-c
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    fprintf(f, "%s", asctime(timeinfo));
    //harmadik sor, eredmeny beirasa
    if(allapot->eredmeny == true)
        fprintf(f, "%s\n", "true");
        else fprintf(f, "%s\n", "false");
    //negyedik sor, jatekmod
    fprintf(f, "%s\n", allapot->jatekmod);
    //otodik sor, hely
    fprintf(f, "%s\n", allapot->hely);
    //otodik sor, inventory
    Lista *seged;
    seged = allapot->inventory;
    if(allapot->inventory == NULL) fprintf(f, "empty");
    else
        while(seged != NULL){
            fprintf(f, "%s\t", seged->adat);
            seged = seged->kov;
        }
    fprintf(f, "\n");
    //hatodik sor, nyomok
    seged = allapot->nyom;
    if(allapot->nyom == NULL) fprintf(f, "empty");
    else
        while(seged != NULL){
            fprintf(f, "%s\t", seged->adat);
            seged = seged ->kov;
        }
    fprintf(f, "\n");
    //maradek sor, informaciok
    seged = allapot->info;
    if(allapot->info == NULL) fprintf(f, "empty");
    else
        while(seged != NULL){
            fprintf(f, "%s\n", seged->adat);
            seged = seged->kov;
        }
    //fajl bezarasa, dinamikus terulet felszabaditasa
    fclose(f);
    free(fajl);
}
