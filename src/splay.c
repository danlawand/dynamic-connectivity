#include "splay.h"
#include <stdlib.h>

#include <stdio.h>

static int valor = 0;
static Node root;

static Node sibling(Node);

static void swapChildren(Node);

static void pushBitUp(Node);

static void pushBitDown(Node);

static void rotate(Node);

static Node maximum(Node);

static Node minimum(Node);

// passo o nivel, para identificar a aresta
// default -1
Node makeSplay(int nivel) {
	return newNode(valor++, NULL, NULL, NULL, NULL, 0, 1, nivel, -1);
}


// v->bit sai daqui sempre zero
void reflectTree(Node v) {
	v->bit = 1 - v->bit;
	pushBitDown(v);
}

// w é filho direito de v
void join(Node v, Node w) {
	v->children[1] = w;
	w->parent = v;
	v->size = v->size + w->size;
	v->n_levelEdges += w->n_levelEdges;
}

void split(Node x) {
	Node greaterThanX;
	if (x->bit==1) printf("*************** Erro: Bit de x era pra ser zero no Split **********************\n");
	greaterThanX = x->children[1];
	if (greaterThanX != NULL) {
		greaterThanX->parent = NULL;
		x->size = x->size - greaterThanX->size;
		x->n_levelEdges -= greaterThanX->n_levelEdges;
	}
	x->children[1] = NULL;
}


/* Comentário 14/07/2022
	Necessária alteração no splay:
	Se eu faço splay(3)
	Para uma splay tree assim:
	(a raiz é o topo)
	     4:0
			  3:1
		   2:0
	Iria fazer o pushBitUp(3): [da linha 75]
	    4:1
	  3:0
	2:0

	Depois o pushBitUp(4): [da linha 78]
	     4:0
			  3:0
		   2:0	
	Assim ficou errado, pois a árvore mudou completamente.

	Após isso, seria feito o splay que resultaria no seguinte erro:
		 3:0
	  4:0
	  	2:0

	-----------------
	Alterei o pushBitUp para pushBitDown, e aparentemente funcionou


*/

void splay (Node x) {
	pushBitDown(x);//pushBitUp(x);//???
	while (x->parent != NULL) {
		Node p = x->parent;
		pushBitDown(x);//pushBitUp(p);//???
		if (p->parent == NULL) rotate(x);
		else { 
			Node g = p->parent;
			pushBitDown(x);//pushBitUp(g);
			if (x->bit == 1 || p->bit == 1 || g->bit == 1) printf("*************** Erro: Algum bit é 1 no splay ***************\n");

			// Zig-Zig ou Zag-Zag
			if (( p == g->children[0] && x == p->children[0] ) ||
			( p == g->children[1] && x == p->children[1] )) {
				rotate(p);
				rotate(x);
			}
			//Zig-Zag ou Zag-Zig
			else {
				rotate(x);
				rotate(x);
			}
		}
	}
	// pushBitDown(x);
	root = x;
	if (x->bit == 1) printf("*************** Erro no bit na função splay ***************\n");
}

// Assume-se que o x e o x->parent tem bit = 0
static void rotate(Node x) {

	Node p = x->parent;
	Node g = p->parent;

	int sizeChild = 0;

	int nLevelChild = 0;

	// L.83 e 84 lidam com path parent
	x->pathParent = p->pathParent;
	p->pathParent = NULL;

	// Lidam com a célula de nonPreferredChild
	x->cel = p->cel;
	p->cel = NULL;

	if (p->children[0] == x) {
		p->children[0] = x->children[1];
		if (x->children[1] != NULL) {
			x->children[1]->parent = p;
			sizeChild = x->children[1]->size;
			nLevelChild = x->children[1]->n_levelEdges;
		}
		x->children[1] = p;
	}

	else {
		p->children[1] = x->children[0];
		if (x->children[0] != NULL) {
			x->children[0]->parent = p;
			sizeChild = x->children[0]->size;
			nLevelChild = x->children[0]->n_levelEdges;
		}
		x->children[0] = p;
	}

	// por enquanto assumimos que os bits destes são zero	
	// x->bit = p->bit;
	// p->bit = 0;

	p->parent = x;
	x->parent = g;

	if (g != NULL) {
		if (p == g->children[0]) g->children[0] = x;
		else g->children[1] = x;
	}

	p->size = p->size - x->size + sizeChild;
	p->n_levelEdges = p->n_levelEdges - x->n_levelEdges + nLevelChild;

	x->size = x->size - sizeChild + p->size; 
	x->n_levelEdges = x->n_levelEdges - nLevelChild + p->n_levelEdges; 
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
	if (x->children[1] == NULL) return x;
	return maximum(x->children[1]);
}

// Não se assume nada sobre o bit do x
static void pushBitUp(Node x) {
	if (x->bit == 1) {
		Node p = x->parent;
		if (p != NULL) {
			p->bit = 1 - p->bit;
			Node s = sibling(x);
			if (s != NULL) s->bit = 1 - s->bit;
			swapChildren(p);
		} else {
			swapChildren(x);
		}
		x->bit = 0;
	}
}

// Não se assume nada sobre o bit do x
static void pushBitDown(Node x) {
	printf("		x->val: %d\n", x->val);
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

// Função de uso apenas para o print final
// Sempre é a raiz que chama
void pushBitDownRec(Node x) {
	if (x == NULL) return;

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
	pushBitDownRec(x->children[0]);
	pushBitDownRec(x->children[1]);
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

/************************   PRINT FUNCTIONS ************************/

void printSPLAY(Node x, int i) {
	if (x != NULL) {
		Node child;
		child  = x->children[0];
		if (child != NULL) child->bit ^= x->bit;
		child  = x->children[1];
		if (child != NULL) child->bit ^= x->bit;

		printSPLAY(x->children[1 - x->bit], i+1);
		int bparent = 0;
		if (x->parent != NULL) {
			bparent = x->parent->bit;
		}
		printf("%*d:%d\n", 2*i, x->val, x->bit^bparent);
		printSPLAY(x->children[x->bit], i+1);

		child  = x->children[0];
		if (child != NULL) child->bit ^= x->bit;
		child  = x->children[1];
		if (child != NULL) child->bit ^= x->bit;
	}
}


// Operação dumb Serve apenas para o print
Node minimumSemMudanca(Node x) {
	if (x->children[x->bit] == NULL) return x;
	return minimumSemMudanca(x->children[x->bit]);
}
