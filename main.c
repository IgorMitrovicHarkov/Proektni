#include "includes.h"
#include "LoadingScreen.h"
#include "MainScreen.h"
#include "GenericFunctions.h"

/**AUTOR: IGRO MITROVIC
          GRUPA 17
          SOLO GRUPA
          INDEKS 1191\17**/

void initGameStatus();
void profile();

void initGameStatus()
{
    FILE *fp;
    fp = fopen("GameStat.txt","a");
    if(fp == NULL)
        printf("ERROR 000: Windows error!");

    fseek(fp,0,SEEK_END);
    if(ftell(fp) == 0)
    {
        fprintf(fp,"%d,%d",0,0);
    }
    rewind(fp);
    fclose(fp);
}

/*Ova funkcija je zaduzena da prilikom prvog pokretanja
  inicijalizuje igre na status zakljucano*/

void profile()
{
        FILE *fp;
        fp = fopen("Profil.txt","a");
        if(fp == NULL)
            printf("ERROR 000: Windows error!");
        fseek(fp,0,SEEK_END);
        if(ftell(fp)==0)
        {
            fprintf(fp,"%d",10);
        }
        rewind(fp);
        fclose(fp);
}

/*Ova funkcija je zaduzena da prilikom prvog pokretanja
  inicijalizuje pocetnih 10 bodova koji korisnik ima na profilu*/

int main()
{
    loadingScreen(); //Pozivamo pocetni ekran za ucitavanje
    keyGen(); //Generisemo kljuceve [samo prilikom prvog instance]
    profile(); //Generisemo 10 bodova na profilu [samo prilikom prvog instance]
    initGameStatus(); //Inicijalizujemo pocetni status obe igre [Zakljucano]
    mainScreen(); //Generisemo glavi ekran
    return 0;
}
