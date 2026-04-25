#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


struct nod{
    double pret;
    struct nod *next;
};

typedef struct nod ACTIUNE;

struct nod1{
    int zi;
    double diferenta;
    char oras[50];
    struct nod1 *next;
};

typedef struct nod1 INFOA;

struct q{
    INFOA *front;
    INFOA *rear;
};

typedef struct q Q;

//Coada
Q* createQ();
void enq(Q *q, double val, int day, const char city[]);    //vpret este valoarea pe care o are P 
void afisareArbitraj(Q *coada, FILE *output);
void deq(Q *q);

//Stack
int isEmptyS(const ACTIUNE *top);
void pushStack(ACTIUNE **top, double vpret);
double popStack(ACTIUNE **top);
void stergereStack(ACTIUNE **top);

//Task
void creareStiva(FILE *input, char oras[], ACTIUNE **topStack);
int posibilArbitraj(double p1, double p2, double p3);
void creareArbitraj(ACTIUNE *top1, ACTIUNE *top2, ACTIUNE *top3, char oras1[], char oras2[], char oras3[], Q *coada);