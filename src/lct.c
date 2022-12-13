#include "lct.h"
#include <stdlib.h>

static void removePreferredChild(Node);
static void switchPreferredChild(Node, Node);

Node maketree() {
	return makeSplay();
}

// Acessa o nó v, criando o preferred path da raiz da lct até o nó v
// Ao final do access V é raiz de sua splay tree, em outras palavras, V não tem filho direito, pois V é o nó de chave maior na splay, portanto é o nó de maior profundidade na LCT
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
// W se torna a raiz da lct e o caminho preferencial vai até V
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

// retira a aresta 'v'-ij-'v->parent'
void cut(Node v) {
	access(v);
	Node m = maxSplay(v->children[0]);
	split(m);
}

int size(Node v) {
	if (v == NULL) return 0;
	return v->size;
}


// v é raiz de sua splay tree
// remove o preferred child de v
static void removePreferredChild(Node v) {
	if (v->children[1] != NULL) {
		v->children[1]->pathParent = v;
		v->children[1]->parent = NULL;
	}
	v->children[1] = NULL;
}


// w é o v->pathParent; 
// w e v são raizes de suas splay trees
// torna v o preferred child de w. E ao antigo preferred child de w, o faz ser non-preferred-child e este tem o pathParent apontando para w.  
static void switchPreferredChild(Node w, Node v) {
	if (w->children[1] != NULL) {
		w->children[1]->pathParent = v;
		w->children[1]->parent = NULL;
	}
	join(v, w);
	v->pathParent = NULL;
}