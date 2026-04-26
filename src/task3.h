#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct nod{
    char nume[5];
    float stoc;
    int pozVect;
    struct nod *next;
};

typedef struct nod STOCK;


struct nod1{
    STOCK *head;
    struct nod1 *left;
    struct nod1 *right;
};

typedef struct nod1 FRUNZA;