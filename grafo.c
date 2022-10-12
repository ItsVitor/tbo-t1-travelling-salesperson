#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "grafo.h"

// ---------------------------- Structs ---------------------------- //

struct stGrafo
{
    tVertice **vertices;
    tAresta **arestas;

    int sizeVertices; // Máximo de elementos do vetor vertices
};

struct stVertice
{
    float x;
    float y;
    int pai; //Índice da lista de vértices que contém o pai dele.
};

struct stAresta
{
    tVertice *v1; // Vértice de origem
    tVertice *v2; // Vértice de destino
    float dist;   // Peso ou Distância
};

// ---------------------------- Funções ---------------------------- //

// =========== Funções estáticas =========== //

static void freeVertices(tGrafo *grafo);
static void freeArestas(tGrafo *grafo);
static int compAresta(const void *aresta_1, const void *aresta_2);

// =========== Funções do Grafo =========== //

/**
 * @brief Cria um tipo tGrafo nulo
 *
 * @return tGrafo*
 */
tGrafo *initGrafo()
{
    tGrafo *grafo = (tGrafo *)calloc(1, sizeof(tGrafo));

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
    freeVertices(grafo);
    freeArestas(grafo);

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

/**
 * @brief Destrói todos os vértices do vetor de vértices, e o anula
 *
 * @param grafo Grafo com o vetor de vértices
 * @pre Vetor de vértice não é um ponteiro para lixo
 * @post Campo do vetor de vértices aponta para NULL
 */
static void freeVertices(tGrafo *grafo)
{
    for (int i = 0; i < getSizeVertices(grafo); i++)
        freeVertice(getVertice(grafo, i));

    free(grafo->vertices);

    grafo->vertices = NULL;
}

// =========== Funções da Aresta =========== //

/**
 * @brief Cria um tipo tAresta conectando dois vértices
 * @details Sendo um grafo não-direcionado, ser destino ou origem não importa.
 *
 * @param v1 Vértice origem da aresta
 * @param v2 Vértice destino da aresta
 * @return tAresta*
 */
tAresta *initAresta(tVertice *v1, tVertice *v2)
{
    tAresta *aresta = (tAresta *)calloc(1, sizeof(tAresta));

    aresta->v1 = v1;
    aresta->v2 = v2;

    // distância == sqrt( (x1 - x2)² + (y1 - y2)² )
    float x = getX(v1) - getX(v2);
    float y = getY(v1) - getY(v2);

    aresta->dist = sqrt(x * x + y * y);

    return aresta;
}

/**
 * @brief Cria todas as arestas possíveis do grafo
 *
 * @param grafo Grafo com os vértices
 * @pre Vetor de vértices completamente preenchido
 * @post Vetor de arestas completamente preenchido
 */
void initAllArestas(tGrafo *grafo)
{
    tVertice *v1, *v2;
    tAresta *aresta;
    int indice = 0;

    for (int i = 0; i < getSizeVertices(grafo); i++)
    {
        v1 = getVertice(grafo, i);

        // i + 1 para não criar aresta consigo mesmo
        for (int j = i + 1; j < getSizeVertices(grafo); j++)
        {
            v2 = getVertice(grafo, j);
            aresta = initAresta(v1, v2);

            setAresta(grafo, indice, aresta);

            // Toda vez que uma aresta é criada, o índice avança em 1
            indice++;
        }
    }
}

/**
 * @brief Destrói a aresta
 *
 * @param aresta Aresta a ser liberada
 */
void freeAresta(tAresta *aresta)
{
    free(aresta);
}

/**
 * @brief Destrói todas as arestas do vetor de arestas, e o anula
 *
 * @param grafo Grafo com o vetor de arestas
 * @post campo do vetor de arestas aponta para NULL
 */
static void freeArestas(tGrafo *grafo)
{
    for (int i = 0; i < getSizeArestas(grafo); i++)
        freeAresta(getAresta(grafo, i));

    free(grafo->arestas);

    grafo->arestas = NULL;
}

/**
 * @brief Checa se aresta_1 < aresta_2
 * @details Criada apenas para ser usada na função qsort.
 *
 * @param aresta_1 Primeira aresta
 * @param aresta_2 Segunda aresta
 * @return int
 */
static int compAresta(const void *aresta_1, const void *aresta_2)
{
    // Qsort pega o endereço dos elementos. Como os elementos são do tipo tAresta * , o endereço deles são tAresta **
    // Depois de indicar isso, pego os elementos em si fazendo *() nesses endereços tAresta **
    tAresta *a1 = *(tAresta **)aresta_1;
    tAresta *a2 = *(tAresta **)aresta_2;

    if (getDist(a1) < getDist(a2))
        return -1;

    if (getDist(a1) > getDist(a2))
        return 1;

    return 0;
}

/**
 * @brief Organiza as arestas em ordem crescente
 *
 * @param grafo Grafo com as arestas
 */
void sortArestas(tGrafo *grafo)
{
    qsort(grafo->arestas, getSizeArestas(grafo), sizeof(tAresta *), compAresta);
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
    grafo->sizeVertices = size;

    if (size < 1)
        freeVertices(grafo);

    else if (grafo->vertices)
        grafo->vertices = (tVertice **)realloc(grafo->vertices, size);

    else
        grafo->vertices = (tVertice **)calloc(size, sizeof(tVertice *));

    // Quantidade de arestas == Qtd_vértices*(Qtd_vértices - 1) / 2
    size = size * (size - 1) / 2;

    if (size < 1)
        freeArestas(grafo);

    else if (grafo->arestas)
        grafo->arestas = (tAresta **)realloc(grafo->arestas, size);

    else
        grafo->arestas = (tAresta **)calloc(size, sizeof(tAresta *));
}

/**
 * @brief Pega a quantidade (máxima) de vértices do grafo
 * @details Quantos elementos cabem no vetor de vértices.
 *
 * @param grafo Grafo com o vetor de vértices
 * @return int
 */
int getSizeVertices(tGrafo *grafo)
{
    return grafo->sizeVertices;
}

/**
 * @brief Pega a quantidade (máxima) de arestas do grafo
 * @details Quantos elementos cabem no vetor de arestas.
 *
 * @param grafo Grafo com o vetor de arestas
 * @return int
 */
int getSizeArestas(tGrafo *grafo)
{
    int size = getSizeVertices(grafo);

    // Quantidade de arestas == Qtd_vértices*(Qtd_vértices - 1) / 2
    size = size * (size - 1) / 2;

    return size;
}

/******************** Parte simples de Getters e Setters abaixo ********************
 * Já se sabe como elas são só pelo grafo.h. Não precisa ler.                      *
 * Os comentários abaixo explicam a função ao usá-la.                              *
 ***********************************************************************************/

// ========= Getters e Setters do vértice ========= //

/**
 * @brief Muda o vértice na posição do vetor indicada
 * @details Coloca o próprio índice como pai
 *
 * @param grafo Grafo com o vetor de vértices
 * @param indice Posição a ser modificada
 * @param vertice Novo vértice
 */
void setVertice(tGrafo *grafo, int indice, tVertice *vertice)
{
    setPai(vertice, indice);
    grafo->vertices[indice] = vertice;
}

/**
 * @brief Pega o vértice na posição do vetor indicada
 *
 * @param grafo Grafo com o vetor de vértices
 * @param indice Posição do vértice
 * @return tVertice*
 */
tVertice *getVertice(tGrafo *grafo, int indice)
{
    if (indice >= getSizeVertices(grafo) || indice < 0)
        exit(1);

    return grafo->vertices[indice];
}

/**
 * @brief Muda a coordenada x do vértice
 *
 * @param vertice Vértice a ser modificado
 * @param x Nova coordenada x
 */
void setX(tVertice *vertice, float x)
{
    vertice->x = x;
}

/**
 * @brief Pega a coordenada x do vértice
 *
 * @param vertice Vértice com a coordenada x
 * @return float
 */
float getX(tVertice *vertice)
{
    return vertice->x;
}

/**
 * @brief Muda a coordenada y do vértice
 *
 * @param vertice Vértice a ser modificado
 * @param y Nova coordenada y
 */
void setY(tVertice *vertice, float y)
{
    vertice->y = y;
}

/**
 * @brief Pega a coordenada y do vértice
 *
 * @param vertice Vértice com a coordenada y
 * @return float
 */
float getY(tVertice *vertice)
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
 * @brief Muda a aresta na posição do vetor indicada
 *
 * @param grafo Grafo com o vetor de arestas
 * @param indice Posição a ser modificada
 * @param aresta Nova aresta
 */
void setAresta(tGrafo *grafo, int indice, tAresta *aresta)
{
    grafo->arestas[indice] = aresta;
}

/**
 * @brief Pega a aresta na posição do vetor indicada
 *
 * @param grafo Grafo com o vetor de arestas
 * @param indice Posição do aresta
 * @return tAresta*
 */
tAresta *getAresta(tGrafo *grafo, int indice)
{
    if (indice >= getSizeArestas(grafo) || indice < 0)
        exit(2);

    return grafo->arestas[indice];
}

/**
 * @brief Muda o vértice v1 da aresta
 *
 * @param aresta Aresta a ser modificada
 * @param v1 Novo vértice v1
 */
void setV1(tAresta *aresta, tVertice *v1)
{
    aresta->v1 = v1;
}

/**
 * @brief Pega o vértice v1 da aresta
 *
 * @param aresta Aresta com v1
 * @return tVertice*
 */
tVertice *getV1(tAresta *aresta)
{
    return aresta->v1;
}

/**
 * @brief Muda o vértice v2 da aresta
 *
 * @param aresta Aresta a ser modificada
 * @param v2 Novo vértice v2
 */
void setV2(tAresta *aresta, tVertice *v2)
{
    aresta->v2 = v2;
}

/**
 * @brief Pega o vértice v2 da aresta
 *
 * @param aresta Aresta com v2
 * @return tVertice*
 */
tVertice *getV2(tAresta *aresta)
{
    return aresta->v2;
}

/**
 * @brief Muda a distância da aresta
 *
 * @param aresta Aresta a ser modificada
 * @param dist Nova distância
 */
void setDist(tAresta *aresta, float dist)
{
    aresta->dist = dist;
}

/**
 * @brief Pega a distância da aresta
 *
 * @param aresta Aresta com a distância
 * @return float
 */
float getDist(tAresta *aresta)
{
    return aresta->dist;
}

// Comentário secreto. Parabéns por chegar aqui.