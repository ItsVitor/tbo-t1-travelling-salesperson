#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "grafo.h"
#include "UF.h"

// ---------------------------- Structs ---------------------------- //

struct stGrafo
{
    tVertice *vertices;
    tAresta *arestas;

    int sizeVertices; // Máximo de elementos do vetor vertices
    int sizeArestas;  // Máximo de elementos do vetor arestas
};

struct stVertice
{
    float x;
    float y;
};

struct stAresta
{
    int v1;     // Índice do vértice de origem
    int v2;     // Índice do vértice de destino
    float dist; // Peso ou Distância

    int percorrida; // Marca quantas vezes a aresta foi percorrida
    // (serve para ajudar no cálculo do tour)
};

// ---------------------------- Funções ---------------------------- //

// =========== Funções estáticas =========== //

static void freeVertices(tGrafo *grafo);
static void freeArestas(tGrafo *grafo);
static int compAresta(const void *aresta_1, const void *aresta_2);

// =========== Funções do Grafo =========== //

tGrafo *initGrafo()
{
    tGrafo *grafo = (tGrafo *)malloc(sizeof(tGrafo));

    grafo->sizeVertices = 0;
    grafo->sizeArestas = 0;

    // Anula tanto vetor vértice quanto vetor aresta
    grafo->vertices = NULL;
    grafo->arestas = NULL;

    return grafo;
}

void freeGrafo(tGrafo *grafo)
{
    freeVertices(grafo);
    freeArestas(grafo);
    free(grafo);
}

// =========== Funções do Vértice =========== //

tVertice *initVertice(float x, float y)
{
    tVertice *vertice = (tVertice *)malloc(sizeof(tVertice));

    setX(vertice, x);
    setY(vertice, y);

    return vertice;
}

void reinitVertice(tVertice *vertice, float x, float y)
{
    setX(vertice, x);
    setY(vertice, y);
}

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
    free(grafo->vertices);

    grafo->vertices = NULL;
}

tGrafo *kruskalAlgorithm(tGrafo *grafo, FILE *outFileMST, FILE *outFileTour)
{
    int size = getSizeVertices(grafo);

    tUF *F = InitUnionFind(size);
    tGrafo *S = initGrafo();

    // Todo o resto é NULL, o grafo é só um vetor de arestas.
    S->arestas = grafo->arestas;
    S->sizeArestas = getSizeArestas(grafo);

    // A MST é um vetor de arestas que serão salvas durante a execução do algoritmo
    tGrafo *MST = initGrafo();
    setSizeArestas(MST, getSizeVertices(grafo) - 1);

    int i = 0, j = 0;
    float pesoTotalMST = 0;
    while (/* !isEmpty(S) */ i < getSizeArestas(grafo) && !isSpanning(F))
    {
        tAresta *menorAresta = getAresta(S, i++);
        if (!IsConnected(F, getV1(menorAresta), getV2(menorAresta)))
        {
            Union(F, getV1(menorAresta), getV2(menorAresta));
            
            MST->arestas[j++] = *menorAresta;

            fprintf(outFileMST, "%d %d\n", getV1(menorAresta) + 1, getV2(menorAresta) + 1);
            pesoTotalMST += getDist(menorAresta);
        }
    }

    freeUnionFind(F);
    free(S);

    return MST;
}

// =========== Funções da Aresta =========== //

tAresta *initAresta(tGrafo *grafo, int indice1, int indice2)
{
    tAresta *aresta = (tAresta *)calloc(1, sizeof(tAresta));

    setV1(aresta, indice1);
    setV2(aresta, indice2);

    tVertice *v1 = getVertice(grafo, indice1);
    tVertice *v2 = getVertice(grafo, indice2);

    // distância == sqrt( (x1 - x2)² + (y1 - y2)² )
    float x = getX(v1) - getX(v2);
    float y = getY(v1) - getY(v2);

    aresta->dist = sqrt(x * x + y * y);
    aresta->percorrida = 0;

    return aresta;
}

void reinitAresta(tGrafo *grafo, tAresta *aresta, int indice1, int indice2)
{
    setV1(aresta, indice1);
    setV2(aresta, indice2);

    tVertice *v1 = getVertice(grafo, indice1);
    tVertice *v2 = getVertice(grafo, indice2);

    // distância == sqrt( (x1 - x2)² + (y1 - y2)² )
    float x = getX(v1) - getX(v2);
    float y = getY(v1) - getY(v2);

    aresta->dist = sqrt(x * x + y * y);
    aresta->percorrida = 0;
}

void initAllArestas(tGrafo *grafo)
{
    // Essa aresta será o "esqueleto" para montar arestas.
    tAresta *aresta = initAresta(grafo, 0, 0);
    int indice = 0;

    for (int i = 0; i < getSizeVertices(grafo); i++)
    {
        // i + 1 para não criar aresta consigo mesmo
        for (int j = i + 1; j < getSizeVertices(grafo); j++)
        {
            // Monta a aresta que será copiada
            reinitAresta(grafo, aresta, i, j);

            setAresta(grafo, indice, aresta);

            // Toda vez que uma aresta é adicionada, o índice avança em 1
            indice++;
        }
    }

    freeAresta(aresta);
}

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
    free(grafo->arestas);

    grafo->arestas = NULL;
}

