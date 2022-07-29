#ifndef _NODE_H
#define _NODE_H

#include "item.h"

typedef struct celula *Celula;
typedef struct node *Node;

// Lista de nonPreferredChildren that have at least one node of level of the lct
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
	
	// Apontador para célula em que este nó esta "guardado" na lista dos filhos não preferenciais do pai deste nó
	Celula cel;


	// É PRECISO UM APONTADOR PARA OS NÓS ARESTAS INCIDENTES NESTE NÓ VÉRTICE?
	// apontador para o nó aresta 
	Node* edgeNodes;


	//****** Atributos usados apenas para nós arestas
	// indetificador da aresta
	int edgeId;

	// Indicador de quantos nós-aresta tem na sua subárvore
	int n_levelEdges;

	// Nível da aresta
	int edgeLevel;

	// ponteiros usados apenas pelas arestas
	Node edgeNode1;
	Node edgeNode2;
	//******
};

Node newNode(Value, Node, Node, Node, Node, int, int, int, int);

// Celula de uma lista duplamente ligada circularmente
Celula newCelula(Celula, Celula, Node);

void freeCelula(Celula);

//	insere w na lista de nonPreferredChildren de v
void push_nonPreferredChild(Node, Node);

//	remove v da lista de nonPreferredChildren em que este pertence
void pop_nonPreferredChild(Node);

//  Na lista do w, tiro o v e insiro o u
void exchange_nonPreferredChild(Node, Node);

#endif
