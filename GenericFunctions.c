#include "GenericFunctions.h"
#include "MainScreen.h"

void clearCustom()
{
    system("cls");
    printHeader();
}
//Funkcija koja se korist kao nova strana ili novi prozor

void sealGame(int igra)
{
    int prvaIgra, drugaIgra;
    readGameStatus(&prvaIgra,&drugaIgra);

    if(igra == 0)
    {
        writeGameStatus(3,drugaIgra); //Ako je prva igra otkazana onda se mjenja status na otkazana
    }
    else
        writeGameStatus(prvaIgra,3); //Ako je druga igra otkazana onda se mjenja status na otkazana

}

//Funkcija koja se koristi da se otkaze i potom zapecati igra

void writeScore(char *ime,int poeni)
{
    int poeniFile;
    FILE *fp;
    fp = fopen(ime,"r");
    if(fp == NULL)
        printf("ERROR 000:Windows error!");
    fscanf(fp,"%d",&poeniFile);
    rewind(fp);
    freopen(ime,"w",fp);
    fprintf(fp,"%d",poeniFile+poeni);
    fclose(fp);
}
/*Pomocna funkcija koja se koristi za upisivanje poena igre u zasebne datoteke*/

void sleepCustom(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}

/*Postoji potreba da se vec sistemska sleep()funkcija prosiri sa sposobnosti
  da se vremenski interval izrazi u milisekundama. Ova funkcija se koristi kod printout()
  pomocne funkcije*/

void getScreenCoordinates(int *x, int *y)
{
  CONSOLE_SCREEN_BUFFER_INFO csbi;
   int columns, rows;
   int ret;
   ret = GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
   columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
   rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
  if(ret)
  {
    *x = columns;
    *y = rows;
  }
    else
      printf("ERROR 000: Windows error!\n");
}
/*Funkcija koja je zaduzena za dobavljanje x i y koordinata konzolnog prozora.*/

