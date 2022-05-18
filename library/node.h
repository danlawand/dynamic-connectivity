#ifndef _NODE_H
#define _NODE_H

#include "item.h"

typedef struct node *Node;
struct node {
	Value val;
	Node children[2];
	Node parent;
	Node pathParent;
	int bit;
	int size;
};

//Node start ===> primeiro nó na lista dos non-preferred child dele
//Node next  
//Node prev

Node newNode(Value, Node, Node, Node, Node, int, int);

#endif
