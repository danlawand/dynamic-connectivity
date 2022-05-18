#ifndef _SPLAY_H
#define _SPLAY_H
#include "node.h"

Node makeSplay();
void splay(Node);
void join(Node, Node);
void split(Node);
Node maxSplay(Node);
Node minSplay(Node);
void reflectTree(Node);

void pushBitDownRec(Node);


void printSPLAY(Node, int);
// Operação dumb Serve apenas para o print
Node minimumSemMudanca(Node);

#endif
