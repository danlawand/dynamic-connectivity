#include "lct.h"
#include <stdlib.h>

static void removePreferredChild(Node);
static void switchPreferredChild(Node, Node);

Node maketree() {
	return makeSplay();
}

void access(Node v) {
	Node w;
	splay(v);
	removePreferredChild(v);

	while (v->pathParent != NULL) {
		w = v->pathParent;
		splay(w);
		switchPreferredChild(w, v);
		splay(v);
	}
}

// v is deeper than w in the represented tree.
// So min(w) of auxiliary tree is the root of the represented tree
void link(Node v, Node w) {
	access(v);
	access(w);
	join(w, v);
}

void evert(Node v) {
	access(v);
	reflectTree(v);
}

Node findroot(Node v) {
	access(v);
	Node m = minSplay(v);
	return m;
}

void cut(Node v) {
	access(v);
	Node m = maxSplay(v->children[0]);
	split(m);
}

int sizeLct(Node v) {
	if (v == NULL) return 0;
	return v->size;
}

static void removePreferredChild(Node v) {
	if (v->children[1] != NULL) {
		v->children[1]->pathParent = v;
		v->children[1]->parent = NULL;
		pushBitDown(v->children[1]); // colocamos isso mas não sabemos se é necessário.
		//Funcionou isso, mas ainda não sabemos o pq
		// Em algum lugar do código devemos estar considerando que a raiz da splay só pode ter bit zero, mas não está explícito.

		//insere o v->children[1] na lista do v 
		v->children[1] = NULL;
	}
}


// Temos que conferir se o pushBitUp está fazendo o papel certo.
// Pode ser que o pushBitUp esteja errado.

static void switchPreferredChild(Node w, Node v) {
	if (w->children[1] != NULL) {
		w->children[1]->pathParent = w;
		w->children[1]->parent = NULL;
		//insere o w->children[1] na lista de w
	}
	join(w, v);

	// v->pathParent = w->pathParent;
	// w->pathParent = NULL;
	
	v->pathParent = NULL;
	// removo o v da lista do w
}


// Operação dumb que só mostra qual é a raiz da árvore, sem mexer nela.
Node findRootSemAccess(Node v) {
	Node m = minimumSemMudanca(v);
	return m;
}
