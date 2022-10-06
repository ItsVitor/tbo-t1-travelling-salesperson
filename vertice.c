#include <stdio.h>
#include <stdlib.h>
#include "vertice.h"

struct stVertice
{
    int x;
    int y;
    int pai; //Índice da lista de vértices que contém o pai dele.
};