void gotoXY(int x, int y)
{
  COORD coord;
  coord.X = x/2 ;
  coord.Y = y/2;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
//Funkcija za pozicioniranje konzolnog kursora na centar ekrana

void printHeader()
{
    int x,y;
    getScreenCoordinates(&x,&y);
    for(int i = 0; i<x; i++)
    {
         printf("%c",205);
    }
    printf("\n");
    gotoXY(x/2,2);
    printf("FREE GAMES v0.1\n");
     for(int i = 0; i<x; i++)
    {
        printf("%c",205);
    }
     printf("\n");
}
//Funkcija za printanje headera

void writeGameHistory(char *imeDatoteke,char *imeIgre,int brojBodova)
{
    FILE *fp;
    char strtime[64];
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    strftime(strtime,sizeof(strtime),"%c",tm);

    fp = fopen(imeDatoteke,"a");
    if(fp == NULL)
        printf("ERROR 000: Windows error!");
    fseek(fp,0,SEEK_END);

    if(ftell(fp)==0)
    {
        fprintf(fp,"%s\n",imeIgre);
    }

    fprintf(fp,"%s %d\n",strtime,brojBodova);
    fclose(fp);
}
//Pomocna funkcija za zapisivanje istorije igranja

int validateKeyGen(int izbor)
{


    FILE *fp;
    char kljuc1[20];
    char kljuc2[20];
    char unos[20];
    int prvaIgra, drugaIgra , opcija;
    int c;

    fp = fopen("Kljucevi.txt","r");
    if(fp == NULL)
        printf("ERROR 000: Windows error!");

    fscanf(fp,"%s\n%s",kljuc1,kljuc2);
    rewind(fp);
    fclose(fp);

    readGameStatus(&prvaIgra,&drugaIgra);

    if(izbor == 0 && prvaIgra == 0) //Ako se trazi validacija prvog kljuca
    {
        system("cls");
        printHeader();
        printf("IGRA JE ZAKLJUCANA!\n");
        Controll1:
                    printf("UNESITE KLJUC: ");
                    fflush(stdin);
                    gets(unos);
                    if(strcmp(kljuc1,unos)==0)
                    {
                        printf("IGRA JE OTKLJUCANA!\n");
                        writeGameStatus(1,drugaIgra);
                        sleep(2);
                        return 1;
                    }
                    else
                    {
                        printf("KLJUC NIJE VALIDAN!\n");
                        printf("IZABERITE OPCIJU\n\n");
                        printf("1. NAZAD\n2. PONOVNI UNOS\n\n");
                        do{
                            AGAIN1:
                            printf("UNESITE OPCIJU: ");
                            fflush(stdin);
                            c = scanf("%d",&opcija);
                        }while(c!=1);

                        if(opcija == 1)
                        {
                             mainScreen();
                              return 0;

                        }
                        if(opcija == 2)
                        {
                           goto Controll1;
                        }
                         goto AGAIN1;
                    }

    }

    if(izbor == 1 && drugaIgra == 0) //Ako se trazi validacija drugog kljuca
    {
        system("cls");
        printHeader();
        printf("IGRA JE ZAKLJUCANA!\n");
        Controll2:
                    printf("UNESITE KLJUC: ");
                    fflush(stdin);
                    gets(unos);
                    if(strcmp(kljuc2,unos)==0)
                    {
                        printf("IGRA JE OTKLJUCANA!\n");
                        writeGameStatus(prvaIgra,1);
                        setKeyTimeLenght();
                        sleep(2);
                        return 1;
                    }
                    else
                        {
                                printf("KLJUC NIJE VALIDAN!\n");
                                printf("IZABERITE OPCIJU\n\n");
                                printf("1. NAZAD\n2. PONOVNI UNOS\n\n");
                              do{
                                    AGAIN2:
                                    printf("UNESITE OPCIJU: ");
                                    fflush(stdin);
                                    c = scanf("%d",&opcija);
                                }while(c!=1);
                                if(opcija == 1)
                                {
                                      mainScreen();
                                    return 0;

                                }
                                if(opcija == 2)
                                {
                                      goto Controll2;
                                }
                                goto AGAIN2;

                        }
    }
    return 2;
}
/*Funkcija za validaciju kljuceva*/

int keyTimer()
{
    int p1, p2;

    time_t t = time(NULL);
    struct tm *tm = localtime(&t);

    FILE *fp;
    char cTime[19];
    char exTime[19];

    strftime(cTime,sizeof(cTime)-1,"%c",tm);
    cTime[19] = '\0';

    readGameStatus(&p1,&p2);

    fp = fopen("Timer.txt","r");
    if(fp == NULL)
        printf("ERROR 000: Windows error!");
    fgets(exTime,18,fp);
    exTime[strcspn(exTime, "\n")] = 0;
    rewind(fp);
    fclose(fp);

    if(strcmp(cTime,exTime)==0 || strcmp(cTime,exTime)>0)
    {
        writeGameStatus(p1,2);
        return 1;
    }
return 0;
}/*Funkcija za provjeravanje da li je kljuc istekao*/

void setKeyTimeLenght()
{
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    FILE *fp;
    fp = fopen("Timer.txt","a");
    if(fp == NULL)
        printf("ERROR 000: Windows error!");
    fseek(fp,0,SEEK_END);
    if(ftell(fp)==0)
    {
        char exDate[19];
        tm->tm_hour+=1;
        mktime(tm);
        strftime(exDate,sizeof(exDate),"%c",tm);
        fprintf(fp,"%s",exDate);
    }
    rewind(fp);
    fclose(fp);
}
/*Funkcija za postavljanje duzine drugog kljuca.
  Samo drugi kljuc je ogranicen i on traje 1 sat*/
void keyGen()
{
    FILE *fp;
    int seed = time(NULL);
    srand(seed);
    fp = fopen("Kljucevi.txt","a");
    if(fp == NULL)
        printf("ERROR 000: Windows error!\n");
    fseek(fp,0,SEEK_END);
    if(ftell(fp) == 0)
    {
        int number;
        char key[20] = {0};
        char buffer[5] = {0};
        for(int z = 0; z<2; z++)
        {
                for(int i = 0, j = 0; i<4; i++ ,j++)
                {
                    number = rand()% 9000+1000;
                    itoa(number,buffer,10);
                    strcat(key,buffer);
                    if(j<3)
                        strcat(key,"-");
                }
                fprintf(fp,"%s\n",key);
                key[0]= '\0';
        }
    }
   rewind(fp);
   fclose(fp);
}
/*Funckija za generisanje dva kljuca prvi je za prvu igru drugi za drugu*/
void readGameStatus(int *prvaIgra, int *drugaIgra)
{
    FILE *fp;
    fp = fopen("GameStat.txt","r");
    if(fp == NULL)
        printf("ERROR 000: Windows error!");

    fscanf(fp,"%d,%d",prvaIgra,drugaIgra);
    rewind(fp);
    fclose(fp);
}
//Funkcija za ocitavanje statusa igara 0 zakljucano 1 otkljucano 2 istako kljuc 3 otkazano

void writeGameStatus(int prvaIgra, int drugaIgra)
{
    FILE *fp;
    fp = fopen("GameStat.txt","w");
    if(fp == NULL)
        printf("ERROR 000: Windows error!");

    fprintf(fp,"%d,%d",prvaIgra,drugaIgra);
    rewind(fp);
    fclose(fp);
}
//Funkcija za upisivanje statusvoid clearCustom();a igara

//Funkcija koja ispisuje status igre na glavni ekran(meni)
void printGameStatus(int izbor)
{
    char exTime[19];
    FILE *fp = fopen("Timer.txt","r");
    if(fp != NULL)
    {
        fgets(exTime,18,fp);
        fclose(fp);
    }

    int prvaIgra,drugaIgra;

    readGameStatus(&prvaIgra,&drugaIgra);

    if(izbor == 0)
    {
        if(prvaIgra == 0)
            printf("\t [ %s ]\n","ZAKLJUCANO");
        if(prvaIgra == 1)
            printf("\t [ %s ]\n","OTKLJUCANO");
        if(prvaIgra == 3)
            printf("\t [ %s ]\n","OTKAZANO");
    }
    else{
        if(drugaIgra == 0)
            printf("\t\t\t [ %s ]\n","ZAKLJUCANO");

        if(drugaIgra == 1)
            printf("\t\t\t [ %s ] DO [ %s ]\n","OTKLJUCANO",exTime);
        if(drugaIgra == 2)
            printf("\t\t\t [ %s ]\n","KLJUC ISTEKAO");
        if(drugaIgra == 3)
            printf("\t\t\t [ %s ]\n","OTKAZANO");
        }

}
