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

/*
void vectorIntervale(FILE *input, float start, float vector[], int *dimVec)
{
    int i;
    vector[(*dimVec) - 1]=start;
    float val;
    printf("zero\n");
    while (fscanf(input, "%f", &val) == 1)
    {
        printf("unu\n");
        int ok=0;   //presupunem ca valoarea nu este deja in vector
        for (i = 0; i < (*dimVec ); i++)
        {
            printf("doi\n");
            if (val == vector[i])
            {
                ok = 1; //valoarea este in vector
            }
        }
        if(ok == 0)
        {
            printf("trei\n");
            (dimVec)++;
            vector=realloc(vector, (*dimVec) * sizeof(float));
            vector[(*dimVec)-1]=val;
            printf("dimvec: %d\n",*dimVec);
        }
    }
}
*/

void vectorIntervale(FILE *input, float start, int vector[], int obs)
{
    int i;
    float val;
    vector[0]=(int)start;

    while(fscanf(input, "%f", &val) == 1)
    {
        int ok=0;
        for(i=0;i<obs;i++)
        {
            if(vector[i] == (int)val)
            {
                ok = 1;
            }
        }
        if(ok == 0)
        {
            i=0;
            while(vector[i]!=0)
            {
                i++;
            }
            vector[i]=(int)val;
        }
    }
}