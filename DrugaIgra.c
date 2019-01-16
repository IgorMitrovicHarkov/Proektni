#include "DrugaIgra.h"
#include "GenericFunctions.h"
#include "MainScreen.h"



int* randNR(){ //Funkcija za ispis pseudonasumicnih neponavljajucih brojeva u opsegu od 1- 15
    time_t t;
    srand((unsigned)time(&t));
    int brojevi[15];
    int static pet[5];
    int j = 0;

    for(int i = 0; i<15; i++)
    {
        brojevi[i] = i+1;
    }
    for(int i = 15; i>0; i--)
    {
        int r = rand()%i;

        if(j != 5)
            pet[j++] = brojevi[r];

        while(r<i-1)
        {
            brojevi[r] = brojevi[r+1];
            r++;
        }
    }
    return pet;
}

int checkAnswer(int tacanOdgovor) //Pomocna funkcija za validaciju odgovora
{
    int odgovor;
    int c;

    do{
        AGAIN8:
         printf("Unesite odgovor: ");
         fflush(stdin);
         c = scanf("%d",&odgovor);
    }while(c!=1);

    if(odgovor!=1 && odgovor!=2 && odgovor!=3)
    {
        goto AGAIN8;
    }
    if(odgovor==tacanOdgovor)
    {
        printf("ODGOVOR JE TACAN! DOBILI STE 20 BODOVA!");
        sleep(1);
        return 1;
    }
        printf("ODGOVOR NIJE TACAN ODUZETO VAM JE 30 BODOVA!");
        sleep(1);
        return 0;
}

