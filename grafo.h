#ifndef GRAFO_H
#define GRAFO_H

typedef struct stGrafo tGrafo;
typedef struct stVertice tVertice;
typedef struct stAresta tAresta;

// Funções inicializadoras / liberadoras

tGrafo *initGrafo();
tVertice *initVertice();
tAresta *initAresta(tGrafo *grafo, int indice1, int indice2);

void freeGrafo(tGrafo *grafo);
void freeVertice(tVertice *vertice);
void freeAresta(tAresta *aresta);

// Funções gerais

void initAllArestas(tGrafo *grafo);
void sortArestas(tGrafo *grafo);

// Funções getters e setters (Grafo)

void setSizeVertices(tGrafo *grafo, int size);

int getSizeVertices(tGrafo *grafo);
int getSizeArestas(tGrafo *grafo);

// Funções getters e setters (Vértice)

void setVertice(tGrafo *grafo, int indice, tVertice *vertice);
void setX(tVertice *vertice, float x);
void setY(tVertice *vertice, float y);
void setPai(tVertice *vertice, int pai);

tVertice *getVertice(tGrafo *grafo, int indice);
float getX(tVertice *vertice);
float getY(tVertice *vertice);
int getPai(tVertice *vertice);

// Funções getters e setters (Aresta)

void setAresta(tGrafo *grafo, int indice, tAresta *aresta);
void setV1(tAresta *aresta, int v1);
void setV2(tAresta *aresta, int v2);
void setDist(tAresta *aresta, float dist);

tAresta *getAresta(tGrafo *grafo, int indice);
int getV1(tAresta *aresta);
int getV2(tAresta *aresta);
float getDist(tAresta *aresta);

#endif