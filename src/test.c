#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tasks.h"
#include "task1.h"
#include "task2.h"

int main(int argc, const char *argv[])
{
    FILE *input, *output;

    input = fopen(argv[1], "rb");
    output = fopen(argv[2], "wb");

    // Verificare status fisiere
    if (input == NULL)
    {
        printf("Eroare, fisierul de input nu a putut fi deschis.\n");
        exit(1);
    }
    if (output == NULL)
    {
        printf("Eroare, fisierul de output nu a putut fi deschis.\n");
        exit(2);
    }

    int lungime;
    lungime = strlen(argv[1]);

    //  Numele fisierului trebuie copiat intr-o noua variabila, deoarece const ne impiedica din a lucra direct cu argv[1]
    char *numeFile = (char *)malloc((lungime + 1) * sizeof(char));  //  lungime + 1 pentru a avea loc si de terminatorul de sir
    strcpy(numeFile, argv[1]);

    if (verificareTask(numeFile)==1)    // Task 1
    {
        // Head ul listei
        NODE *head;
        double val;
        int n;
        head = (NODE *)malloc(sizeof(NODE));
        fscanf(input, "%d", &n);

        fscanf(input, "%lf", &val);
        head->valoare = val;
        head->next = NULL;

        creareLista(n, &head, input);

        adaugareRand(head);

        double randMed = 0, volatilitate = 0, sharpeR = 0;
        randMed = randamentMediu(n, head);
        volatilitate = calculVolatilitate(n, randMed, head);
        sharpeR = calculSharpeRaio(randMed, volatilitate);

        // Trunchierea valorilor calculate
        randMed = trunchiere(randMed);
        volatilitate = trunchiere(volatilitate);
        sharpeR = trunchiere(sharpeR);

        // Printarea valorilor in fisierul de output
        fprintf(output, "%.3lf\n", randMed);
        fprintf(output, "%.3lf\n", volatilitate);
        fprintf(output, "%.3lf\n", sharpeR);

        // Golirea listei
        stergereLista(&head);

        // Inchiderea fisierleor
        fclose(input);
        fclose(output);

        // End Task 1
    }
    else if(verificareTask(numeFile)==2)
    {
        //Capetele stivelor pentru cele 3 orase
        ACTIUNE *stivaUnu=NULL;
        ACTIUNE *stivaDoi=NULL;
        ACTIUNE *stivaTrei=NULL;

        Q *arbitraj=createQ();

        char oras1[50];
        char oras2[50];
        char oras3[50];
       
        creareStiva(input, oras1, &stivaUnu);
        creareStiva(input, oras2, &stivaDoi);
        creareStiva(input, oras3, &stivaTrei);

        creareArbitraj(stivaUnu, stivaDoi, stivaTrei, oras1, oras2, oras3, arbitraj);
        afisareArbitraj(arbitraj,output);

        //Stivele trebuiesc sterse pentru ca ele sunt inegale
        stergereStack(&stivaUnu);
        stergereStack(&stivaDoi);
        stergereStack(&stivaTrei);

        free(arbitraj);

        fclose(input);
        fclose(output);
    }

    free(numeFile);
    
    return 0;
}