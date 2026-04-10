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
        return NULL;
    }
    q->front = NULL;
    q->rear = NULL;
    return q;
}

void enq(Q *q, float vpret)
{
    ACTIUNE *nou=(ACTIUNE *)malloc(sizeof(ACTIUNE));
    nou->pret = vpret;
    nou->next = NULL;
    if(q->rear == NULL)
    {
        (q->rear) = nou;
    }
    else
    {
        (q->rear)->next = nou;
        q->rear = nou;
    }
    if(q->front == NULL)
    {
        q->front = q->rear;
    }
}

float deq(Q *q)
{
    ACTIUNE *aux;
    aux=(ACTIUNE *)malloc(sizeof(ACTIUNE));
    float v;
    if(q->front == NULL)
    {
        return (-1);
    } 
    aux = q->front;
    v=aux->pret;
    q-> front =(q-> front )-> next ;
    if (q-> front == NULL )
    {
        q-> rear = NULL;
    }
    else
    {
        (q->front)->next = NULL;
    }
    free (aux);

    return v;
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