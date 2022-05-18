#include <stdlib.h>
#include "forest.h"

#include <stdio.h>
static void *mallocSafe(size_t);

static Node *nodes;

Node* dynamicForest(int n) {
    nodes = mallocSafe(n * sizeof(Node));

    for (int i = 0; i < n; ++i) {
        nodes[i] = maketree();
    }
    return nodes;
}

void addEdge(int i, int j) {
    evert(nodes[i]);
    link(nodes[i], nodes[j]);
}

void deleteEdge(int i, int j) {
    cut(nodes[i]);
}

int connected(int i, int j) {
    if (findroot(nodes[i]) == findroot(nodes[j])) return 1;
    return 0;
}

int sizeTree(int i) {
    access(nodes[i]);
    return sizeLct(nodes[i]);
}


// 
static void *mallocSafe(size_t nbytes) {
    void *p = malloc(nbytes);
    if (p == NULL) {
        printf("Erro: alocação de memória falhou no módulo forest.\n");
        exit(0);
    }
    return p;
}
