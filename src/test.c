#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct node{
    double valoare;
    double randament;
    struct node *next;
};

typedef struct node NODE;

void creereLista(int n, NODE *head, FILE *input)
{
    NODE *p, *nod, *nou;
    int i;
    double val;

    
    fseek(input, 1L*sizeof(int), 0);    //Sarit peste prima valoare din fisier
    fseek(input, 1L*sizeof(double), 1);
    
    nod=(NODE *)malloc(sizeof(NODE));   //Creat si umplut primul element din lista

    fscanf(input, "%lf", &val);
    nod->valoare=val;
    nod->next=NULL;

    head=nod;   
    p=head;


    for(i=2;i<=n;i++)
    {
        nou=(NODE *)malloc(sizeof(NODE));
        fscanf(input, "%lf", &val);
        nou->valoare=val;
        nou->next=NULL;
        p->next=nou;
        p=nou;
    }
}

int main(int argc, char *argv[])
{
    FILE *input, *output;

    int nrObserv; //numarul de observatii (prima linie a fisierului)

    input=fopen(argv[1], "rb");
    output=fopen(argv[2],"wb");

    if(input == NULL)
    {
        printf("Eroare, fisierul de input nu a putut fi deschis.\n");
        exit(1);
    }
    if(output == NULL)
    {
        printf("Eroare, fisierul de output nu a putut fi deschis.\n");
        exit(2);
    }

    fscanf(input, "%d", &nrObserv);

    NODE *head, *nod;
    double val;
    nod=(NODE *)malloc(sizeof(NODE));
    fscanf(input, "%lf", &val);
    nod->valoare=val;
    nod->next=NULL;
    head=nod;

    creereLista(nrObserv, head, input);

    NODE *p;
    int i=1;

    for(p=head; p->next != NULL; p=p->next)
    {
        printf("Valoarea nodului %d: %lf",i,p->valoare);
        i++;
    }

    return 0;
}