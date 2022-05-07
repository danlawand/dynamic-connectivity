#include "node.h"
#include <stdlib.h>

static void *mallocSafe(size_t);

Node newNode(Value val, Node left, Node right, Node parent, Node pathParent, int bit, int N) {
	Node p = mallocSafe(sizeof(*p));
	p->val = val;
	p->children[1] = right;
	p->children[0] = left;
	p->parent = parent;
	p->pathParent = pathParent;
	p->bit = bit;
	p->N = N;
	return p;
}

static void *mallocSafe(size_t nbytes) {
	void *p = malloc(nbytes);
	if (p == NULL) {
		printf("Erro: alocação de memória falhou no módulo node.\n");
		exit(0);
	}
	return p;
}
