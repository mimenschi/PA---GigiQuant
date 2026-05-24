#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


struct graf{
    int V;
    int **matrice;
};

typedef struct graf GRAPH;


void citireParametrii(FILE *input, int *observatii, float *dimensiune, int *zile, float *start, float *final);
void vectorValori(FILE *input, float start, float valori[], float *maxe, float *mine);
void vectorIntervale(float preturi[], int intervale[], float start, float dimensiune, int observatii, int *contInterval);
GRAPH *createGraf(int intervale[], int size, int observatii, float valori[], float dimensiune, float start);
long long cmmdc(long long a, long long b);
void cmmdcVoid(long long *numarator, long long *numitor);
void afisareGraf(GRAPH *g);
void golireGraf(GRAPH *g);
void lantMarkov(FILE *output, GRAPH *g, float preturi[], int intervale[], int size, float dimensiune, int zile, float start, float target);