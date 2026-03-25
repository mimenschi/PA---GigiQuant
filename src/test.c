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


    for(i=1;i<=n;i++)
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

int main(int argc, char *argv[])
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

    NODE *head, *nod;
    double val;
    int n;
    head=(NODE *)malloc(sizeof(NODE));
    nod=(NODE *)malloc(sizeof(NODE));
    fscanf(input, "%d", &n);

    printf("n=%d\n",n); //Verificare valoare n

    fscanf(input, "%lf", &val);
    nod->valoare=val;
    nod->next=NULL;
    head=nod;


    //printf("Valoarea head: %lf, %p\n",head->valoare,head->next);  //Valoare HEAD

    creareLista(n, &head, input);

    NODE *p;
    p=(NODE *)malloc(sizeof(NODE));
    int i=1; //Pentru afisare

    printf("%p\n",head); //Verificare head
    printf("%p\n",head->next); //verificare head next


    //For pentru verificat lista
    for(p=head; p->next != NULL; p=p->next)
    {
        printf("Valoarea nodului %d, %p se uita la %p: %lf\n",i,p,p->next,p->valoare);
        i++;
    }

    return 0;
}