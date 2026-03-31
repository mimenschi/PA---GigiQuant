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

    //printf("n=%d\n",n); //Verificare valoare n

    fscanf(input, "%lf", &val);
    head->valoare=val;
    head->next=NULL;


    //printf("Valoarea head: %lf, %p\n",head->valoare,head->next);  //Valoare HEAD

    creareLista(n, &head, input);

    adaugareRand(head);

    /*
    NODE *p;
    p=(NODE *)malloc(sizeof(NODE));
    int i=1; //Pentru afisare

    
    printf("%p\n",head); //Verificare head
    printf("%p\n",head->next); //verificare head next
    

    //For pentru verificat lista
    
    for(p=head; p != NULL; p=p->next)
    {
        printf("Valoarea rand nodului %d: %lf si %lf\n",i,p->valoare,p->randament);
        i++;
    }
        */

    double randMed=0, volatilitate=0, sharpeR=0;
    randMed = randamentMediu(n, head);
    volatilitate = calculVolatilitate(n, randMed, head);
    sharpeR = calculSharpeRaio(randMed, volatilitate);

    //Trunchierea valorilor calculate
    randMed=((int)(randMed*1000))*1.0/1000;
    volatilitate=((int)(volatilitate*1000))*1.0/1000;
    sharpeR=((int)(sharpeR*1000))*1.0/1000;

    /*
    printf("\nRandamentul mediu este: %.3lf\n", randMed);    ///RANDAMENT MEDIU OK 
    printf("\nVolatilitatea este: %.3lf\n", volatilitate);   ///
    printf("\nShrapeR este: %.3lf\n", sharpeR);              ///
    */

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