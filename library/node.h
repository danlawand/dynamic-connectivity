#ifndef _NODE_H
#define _NODE_H

#include "item.h"

typedef struct celula *Celula;
typedef struct node *Node;

struct celula {
    Celula next;
    Celula prev;
    Node no;
};

struct node {
	Value val;
	Node children[2];
	Node parent;
	Node pathParent;
	int bit;
	int size;

	// Eu não quero um apontador para uma lista, aqui eu quero a própria lista. Que é o struct
	// cabeça da lista dos nós não preferenciais
	struct celula lista; 
	
	// Apontador para célula da lista do pai do nó
	Celula cel;
};

Node newNode(Value, Node, Node, Node, Node, int, int);

// Celula de uma lista duplamente ligada circularmente
Celula newCelula(Celula, Celula, Node);

void freeCelula(Celula);

//	insere w na lista de nonPreferredChildren de v
void push_queue(Node, Node);

//	remove v da lista de nonPreferredChildren em que este pertence
void pop_queue(Node);

//  Na lista do w, tiro o v e insiro o u
void exchange_queue(Node, Node);

#endif
