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
void vectorIntervale(const float preturi[], int intervale[], float start, float dimensiune, int observatii, int *contInterval);
GRAPH *createGraf(const int intervale[], int size, int observatii, const float valori[], float dimensiune, float start);
void cmmdcVoid(long long *numarator, long long *numitor);
void afisareGraf(const GRAPH *g);
void golireGraf(GRAPH *g);
void lantMarkov(FILE *output, GRAPH *g, float preturi[], const int intervale[], int size, float dimensiune, int zile, float start, float target);