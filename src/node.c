#include "node.h"
#include <stdlib.h>
#include <stdio.h>

static void *mallocSafe(size_t);

Node newNode(Value val, Node left, Node right, Node parent, Node pathParent, int bit, int size) {
	Node p = mallocSafe(sizeof(*p));
	p->val = val;
	p->children[1] = right;
	p->children[0] = left;
	p->parent = parent;
	p->pathParent = pathParent;
	p->bit = bit;
	p->size = size;
	return p;
}

static void *mallocSafe(size_t nbytes) {
	void *p = malloc(nbytes);
	if (p == NULL) {
		perror("Erro: alocação de memória falhou no módulo node.\n");
		exit(EXIT_FAILURE);
	}
	return p;
}
