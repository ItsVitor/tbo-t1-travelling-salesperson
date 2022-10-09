#ifndef GRAFO_H
#define GRAFO_H

typedef struct stGrafo tGrafo;
typedef struct stVertice tVertice;
typedef struct stAresta tAresta;

tGrafo *initGrafo();
void freeGrafo(tGrafo *grafo);

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

// Funções getters e setters (Vértice)

void setX(tVertice *vertice, int x);
void setY(tVertice *vertice, int y);
void setPai(tVertice *vertice, int pai);

int getX(tVertice *vertice);
int getY(tVertice *vertice);
int getPai(tVertice *vertice);

// Funções getters e setters (Aresta)

void setV1(tAresta *aresta, int v1);
void setV2(tAresta *aresta, int v2);
void setDist(tAresta *aresta, int dist);

int getV1(tAresta *aresta);
int getV2(tAresta *aresta);
int getDist(tAresta *aresta);

#endif