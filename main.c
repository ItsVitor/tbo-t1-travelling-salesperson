#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "grafo.h"
#include "UF.h"

void readFileHeader(FILE *arq, tGrafo *grafo, char *name, int *dimension);

static void imprimeVetor(int * vetor, int N, FILE * fOut){
    for (int i = 0; i < N; i++){
        fprintf(fOut, "%d\n", vetor[i]);
    }
}

// Insere um elemento se ele ainda não estiver no vetor
static int insereVetor(int * vetor, int N, int elem, int pos){
    for (int i = 0; i < pos; i++){
        if (vetor[i] == elem) {
            return 0;
        }
    }
    vetor[pos] = elem;
    return 1;
}

static void inverteVetor(int * vetor, int N){
    int aux;
    for (int i = 0; i < N / 2; i++){
        aux = vetor[i];
        vetor[i] = vetor[N - 1 - i];
        vetor[N - 1 - i] = aux;
    } 
}

int main()
{
    char name[50];
    int dimension = 0;
    char path[] = "exemplos/in/";
    char example_name[] = "berlin52";
    strcat(strcat(path, example_name), ".tsp");

    FILE *arq = fopen(path, "r");

    if (!arq)
        exit(3);

    // --------------------- Lê o cabeçalho do arquivo --------------------- //

    // Name
    fscanf(arq, " %*s %s", name);
    // Comment
    fscanf(arq, " %*[^\n]");
    // Type
    fscanf(arq, " %*[^\n]");
    // Dimension
    fscanf(arq, " %*s %d", &dimension);
    // Edge Weight Type
    fscanf(arq, " %*[^\n]");

    // A frase "NODE_COORD_SECTION"
    fscanf(arq, " %*[^\n]");

    // --------------------- Lê os vértices do arquivo --------------------- //

    tGrafo *grafo = initGrafo();
    float x = 0, y = 0;
    tVertice *v;

    setSizeVertices(grafo, dimension);

    for (int i = 0; i < dimension; i++)
    {
        fscanf(arq, " %*s %f %f\n", &x, &y);

        v = initVertice(x, y);

        setVertice(grafo, i, v);
    }

    fclose(arq);

    // -------------------------(Término da leitura)------------------------- //

    initAllArestas(grafo);
    sortArestas(grafo);

    // imprimeArestas(grafo);

    // ------------------------- (Execução do Algoritmo)------------------------- //

    char path_out[] = "exemplos/out/";
    strcat(strcat(path_out, name), ".mst");
    FILE * fMST = fopen(path_out, "w");
    fprintf(fMST, "NAME: %s\n", name);
    fprintf(fMST, "TYPE: MST\n");
    fprintf(fMST, "DIMENSION: %d\n", dimension);
    fprintf(fMST, "MST_SECTION\n");

    char path_out2[] = "exemplos/out/";
    strcat(strcat(path_out2, name), ".tour");
    FILE * fTour = fopen(path_out2, "w");
    fprintf(fTour, "NAME: %s\n", name);
    fprintf(fTour, "TYPE: TOUR\n");
    fprintf(fTour, "DIMENSION: %d\n", dimension);
    fprintf(fTour, "TOUR_SECTION\n");

    // De acordo com o algoritmo disponível em 
    // https://en.wikipedia.org/wiki/Kruskal%27s_algorithm
    tAresta ** MST = kruskalAlgorithm(grafo, fMST, fTour);
    
    // Verificando se a MST foi gerada direitinho: Foi!
    // for (int i = 0; i < getSizeVertices(grafo) - 1; i++) {
    //     printf("v1: %d v2: %d\n", getV1(MST[i]), getV2(MST[i]));
    // }

    // Gerando o nosso TOUR
    int tam = getSizeVertices(grafo);
    int tour[tam];
    int insert_pos = 0;

    insereVetor(tour, tam, getV1(MST[0]), insert_pos);
    insert_pos++;
    insereVetor(tour, tam, getV2(MST[0]), insert_pos);
    insert_pos++;
    incPercorrido(MST[0]);
    int vertAtual = getV2(MST[0]);
    int flag_continuar_caminhamento = 1;
    int i = 1;

    int flagWhile = 0;
    while (!todoPercorrido(MST, tam - 1) && flag_continuar_caminhamento) {

        // printf("%d\n", flagWhile++);

        for (int i = 0; i < insert_pos; i++) {
            printf("%d ", tour[i] + 1);
        }
        printf("\n");

        for (; i < tam - 1; i++) {

            // Para cada aresta
            if (getPercorrido(MST[i]) < 2){

                int v1 = getV1(MST[i]);
                int v2 = getV2(MST[i]);

                if (vertAtual == v1) {
                    if (insereVetor(tour, tam, v2, insert_pos))
                        insert_pos++;
                    if (insert_pos == tam) {
                        flag_continuar_caminhamento = 0;
                        break;
                    }
                    vertAtual = v2;
                    incPercorrido(MST[i]);
                }
                else if (vertAtual == v2) {
                    if (insereVetor(tour, tam, v1, insert_pos));
                        insert_pos++;
                    if (insert_pos == tam) {
                        flag_continuar_caminhamento = 0;
                        break;
                    }
                    vertAtual = v1;
                    incPercorrido(MST[i]);
                }
            }
        }
        i = 0;
    }

    // Imprimir nosso tour no arquivo
    for (int i = 0; i < tam; i++){
        fprintf(fTour, "%d\n", tour[i]);
    }
    
    fprintf(fMST, "EOF\n");
    fprintf(fTour, "EOF\n");

    fclose(fMST);
    fclose(fTour);
    // Liberar MST depois!
    freeGrafo(grafo);

    return 0;
}