#include "node.h"
#include <stdlib.h>
#include <stdio.h>

static void *mallocSafe(size_t);

Node newNode(Value val, Node left, Node right, Node parent, Node pathParent ,int bit, int size, int level, int edgeId) {
	Node p = mallocSafe(sizeof(*p));
	p->val = val;
	p->children[1] = right;
	p->children[0] = left;
	p->parent = parent;
	p->pathParent = pathParent;
	p->bit = bit;
	p->size = size;
	
	//list of Non Preferred Children nodes of this node
	(p->lista).next = &p->lista;
	(p->lista).prev = &p->lista;


	// cel of this node in the list of Non Preferred Children of its own pathParent
	p->cel = NULL;

	//*** Atributos usados apenas para nós arestas
	p->edgeId = edgeId;
	p->n_levelEdges = 0;
	p->edgeLevel = level;
	p->edgeNode1 = NULL;
	p->edgeNode2 = NULL;

	return p;
}

void freeCelula(Celula c) {
	c->next = NULL;
	c->prev = NULL;
	c->no = NULL;
	free(c);
}

//	insere w na lista de nonPreferredChildren de v
void push_nonPreferredChild(Node v, Node w) {
	Celula c = mallocSafe(sizeof(*c));
    c->prev = &(v->lista);
    c->next = (v->lista).next;
	(v->lista).next->prev = c;
	(v->lista).next = c;

    c->no = w;
	w->cel = c;
}

//	remove v da lista de nonPreferredChildren em que este pertence
void pop_nonPreferredChild(Node v) {
	Celula cV = v->cel;
	cV->prev->next = cV->next;
	cV->next->prev = cV->prev;
	freeCelula(cV);
}

// Na lista do w, tiro o v e insiro o u
void exchange_nonPreferredChild(Node v, Node u) {
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
