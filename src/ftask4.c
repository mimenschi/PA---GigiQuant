#include "task4.h"


void citireParametrii(FILE *input, int *observatii, float *dimensiune, int *zile, float *start, float *final)
{
    fscanf(input, "%d", observatii);
    fscanf(input, "%f", dimensiune);
    fscanf(input, "%d", zile);
    fscanf(input, "%f", start);
    fscanf(input, "%f", final);
    printf(" Observatii: %d\n Dimensiune: %f\n Zile: %d\n Start: %f\n Final:%f\n",*observatii, *dimensiune, *zile, *start, *final);
}

long long cmmdc(long long a, long long b)
{
    if(a<0)
    {
        a=-a;
    }
    if(b<0)
    {
        b=-b;
    }
    long long r;
    while(b)
    {
        r=a%b;
        a=b;
        b=r;
    }
    return a;
}

void cmmdcVoid(long long *numarator, long long *numitor)
{
    long long x,y;
    x=*numarator;
    y=*numitor;
    if(x<0)
    {
        x=-x;
    }
    if(y<0)
    {
        y=-y;
    }

    while(y)
    {
        long long r = x % y;
        x = y;
        y = r;
    }
    if(x != 0)
    {
        *numarator /= x;
        *numitor /= x;
    }
}

void vectorIntervale(float valori[], int intervale[], float start, float dimensiune, int observatii, int *contInterval)
{
    int i,j;

    for(i=0; i< observatii; i++)
    {
        float capat = floor(valori[i] / dimensiune) * dimensiune;

        int ok=0; // presupunem ca capatul nu se afla deja in vector
        for(j=0; j<(*contInterval); j++)
        {
            if( fabs(intervale[j] - capat) < 0.001 )
            {
                ok=1;
            }
        }
        if(ok==0)
        {
            intervale[(*contInterval)] = capat;
            (*contInterval)++;
        }
    }

    //sortare - maybe inutila
    int aux;
    for(i=0;i<(*contInterval)-1;i++)
    {
        for(j=i+1;j<(*contInterval);j++)
        {
            if(intervale[i] > intervale[j])
            {
                aux=intervale[i];
                intervale[i]=intervale[j];
                intervale[j]=aux;
            }
        }
    }
}



void vectorValori(FILE *input, float start, float valori[], float *maxe, float *mine)
{
    int i=0;
    float val;

    while(fscanf(input, "%f", &val) == 1)
    {
        valori[i]=val;
        if(valori[i] > (*maxe))
        {
            (*maxe)=valori[i];
        }
        if(valori[i] < (*mine))
        {
            (*mine)=valori[i];
        }
        i++;
    }
}

GRAPH *createGraf(int intervale[], int size, int observatii, float valori[], float dimensiune, float start)
{
    GRAPH *g=(GRAPH *)malloc(sizeof(GRAPH));
    int i,j;

    if(g == NULL)
    {
        printf("Alocare esuata la graf in task 4.\n");
        exit(4);
    }

    g->V=size;

    g->matrice=(int **)calloc(g->V, sizeof(int *));
    if(g->matrice == NULL)
    {
        printf("Alocare esuata la matricea de adiacenta.\n");
        exit(4);
    }

    for(i=0; i < g->V; i++)
    {
        g->matrice[i] = (int *)calloc(g->V, sizeof(int));
        if(g->matrice[i] == NULL)
        {
            printf("Alocare esuata la linia matricei de diacenta.\n");
            exit(4);
        }
    }

    for (i = 0; i < observatii - 1; i++)
    {
        float capat = floor(valori[i] / dimensiune) * dimensiune;
        float capatNext = floor(valori[i + 1] / dimensiune) * dimensiune;

        int mati=-1, matj=-1;
        for(j=0;j<size;j++)
        {
            if( fabs(intervale[j] - capat) < 0.001 )  //mutumesc PCLP, daca nu faceam nu stiam ca asa se compara corect 2 float uri
            {
                mati=j;
            }
            if( fabs(intervale[j] - capatNext) < 0.001 )
            {
                matj=j;
            }
        }

        if(mati != -1 && matj != -1)
        {
            g->matrice[mati][matj]++;
        }
    }

    return g;
}



