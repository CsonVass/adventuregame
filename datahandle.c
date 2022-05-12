#include <dirent.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include "display.h"
#include "filehandle.h"
#include "datahandle.h"
#include "game.h"
#include "debugmalloc.h"


void beolvas_string(char *str){
    printf("\n");
    scanf("%s", str);
}

void beolvas_enterig(char *str){
    printf("\n");
    scanf("\n");
    fgets(str, 200, stdin);
    csonkit(str, 1);
    printf("\n");
}

void csonkit(char *szo, int levagando){
    int hossz = strlen(szo);
    if(strlen(szo) > levagando)
        szo[hossz-levagando] = '\0';
    else
        szo = NULL;
}


bool bemenet_ellenorzes(char *bemenet, Lista *elvart){
    if(elvart == NULL) return false;
    Lista *seged;
    seged = elvart;
    while(seged->kov != NULL){
        if(strcmp(seged->adat, bemenet)==0) return true;
        seged = seged->kov;
    }
    if(strcmp(seged->adat, bemenet)==0) return true;
    return false;
}

void listabatesz(char *mit, Lista **lista){
    Lista *uj;
    uj = (Lista*) malloc(sizeof(Lista));
    uj -> kov = NULL;
    int hossz = strlen(mit);
    uj -> adat = (char*) malloc((hossz+1)*sizeof(char));
    strcpy(uj -> adat, mit);
    if(*lista != NULL && strcmp((*lista)->adat, "empty")==0){
       free((*lista)->adat);
       free((*lista));
       *lista = NULL;
    }
    if(*lista == NULL){
        *lista = uj;
    }else{
        Lista *seged = *lista;
        while (seged -> kov != NULL)
            seged = seged->kov;
        seged->kov = uj;
    }

}

void listakiir(Lista *lista, Formatum forma){
    if(lista == NULL){
       if(forma == inventory) printf_formazott(inventory, "[empty]");
       else printf_formazott(listae, "empty\n");
    }else{
    Lista *seged = lista;
    if(forma == inventory){
        printf_formazott(inventory, "Inventory: [");
        while(seged->kov != NULL){
            printf_formazott(inventory, seged->adat);
            printf_formazott(inventory, ", ");
            seged = seged->kov;
        }
        printf_formazott(inventory, seged->adat);
        printf_formazott(inventory, "]");
        printf("\n");
    }else{
    while(seged->kov != NULL){
        printf_formazott(listae, seged->adat);
        if(forma == listae)
            printf("\n");
        else
            printf_formazott(listae, ", ");
        seged = seged->kov;
    }
    printf_formazott(listae, seged->adat);
    printf("\n");
    }
    }
}

void felszabadit_lista(Lista *lista){
    Lista *now = lista;
    while(now != NULL){
        Lista *next = now->kov;
        free(now->adat);
        free(now);
        now = next;
    }
}

void felszabadit_allapot(Allapot *allapot){
    felszabadit_lista(allapot->inventory);
    felszabadit_lista(allapot->nyom);
    felszabadit_lista(allapot->info);
    free(allapot->nev);
    free(allapot->hely);
    free(allapot->jatekmod);
    free(allapot->tettes);
    for(int y = 0; y < allapot->helyek_szama; y++){
        for(int x = 0; x < allapot->helyek_szama; x ++)
            free(allapot->palya[y][x]);
        free(allapot->palya[y]);
    }
    free(allapot->palya);

    for(int y = 0; y < allapot->szovegek_szama; y++){
        for(int x = 0; x < 7; x ++)
            free(allapot->story[y][x]);
        free(allapot->story[y]);
    }
    free(allapot->story);
}

void hova_mehet(Allapot *allapot){
    char temp[201];
    int oszlop;
    for(oszlop = 1; oszlop < allapot->helyek_szama && strcmp(allapot->palya[0][oszlop], allapot->hely) != 0; oszlop++)
        ;
        printf("\n");
        strcpy(temp, allapot->hely);
        strcat(temp, " helyrol ide mehetsz:");
        printf_formazott(story, temp);
        for(int i = 1; i < allapot->helyek_szama; i++)
            if(strcmp(allapot->palya[i][oszlop], "1") == 0){
                printf_formazott(listae, allapot->palya[i][0]);
                printf_formazott(listae, "    ");
            }
            printf("\n");
}

void info_feltetel(Allapot *allapot, int i, char* feltetel){
    int sor;
    sscanf(allapot->story[i][2], "%d", &sor);
                strcpy(feltetel, allapot->story[sor][4]);
                strcat(feltetel, ": ");
                strcat(feltetel, allapot->story[sor][3]);
}


