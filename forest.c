#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "forest.h"

static Node *nodes; 

Node dynamicForest(int n) {
    nodes = mallocSafe(n * sizeof(Node));

    for (int i = 0; i < n; ++i) {
        nodes[i] = maketree();
    }
    return nodes;
}

void addEdge(int i, int j) {
    link(nodes[i], nodes[j]);
}

void deleteEdge(int i, int j) {
    cut(nodes[i]);
}

int connected(int i, int j) {
    if (findroot(nodes[i]) == findroot(nodes[j])) return 1;
    return 0;
}
