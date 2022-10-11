#ifndef GRAFO_H
#define GRAFO_H

typedef struct stGrafo tGrafo;
typedef struct stVertice tVertice;
typedef struct stAresta tAresta;

// Funções do grafo

tGrafo *initGrafo();
void freeGrafo(tGrafo *grafo);

// Funções do vértice

tVertice *initVertice();
void freeVertice(tVertice *vertice);

// Funções da aresta

tAresta *initAresta(tVertice *v1, tVertice *v2);
void freeAresta(tAresta *aresta);
void sortArestas(tGrafo *grafo);

// Funções getters e setters (Grafo)

void setName(tGrafo *grafo, char *name);
void setComment(tGrafo *grafo, char *comment);
void setType(tGrafo *grafo, char *type);
void setDim(tGrafo *grafo, int dim);
void setEdge(tGrafo *grafo, char *edge);
void setSizeVertices(tGrafo *grafo, int size);

char *getName(tGrafo *grafo);
char *getComment(tGrafo *grafo);
char *getType(tGrafo *grafo);
int getDim(tGrafo *grafo);
char *getEdge(tGrafo *grafo);
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
void setV1(tAresta *aresta, tVertice *v1);
void setV2(tAresta *aresta, tVertice *v2);
void setDist(tAresta *aresta, float dist);

tAresta *getAresta(tGrafo *grafo, int indice);
tVertice *getV1(tAresta *aresta);
tVertice *getV2(tAresta *aresta);
float getDist(tAresta *aresta);

#endif