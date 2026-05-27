#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct nod3{
    char nume[5];
    double stoc;
    int pozVect;
    struct nod3 *next;
};

typedef struct nod3 STOCK;


struct nod4{
    STOCK *head;
    struct nod4 *left;
    struct nod4 *right;
};

typedef struct nod4 ROOT;

int numarLinii(FILE *input);
void citireFirme(FILE *input, STOCK *head);
void citireValori(FILE *input, double *valori, int linii);
void insertValori(STOCK *head, const double *valori);
void populateTree(ROOT *root, STOCK **head, double valori[], int linii, int *contor);
void functieFrunze(ROOT *root);

void vectorFrunze(ROOT *root, ROOT **frunze, int *contor);
void afisarePerechi2(FILE *output, ROOT *root);

void golireLista(STOCK *head);
void golireArbore(ROOT *root);