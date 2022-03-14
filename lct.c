#include "lct.h"
#include <stdio.h>

static void removePreferredChild(Node);
static void switchPreferredChild(Node, Node);

Node maketree() {
	return makeSplay();
}


void access(Node v) {
	Node w;
	splay(v);
	removePreferredChild(v);

	while (v->pathParent != NULL) {
		w = v->pathParent;
		splay(w);
		switchPreferredChild(w, v);
		splay(v);
	}
}

void link(Node v, Node w) {
	access(v);
	access(w);
	join(w, v);
}

void evert(Node v) {
	access(v);
	reflectTree(v);
}

Node findroot(Node v) {
	access(v);
	Node m = minSplay(v);
	return m;
}

void cut(Node v) {
	access(v);
	Node m = maxSplay(v->children[0]);
	split(m);
}

static void removePreferredChild(Node v) {
	if (v->children[1] != NULL) {
		v->children[1]->pathParent = v;
		v->children[1]->parent = NULL;
	}
	v->children[1] = NULL;
}

static void switchPreferredChild(Node w, Node v) {
	if (w->children[1] != NULL) {
		w->children[1]->pathParent = v;
		w->children[1]->parent = NULL;
	}
	join(v, w);
	v->pathParent = NULL;
}