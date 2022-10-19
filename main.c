#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "grafo.h"
#include "UF.h"

void readFileHeader(FILE *arq, tGrafo *grafo, char *name, int *dimension);

int main()
{
    char name[50];
    int dimension = 0;

    char path[] = "exemplos/in/berlin52.tsp";

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

    // imprimeArestas(grafo);

    // ------------------------- (Execução do Algoritmo)------------------------- //

    // Calcula peso da MST do professor
    char path2[] = "exemplos/mst/berlin52.mst";
    FILE *fArqMST = fopen(path2, "r");
    float pesoProfessorMST = 0;

    fscanf(fArqMST, " %*s %s", name);
    fscanf(fArqMST, " %*[^\n]");
    fscanf(fArqMST, " %*s %d", &dimension);
    fscanf(fArqMST, " %*[^\n]");

    int v1, v2;
    while (fscanf(fArqMST, "%d %d", &v1, &v2) == 2) 
    {
        tVertice * ver1 = getVertice(grafo, v1 - 1);
        tVertice * ver2 = getVertice(grafo, v2 - 1);

        float x = getX(ver1) - getX(ver2);
        float y = getY(ver1) - getY(ver2);
        float peso = sqrt(x * x + y * y);

        pesoProfessorMST += peso;
        printf("\npesoProfessorMST: %f\n", pesoProfessorMST);
    }

    fclose(fArqMST);

    // De acordo com o algoritmo disponível em 
    // https://en.wikipedia.org/wiki/Kruskal%27s_algorithm
    tUF * MST = kruskalAlgorithm(grafo);

    freeUnionFind(MST);
    freeGrafo(grafo);

    return 0;
}