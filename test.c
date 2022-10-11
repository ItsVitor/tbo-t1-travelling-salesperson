#include <stdio.h>
#include "grafo.h"

int main()
{

    tGrafo *grafo = initGrafo();

    freeGrafo(grafo);

    return 0;
}