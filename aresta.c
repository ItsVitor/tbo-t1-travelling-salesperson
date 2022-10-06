#include <stdio.h>
#include <stdlib.h>
#include "vertice.h"

struct stAresta
{
    tVertice *v1;
    tVertice *v2;
    int *dist; // Peso ou Distância
};