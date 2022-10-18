#include <stdio.h>
#include <stdlib.h>
#include "UF.h"

struct stUF{
    int * itens;
    int * num_objs;
    int length;
};

tUF * InitUnionFind(int size){

    tUF * new_UF = (tUF*) malloc(sizeof(tUF));
    new_UF->length = size;
    new_UF->itens = (int*) malloc(sizeof(int) * size);
    new_UF->num_objs = (int*) malloc(sizeof(int) * size);
    
    // Set value of each object in itens to it's own index
    for (int i = 0; i < size; i++){
        new_UF->itens[i] = i;
    }

    // Set value of each num_objs initially to 1
    for (int i = 0; i < size; i++){
        new_UF->num_objs[i] = 1;
    }

    return new_UF;
}

int IsConnected(tUF * u, int p, int q){
    return GetRoot(u, p) == GetRoot(u, q);
}

int isSpanning(tUF * u){
    int first_root = GetRoot(u, 0);
    for (int i = 1; i < u->length; i++){
        if (GetRoot(u, i) != first_root)
            return 0;
    }
    return 1;
}

int GetRoot(tUF * u, int i){
    while (i != u->itens[i]){
        u->itens[i] = u->itens[u->itens[i]];
        i = u->itens[i];
    }
    return i;
}

void Union(tUF * u, int p, int q){
    int i = GetRoot(u, p);
    int j = GetRoot(u, q);
    if (u->num_objs[i] < u->num_objs[j]){
        u->itens[i] = j;
        u->num_objs[j] += u->num_objs[i];
    }
    else{
        u->itens[j] = i;
        u->num_objs[i] += u->num_objs[j];
    }
}

void PrintUF(tUF * u){
    for (int i = 0; i < u->length; i++){
        printf("%d ", u->itens[i]);
    }
    printf("\n");
}