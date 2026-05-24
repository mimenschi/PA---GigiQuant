#include "task3.h"


int numarLinii(FILE *input)
{
    char c;
    int linii=0;
    while(fscanf(input, "%c", &c) == 1)
    {
        if(c=='\n')
        {
            linii++;
        }
    }

    return (linii); //vrem doar numarul de linii care au numere 
}



void citireFirme(FILE *input, STOCK *head)
{
    int poz=0, i=0;
    char c;
    STOCK *p=head;
    p->pozVect=poz;
    p->stoc=0;

    while(fscanf(input, "%c", &c)==1 && c!='\n')
    {
        if(c != ',')
        {
            p->nume[i]=c;
            i++;
        }
        if(c == ',')
        {
            p->nume[i]='\0';
            i=0;
            poz++;

            STOCK *nou=(STOCK *)malloc(sizeof(STOCK));
            nou->next=NULL;
            nou->pozVect=poz;
            nou->stoc=0;

            p->next=nou;
            p=nou;
            strcpy(p->nume,"");
        }
    }
    p->nume[i]='\0';
}

void citireValori(FILE *input, double *valori, int linii)
{
    int i,j;

    for (j = 0; j <= linii; j++)
    {
        //for ul asta este un hack incredibil de mare, de ce?
        //pentru ca initial nu parcurgea cum doream fisierul asa ca am zis ok, pun -1 la i
        //dupa, cand am afisat vectorul, mergea doar pana la 39/49 49/59 29/39 etc.
        //dupa am zis ok, hai sa dau return direct la linii in loc de linii-1 la functia de linii
        //ce vreau sa spun este ca am avut o logica minimala si desi este scris urat, isi face treaba corect
        for (i = j*10; i < (j+1)*10-1; i++) 
        {
            fscanf(input, "%lf,", &valori[i]);
        }
        fscanf(input, "%lf\n", &valori[i]);
    }
}


void insertValori(STOCK *head, const double *valori)
{
    int i;
    STOCK *p;
    for(p=head, i=0; p!=NULL; p=p->next,i++)
    {
        p->stoc=valori[i];
    }
}



void populateTree(ROOT *root, STOCK **head, double valori[], int linii, int *contor)
{

    if ((*head) == NULL)
    {
        return;
    }

    int i = 1;
    int poz = (*head)->pozVect;

    ROOT *q = root;
    STOCK *p;
    STOCK *urm = (*head)->next;
    STOCK *nou = (*head);
    nou->next = NULL;

    while (i <= linii) // folosim numarul de linii ca si contor de zile
    {
        if (i < linii)
        {
            if ((*head)->stoc < valori[*contor + poz]) // se uita in vector doar la elementele care sunt pe pozitia firmei cu pozitia i in lista
            {
                if (q->right == NULL)
                {
                    q->right = (ROOT *)malloc(sizeof(ROOT));
                    q->right->left = NULL;
                    q->right->right = NULL;
                    q->right->head = NULL;
                }
                q = q->right;
            }
            else
            {
                if (q->left == NULL)
                {
                    q->left = (ROOT *)malloc(sizeof(ROOT));
                    q->left->left = NULL;
                    q->left->right = NULL;
                    q->left->head = NULL;
                }
                q = q->left;
            }
        }
        else
        {
            // partea dreapta
            if ((*head)->stoc < valori[*contor + poz])
            {
                if (q->right == NULL)
                {
                    q->right = (ROOT *)malloc(sizeof(ROOT));
                    q->right->left = NULL;
                    q->right->right = NULL;
                    q->right->head = NULL;
                }
                if (q->right->head == NULL)
                {
                    q->right->head = nou;
                }
                else
                {
                    for (p = q->right->head; p->next != NULL; p = p->next)
                        ;
                    p->next = nou;
                }
            }

            // partea stanga
            else
            {
                if (q->left == NULL)
                {
                    q->left = (ROOT *)malloc(sizeof(ROOT));
                    q->left->left = NULL;
                    q->left->right = NULL;
                    q->left->head = NULL;
                }
                if (q->left->head == NULL)
                {
                    q->left->head = nou;
                }
                else
                {
                    for (p = q->left->head; p->next != NULL; p = p->next)
                        ;
                    p->next = nou;
                }
            }
        }
        (*head)->stoc = valori[*contor + poz]; // suprascriem valoarea din nod a numarului pentru a putea compara cu urm zi
        (*contor) += 10;                       // ne mutam pe urmatoarea zi
        i++;
    }

    (*contor) = 10; // vrem sa revenim inapoi pe pozitia 10 adica la ziua 1
    populateTree(root, &urm, valori, linii, contor);
}

