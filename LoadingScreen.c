#include "LoadingScreen.h"
#include "GenericFunctions.h"


void printout(int x,int y)
{
  gotoXY(x,y);
  printf("Loading...\n");
  gotoXY(x-20,y+2);
  for(int i = 1; i<=30; i++)
  {
    printf("%c", 219);
    sleepCustom(100);
  }
  system("cls");
}
/*Funckija printout predstavlja komponentu funkcije loadingScreen() i
  zadužena je za isprintavanje progress bara*/

/*Funckija loadingScreen() je zaduzena za prikazivanje ekrana za ucitavanje
  nakon cega se prvobitno prikazuje opcija za unos imena a onda nakon svakog
  pogretanja korisnickovo ime*/
void loadingScreen()
{
  int x,y;
  char ime[20];
  FILE *fp;

  getScreenCoordinates(&x,&y);
  printout(x,y);
  gotoXY(x-18,y);

  fp = fopen("Ime.txt","a");
  if(fp == NULL)
    printf("ERROR 000: Windows error!");
  fseek(fp,0,SEEK_END);

  if(ftell(fp) == 0) //Ako ime nije unešeno prije pokretanja
  {
    printf("Unesite svoje ime: ");
    fflush(stdin);
    gotoXY(x+20,y);
    scanf("%s",ime);
    system("cls");
    fprintf(fp,"%s",ime);
    rewind(fp);
    fclose(fp);
  }
  else
  {
     freopen("Ime.txt","r",fp);
     fscanf(fp,"%s",ime);
     gotoXY(x,y);
     printf("Pozdrav %s",ime);
     sleep(1);
     rewind(fp);
     fclose(fp);
  }

}

