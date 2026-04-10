#include "task2.h"

//Functii coada

int isEmptyQ(Q *q)
{
    return (q->front==NULL);
}

Q* createQ()
{
    Q *q;
    q=(Q *)malloc(sizeof(Q));
    if(q == NULL)
    {
        printf("Eroare: Coada creata prost\n");
        return NULL;
    }
    q->front = NULL;
    q->rear = NULL;
    return q;
}

void enq(Q *q, float val)
{
    ACTIUNE *nou = (ACTIUNE *)malloc(sizeof(ACTIUNE));
    nou->pret = val;
    nou->next = NULL;

    if (q->rear == NULL)  // queue e empty
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

float deq(Q *q)
{
    if (q->front == NULL)
    {
        return (float)(-1);  // q e empty 
    }

    ACTIUNE *aux = q->front;
    float val = aux->pret;

    q->front = (q->front)->next;

    if (q->front == NULL)
    {
        q->rear = NULL;
    }

    free(aux);

    return val;
}


//Functii stiva

int isEmptyS(ACTIUNE *top)
{
    return top == NULL;
}


void pushStack(ACTIUNE **top, float vpret)
{
    ACTIUNE *nou = (ACTIUNE *)malloc(sizeof(ACTIUNE));

    nou->pret=vpret;
    nou->next=*top;
    *top=nou;
}

float popStack(ACTIUNE **top)
{
    if(isEmptyS(*top))
    {
        return -1.0;
    }
    ACTIUNE *aux=(*top);

    float auxval=aux->pret;
    *top=(*top)->next;

    free(aux);  //Elimina elementul

    return auxval;  //Returneaza valoarea pe care o aveam pe stiva
}

void stergereStack(ACTIUNE **top)
{
    ACTIUNE *aux;
    while ( (*top) != NULL )
    {
        aux=*top;
        *top=(*top)->next;
        free(aux);
    }
}