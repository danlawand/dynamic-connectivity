#include "analisaLct.h"
#include <stdio.h>

// função auxiliar de 'analisaSplay', para analisar em pre-ordem a splay
static void analisaPreOrdemSplay(Node x);

static Node encontraRaiz(Node x);

static void printaCaminho(Node, FILE*);

void quemEhDireito(Node x, FILE* fp) {
	if (x == NULL) return;

	if (fp != NULL) {
		if(x->children[1 - x->bit] == NULL) {
			fprintf(fp, "%d->Right: Eh null\n",x->val);
		} else {
			fprintf(fp, "%d->Right: %d\n",x->val, x->children[1 - x->bit]->val);
		}
	}

	if(x->children[1 - x->bit] == NULL) {
		printf("%d->Right: Eh null\n",x->val);
	} else {
		printf("%d->Right: %d\n",x->val, x->children[1 - x->bit]->val);
	}
}

void quemEhEsquerdo(Node x, FILE* fp) {
	if (x == NULL) return;

	if (fp != NULL) {
		if(x->children[x->bit] == NULL) {
			fprintf(fp, "%d->Left: Eh null\n",x->val);
		} else {
			fprintf(fp, "%d->Left: %d\n",x->val, x->children[x->bit]->val);
		}
	}

	if(x->children[x->bit] == NULL) {
		printf("%d->Left: Eh null\n",x->val);
	} else {
		printf("%d->Left: %d\n",x->val, x->children[x->bit]->val);
	}
}

void quemEhPai(Node x, FILE* fp) {
	if (x == NULL) return;

	if (fp != NULL) {
		if(x->parent == NULL) {
			fprintf(fp, "%d->parent: Eh null\n",x->val);
		} else {
			fprintf(fp, "%d->parent: %d\n",x->val, x->parent->val);
		}
	}

	if(x->parent == NULL) {
		printf("%d->parent: Eh null\n",x->val);
	} else {
		printf("%d->parent: %d\n",x->val, x->parent->val);
	}
}

void quemEhPathParent(Node x, FILE* fp) {
	if (x == NULL) return;

	if (fp != NULL) {
		if(x->pathParent == NULL) {
			fprintf(fp, "%d->pathParent: Eh null\n",x->val);
		} else {
			fprintf(fp, "%d->pathParent: %d\n",x->val, x->pathParent->val);
		}
	}

	if(x->pathParent == NULL) {
		printf("%d->pathParent: Eh null\n",x->val);
	} else {
		printf("%d->pathParent: %d\n",x->val, x->pathParent->val);
	}
}

void qualBit(Node x, FILE *fp) {
	if (x == NULL) return;

	if (fp != NULL) {
		fprintf(fp, "%d->bit: %d\n",x->val, x->bit);
	}
	printf("%d->bit: %d\n",x->val, x->bit);
}

void quemEhMinimumNaArvore(Node x, FILE* fp) {
	if (x == NULL) return;

	Node k = minimumSemMudanca(encontraRaiz(x));
	if (fp != NULL) {
		if(k != NULL) {
			fprintf(fp, "%d->minimo: %d\n",x->val, k->val);
		} else {
			fprintf(fp, "%d->minimo: Eh null\n",x->val);
		}
	}

	if(k != NULL) {
		printf("%d->minimo: %d\n",x->val, k->val);
	} else {
		printf("%d->minimo: Eh null\n",x->val);
	}
}

void qualEhOPreferredPath(Node x, FILE* fp) {
	if (x == NULL) return;
	if (fp != NULL)	fprintf(fp, "Preferred Path: \n");
	printf("Preferred Path: \n");
	Node r = encontraRaiz(x);
	printaCaminho(r, fp);
	if (fp != NULL)	fprintf(fp, "\n");
	printf("\n");
}

// função auxiliar de 'analisaSplay', para analisar em pre-ordem a splay
static void printaCaminho(Node x, FILE* fp) {
	if (x == NULL) return;
	printaCaminho(x->children[x->bit], fp);
	if (fp != NULL)	fprintf(fp, "%d -> ", x->val);
	printf("%d -> ", x->val);
	printaCaminho(x->children[1-x->bit], fp);
	return;
}


static Node encontraRaiz(Node x) {
	Node k = x;
	while(k->parent != NULL) {
		k = k->parent;
	}
	return k;
}

// Descreve o nó, com a opção de imprimir em um arquivo
void analisaNode(Node x, FILE* fp) {
	if (x == NULL) return;

	printf("Sobre o %d\n", x->val);
	if (fp != NULL) {
		fprintf(fp, "Sobre o %d\n", x->val);
	}
	// quemEhDireito(x, fp);
	// quemEhEsquerdo(x, fp);
	// quemEhPai(x, fp);
	quemEhPathParent(x, fp);
	// qualBit(x, fp);
	// quemEhMinimumNaArvore(x, fp);
	qualEhOPreferredPath(x, fp);

	//qual é o size
	// int k = sizeLct(x);
	// printf("Size: %d\n", k);

	// if (fp != NULL) {
	// 	fprintf(fp, "Size: %d\n", k);
	// }


	if (fp != NULL) {
		fprintf(fp, "\n");
	}
	printf("\n");
	if (x->parent == NULL) {
		printSPLAY(x, 1);
		printf("\n");
	}
}

void analisaSplay(Node x) {
	if (x == NULL) return;
	if (x->parent != NULL) x = findRootSemAccess(x);
	analisaPreOrdemSplay(x);
}

// função auxiliar de 'analisaSplay', para analisar em pre-ordem a splay
static void analisaPreOrdemSplay(Node x) {
	if (x == NULL) return;
	analisaNode(x, NULL);
	analisaPreOrdemSplay(x->children[1-x->bit]);
	analisaPreOrdemSplay(x->children[x->bit]);
}
