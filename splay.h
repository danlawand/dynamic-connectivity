#ifndef _SPLAY_H
#define _SPLAY_H
#include "node.h"
#include <stdio.h>

Node makeSplay();
void splay(Node);
void join(Node, Node);
void split(Node);
Node maxSplay(Node);
Node minSplay(Node);
void reflectTree(Node);

#endif
