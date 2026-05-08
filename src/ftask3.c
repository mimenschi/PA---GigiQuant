#include "task3.h"


int numarLinii(FILE *input)
{
    char c;
    int linii=0;
    while(fscanf(input, "%c", &c) == 1)
    {
        if(c=='\n')
        {
            linii++;
        }
    }

    return (linii); //vrem doar numarul de linii care au numere 
}



void citireFirme(FILE *input, STOCK *head)
{
    int poz=0, i=0;
    char c;
    STOCK *p=head;
    p->pozVect=poz;
    p->stoc=0;

    do{
        fscanf(input, "%c", &c);
        if(c != ',')
        {
            p->nume[i]=c;
            i++;
        }
        if(c == ',')
        {
            p->nume[i]='\0';
            i=0;
            poz++;

            STOCK *nou=(STOCK *)malloc(sizeof(STOCK));
            nou->next=NULL;
            nou->pozVect=poz;
            nou->stoc=0;

            p->next=nou;
            p=nou;
            strcpy(p->nume,"");
        }
    }while(c != '\n');
}

void citireValori(FILE *input, double *valori, int linii)
{
    int i,j;

    for (j = 0; j <= linii; j++)
    {
        //for ul asta este un hack incredibil de mare, de ce?
        //pentru ca initial nu parcurgea cum doream fisierul asa ca am zis ok, pun -1 la i
        //dupa, cand am afisat vectorul, mergea doar pana la 39/49 49/59 29/39 etc.
        //dupa am zis ok, hai sa dau return direct la linii in loc de linii-1 la functia de linii
        //ce vreau sa spun este ca desi este scris urat, isi face treaba corect
        for (i = j*10; i < (j+1)*10-1; i++) 
        {
            fscanf(input, "%lf,", &valori[i]);
        }
        fscanf(input, "%lf\n", &valori[i]);
    }
}


void insertValori(STOCK *head, double *valori, int start)
{
    int i;
    STOCK *p;
    for(p=head, i=start; p!=NULL; p=p->next,i++)
    {
        p->stoc=valori[i];
    }
}