void functieFrunze(ROOT *root)
{
    if (root == NULL)
        return;
    functieFrunze(root->left);

    if (root->left == NULL && root->right == NULL)
        for (STOCK *p = root->head; p != NULL; p = p->next)
            printf("%s ", p->nume);
    functieFrunze(root->right);
}

/*
void afisarePerechi(FILE *output, ROOT *stanga, ROOT *dreapta)
{
    // left face preorder
    // right face postorder

    // postordinea lui right
    if (stanga == NULL || dreapta == NULL)
    {
        return;
    }

        printf("s-d: %p\n",stanga->right);
        printf("s-s: %p\n",stanga->left);
        printf("d-d: %p\n",dreapta->right);
        printf("d-s: %p\n",dreapta->left);

    // ambele sunt frunze
    if (stanga->right == NULL && stanga->left == NULL && dreapta->right == NULL && dreapta->left == NULL)
    {
        printf("%p",stanga->right);
        printf("%p",stanga->left);
        printf("%p",dreapta->right);
        printf("%p",dreapta->left);
        STOCK *p, *q;
        for (p = stanga->head; p != NULL; p = p->next)
        {
            printf("%p",p);
            for (q = dreapta->head; q != NULL; q = q->next)
            {
                    printf("%p",q);
                
                    //printf("%s-%s\n", q->nume, p->nume);
                    fprintf(output, "%s-%s\n", dreapta->head->nume, p->nume);
                
                    fprintf(output, "%s-%s\n", stanga->head->nume, q->nume);
                    //printf("%s-%s\n", q->nume, p->nume);
                
            }
        }
        return;
    }
    // numai left este frunza
    if (stanga->head != NULL && stanga->left == NULL && stanga->right == NULL)
    {
        afisarePerechi(output, stanga, dreapta->right);
        afisarePerechi(output, stanga, dreapta->left);
    }
    // numai right este frunza
    if (dreapta->head != NULL && dreapta->left == NULL && dreapta->right == NULL)
    {
        afisarePerechi(output, stanga->left, dreapta);
        afisarePerechi(output, stanga->right, dreapta);
    }
    afisarePerechi(output, stanga->left, dreapta->right);
    afisarePerechi(output, stanga->right, dreapta->left);
    
}
*/



void vectorFrunze(ROOT *root, ROOT **frunze, int *contor)
{
    if(root == NULL)
    {
        return;
    }

    if(root->left == NULL && root->right == NULL)
    {
        if(root->head != NULL)
        {
            frunze[*contor] = root;
            (*contor)++;
        }
        return ;
    }

    vectorFrunze(root->left, frunze, contor);
    vectorFrunze(root->right, frunze, contor);
}

void afisarePerechi2(FILE *output, ROOT *root)
{
    if (root == NULL)
    {
        return;
    }

    ROOT *frunze[512];
    int nrFrunze = 0;

    vectorFrunze(root, frunze, &nrFrunze);

    int i = 0;
    int j = nrFrunze - 1;

    while (i < j)
    {
        STOCK *p, *q;
        for (p = frunze[i]->head; p != NULL; p = p->next)
        {
            for (q = frunze[j]->head; q != NULL; q = q->next)
            {
                if (p->pozVect > q->pozVect)
                {
                    fprintf(output, "%s-%s\n", q->nume, p->nume);
                }
                else
                {
                    fprintf(output, "%s-%s\n", p->nume, q->nume);
                }
            }
        }
        i++;
        j--;
    }
}