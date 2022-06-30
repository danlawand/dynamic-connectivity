#ifndef _FOREST_H
#define _FOREST_H
#include "lct.h"

typedef struct lct *LCT;
struct lct {
    Node* nodes;
    int lctLevel;
};

LCT dynamicForest(int);

void addEdge(int, int);

void deleteEdge(int, int);

int connected(int, int);

int sizeTree(int);

void inorderTraversal(int v);
// void bfsTraversal(int v);
#endif