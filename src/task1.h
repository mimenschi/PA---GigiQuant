#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct node{
    double valoare;
    double randament;
    struct node *next;
};

typedef struct node NODE;

void creareLista(int n,NODE **head, FILE *input);
void stergereLista(NODE **head);

double calculRand(double p1, double p2);
void adaugareRand(NODE *head);
double randamentMediu(int n, NODE *head);
double calculVolatilitate(int n, double ranMed, NODE *head);
double calculSharpeRaio(double randMed, double volatilitate);
double trunchiere(double val);