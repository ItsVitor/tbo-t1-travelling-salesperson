#ifndef GRAFO_H
#define GRAFO_H

typedef struct stGrafo tGrafo;
typedef struct stVertice tVertice;
typedef struct stAresta tAresta;

// Funções inicializadoras

/**
 * @brief Cria um tipo tGrafo nulo
 *
 * @return tGrafo*
 */
tGrafo *initGrafo();

/**
 * @brief Cria um tipo tVertice
 *
 * @param x Coordenada x do vértice
 * @param y Coordenada y do vértice
 * @return tVertice*
 */
tVertice *initVertice(float x, float y);

/**
 * @brief Cria um tipo tAresta conectando dois vértices
 * @details Sendo um grafo não-direcionado, ser destino ou origem não importa.
 *
 * @param grafo Grafo com o vetor de vértices
 * @param indice1 Índice do vértice origem
 * @param indice2 Índice do vértice destino
 * @return tAresta*
 */
tAresta *initAresta(tGrafo *grafo, int indice1, int indice2);

// Funções liberadoras

/**
 * @brief Destrói o grafo e seus elementos
 *
 * @param grafo Grafo a ser liberado
 */
void freeGrafo(tGrafo *grafo);

/**
 * @brief Destrói o vértice
 *
 * @param vertice Vértice a ser liberado
 */
void freeVertice(tVertice *vertice);

/**
 * @brief Destrói a aresta
 *
 * @param aresta Aresta a ser liberada
 */
void freeAresta(tAresta *aresta);

// Funções gerais

/**
 * @brief Pega o índice do vértice raíz
 * @details Usa o método Quick-Union na procura. O "weighted" é trabalho da função que une.
 *
 * @param grafo Grafo com o vetor de vértices
 * @param indice Índice do vértice filho
 * @return int
 */
int root(tGrafo *grafo, int indice);

/**
 * @brief Cria todas as arestas possíveis do grafo
 *
 * @param grafo Grafo com os vértices
 * @pre Vetor de vértices completamente preenchido
 * @post Vetor de arestas completamente preenchido
 */
void initAllArestas(tGrafo *grafo);

/**
 * @brief Organiza as arestas em ordem crescente
 *
 * @param grafo Grafo com as arestas
 */
void sortArestas(tGrafo *grafo);

// Funções getters e setters (Grafo)

/**
 * @brief Define quantos vértices o grafo terá. (E quantas arestas)
 *
 * @param grafo Grafo a ser modificado
 * @param size Tamanho do vetor de vértices
 * @pre Grafo não é NULL, size >= 0
 * @post Tamanho de vetor de vértices e de arestas foram ajustados
 */
void setSizeVertices(tGrafo *grafo, int size);

/**
 * @brief Pega a quantidade (máxima) de vértices do grafo
 * @details Quantos elementos cabem no vetor de vértices.
 *
 * @param grafo Grafo com o vetor de vértices
 * @return int
 */
int getSizeVertices(tGrafo *grafo);

/**
 * @brief Pega a quantidade (máxima) de arestas do grafo
 * @details Quantos elementos cabem no vetor de arestas.
 *
 * @param grafo Grafo com o vetor de arestas
 * @return int
 */
int getSizeArestas(tGrafo *grafo);

// Funções getters e setters (Vértice)

/**
 * @brief Muda o vértice na posição do vetor indicada
 * @details Coloca o próprio índice como pai
 *
 * @param grafo Grafo com o vetor de vértices
 * @param indice Posição a ser modificada
 * @param vertice Novo vértice
 */
void setVertice(tGrafo *grafo, int indice, tVertice *vertice);

/**
 * @brief Muda a coordenada x do vértice
 *
 * @param vertice Vértice a ser modificado
 * @param x Nova coordenada x
 */
void setX(tVertice *vertice, float x);

/**
 * @brief Muda a coordenada y do vértice
 *
 * @param vertice Vértice a ser modificado
 * @param y Nova coordenada y
 */
void setY(tVertice *vertice, float y);

/**
 * @brief Muda o pai do vértice
 *
 * @param vertice Vértice a ser modificado
 * @param pai Índice do novo pai
 */
void setPai(tVertice *vertice, int pai);

/**
 * @brief Pega o vértice na posição do vetor indicada
 *
 * @param grafo Grafo com o vetor de vértices
 * @param indice Posição do vértice
 * @return tVertice*
 */
tVertice *getVertice(tGrafo *grafo, int indice);

/**
 * @brief Pega a coordenada x do vértice
 *
 * @param vertice Vértice com a coordenada x
 * @return float
 */
float getX(tVertice *vertice);

/**
 * @brief Pega a coordenada y do vértice
 *
 * @param vertice Vértice com a coordenada y
 * @return float
 */
float getY(tVertice *vertice);

/**
 * @brief Pega o índice do pai do vértice
 *
 * @param vertice Vértice com o pai
 * @return int
 */
int getPai(tVertice *vertice);

// Funções getters e setters (Aresta)

/**
 * @brief Muda a aresta na posição do vetor indicada
 *
 * @param grafo Grafo com o vetor de arestas
 * @param indice Posição a ser modificada
 * @param aresta Nova aresta
 */
void setAresta(tGrafo *grafo, int indice, tAresta *aresta);

/**
 * @brief Muda o vértice v1 da aresta
 *
 * @param aresta Aresta a ser modificada
 * @param v1 Índice do novo vértice v1
 */
void setV1(tAresta *aresta, int v1);

/**
 * @brief Muda o vértice v2 da aresta
 *
 * @param aresta Aresta a ser modificada
 * @param v2 Índice do novo vértice v2
 */
void setV2(tAresta *aresta, int v2);

/**
 * @brief Muda a distância da aresta
 *
 * @param aresta Aresta a ser modificada
 * @param dist Nova distância
 */
void setDist(tAresta *aresta, float dist);

/**
 * @brief Pega a aresta na posição do vetor indicada
 *
 * @param grafo Grafo com o vetor de arestas
 * @param indice Posição do aresta
 * @return tAresta*
 */
tAresta *getAresta(tGrafo *grafo, int indice);

/**
 * @brief Pega o índice do vértice v1 da aresta
 *
 * @param aresta Aresta com v1
 * @return int
 */
int getV1(tAresta *aresta);

/**
 * @brief Pega o índice do vértice v2 da aresta
 *
 * @param aresta Aresta com v2
 * @return int
 */
int getV2(tAresta *aresta);

/**
 * @brief Pega a distância da aresta
 *
 * @param aresta Aresta com a distância
 * @return float
 */
float getDist(tAresta *aresta);

#endif