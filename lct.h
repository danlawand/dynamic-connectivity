#ifndef _LCT_H
#define _LCT_H
#include "splay.h"
#include <stdio.h>

Node maketree();

void link(Node, Node);

void access(Node);

Node findroot(Node);

void evert(Node);

void cut(Node);

#endif
