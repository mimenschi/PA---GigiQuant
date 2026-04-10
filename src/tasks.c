#include "tasks.h"

int verificareTask(char numeFile[])
{
    int i;
    int numar = 0;
    for (i = 0; i < strlen(numeFile); i++)
    {
        if (numeFile[i] >= '0' && numeFile[i] <= '9')
        {
            numar = numar * 10 + (int)numeFile[i] - 48;
        }
    }

    if(numar<=5) return 1;
    else if(numar >= 6 && numar <= 10) return 2;
    else if(numar >= 11 && numar <= 15) return 3;
    else return 4;

    return 0;
}