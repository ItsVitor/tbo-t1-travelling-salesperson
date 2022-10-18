#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"
#include "UF.h"

void readFileHeader(FILE *arq, tGrafo *grafo, char *name, int *dimension);

int main()
{
    char name[50];
    int dimension = 0;

    char path[] = "exemplos/in/simples3.tsp";

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

    initAllArestas(grafo);
    sortArestas(grafo);

    imprimeArestas(grafo);

    // ------------------------- (Execução do Algoritmo)------------------------- //

    // De acordo com o algoritmo disponível em 
    // https://en.wikipedia.org/wiki/Kruskal%27s_algorithm

    freeGrafo(grafo);

    return 0;
}