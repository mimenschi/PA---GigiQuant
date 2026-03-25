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
    NODE *p, *nod, *nou;
    int i;
    double val;
    
    nod=(NODE *)malloc(sizeof(NODE));   //Creat si umplut primul element din lista

    printf("%p\n",*head);
    //fscanf(input, "%d", &n);
    fscanf(input, "%lf", &val);
    nod->valoare=val;
    nod->next=NULL;

    p=(*head);


    for(i=2;i<=n;i++)
    {
        nou=(NODE *)malloc(sizeof(NODE));
        fscanf(input, "%lf", &val);
        nou->valoare=val;
        nou->next=NULL;
        
        printf("%d: %lf, %p\n",i, nou->valoare, nou);
        p->next=nou;
        p=nou;
    }
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
    printf("n=%d\n",n);
    fscanf(input, "%lf", &val);
    nod->valoare=val;
    nod->next=NULL;
    head=nod;

    creareLista(n, &head, input);

    NODE *p;
    p=(NODE *)malloc(sizeof(NODE));
    int i=1;

    printf("aici\n");
    printf("%p",head);
    printf("%p",head->next);


    for(p=head; p->next != NULL; p=p->next)
    {
        printf("\naici 2 %p ", p);
        printf("Valoarea nodului %d: %lf",i,p->valoare);
        i++;
    }

    return 0;
}