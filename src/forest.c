#include <stdlib.h>
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
    evert(nodes[i]);
    link(nodes[i], nodes[j]);
}

void deleteEdge(int i, int j) {
    // evert(i) faz com que i seja a raiz da LCT, assim, i é mais superficial do que j na LCT, portanto, se houver aresta entre i e j, j é filho de i na LCT
    evert(nodes[i]);
    cut(nodes[j]);
}

int connected(int i, int j) {
    if (findroot(nodes[i]) == findroot(nodes[j])) return 1;
    return 0;
}
