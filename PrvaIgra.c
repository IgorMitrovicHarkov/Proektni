#include "MainScreen.h"
#include "GenericFunctions.h"
#include "PrvaIgra.h"

void brojevi() //Funkcija za pozivanje prve igre
{
    int seed = time(NULL);
    int unos,brojac = 0, bodoviPrvaIgra, izbor, c;

    srand(seed);
    system("cls");
    printHeader();

    printf("POGADJANJE BROJA\n");
    sleep(1);
    int broj = rand()% 100+0;

    printf("BROJ GENERISAN!\n");
    printf("BROJ POKUSAJA JE 5\n");

    for(int i = 1; i<=5; i++)
    {
        brojac++;
        printf("%d. Pokusaj\n\n",i);
        do{
            fflush(stdin);
            printf("Unesite broj: ");
            fflush(stdin);
            c = scanf("%d",&unos);
        }while(c!=1);


        if(broj>unos)
            printf("Broj koji ste unijeli je manji od zamisljenog broja!\n\n");
        else
        {
            if(broj < unos)
                printf("Broj koji ste unijeli je veci od zamisljenog broja!\n\n");
            else
            {
                if(checkWritePlayHistory(1)!=1) //Ako je igra pobjedjena prvih 3 puta onda nema kontrole
                {
                    printf("Pogodili ste broj iz %d. pokusaja!\n",i);
                    printf("Vas broj: %d zamisljen broj: %d\n",unos,broj);
                    bodoviPrvaIgra = 100/brojac;
                    printf("Dobili ste %d bodova!\n\n",bodoviPrvaIgra);
                    writeScore("Profil.txt",bodoviPrvaIgra);
                    writeGameHistory("Igra1.txt","POGADJANJE BROJEVA",bodoviPrvaIgra);
                    break;
                }
                else //Ako je igra povjedjena vise od 3 puta onda se ispunjava uslov dat u opisu zadatka
                {
                    int ulozeniBodovi = readScore();
                    printf("Pogodili ste broj iz %d. pokusaja!\n",i);
                    printf("Vas broj: %d zamisljen broj: %d\n",unos,broj);
                    bodoviPrvaIgra = 100/brojac;

                    if(ulozeniBodovi>bodoviPrvaIgra)
                    {
                        int n = 0.4*bodoviPrvaIgra;

                        int izgubljeniBodovi = n+bodoviPrvaIgra;
                        int ukupno = bodoviPrvaIgra - izgubljeniBodovi;
                        printf("Ulozili ste previse bodova!\n");
                        printf("Kontrola:\n");
                        printf("Dobili ste %d bodova!\n\n",ukupno);
                        writeScore("Profil.txt",ukupno);
                        writeGameHistory("Igra1.txt","POGADJANJE BROJEVA",ukupno);
                        break;
                    }
                    else
                    {
                        printf("Dobili ste %d bodova!\n\n",bodoviPrvaIgra);
                        writeScore("Profil.txt",bodoviPrvaIgra);
                        writeGameHistory("Igra1.txt","POGADJANJE BROJEVA",bodoviPrvaIgra);
                        break;
                    }

                }
            }
        }

    }
    if(brojac == 5)
    {
        printf("Niste uspijeli pogoditi broj!\nZamisljen broj je bio %d\n\n",broj);
    }


        printf("1. IZLAZ\n");
        printf("2. PONOVNA IGRA\n");
        printf("3. OTKAZI IGRU\n");
        do{
        AGAIN4:
        printf("UNESITE OPCIJU: ");
        fflush(stdin);
        c = scanf("%d",&izbor);
    }while(c!=1);

    if(izbor == 1)
        mainScreen();
    if(izbor == 2)
        brojevi();
    if(izbor == 3)
    {
        sealGame(0);
        mainScreen();
    }
goto AGAIN4;
}

int readScore() //Funkcija za citanje profilnih bodova iskoristena za validaciju uslova
{
    FILE *fp;
    fp = fopen("Profil.txt","r");
    if(fp == NULL)
        printf("ERROR 000: Windows error!");
    int score;
    fscanf(fp,"%d",&score);
    rewind(fp);
    fclose(fp);
    return score;
}

/*Pomocna funkcija za brojanje i validaciju koliko je puta igra pobjedjena
  sluzi za validaciju uslova*/

int checkWritePlayHistory(int put)
{
    FILE *fp;
    int suma;
    fp = fopen("IgranjeIstorija.txt","a");
    if(fp == NULL)
        printf("ERROR 000: Windows error!");
    fseek(fp,0,SEEK_END);
    if(ftell(fp)==0)
    {
         fprintf(fp,"%d",1);
         rewind(fp);
         fclose(fp);
         return 0;
    }
    rewind(fp);
    freopen("IgranjeIstorija.txt","r",fp);
    fscanf(fp,"%d",&suma);
    suma+=put;
    if(suma<=3)
    {
        freopen("igranjeIstorija.txt","w",fp);
        fprintf(fp,"%d",suma);
        fclose(fp);
        return 0;
    }
    fclose(fp);
    return 1;
}
