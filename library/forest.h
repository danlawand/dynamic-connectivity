#ifndef _FOREST_H
#define _FOREST_H
#include "lct.h"

typedef struct lct *LCT;
struct lct {
    Node* nodes;
    int lctLevel;
};

Node* dynamicForest(int);

void addEdge(LCT, int, int);

void deleteEdge(LCT, int, int);

int connected(LCT, int, int);

int sizeTree(LCT, int);

void inorderTraversal(LCT, int v);
// void bfsTraversal(int v);

// Seria bom ter um freeForest, freeLCT, freeSplay, freeNode ...
#endif