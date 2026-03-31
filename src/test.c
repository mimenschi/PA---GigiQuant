#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct node{
    double valoare;
    double randament;
    struct node *next;
};

typedef struct node NODE;

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

        //printf("s a creat nodul %d la %p se uita la %p: %lf\n",i, p, p->next, p->valoare); //Pentru test lista
    }
    //printf("Ultimul ultimul nod are adresa: %p\n", p);
    //printf("In functie: ultimul next: %p\n",p->next);
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
    //free(p);
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

int main(int argc, const char *argv[])
{
    FILE *input, *output;


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

    randMed=((int)(randMed*1000))*1.0/1000;
    volatilitate=((int)(volatilitate*1000))*1.0/1000;
    sharpeR=((int)(sharpeR*1000))*1.0/1000;

    /*
    printf("\nRandamentul mediu este: %.3lf\n", randMed);    ///RANDAMENT MEDIU OK 
    printf("\nVolatilitatea este: %.3lf\n", volatilitate);   ///
    printf("\nShrapeR este: %.3lf\n", sharpeR);              ///
    */

    fprintf(output, "%.3lf\n", randMed);
    fprintf(output, "%.3lf\n", volatilitate);
    fprintf(output, "%.3lf\n", sharpeR);

    stergereLista(&head);
    fclose(input);
    fclose(output);
    return 0;
}