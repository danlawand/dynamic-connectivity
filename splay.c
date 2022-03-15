#include "splay.h"
#include <stdlib.h>

static int valor = 0;
static Node  root;

static Node sibling(Node);

static void swapChildren(Node);

static void pushBitUp(Node);

static void pushBitDown(Node);

static void  rotate(Node);

static Node maximum(Node);

static Node minimum(Node);


Node makeSplay() {
	return newNode(valor++, NULL, NULL, NULL, NULL, 0);
}

void reflectTree(Node v) {
	v->bit = 1 - v->bit;
	pushBitDown(v);
}

void join(Node v, Node w) {
	v->children[1] = w;
	w->parent = v;
}

void split(Node x) {
	Node T;

	T = x->children[1 - x->bit];
	if (T != NULL) {
		T->parent = NULL;
		T->bit ^= x->bit;
	}
	x->children[1 - x->bit] = NULL;
}


void splay (Node x) {
	while (x->parent != NULL) {
		Node p = x->parent;

		if (p->parent == NULL) rotate(x);

		else if (( p == p->parent->children[0] && x == p->children[p->bit] ) ||
		( p == p->parent->children[1] && x == p->children[1 - p->bit] )) {
			rotate(p);
			rotate(x);
		}

		else {
			rotate(x);
			rotate(x);
		}
	}
	pushBitDown(x);
	root = x;
}


static void rotate(Node x) {
	if (x->bit == 1) pushBitUp(x);

	Node p = x->parent;
	Node g = p->parent;

	if (p->children[0] == x) {
		p->children[0] = x->children[1];
		if (x->children[1] != NULL) x->children[1]->parent = p;
		x->children[1] = p;
	}

	else {
		p->children[1] = x->children[0];
		if (x->children[0] != NULL) x->children[0]->parent = p;
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
}

Node minSplay(Node x) {
	Node m = minimum(x);
	splay(m);
	return m;
}

static Node minimum(Node x) {
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
	pushBitDown(x);
	if (x->children[1-x->bit] == NULL) return x;
	return maximum(x->children[1-x->bit]);
}


static void pushBitUp(Node x) {
	Node p = x->parent;
	p->bit = 1 - p->bit;

	Node s = sibling(x);

	if (s != NULL) s->bit = 1 - s->bit;
	swapChildren(p);
	x->bit = 0;
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
