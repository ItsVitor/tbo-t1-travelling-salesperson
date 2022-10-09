#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"

// ---------------------------- Structs ---------------------------- //

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

struct stVertice
{
    int x;
    int y;
    int pai; //Índice da lista de vértices que contém o pai dele.
};

struct stAresta
{
    int v1;   //Índice da lista de vértices que contém v1
    int v2;   //Índice da lista de vértices que contém v2
    int dist; // Peso ou Distância
};

// ---------------------------- Funções ---------------------------- //

// =========== Funções do Grafo =========== //

/**
 * @brief Cria um tipo tGrafo nulo
 *
 * @return tGrafo*
 */
tGrafo *initGrafo()
{
    tGrafo *grafo = (tGrafo *)calloc(1, sizeof(tGrafo));

    setName(grafo, NULL);
    setComment(grafo, NULL);
    setType(grafo, NULL);
    setDim(grafo, 0);
    setEdge(grafo, NULL);

    // Anula tanto vetor vértice quanto vetor aresta
    setSizeVertices(grafo, 0);

    return grafo;
}

/**
 * @brief Destrói o grafo
 *
 * @param grafo Grafo a ser liberado
 */
void freeGrafo(tGrafo *grafo)
{
    free(grafo->name);
    free(grafo->comment);
    free(grafo->type);
    free(grafo->edge_weight_type);

    free(grafo->vertices);
    free(grafo->arestas);

    free(grafo);
}

// =========== Funções do Vértice =========== //

/**
 * @brief Cria um tipo tVertice zerado
 *
 * @return tVertice*
 */
tVertice *initVertice()
{
    tVertice *vertice = (tVertice *)calloc(1, sizeof(tVertice));

    return vertice;
}

/**
 * @brief Destrói o vértice
 *
 * @param vertice Vértice a ser liberado
 */
void freeVertice(tVertice *vertice)
{
    free(vertice);
}

// ----------------- Getters e Setters daqui para baixo ----------------- //

// ========= Getters e Setters do grafo ========= //

/**
 * @brief Define quantos vértices o grafo terá. (E quantas arestas)
 *
 * @param grafo Grafo a ser modificado
 * @param size Tamanho do vetor de vértices
 * @pre Grafo não é NULL, size >= 0
 * @post Tamanho de vetor de vértices e de arestas foram ajustados
 */
void setSizeVertices(tGrafo *grafo, int size)
{
    if (size < 1)
    {
        free(grafo->vertices);
        grafo->vertices = NULL;
    }

    else if (grafo->vertices)
        grafo->vertices = (tVertice *)realloc(grafo, size);

    else
        grafo->vertices = (tVertice *)calloc(size, sizeof(tVertice));

    // Quantidade de arestas == Qtd_vértices*(Qtd_vértices - 1) / 2
    size = size * (size - 1) / 2;

    if (size < 1)
    {
        free(grafo->arestas);
        grafo->arestas = NULL;
    }

    else if (grafo->arestas)
        grafo->arestas = (tAresta *)realloc(grafo, size);

    else
        grafo->arestas = (tAresta *)calloc(size, sizeof(tAresta));
}

// ============ Parte simples abaixo ============

// Já se sabe como elas são só pelo grafo.h. Não precisa ler.
// Os comentários abaixo explicam a função ao usá-la.

/**
 * @brief Muda o nome do grafo
 *
 * @param grafo Grafo a ser modificado
 * @param name Novo nome
 */
void setName(tGrafo *grafo, char *name)
{
    grafo->name = strdup(name);
}

/**
 * @brief Pega o nome do grafo
 * @details Tecnicamente uma cópia do nome
 *
 * @param grafo Grafo com o nome
 * @return char*
 */
char *getName(tGrafo *grafo)
{
    return strdup(grafo->name);
}

/**
 * @brief Muda o comentário do grafo
 *
 * @param grafo Grafo a ser modificado
 * @param comment Novo comentário
 */
void setComment(tGrafo *grafo, char *comment)
{
    grafo->comment = strdup(comment);
}

/**
 * @brief Pega o comentário do grafo
 * @details Tecnicamente uma cópia do comentário
 *
 * @param grafo Grafo com o comentário
 * @return char*
 */
char *getComment(tGrafo *grafo)
{
    return strdup(grafo->comment);
}

/**
 * @brief Muda o tipo do grafo
 *
 * @param grafo Grafo a ser modificado
 * @param type Novo tipo
 */
