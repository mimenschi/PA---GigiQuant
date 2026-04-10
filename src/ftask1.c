#include "task1.h"

void creareLista(int n,NODE **head, FILE *input)
{
    NODE *p, *nou;
    int i;
    double val;

    p=(*head);


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

void stergereLista(NODE **head)
{
    NODE *p;

    while((*head)!=NULL)
    {
        p=(*head)->next;
        free(*head);
        *head = p;
    }
    *head=NULL;
}

double calculRand(double p1, double p2)
{
    return ( (p2-p1)/p1 )*1.0;
}

void adaugareRand(NODE *head)
{
    NODE *p;

    for(p=head; p->next != NULL; p=p->next)
    {
        (p->next)->randament=calculRand(p->valoare, (p->next)->valoare );
    }
}

double randamentMediu(int n, NODE *head)
{
        double suma=0, randMed=0;
        NODE *p;

        //Porneste de la al doilea element, deoarece primul nu are randament
        for(p=head->next; p!=NULL; p=p->next)
        {
            suma += p->randament;
        }
        
        randMed = (1.0/(n-1) )*suma;

        return randMed;
}

double calculVolatilitate(int n, double ranMed, NODE *head)
{
    double volatilitate=0, suma=0;
    NODE *p;

    //Acelasi principiuca la randament
    for(p=head->next; p!=NULL; p=p->next)
    {
        suma += pow(p->randament - ranMed, 2); 
    }

    volatilitate = sqrt( (1.0)/(n-1) * suma );
    return volatilitate;
}

double calculSharpeRaio(double randMed, double volatilitate)
{
    double sharpeR=0;
    sharpeR = (1.0)*randMed / volatilitate;
    return sharpeR;
}

double trunchiere(double val)
{
    val=((int)(val*1000))*1.0/1000;
    
    return val;
}