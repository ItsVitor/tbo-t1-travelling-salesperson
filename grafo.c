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
    tVertice *v1;
    tVertice *v2;
    int *dist; // Peso ou Distância
};

// ---------------------------- Funções ---------------------------- //

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
    if (grafo->vertices)
        grafo->vertices = (tVertice *)realloc(grafo, size);

    else if (size < 1)
        grafo->vertices = NULL;

    else
        grafo->vertices = (tVertice *)calloc(size, sizeof(tVertice));

    // Quantidade de arestas == Qtd_vértices*(Qtd_vértices - 1) / 2
    size = size * (size - 1) / 2;

    if (grafo->arestas)
        grafo->arestas = (tAresta *)realloc(grafo, size);

    else if (size < 1)
        grafo->arestas = NULL;

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
 * @return void*
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
 * @return void*
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
 * @return void*
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
 * @return void*
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
 * @return void*
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

// Comentário secreto. Parabéns por chegar aqui.