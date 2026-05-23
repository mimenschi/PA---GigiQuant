#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct graf{
    int V;
    int E;
    float **matrice;
};

typedef struct graf GRAPH;


void citireParametrii(FILE *input, int *observatii, float *dimensiune, int *zile, float *start, float *final);
void vectorIntervale(FILE *input, float start, int vector[], int obs);
