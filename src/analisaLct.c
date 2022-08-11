#include "analisaLct.h"
#include <stdio.h>

// função auxiliar de 'analisaSplay', para analisar em pre-ordem a splay
static void analisaPreOrdemSplay(Node x);

static Node encontraRaiz(Node x);

static void printaCaminho(Node, FILE*);

static Node raizSplay(Node);


void quemEhDireito(Node x, FILE* fp) {
	if (x == NULL) return;

	if (fp != NULL) {
		if(x->children[1 - x->bit] == NULL) {
			fprintf(fp, "%d->Right: Eh null\n",x->val);
		} else {
			if(x->children[1 - x->bit]->children[0] != NULL) {
				fprintf(fp, "(No 0) %d->Right: %d\n",x->val, x->children[1 - x->bit]->children[0]->val);
			}
			if(x->children[1 - x->bit]->children[1] != NULL) {
				fprintf(fp, "(No 1) %d->Right: %d\n",x->val, x->children[1 - x->bit]->children[1]->val);
			}
		}
	}

	if(x->children[1 - x->bit] == NULL) {
		printf("%d->Right: Eh null\n",x->val);
	} else {
		if(x->children[1 - x->bit]->children[0] != NULL) {
			printf("(No 0) %d->Right: %d\n",x->val, x->children[1 - x->bit]->children[0]->val);
		}
		if(x->children[1 - x->bit]->children[1] != NULL) {
			printf("(No 1) %d->Right: %d\n",x->val, x->children[1 - x->bit]->children[1]->val);
		}
	}
}

void quemEhEsquerdo(Node x, FILE* fp) {
	if (x == NULL) return;

	if (fp != NULL) {
		if(x->children[x->bit] == NULL) {
			fprintf(fp, "%d->Left: Eh null\n",x->val);
		} else {
			if(x->children[x->bit]->children[0] != NULL) {
				fprintf(fp, "(No 0) %d->Left: %d\n",x->val, x->children[x->bit]->children[0]->val);
			}
			if(x->children[x->bit]->children[1] != NULL) {
				fprintf(fp, "(No 1) %d->Left: %d\n",x->val, x->children[x->bit]->children[1]->val);
			}
		}
	}

	if(x->children[x->bit] == NULL) {
		printf("%d->Left: Eh null\n",x->val);
	} else {
		if(x->children[x->bit]->children[0] != NULL) {
			printf("(No 0) %d->Left: %d\n",x->val, x->children[x->bit]->children[0]->val);
		}
		if(x->children[x->bit]->children[1] != NULL) {
			printf("(No 1) %d->Left: %d\n",x->val, x->children[x->bit]->children[1]->val);
		}
	}
}

void quemEhPai(Node x, FILE* fp) {
	if (x == NULL) return;

	if (fp != NULL) {
		if(x->parent == NULL) {
			fprintf(fp, "%d->parent: Eh null\n",x->val);
		} else {
			if(x->parent->parent != NULL) {
				fprintf(fp, "(No 0) %d->parent: %d\n",x->val, x->parent->parent->val);
			} else {
				fprintf(fp, "(No 1) %d->parent: Eh null\n",x->val);
			}
		}
	}

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
		if(x->parent->parent != NULL) {
			printf("(No 0) %d->parent: %d\n",x->val, x->parent->parent->val);
		} else {
			printf("(No 1) %d->parent: Eh null\n",x->val);
		}
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
	// pushBitDownRec(r);
	printaCaminho(r, fp);
	if (fp != NULL)	fprintf(fp, "\n");
	printf("\n");
}

// função auxiliar de 'analisaSplay', para analisar em pre-ordem a splay
// Invariante: Node x é a raiz de sua splay tree
static void printaCaminho(Node x, FILE* fp) {
	if (x == NULL) return;

	if (x->edgeLevel != -1) {
		printaCaminho(x->children[0], fp);
		printaCaminho(x->children[1], fp);
		return;
	}

	printaCaminho(x->children[x->bit], fp);
	if (fp != NULL)	fprintf(fp, "%d -> ", x->val);
	printf("%d (bit: %d)-> ", x->val, x->bit);
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

	
	//
	fprintf(fp, "Lista de nonPreferredChildren:\n");
	Celula p = (x->lista).next;
    while(p != &(x->lista) ) {
        // splay(p->no);
        fprintf(fp, "%d, ", p->no->val);
		// percurso(p->no);
        p = p->next;
    }
	fprintf(fp, "\n");

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

	printf("Sobre o %d\n", x->val);
	quemEhDireito(x, NULL);
	quemEhEsquerdo(x, NULL);
	quemEhPai(x, NULL);
	quemEhPathParent(x, NULL);

	// if (x->parent != NULL) x = findRootSemAccess(x);
	Node r = raizSplay(x);
	printf("[Sem ordem]Quem tá na SplayTree:\n");
	analisaPreOrdemSplay(r);
}

static Node raizSplay(Node x) {
	if (x->parent == NULL) return x;
	raizSplay(x->parent);
}

// função auxiliar de 'analisaSplay', para analisar em pre-ordem a splay
static void analisaPreOrdemSplay(Node x) {
	if (x == NULL) return;
	if (x->edgeLevel != -1) {
		analisaPreOrdemSplay(x->children[0]);
		analisaPreOrdemSplay(x->children[1]);
		return;
	}
	// analisaNode(x, NULL);
	printf("%d:%d - ", x->val,x->bit);
	analisaPreOrdemSplay(x->children[0]);
	analisaPreOrdemSplay(x->children[1]);
}
