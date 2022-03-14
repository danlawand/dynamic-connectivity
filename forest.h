#ifndef _FOREST_H
#define _FOREST_H
#include "lct.h"
#include <stdio.h>


Node dynamicForest(int);

void addEdge(int, int);

void deleteEdge(int, int);

int connected(int, int);

#endif