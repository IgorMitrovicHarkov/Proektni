#ifndef GAMESTATISTICS_H_INCLUDED
#define GAMESTATISTICS_H_INCLUDED
#include "includes.h"

typedef struct node{
    struct node *next;
    int poeni;
    char datum[64];
    char sat[64];
} NODE;

void makeList(NODE **, char *,char *,int);
void printList(NODE*);
void sortList(NODE*);
void pregledStatistike();

int readData(char*,int);

#endif // GAMESTATISTICS_H_INCLUDED
