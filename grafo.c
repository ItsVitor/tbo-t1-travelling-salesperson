#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "grafo.h"
#include "UF.h"

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
    int v1;     // Índice do vértice de origem
    int v2;     // Índice do vértice de destino
    float dist; // Peso ou Distância
};

// ---------------------------- Funções ---------------------------- //

// =========== Funções estáticas =========== //

static void freeVertices(tGrafo *grafo);
static void freeArestas(tGrafo *grafo);
static int compAresta(const void *aresta_1, const void *aresta_2);

// =========== Funções do Grafo =========== //

tGrafo *initGrafo()
{
    tGrafo *grafo = (tGrafo *)calloc(1, sizeof(tGrafo));

    // Anula tanto vetor vértice quanto vetor aresta
    setSizeVertices(grafo, 0);

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
    tVertice *vertice = (tVertice *)calloc(1, sizeof(tVertice));

    setX(vertice, x);
    setY(vertice, y);

    return vertice;
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
    for (int i = 0; i < getSizeVertices(grafo); i++)
        freeVertice(getVertice(grafo, i));

    free(grafo->vertices);

    grafo->vertices = NULL;
}

int root(tGrafo *grafo, int indice)
{
    tVertice *vf = getVertice(grafo, indice);
    tVertice *vp = getVertice(grafo, getPai(vf));

    // Checa se filho != pai (vê se o endereço dos ponteiros é diferente)
    while (vf != vp)
    {
        setPai(vf, getPai(vp));

        // O pai agora é visto como o próximo filho
        vf = vp;
        vp = getVertice(grafo, getPai(vp));
    }

    // Vértice raíz tem ele mesmo como pai (getPai(vp) também funcionaria)
    return getPai(vf);
}

/**
 * @brief 
 *
 * @param grafo 
 * @pre 
 * @post 
 */
tUF * kruskalAlgorithm(tGrafo * grafo) 
{
    tUF * F = InitUnionFind(grafo->sizeVertices);
    tAresta ** S = grafo->arestas;

    FILE * fMST = fopen("./teste.txt", "w");

    int i = 0;
    float pesoTotalMST = 0;
    while(/* !isEmpty(S) */ i < getSizeArestas(grafo) && !isSpanning(F))
    {
        tAresta * menorAresta = S[i++];
        if (!IsConnected(F, menorAresta->v1, menorAresta->v2))
        {
            Union(F, menorAresta->v1, menorAresta->v2);
            fprintf(fMST, "%d %d\n", menorAresta->v1 + 1, menorAresta->v2 + 1);
            pesoTotalMST += menorAresta->dist;
        }
    }
    fprintf(fMST, "peso total MST: %f\n", pesoTotalMST);

    fclose(fMST);

    return F;
}

// =========== Funções da Aresta =========== //

tAresta *initAresta(tGrafo *grafo, int indice1, int indice2)
{
    tAresta *aresta = (tAresta *)calloc(1, sizeof(tAresta));

    aresta->v1 = indice1;
    aresta->v2 = indice2;

    tVertice *v1 = getVertice(grafo, indice1);
    tVertice *v2 = getVertice(grafo, indice2);

    // distância == sqrt( (x1 - x2)² + (y1 - y2)² )
    float x = getX(v1) - getX(v2);
    float y = getY(v1) - getY(v2);

    aresta->dist = sqrt(x * x + y * y);

    return aresta;
}

void initAllArestas(tGrafo *grafo)
{
    tAresta *aresta;
    int indice = 0;

    for (int i = 0; i < getSizeVertices(grafo); i++)
    {
        // i + 1 para não criar aresta consigo mesmo
        for (int j = i + 1; j < getSizeVertices(grafo); j++)
        {
            aresta = initAresta(grafo, i, j);

            setAresta(grafo, indice, aresta);

            // Toda vez que uma aresta é criada, o índice avança em 1
            indice++;
        }
    }
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
    for (int i = 0; i < getSizeArestas(grafo); i++)
        freeAresta(getAresta(grafo, i));

    free(grafo->arestas);

    grafo->arestas = NULL;
}

void imprimeArestas(tGrafo * grafo)
{
    for (int i = 0; i < getSizeArestas(grafo); i++){
        printf("%f ", getDist(grafo->arestas[i]));
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
    // Qsort pega o endereço dos elementos. Como os elementos são do tipo tAresta * , o endereço deles são tAresta **
    // Depois de especificar isso, pego os elementos em si usando * à esquerda desses endereços tAresta **
    tAresta *a1 = *(tAresta **)aresta_1;
    tAresta *a2 = *(tAresta **)aresta_2;

    if (getDist(a1) < getDist(a2))
        return -1;

    if (getDist(a1) > getDist(a2))
        return 1;

    return 0;
}

void sortArestas(tGrafo *grafo)
{
    qsort(grafo->arestas, getSizeArestas(grafo), sizeof(tAresta *), compAresta);
}

// ----------------- Getters e Setters daqui para baixo ----------------- //

// ========= Getters e Setters do grafo ========= //

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

int getSizeVertices(tGrafo *grafo)
{
    return grafo->sizeVertices;
}

int getSizeArestas(tGrafo *grafo)
{
    int size = getSizeVertices(grafo);

    // Quantidade de arestas == Qtd_vértices*(Qtd_vértices - 1) / 2
    size = size * (size - 1) / 2;

    return size;
}

/******************** Parte simples de Getters e Setters abaixo ********************
 * Já se sabe como elas são só pelo grafo.h. Não precisa ler.                      *
 * Os nomes abaixo explicam a função.                                              *
 ***********************************************************************************/

// ========= Getters e Setters do vértice ========= //

void setVertice(tGrafo *grafo, int indice, tVertice *vertice)
{
    setPai(vertice, indice);
    grafo->vertices[indice] = vertice;
}

tVertice *getVertice(tGrafo *grafo, int indice)
{
    if (indice >= getSizeVertices(grafo) || indice < 0)
        exit(1);

    return grafo->vertices[indice];
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

void setPai(tVertice *vertice, int pai)
{
    vertice->pai = pai;
}

int getPai(tVertice *vertice)
{
    return vertice->pai;
}

// ========= Getters e Setters da aresta ========= //

void setAresta(tGrafo *grafo, int indice, tAresta *aresta)
{
    grafo->arestas[indice] = aresta;
}

tAresta *getAresta(tGrafo *grafo, int indice)
{
    if (indice >= getSizeArestas(grafo) || indice < 0)
        exit(2);

    return grafo->arestas[indice];
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

// Comentário secreto. Parabéns por chegar aqui.