void lantMarkov(FILE *output, GRAPH *g, float preturi[], int intervale[], int size, float dimensiune, int zile, float start, float target)
{
    //IMPORTANT
    //  size este dimensiunea vectorului de intervale, adica si dimensiunea matricei de adiacenta
    //  dimensiune este dimensiunea intervalelor data in fisier


    /*------MEMORIE------*/

    //sper din suflet sa nu dau segfaul la vectorii astia pentru fractii
    long long *numarator=(long long *)calloc(g->V, sizeof(long long));
    long long *numitor=(long long *)calloc(g->V, sizeof(long long));
    long long *numarator_next=(long long *)calloc(g->V, sizeof(long long));
    long long *numitor_next=(long long *)calloc(g->V, sizeof(long long));

    int *numariesiri=(int *)calloc(g->V, sizeof(int));      //care iesiri sunt din nod


    float capat_start = floor(start / dimensiune) * dimensiune;
    float capat_target = floor(target / dimensiune) * dimensiune;
    /*fiecare secunda pe care o petrec in acest cod urasc din ce
    in ce mai mult numele pe care le-am dat variabilelor*/

    int i,j,astazi;
    int starti = -1;    
    int finali = -1;

    for(i=0;i<size;i++)
    {
        if( fabs(intervale[i] - capat_start) < 0.001 )
        {
            starti=i;
        }
        if( fabs(intervale[i] - capat_target) < 0.001 )
        {
            finali=i;
        }
    }

    //probabilitati

    for(i=0;i<g->V;i++)
    {
        numitor[i]=1;
    }
    if(starti != -1)
    {
        numarator[starti] = 1;
    }

    for(i=0; i < g->V; i++)
    {
        for(j=0;j<g->V;j++)
        {
            numariesiri[i] += g->matrice[i][j];
        }
    }

    //simulare

    //conditii pentru prima zi, ca sa afiseze corect 1 sau 0
    if (finali == -1 || numarator[finali] == 0)
    {
        fprintf(output, "0\n");
    }
    else if (numarator[finali] == numitor[finali])
    {
        fprintf(output, "1\n");
    }

    for(astazi=0; astazi<zile-1; astazi++)
    {
        for(i=0;i<g->V;i++)
        {
            numarator_next[i]=0;
            numitor_next[i]=1;
        }

        for(i=0;i<g->V;i++)
        {
            if( numarator[i] > 0 && numariesiri[i] > 0 )
            {
                for(j=0;j<g->V;j++)
                {
                    if(g->matrice[i][j]>0)
                    {
                        long long numaratorprob = numarator[i] * g->matrice[i][j];
                        long long numitorprob = numitor[i] * numariesiri[i];

                        if(numarator_next[j] == 0)  //daca fractia e goala
                        {
                            numarator_next[j] = numaratorprob;
                            numitor_next[j] = numitorprob;
                        }
                        else
                        {
                            long long numarator_comun = numarator_next[j] * numitorprob + numaratorprob * numitor_next[j];
                            long long numitor_comun = numitor_next[j] * numitorprob;
                            
                            numarator_next[j] = numarator_comun;
                            numitor_next[j] = numitor_comun;
                        }
                        cmmdcVoid(&numarator_next[j], &numitor_next[j]);
                    }
                }
            }
        }

        for(i=0; i<g->V; i++)   //ne mutam cu valorile calculate
        {
            numarator[i] = numarator_next[i];
            numitor[i] = numitor_next[i];
        }

        if (astazi == zile - 2)
        {
            if (finali == -1 || numarator[finali] == 0)
            {
                fprintf(output, "0");
            }
            else if (numarator[finali] == numitor[finali])
            {
                fprintf(output, "1");
            }
            else
            {
                fprintf(output, "%lld/%lld", numarator[finali], numitor[finali]);
            }
        }
        else
        {
            if (finali == -1 || numarator[finali] == 0)
            {
                fprintf(output, "0\n");
            }
            else if (numarator[finali] == numitor[finali])
            {
                fprintf(output, "1\n");
            }
            else
            {
                fprintf(output, "%lld/%lld\n", numarator[finali], numitor[finali]);
            }
        }
    }

    free(numarator);
    free(numitor);
    free(numarator_next);
    free(numitor_next);
    free(numariesiri);
}



void afisareGraf(GRAPH *g)
{
    int i,j;
    for(i=0; i < g->V; i++)
    {
        for(j=0; j < g->V; j++)
        {
            printf("%d ",g->matrice[i][j]);
        }
        printf("\n");
    }
}

void golireGraf(GRAPH *g)
{
    int i;
    for(i=0; i < g->V; i++)
    {
       free(g->matrice[i]);
    }
    free(g->matrice);
    free(g);
}
