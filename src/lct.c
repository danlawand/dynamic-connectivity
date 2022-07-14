#include "lct.h"
#include <stdlib.h>
#include <stdio.h>

static void removePreferredChild(Node);
static void switchPreferredChild(Node, Node);

static void insertNonPreferredChildren(Node, Node);
static void removeNonPreferredChildren(Node);
static void exchangeNonPreferredChildren(Node, Node);

// Tem como o cara que tem o PathParent ficar na raiz da splay tree?


Node maketree(int nivel) {
	return makeSplay(nivel);
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
// W se torna a raiz da lct e o caminho preferencial vai até V
void link(Node v, Node w) {
	access(v);
	access(w);
	
	// Torna v filho direito de w na splay tree
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

// retira a aresta 'v'-ij-'v->parent'
void cut(Node v) {
	access(v);

	Node m = maxSplay(v->children[0]);
	split(m);
	// retiro o 'm', que é a aresta, do seu filho direito.
	// Porém, ela permanece conectada com o filho esquerdo. 

	Node u = m->children[0];
	splay(u);
	// Agora u tem bit zero. Portanto posso cortá-lo
	split(u);
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


// v é raiz de sua splay tree
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


// w é o v->pathParent; 
// w e v são raizes de suas splay trees
// torna v o preferred child de w. E ao antigo preferred child de w, o faz ser non-preferred-child e este tem o pathParent apontando para w.  
static void switchPreferredChild(Node w, Node v) {
	if (w->children[1] != NULL) {
		w->children[1]->pathParent = w;
		w->children[1]->parent = NULL;

		// Na lista do w, tiro o v e insiro o w->children[1]
		// v e w->children[1] são raizes
		exchangeNonPreferredChildren(v, w->children[1]);

	} else {
		// removo o v da lista do w. 
		//Como v faz parte apenas de uma única lista, pois é filho não preferencial de apenas um pai, logo não preciso indicar sobre qual lista estou removendo. 
		removeNonPreferredChildren(v);

		// Inseri as seguintes linhas na rotina rotate:
		/*
			// Lidam com a célula de nonPreferredChild
			x->cel = p->cel;
			p->cel = NULL;
		*/
		// Estou fazendo a raiz da splay tree carregar o apontador à celula que identifica qual nó é o nonPreferredChild do nó pathParent, indicado pelo ponteiro pathParent da raiz.
		// A raiz tem o ponteiro pathParent que identifica que há uma aresta entre o pathParent e o nó de menor profundidade desta árvore.
		// Além disso, carrega o ponteiro 'cel', que indentifica a célula que está na lista dos nonPreferredChildren do pathParent. 
		// Esta célula segue com o comportamento normal em relação à lista ligada. Mas ela possui um ponteiro para o nó que de fato tem uma aresta com o pathParent. Que é o nó de menor profundidade desta árvore. 

	}
	join(w, v);

	v->pathParent = NULL;
}

//	insere w na lista de nonPreferredChildren de v
static void insertNonPreferredChildren(Node v, Node w) {
	// printf("Insere %d na lista de %d\n", w->val, v->val);
	push_nonPreferredChild(v, w);
}

//	remove v da lista de nonPreferredChildren em que este pertence
static void removeNonPreferredChildren(Node v) {
	// printf("Remove %d da lista em que está\n", v->val);
	pop_nonPreferredChild(v);
}

// Na lista de nonPreferredChildren de w, tiro o v e insiro o u
static void exchangeNonPreferredChildren(Node v, Node u) {
	// printf("Insere %d, e retira %d\n", v->val, u->val);
	exchange_nonPreferredChild(v, u);
}

// Operação dumb que só mostra qual é a raiz da árvore, sem mexer nela.
Node findRootSemAccess(Node v) {
	Node m = minimumSemMudanca(v);
	return m;
}
