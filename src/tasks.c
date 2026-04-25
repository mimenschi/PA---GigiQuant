#include "tasks.h"

int verificareTask(char numeFile[])
{
    int i;
    int numar = 0;
    for (i = 0; i < strlen(numeFile); i++)
    {
        if (numeFile[i] >= '0' && numeFile[i] <= '9')
        {
            numar = numar * 10 + (int)numeFile[i] - 48; // -48 pentru a converti ASCII ul in cifre 0-9
        }
    }

    if(numar<=5) return 1;
    else if(numar <= 10) return 2;
    else if(numar <= 15) return 3;
    else return 4;

    return 0;
}