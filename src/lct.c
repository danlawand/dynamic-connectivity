#include "lct.h"
#include <stdlib.h>

static void removePreferredChild(Node);
static void switchPreferredChild(Node, Node);

static void insertNonPreferredChildren(Node, Node);
static void removeNonPreferredChildren(Node);
static void exchangeNonPreferredChildren(Node, Node);

Node maketree() {
	return makeSplay();
}

// Acessa o nó v, criando o preferred path da raiz da lct até o nó v
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

// v e w estão em árvores distintas
// v is deeper than w in the represented tree.
// So min(w) of auxiliary tree is the root of the represented tree
void link(Node v, Node w) {
	access(v);
	access(w);
	join(w, v);
}

// torna v raíz da LCT
void evert(Node v) {
	access(v);
	reflectTree(v);
}

Node findroot(Node v) {
	access(v);
	Node m = minSplay(v);
	return m;
}

// retira a aresta 'v'-'v->parent'
void cut(Node v) {
	access(v);
	Node m = maxSplay(v->children[0]);
	split(m);
}

int sizeLct(Node v) {
	if (v == NULL) return 0;
	return v->size;
}

//-----------------------------------------------------
// Em algum lugar do código devemos estar considerando que a raiz da splay só pode ter bit zero, mas não está explícito.
//-----------------------------------------------------

//-----------------------------------------------------
// Temos que conferir se o pushBitUp está fazendo o papel certo.
// Pode ser que o pushBitUp esteja errado.
//-----------------------------------------------------



// remove o preferred child de v
static void removePreferredChild(Node v) {
	if (v->children[1] != NULL) {
		v->children[1]->pathParent = v;
		v->children[1]->parent = NULL;

		//insere o v->children[1] na lista do v 
		insertNonPreferredChildren(v, v->children[1]);

		v->children[1] = NULL;
	}
}



// torna v o preferred child de w. E ao antigo preferred child de w, o faz ser non-preferred-child e este tem o pathParent apontando para w.  
static void switchPreferredChild(Node w, Node v) {
	if (w->children[1] != NULL) {
		w->children[1]->pathParent = w;
		w->children[1]->parent = NULL;

		// Na lista do w, tiro o v e insiro o w->children[1]
		exchangeNonPreferredChildren(v, w->children[1]);

	} else {
		// removo o v da lista do w. 
		//Como v faz parte apenas de uma única lista, pois é filho não preferencial de apenas um pai, logo não preciso indicar sobre qual lista estou removendo. 
		removeNonPreferredChildren(v);
	}
	join(w, v);

	v->pathParent = NULL;
}

//	insere w na lista de nonPreferredChildren de v
static void insertNonPreferredChildren(Node v, Node w) {
	push_queue(v, w);
}

//	remove v da lista de nonPreferredChildren em que este pertence
static void removeNonPreferredChildren(Node v) {
	pop_queue(v);
}

// Na lista de nonPreferredChildren de w, tiro o v e insiro o u
static void exchangeNonPreferredChildren(Node v, Node u) {
	exchange_queue(v, u);
}

// Operação dumb que só mostra qual é a raiz da árvore, sem mexer nela.
Node findRootSemAccess(Node v) {
	Node m = minimumSemMudanca(v);
	return m;
}
