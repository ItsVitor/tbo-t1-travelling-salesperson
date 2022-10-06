#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"
#include "vertice.h"
#include "aresta.h"

struct stGrafo
{
    char *name;
    char *comment;
    char *type;
    int dim;
    char *edge_weight_type;

    // Aqui são as partes que usaremos mais
    tVertice *vertices;
    tAresta *arestas;
};

/**
 * @brief Cria um grafo com N vértices
 *
 * @param dim Quantidade de vértices do grafo
 *
 * @pre dim >= 0
 *
 * @return tGrafo*
 */
tGrafo *initGrafo(int dim)
{
}