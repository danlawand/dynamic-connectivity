#include <stdlib.h>
#include <stdio.h>
#include "dynamic_forest.h"

static Node *nodes;
static void *mallocSafe(size_t);

void dynamicForest(int n) {
    nodes = mallocSafe(n * sizeof(Node));

    for (int i = 0; i < n; ++i) {
        nodes[i] = maketree();
    }
}

void addEdge(int i, int j) {
    printf("evert(%d)\n", nodes[i]->val);
    evert(nodes[i]);
    printf("link(%d, %d)\n", nodes[i]->val, nodes[j]->val);
    link(nodes[i], nodes[j]);
}

void deleteEdge(int i, int j) {
    // evert(i) faz com que i seja a raiz da LCT, assim, i é mais superficial do que j na LCT, portanto, se houver aresta entre i e j, j é filho de i na LCT
    printf("evert(%d)\n", nodes[i]->val);
    evert(nodes[i]);
    printf("cut(%d)\n", nodes[j]->val);
    cut(nodes[j]);
}

int connected(int i, int j) {
    Node u = findroot(nodes[i]);
    Node v = findroot(nodes[j]);
    printf("root of i: %d and root of j: %d\n", u->val, v->val);
    if (findroot(nodes[i]) == findroot(nodes[j])) return 1;
    return 0;
}

int sizeTree(int i) {
    return size(findroot(nodes[i]));
}

static void *mallocSafe(size_t nbytes) {
	void *p = malloc(nbytes);
	if (p == NULL) {
		perror("Erro: alocação de memória falhou no módulo node.\n");
		exit(EXIT_FAILURE);
	}
	return p;
}
