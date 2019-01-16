#ifndef GENERICFUNCTIONS_H_INCLUDED
#define GENERICFUNCTIONS_H_INCLUDED
#include "includes.h"

void writeScore(char *,int);
void keyGen();
void gotoXY(int,int);
void getScreenCoordinates(int *, int *);
void printGameStatus(int);
void readGameStatus(int*,int*);
void writeGameStatus(int,int);
int validateKeyGen(int);
void printHeader();
void writeGameHistory(char*,char *,int);
int keyTimer();
void sleepCustom(unsigned int);
void setKeyTimeLenght();
void sealGame(int);
void clearCustom();

#endif // GENERICFUNCTIONS_H_INCLUDED
