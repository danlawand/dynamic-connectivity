#include "splay.h"
#include <stdlib.h>

static int valor = 0;
static Node  root;

static Node sibling(Node);

static void swapChildren(Node);

static void pushBitDown(Node);

static void  rotate(Node);

static Node maximum(Node);

static Node minimum(Node);


Node makeSplay() {
	return newNode(valor++, NULL, NULL, NULL, NULL, 0, 1);
}

void reflectTree(Node v) {
	v->bit = 1 - v->bit;
	pushBitDown(v);
}

void join(Node v, Node w) {
	v->children[1] = w;
	w->parent = v;
	v->size = v->size + w->size;
}

// Considero que o bit de X é zero
void split(Node x) {
	Node greaterThanX;
	if (x->bit==1) printf("*************** Erro no módulo Split: Bit de x era pra ser zero no Split **********************\n");
	greaterThanX = x->children[1 - x->bit];
	if (greaterThanX != NULL) {
		greaterThanX->parent = NULL;
		x->size = x->size - greaterThanX->size;
		greaterThanX->bit ^= x->bit;
	}
	x->children[1 - x->bit] = NULL;
}


void splay (Node x) {
	while (x->parent != NULL) {
		Node p = x->parent;

		if (p->parent == NULL) {
			pushBitDown(p);
			pushBitDown(x);
			rotate(x);
		} else {
			Node g = p->parent;

			// A ordem importa aqui
			pushBitDown(g);
			pushBitDown(p);
			pushBitDown(x);

			// Zig-Zig ou Zag-Zag
			if (( p == g->children[0] && x == p->children[0] ) ||
			( p == g->children[1] && x == p->children[1] )) {
				rotate(p);
				rotate(x);
			}

			// Zig-Zag ou Zag-Zig
			else {
				rotate(x);
				rotate(x);
			}
		}
	}
	// Garantir que a raiz tenha bit 0
	pushBitDown(x);
	root = x;
}

// x pode ter bit = 1
static void rotate(Node x) {
	Node p = x->parent;
	Node g = p->parent;

	int sizeChild = 0;

	x->pathParent = p->pathParent;
	p->pathParent = NULL;

	if (p->children[0] == x) {
		p->children[0] = x->children[1];
		if (x->children[1] != NULL) {
			x->children[1]->parent = p;
			sizeChild = x->children[1]->size;
		}
		x->children[1] = p;
	}

	else {
		p->children[1] = x->children[0];
		if (x->children[0] != NULL) {
			x->children[0]->parent = p;
			sizeChild = x->children[0]->size;
		}
		x->children[0] = p;
	}

	x->bit = p->bit;
	p->bit = 0;

	p->parent = x;
	x->parent = g;

	if (g != NULL) {
		if (p == g->children[0]) g->children[0] = x;
		else g->children[1] = x;
	}

	p->size = p->size - x->size + sizeChild;

	x->size = x->size - sizeChild + p->size; 
}

Node minSplay(Node x) {
	Node m = minimum(x);
	splay(m);
	return m;
}

static Node minimum(Node x) {
	// Dou pushBitDown, pois caso tenha um bit 1 nas subárvores, então, preciso passar para baixo, para saber qual caminho devo prosseguir
	pushBitDown(x);
	if (x->children[x->bit] == NULL) return x;
	return minimum(x->children[x->bit]);
}


Node maxSplay(Node x) {
	Node m = maximum(x);
	splay(m);
	return m;
}

static Node maximum(Node x) {
	// Dou pushBitDown, pois caso tenha um bit 1 nas subárvores, então, preciso passar para baixo, para saber qual caminho devo prosseguir
	pushBitDown(x);
	if (x->children[1-x->bit] == NULL) return x;
	return maximum(x->children[1-x->bit]);
}

static void pushBitDown(Node x) {
	if (x->bit == 1) {
		swapChildren(x);
		x->bit = 0;

		Node cLeft = x->children[0];
		if (cLeft != NULL) {
			cLeft->bit = 1 - cLeft->bit;
		}

		Node cRight = x->children[1];
		if (cRight != NULL) {
			cRight->bit = 1 - cRight->bit;
		}
	}
}

static Node sibling(Node x) {
	Node p = x->parent;
	if (p->children[0] == x) return p->children[1];
	else return p->children[0];
}

static void swapChildren(Node p) {
	Node aux = p->children[0];
	p->children[0] = p->children[1];
	p->children[1] = aux;
}