void imprimeArestas(tGrafo *grafo)
{
    for (int i = 0; i < getSizeArestas(grafo); i++)
    {
        printf("%f ", getDist(&(grafo->arestas[i])));
    }
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
    // Qsort pega o endereço dos elementos. Como os elementos são do tipo tAresta, o endereço deles são tAresta *
    // Guardo os endereços em si para poder usar as funções de arestas
    tAresta *a1 = (tAresta *)aresta_1;
    tAresta *a2 = (tAresta *)aresta_2;

    if (getDist(a1) < getDist(a2))
        return -1;

    if (getDist(a1) > getDist(a2))
        return 1;

    return 0;
}

void sortArestas(tGrafo *grafo)
{
    qsort(grafo->arestas, getSizeArestas(grafo), sizeof(tAresta), compAresta);
}

// ----------------- Getters e Setters daqui para baixo ----------------- //

// ========= Getters e Setters do grafo ========= //

void setSizeVertices(tGrafo *grafo, int size)
{
    grafo->sizeVertices = size;

    if (size < 1)
        freeVertices(grafo);

    else if (grafo->vertices)
        grafo->vertices = (tVertice *)realloc(grafo->vertices, size * sizeof(tVertice));

    else
        grafo->vertices = (tVertice *)calloc(size, sizeof(tVertice));

    // Quantidade de arestas == Qtd_vértices*(Qtd_vértices - 1) / 2
    size = size * (size - 1) / 2;

    grafo->sizeArestas = size;

    if (size < 1)
        freeArestas(grafo);

    else if (grafo->arestas)
        grafo->arestas = (tAresta *)realloc(grafo->arestas, size * sizeof(tAresta));

    else
        grafo->arestas = (tAresta *)calloc(size, sizeof(tAresta));
}

void setSizeArestas(tGrafo *grafo, int size)
{
    grafo->sizeArestas = size;

    if (size < 1)
        freeArestas(grafo);

    else if (grafo->arestas)
        grafo->arestas = (tAresta *)realloc(grafo->arestas, size * sizeof(tAresta));

    else
        grafo->arestas = (tAresta *)calloc(size, sizeof(tAresta));
}

int getSizeVertices(tGrafo *grafo)
{
    return grafo->sizeVertices;
}

int getSizeArestas(tGrafo *grafo)
{
    return grafo->sizeArestas;
}

/******************** Parte simples de Getters e Setters abaixo ********************
 * Já se sabe como elas são só pelo grafo.h. Não precisa ler.                      *
 * Os nomes abaixo explicam a função.                                              *
 ***********************************************************************************/

// ========= Getters e Setters do vértice ========= //

void setVertice(tGrafo *grafo, int indice, tVertice *vertice)
{
    tVertice *vertice_antigo = getVertice(grafo, indice);

    setX(vertice_antigo, getX(vertice));
    setY(vertice_antigo, getY(vertice));
}

tVertice *getVertice(tGrafo *grafo, int indice)
{
    if (indice >= getSizeVertices(grafo) || indice < 0)
        exit(1);

    // Retorna o endereço daquela posição do vetor
    return &(grafo->vertices[indice]);
}

void setX(tVertice *vertice, float x)
{
    vertice->x = x;
}

float getX(tVertice *vertice)
{
    return vertice->x;
}

void setY(tVertice *vertice, float y)
{
    vertice->y = y;
}

float getY(tVertice *vertice)
{
    return vertice->y;
}

// ========= Getters e Setters da aresta ========= //

void setAresta(tGrafo *grafo, int indice, tAresta *aresta)
{
    tAresta *aresta_antiga = getAresta(grafo, indice);

    setV1(aresta_antiga, getV1(aresta));
    setV2(aresta_antiga, getV2(aresta));
    setDist(aresta_antiga, getDist(aresta));
    setPercorrida(aresta_antiga, getPercorrida(aresta));
}

tAresta *getAresta(tGrafo *grafo, int indice)
{
    if (indice >= getSizeArestas(grafo) || indice < 0)
        exit(2);

    // Retorna o endereço daquela posição do vetor
    return &(grafo->arestas[indice]);
}

void setV1(tAresta *aresta, int v1)
{
    aresta->v1 = v1;
}

int getV1(tAresta *aresta)
{
    return aresta->v1;
}

void setV2(tAresta *aresta, int v2)
{
    aresta->v2 = v2;
}

int getV2(tAresta *aresta)
{
    return aresta->v2;
}

void setDist(tAresta *aresta, float dist)
{
    aresta->dist = dist;
}

float getDist(tAresta *aresta)
{
    return aresta->dist;
}

void setPercorrida(tAresta *aresta, int percorrida)
{
    aresta->percorrida = percorrida;
}

int getPercorrida(tAresta *aresta)
{
    return aresta->percorrida;
}

void incPercorrida(tAresta *aresta)
{
    aresta->percorrida++;
}

int todoPercorrido(tGrafo *arestas, int tam)
{
    int percorrida_atual;
    for (int i = 0; i < tam; i++)
    {
        percorrida_atual = getPercorrida(getAresta(arestas, i));
        if (percorrida_atual < 2)
            return 0;
        else if (percorrida_atual > 2)
        {
            printf("percorrida_atual > 2: algo de muito errado aconteceu!\n");
            exit(EXIT_FAILURE);
        }
    }
    return 1;
}

// Comentário secreto. Parabéns por chegar aqui.
