#include "task2.h"


//Functii coada

Q* createQ()
{
    Q *q=(Q *)malloc(sizeof(Q));
    if(q == NULL)
    {
        printf("Eroare: Coada creata prost\n");
        return NULL;
    }
    q->front = NULL;
    q->rear = NULL;
    return q;
}

void enq(Q *q, double val, int day, const char city[])
{
    INFOA *nou = (INFOA *)malloc(sizeof(INFOA));
    nou->diferenta=val;
    nou->zi=day;
    strcpy(nou->oras,city);
    nou->next = NULL;

    if (q->rear == NULL)  // Coada e goala
    {
        q->front = nou;
        q->rear = nou;
    }
    else
    {
        (q->rear)->next = nou;
        q->rear = nou;
    }
}

void deq(Q *q)
{
    if (q->front == NULL)
    {
        return ;  // q e empty 
    }

    INFOA *aux = q->front;

    q->front = (q->front)->next;

    if (q->front == NULL)
    {
        q->rear = NULL;
    }

    free(aux);
}




void afisareArbitraj(Q *coada, FILE *output)
{
    while (coada->front!=NULL)
    {
        fprintf(output, "ziua %d - %.2lf - %s\n",(coada->front)->zi,(coada->front)->diferenta,(coada->front)->oras);
        deq(coada);
    }
}


//Functii stiva

int isEmptyS(const ACTIUNE *top)
{
    return top == NULL;
}


void pushStack(ACTIUNE **top, double vpret)
{
    ACTIUNE *nou = (ACTIUNE *)malloc(sizeof(ACTIUNE));

    nou->pret=vpret;
    nou->next=*top;
    *top=nou;
}

double popStack(ACTIUNE **top)
{
    if(isEmptyS(*top))
    {
        return -1.0;
    }
    ACTIUNE *aux=(*top);

    double auxval=aux->pret;
    *top=(*top)->next;

    free(aux);  //Elimina elementul

    return auxval;  //Returneaza valoarea pe care o aveam pe stiva
}

void stergereStack(ACTIUNE **top)
{
    while ( (*top) != NULL )
    {
        ACTIUNE *aux;
        aux=*top;
        *top=(*top)->next;
        free(aux);
    }
}


void creareStiva(FILE *input, char oras[], ACTIUNE **topStack)
{
    char c;
    int i=0;

    strcpy(oras, "");

    do
    {
        c = getc(input);
        if (c != '\n' && c != '\r')
        {
            oras[i++] = c;
        }
    }while(c != '\n');

    oras[i] = '\0';

    double val;
    while (fscanf(input, "%lf", &val) == 1) //Fara == 1 programul nu se opreste pentru ca la final de fisier gaseste junk care impiedica conditia de while
    {
        pushStack(topStack, val);
    }
}



//Functii task

int posibilArbitraj(double p1, double p2, double p3)
{
    if(p1 == p2 && p2 != p3)
    {
        return 3;
    }
    else if( p1 == p3 && p3 != p2 )
    {
        return 2;
    }
    else if(p2 == p3 && p3 != p1)
    {
        return 1;
    }
    else return 0;
}

void creareArbitraj(ACTIUNE *top1, ACTIUNE *top2, ACTIUNE *top3, char oras1[], char oras2[], char oras3[], Q *coada)
{
    int zi=0;
    while( !(isEmptyS(top1)) && !(isEmptyS(top2)) && !isEmptyS(top3) )
    {
        double p1, p2, p3;
        p1=popStack(&top1);
        p2=popStack(&top2);
        p3=popStack(&top3);
        zi++;

        if( posibilArbitraj(p1,p2,p3) == 1)
        {
            double dif=fabs(p1-p3);
            enq(coada, dif, zi, oras1);
        }
        if( posibilArbitraj(p1,p2,p3) == 2)
        {
            double dif=fabs(p2-p3);
            enq(coada, dif, zi, oras2);
        }
        if( posibilArbitraj(p1,p2,p3) == 3)
        {
            double dif=fabs(p3-p1);
            enq(coada, dif, zi, oras3);
        }
    }
}