void kviz() //Funkcija za pocetak igranja 2 igre
{
    if(keyTimer()==1)
    {
        system("cls");
        printHeader();
        printf("KLJUC ISTEKAO!");
        sleep(2);
        mainScreen();
    }
    clearCustom();

    int izbor;
    int brojac = 0;
    int c;

    printf("\nKVIZ\n");

    printf("\n1. POCETAK IGRE\n2. NAZAD\n3. OTKAZI\n\n");
    do{
        AGAIN5:
        printf("UNESITE OPCIJU: ");
        fflush(stdin);
        c = scanf("%d",&izbor);
    }while(c!=1);



    if(izbor == 2)
        mainScreen();

    if(izbor == 3)
    {
        sealGame(1);
        mainScreen();
    }

if(izbor == 1)
    {

    int *p = randNR();

    for(int i = 1; i<=5; i++)
    {
        clearCustom();
        printf("Pitanje %d.\n\n",i);
        int broj = *(p+(i-1));
         switch(broj)
         {
                case 1:
                    printf("Prema pravoslavnoj crkvi od koliko knjiga se sastoji biblija?\n\n");
                    printf("1. 72\n2. 66\n3. 88\n\n");
                    brojac += checkAnswer(2);
                    break;
                case 2:
                    printf("Koliko je najduze vrijeme drzanja vazduha?\n\n");
                    printf("1. 3 min\n2. 12 min 3 sek\n3. 24 min 3.45 sek\n\n");
                    brojac += checkAnswer(3);
                    break;
                case 3:
                    printf("Koliko godina je imao Isus kada je razapet?\n\n");
                    printf("1. 33\n2. 45\n3. 24\n\n");
                    brojac += checkAnswer(1);
                    break;
                case 4:
                    printf("Filozof koji je najpoznatiji po tome sto je zivio u buretu zvao se:\n\n");
                    printf("1. Diogen\n2. Platon\n3. Sofokle\n\n");
                    brojac += checkAnswer(1);
                    break;
                case 5:
                    printf("Kada je poceo Americki gradjanski rat?\n\n");
                    printf("1. 28.5.1863\n2. 12.4.1861\n3. 14.6.1869\n\n");
                    brojac += checkAnswer(2);
                    break;
                case 6:
                    printf("Kako se zove nacionalni sport Skotske?\n\n");
                    printf("1. Tenis\n2. Fudbal\n3. Golf\n\n");
                    brojac += checkAnswer(3);
                    break;
                case 7:
                    printf("Koliko je udaljen Mjesec od Zemlje?\n\n");
                    printf("1. 226,060 km\n2. 520,000 km\n3. 384,400 km\n\n");
                    brojac += checkAnswer(3);
                    break;
                case 8:
                    printf("Ko je trenutni presednik Izraela?\n\n");
                    printf("1. Benjamin Netenjahu\n2. Ruven Rivlin\n3. Chaim Weizmann\n\n");
                    brojac += checkAnswer(2);
                    break;
                case 9:
                    printf("Koji od sljedecih brojeva je palindrom?\n\n");
                    printf("1. 1234\n2. 56\n3. 1001\n\n");
                    brojac += checkAnswer(3);
                    break;
                case 10:
                    printf("Kada je zapoceta bitka na Somi?\n\n");
                    printf("1. 1.7.1916\n2. 3.7.1916\n3. 9.7.1916\n\n");
                    brojac += checkAnswer(1);
                    break;
                case 11:
                    printf("Kada je zapoceta Staljingradska bitka?\n\n");
                    printf("1. 23.8.1942\n2. 2.1.1943\n3. 9.7.1941\n\n");
                    brojac += checkAnswer(1);
                    break;
                case 12:
                    printf("Koji je glavni grad Turske?\n\n");
                    printf("1. Istanbul\n2. Ankara\n3. Jedrene\n\n");
                    brojac += checkAnswer(2);
                    break;
                case 13:
                    printf("Koja rijeka tece kroz Rim?\n\n");
                    printf("1. Arno\n2. Po\n3. Tibar\n\n");
                    brojac += checkAnswer(3);
                    break;
                case 14:
                    printf("Kako se zove prva kriptovaluta?\n\n");
                    printf("1. Bitcoin\n2. Litecoin\n3. Dogecoin\n\n");
                    brojac += checkAnswer(1);
                    break;
                case 15:
                    printf("Na kojem ostrvu se nalazi Italijanski grad Palermo?\n\n");
                    printf("1. Siciliji\n2. Korzici\n3. Sardiniji\n\n");
                    brojac += checkAnswer(1);
                    break;
            default: printf("ERROR 000: Windows error!");
         }
    }

    if(brojac == 5)
    {
        printf("\n\nIspravno ste odgovorili na sva pitanja!\n");
        printf("\n\nDobijate jos bonus 50 poena!\n\n");
        writeScore("Profil.txt",150);
        writeGameHistory("Igra2.txt","KVIZ",150);
        printf("1. NAZAD\n");
        printf("2. IGRAJ PONOVO\n");
        printf("3. OTKAZI\n");
        do{
            AGAIN6:
            printf("UNESITE OPCIJU: ");
            fflush(stdin);
            c = scanf("%d",&izbor);
        }while(c!=1);

        if(izbor == 1)
            mainScreen();
        if(izbor == 2)
        {
            kviz();
        }
        if(izbor == 3)
        {
            sealGame(1);
            mainScreen();
        }
       goto AGAIN6;
    }

    int s = 5-brojac;
    int razlika = brojac*20-s*30;
    clearCustom();
    printf("\n\nImate ukupno %d pozitivnih i %d negativnih poena!\n",brojac*20,s*30);
    writeScore("Profil.txt",razlika);
    writeGameHistory("Igra2.txt","KVIZ",razlika);
    printf("1. NAZAD\n");
    printf("2. IGRAJ PONOVO\n");
    printf("3. OTKAZI\n");
    do{
        AGAIN7:
        printf("UNESITE OPCIJU: ");
        fflush(stdin);
        c = scanf("%d",&izbor);
    }while(c!=1);

     if(izbor == 1)
            mainScreen();

    if(izbor == 3)
        {
            sealGame(1);
            mainScreen();
        }
    if(izbor == 2)
        kviz();

    goto AGAIN7;
    }
    goto AGAIN5;
}
