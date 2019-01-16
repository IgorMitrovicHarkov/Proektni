#include "GameStatistics.h"
#include "GenericFunctions.h"
#include "MainScreen.h"

void makeList(NODE **head,char *datum, char *sat, int bodovi)
{
    NODE *novi = (NODE*)malloc(sizeof(NODE));
    strcpy(novi->datum,datum);
    strcpy(novi->sat,sat);
    novi->poeni = bodovi;
    novi->next = NULL;


    if(*head == NULL)
        *head = novi;
    else{
        NODE *tmp = *head;
        while(tmp->next != NULL)
            tmp = tmp->next;
        tmp->next = novi;
    }
}
//Pomocna funkcija za kreiranje ulancane liste

void printList(NODE *head)
{
    while(head !=NULL){
        printf("%s %s %d\n",head->datum,head->sat,head->poeni);
        head = head->next;
    }

}
//Funkcija za prikaz liste

void sortList(NODE *head)
{
    NODE *i,*j;
    NODE tmp;

    for(i = head; i->next != NULL; i = i->next)
    {
        for(j =i->next; j != NULL; j = j->next)
        {
            if(i->poeni < j->poeni)
            {
                tmp.poeni = i->poeni;
                strcpy(tmp.datum,i->datum);
                strcpy(tmp.sat,i->sat);

                i->poeni = j->poeni;
                strcpy(i->datum,j->datum);
                strcpy(i->sat,j->sat);

                j->poeni = tmp.poeni;
                strcpy(j->datum,tmp.datum);
                strcpy(j->sat,tmp.sat);
            }
        }
    }
}
//Funkcija za sortiranje liste

int readData(char *ime, int k)
{
    FILE *fpCSV;
    FILE *fp;

    char naslov[256];
    char datum[64];
    char sat[64];
    int bodovi;
    int brojac1 = 0, brojac2 = 0;
    NODE *head = NULL;

    if(k == 0) //Ako se samo prikazuju podatci
    {
            fp = fopen(ime,"r");
            if(fp == NULL)
                printf("ERROR 000: Windows error!");

            fgets(naslov,sizeof(naslov),fp);
            printf("\n%s",naslov);

            while(fscanf(fp,"%s %s %d\n",datum,sat,&bodovi) == 3 && brojac1 <10)
            {
                makeList(&head,datum,sat,bodovi);
                brojac1++;
            }

            sortList(head);
            printList(head);
            rewind(fp);
            fclose(fp);
    }else //Ako je pritisnuta opcija za upisiivanje u csv
    {

            fp = fopen(ime,"r");
            fpCSV = fopen("Statistika.csv","a");

            if(fpCSV == NULL || fp == NULL)
                printf("ERROR 000: Windows error!");

            fgets(naslov,sizeof(naslov),fp);
            fprintf(fpCSV,"%s\n",naslov);

            while(fscanf(fp,"%s %s %d\n",datum,sat,&bodovi) == 3 && brojac2<10)
            {
                makeList(&head,datum,sat,bodovi);
                brojac2++;
            }

            while(head!=NULL)
            {
                fprintf(fpCSV,"%s %s,%d\n",head->datum,head->sat,head->poeni);
                head = head->next;
            }

             rewind(fp);
             fclose(fp);
             fclose(fpCSV);

    }
    return 1;
}
//Funkcija za ocitavaje podataka iz fajlova i uspisvanje u listu te sortiranje

//Glavna funkcija za pregled statistike igranja
void pregledStatistike()
{
    system("cls");
    int opcija;
    printHeader();
    FILE *fp1, *fp2;
    int c;

    fp1 = fopen("Igra1.txt","r");
    fp2 = fopen("Igra2.txt","r");
    if(fp1 == NULL && fp2 == NULL)
    {
        printf("NEMA PODATAKA IGRANJA!");
        sleep(2);
        mainScreen();
    }

    if(fp1 !=NULL && fp2 == NULL)
    {
        readData("Igra1.txt",0);
    }
    if(fp1 ==NULL && fp2 != NULL)
    {
        readData("Igra2.txt",0);
    }

    if(fp1 !=NULL && fp2 != NULL)
    {
        readData("Igra1.txt",0);
        readData("Igra2.txt",0);
    }

    printf("\n1. NAZAD\n2. SACUVAJ U CSV\n");
        do{
            AGAIN3:
            printf("UNESITE OPCIJU:");
            fflush(stdin);
            c = scanf("%d",&opcija);
        }while(c!=1);



    if(opcija == 1)
        mainScreen();
    if(opcija == 2)
    {
        int k=0;
            if(fp1 !=NULL && fp2 == NULL)
            {
                k+=readData("Igra1.txt",1);
                k+=1;
            }

            if(fp1 ==NULL && fp2 != NULL)
            {
                k+=readData("Igra2.txt",1);
                k+=1;
            }

            if(fp1 !=NULL && fp2 != NULL)
            {
                k+=readData("Igra1.txt",1);
                k+=readData("Igra2.txt",1);
            }
        if(k == 2)
        {
            printf("USPJESNO STE SACUVALI PODATKE U CSV FORMATU!");
            sleep(2);
            mainScreen();
        }
        else
        {
            printf("ERROR 001: NEUSPJELA OPERACIJA!");
            sleep(2);
            mainScreen();
        }
    }
    goto AGAIN3;
    fclose(fp1);
    fclose(fp2);
}