void setType(tGrafo *grafo, char *type)
{
    grafo->type = strdup(type);
}

/**
 * @brief Pega o tipo do grafo
 * @details Tecnicamente uma cópia do tipo
 *
 * @param grafo Grafo com o tipo
 * @return char*
 */
char *getType(tGrafo *grafo)
{
    return strdup(grafo->type);
}

/**
 * @brief Muda a dimensão do grafo
 *
 * @param grafo Grafo a ser modificado
 * @param dim Nova dimensão
 */
void setDim(tGrafo *grafo, int dim)
{
    grafo->dim = dim;
}

/**
 * @brief Pega a dimensão do grafo
 *
 * @param grafo Grafo com a dimensão
 * @return int
 */
int getDim(tGrafo *grafo)
{
    return grafo->dim;
}

/**
 * @brief Muda o parâmetro EDGE_WEIGHT_TYPE
 *
 * @param grafo Grafo a ser modificado
 * @param edge Novo EDGE_WEIGHT_TYPE
 */
void setEdge(tGrafo *grafo, char *edge)
{
    grafo->edge_weight_type = strdup(edge);
}

/**
 * @brief Pega o EDGE_WEIGHT_TYPE do grafo
 * @details Tecnicamente uma cópia do EDGE_WEIGHT_TYPE
 *
 * @param grafo Grafo com o EDGE_WEIGHT_TYPE
 * @return char*
 */
char *getEdge(tGrafo *grafo)
{
    return strdup(grafo->edge_weight_type);
}

// ========= Getters e Setters do vértice ========= //

/**
 * @brief Muda a coordenada x do vértice
 *
 * @param vertice Vértice a ser modificado
 * @param x Nova coordenada x
 */
void setX(tVertice *vertice, int x)
{
    vertice->x = x;
}

/**
 * @brief Pega a coordenada x do vértice
 *
 * @param vertice Vértice com a coordenada x
 * @return int
 */
int getX(tVertice *vertice)
{
    return vertice->x;
}

/**
 * @brief Muda a coordenada y do vértice
 *
 * @param vertice Vértice a ser modificado
 * @param y Nova coordenada y
 */
void setY(tVertice *vertice, int y)
{
    vertice->y = y;
}

/**
 * @brief Pega a coordenada y do vértice
 *
 * @param vertice Vértice com a coordenada y
 * @return int
 */
int getY(tVertice *vertice)
{
    return vertice->y;
}

/**
 * @brief Muda o pai do vértice
 *
 * @param vertice Vértice a ser modificado
 * @param pai Índice do novo pai
 */
void setPai(tVertice *vertice, int pai)
{
    vertice->pai = pai;
}

/**
 * @brief Pega o índice do pai do vértice
 *
 * @param vertice Vértice com o pai
 * @return int
 */
int getPai(tVertice *vertice)
{
    return vertice->pai;
}

// ========= Getters e Setters da aresta ========= //

/**
 * @brief Muda o vértice v1 da aresta
 *
 * @param aresta Aresta a ser modificada
 * @param v1 Índice do novo vértice v1
 */
void setV1(tAresta *aresta, int v1)
{
    aresta->v1 = v1;
}

/**
 * @brief Pega o índice do vértice v1 da aresta
 *
 * @param aresta Aresta com v1
 * @return int
 */
int getV1(tAresta *aresta)
{
    return aresta->v1;
}

/**
 * @brief Muda o vértice v2 da aresta
 *
 * @param aresta Aresta a ser modificada
 * @param v2 Índice do novo vértice v2
 */
void setV2(tAresta *aresta, int v2)
{
    aresta->v2 = v2;
}

/**
 * @brief Pega o índice do vértice v2 da aresta
 *
 * @param aresta Aresta com v2
 * @return int
 */
int getV2(tAresta *aresta)
{
    return aresta->v2;
}

/**
 * @brief Muda a distância da aresta
 *
 * @param aresta Aresta a ser modificada
 * @param dist Nova distância
 */
void setDist(tAresta *aresta, int dist)
{
    aresta->dist = dist;
}

/**
 * @brief Pega a distância da aresta
 *
 * @param aresta Aresta com a distância
 * @return int
 */
int getDist(tAresta *aresta)
{
    return aresta->dist;
}

// Comentário secreto. Parabéns por chegar aqui.