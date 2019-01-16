#include "MainScreen.h"
#include "GenericFunctions.h"
#include "PrvaIgra.h"
#include "GameStatistics.h"
#include "DrugaIgra.h"

void quitGame()
{
    int izbor;
    int c;
    clearCustom();
    printf("DA LI ZELITE STVARNO DA IZADJETE IZ PLATFORME?\n");
    printf("1. DA\n2. NE\n");
    do{
        AGAIN:
        printf("UNESITE OPCIJU:");
        fflush(stdin);
        c = scanf("%d",&izbor);
    }while(c!=1);


    if(izbor == 1)
        exit(0);
    if(izbor == 2)
        mainScreen();
    goto AGAIN;
}
/*Funkcija quitGame() je funkcija za izlazak iz platforme i kraj rada*/

void printScore()
{
    FILE *fp;
    fp = fopen("Profil.txt","r");
    if(fp == NULL)
        printf("ERROR 000:Windows error!\n");
    int bodovi;
    fscanf(fp,"%d",&bodovi);
    fclose(fp);
    printf("\n UKUPAN BROJ BODOVA: %d\n",bodovi);
}
/*printScore funkcije je funkcija koja ucitava ukupan broj bodova iz
  profilne datoteke u kojoj se cuvaju bodovi na profilu*/

void printFooter()
{
    int x,y;
    getScreenCoordinates(&x,&y);
    printf("\n");
    for(int i = 0; i<x; i++)
    {
        printf("%c",205);
    }
}
/*printFooter() funkcija je funkcija za isprintanje footera nakon headera*/

void printMainScreen()
{
    printf("1. POGADJANJE BROJA");
    printGameStatus(0);
    printf("2. KVIZ");
    printGameStatus(1);
    printf("3. PREGLED STATISTIKE\n");
    printf("4. IZLAZ");
}
/*Komponenta funkcije mainScreen() koja isprintava opcije platforme i status
  igara*/

/*Funkcija mainScreen() je funkcija koja je zadužena za:
    1. Ispisivanje naslovne trake
    2. Ispisivanje poena na profilu
    3. Validaciju statusa igara
    4. Ispisivanje opcija platforme i statusa
       igara*/
void mainScreen()
{
    FILE *fp;
    int opcija;
    bool controll = false;

    system("cls");
    printHeader();
    printScore();
    printFooter();
    //Ispis naslovne trake i bodova

    fp = fopen("Timer.txt","r");
    if(fp != NULL)
    {
        keyTimer();
        fclose(fp);
    }
    //Provjeravanje da li je otpoceo timer za drugi kljuc i njegov status
    printMainScreen();

    while(!controll){
    fflush(stdin);
    printf("\nIZABERITE OPCIJU:");
    scanf("%d",&opcija);
        switch(opcija)
        {
            case 1:
                if(validateKeyGen(0)==1 || validateKeyGen(0) == 2) //Ako je kljuc validan...
                {
                    int prvaIgra, drugaIgra;
                    readGameStatus(&prvaIgra,&drugaIgra);
                    if(prvaIgra == 3)
                    {
                        clearCustom();
                        printf("IGRA JE OTKAZANA NE MOZE SE VISE IGRATI!\n");
                        sleep(2);
                        mainScreen();
                    }
                    //... jos provjeriti da nije igra otkazana ako jest onda se ne moze igrati
                        //ako nije onda zapocinje prva igra.
                    else
                        brojevi();
                };
            break;
            case 2:
                //Isto kao i u prvoj igri samo ovde jos provjeravamo da li timer nije istekao
                if(validateKeyGen(1)==1 || validateKeyGen(1) == 2)
                {
                    if(keyTimer() == 0)
                    {
                         int prvaIgra, drugaIgra;
                         readGameStatus(&prvaIgra,&drugaIgra);
                         if(drugaIgra == 3)
                         {
                            clearCustom();
                            printf("IGRA JE OTKAZANA NE MOZE SE VISE IGRATI!\n");
                            sleep(2);
                            mainScreen();
                         }

                        kviz();
                    }
                    else
                    {
                        system("cls");
                        printHeader();
                        printf("KLJUC ISTEKAO!");
                        sleep(2);
                        mainScreen();
                    }
                };
            break;
            case 3: pregledStatistike();
            break;
            case 4: controll = true;

            break;
            default: printf("NEPOSTOJECA OPCIJA!");
        }
    }
    quitGame();
}
