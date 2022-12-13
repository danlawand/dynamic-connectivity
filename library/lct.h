#ifndef _LCT_H
#define _LCT_H
#include "splay.h"

Node maketree();

void link(Node, Node);

void access(Node);

Node findroot(Node);

void evert(Node);

void cut(Node);

int size(Node);

#endif
