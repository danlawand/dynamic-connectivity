#ifndef _LCT_H
#define _LCT_H
#include "splay.h"

Node makeTree(int);

void link(Node, Node);

void access(Node);

Node findroot(Node);

void evert(Node);

void cut(Node);

int sizeLct(Node);

// Operação dumb que só mostra qual é a raiz da árvore, sem mexer nela.
Node findRootSemAccess(Node);


#endif
