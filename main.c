#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

void readFileHeader(FILE *arq, tGrafo *grafo, char *name, int *dimension);

int main()
{
    char name[50];
    int dimension = 0;

    char path[] = "exemplos/in/a280.tsp";

    FILE *arq = fopen(path, "r");

    if (!arq)
        exit(3);

    // --------------------- Lê o cabeçalho do arquivo --------------------- //

    // Name
    fscanf(arq, " %*s %s", name);
    // Comment
    fscanf(arq, " %*[^\n]");
    // Type
    fscanf(arq, " %*[^\n]");
    // Dimension
    fscanf(arq, " %*s %d", &dimension);
    // Edge Weight Type
    fscanf(arq, " %*[^\n]");

    // A frase "NODE_COORD_SECTION"
    fscanf(arq, " %*[^\n]");

    // --------------------- Lê os vértices do arquivo --------------------- //

    tGrafo *grafo = initGrafo();
    float x = 0, y = 0;
    tVertice *v;

    setSizeVertices(grafo, dimension);

    for (int i = 0; i < dimension; i++)
    {
        fscanf(arq, " %*s %f %f\n", &x, &y);

        v = initVertice(x, y);

        setVertice(grafo, i, v);
    }

    fclose(arq);

    // -------------------------(Término da leitura)------------------------- //

    freeGrafo(grafo);

    return 0;
}