#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "task1.h"

int main(int argc, const char *argv[])
{
    FILE *input, *output;

    input=fopen(argv[1], "rb");
    output=fopen(argv[2],"wb");

    //Verificare status fisiere
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

    //Head ul listei
    NODE *head;
    double val;
    int n;
    head=(NODE *)malloc(sizeof(NODE));
    fscanf(input, "%d", &n);

    fscanf(input, "%lf", &val);
    head->valoare=val;
    head->next=NULL;

    creareLista(n, &head, input);

    adaugareRand(head);

    double randMed=0, volatilitate=0, sharpeR=0;
    randMed = randamentMediu(n, head);
    volatilitate = calculVolatilitate(n, randMed, head);
    sharpeR = calculSharpeRaio(randMed, volatilitate);

    //Trunchierea valorilor calculate
    randMed=((int)(randMed*1000))*1.0/1000;
    volatilitate=((int)(volatilitate*1000))*1.0/1000;
    sharpeR=((int)(sharpeR*1000))*1.0/1000;

    //Printarea valorilor in fisierul de output
    fprintf(output, "%.3lf\n", randMed);
    fprintf(output, "%.3lf\n", volatilitate);
    fprintf(output, "%.3lf\n", sharpeR);

    //Golirea listei
    stergereLista(&head);

    //Inchiderea fisierleor
    fclose(input);
    fclose(output);
    return 0;
}