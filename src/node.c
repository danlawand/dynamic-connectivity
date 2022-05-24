#include "node.h"
#include <stdlib.h>
#include <stdio.h>

static void *mallocSafe(size_t);

Node newNode(Value val, Node left, Node right, Node parent, Node pathParent, int bit, int N) {
	Node p = mallocSafe(sizeof(*p));
	p->val = val;
	p->children[1] = right;
	p->children[0] = left;
	p->parent = parent;
	p->pathParent = pathParent;
	p->bit = bit;
	p->size = N;
	
	//list of Non Preferred Children nodes
	(p->lista).next = &p->lista;
	(p->lista).prev = &p->lista;

	p->cel = NULL;
	return p;
}

Celula newCelula(Celula prev, Celula next, Node v) {
    Celula c = mallocSafe(sizeof(*c));
    c->next = next;
    c->prev = prev;
    c->no = v;
	return c;
}

void freeCelula(Celula c) {
	c->next = NULL;
	c->prev = NULL;
	c->no = NULL;
	free(c);
}

//	insere w na lista de nonPreferredChildren de v
void push_queue(Node v, Node w) {
	Celula c = newCelula((v->lista).prev, (v->lista).next, w);
	c->prev->next = c;
	c->next->prev = c;
}

//	remove v da lista de nonPreferredChildren em que este pertence
void pop_queue(Node v) {
	Celula cV = v->cel;
	cV->prev->next = cV->next;
	cV->next->prev = cV->prev;
	cV->next = NULL;
	cV->prev = NULL;
}

// Na lista do w, tiro o v e insiro o u
void exchange_queue(Node v, Node u) {
	u->cel = v->cel;
	u->cel->no = u;
	v->cel = NULL;
}


static void *mallocSafe(size_t nbytes) {
	void *p = malloc(nbytes);
	if (p == NULL) {
		printf("Erro: alocação de memória falhou no módulo node.\n");
		exit(0);
	}
	return p;
}
