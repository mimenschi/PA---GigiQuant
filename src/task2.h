#include <stdio.h>
#include <stdlib.h>

struct nod{
    char oras[30];
    float pret;
    int zi;
    struct nod *next;
};

typedef struct nod ACTIUNE;

struct q{
    ACTIUNE *front;
    ACTIUNE *rear;
};

typedef struct q Q;

//Coada
int isEmptyQ(Q *q);
Q* createQ();
void enq(Q *q, float vpret);    //vpret este valoarea pe care o are P 
float deq(Q *q);

//Stack
int isEmptyS(ACTIUNE *top);
void pushStack(ACTIUNE **top, float vpret);
float popStack(ACTIUNE **top);
void stergereStack(ACTIUNE **top);