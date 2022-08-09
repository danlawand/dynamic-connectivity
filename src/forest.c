#include <stdlib.h>
#include "forest.h"
#include "queue.h"

#include <stdio.h>
static void *mallocSafe(size_t);
static void percursoNode(Node);
static void percursoEdge(Node);

static Node* nodes;

static int n_vertices;

// LCT é um struct que possui vetor de nós e nível
LCT dynamicForest(int n) {
    n_vertices = n;
    LCT linkCutTree = mallocSafe(sizeof(LCT));

    nodes = mallocSafe(n * sizeof(Node));

    for (int i = 0; i < n; ++i) {
        // passo o -1 aqui como nivel
        nodes[i] = makeTree(-1);
    }
    linkCutTree->nodes = nodes;
    linkCutTree->lctLevel = 1;

    return linkCutTree;
}
/*
1. INSERIR CELULAS DE ARESTAS

2. 

dynamicForest
    linkCutTree->lctLevel = 1;
addEdge
    int level = 1;
--> PERCORRE TUDO


dynamicForest
    linkCutTree->lctLevel = 0;
addEdge
    int level = 1;
--> NÃO PERCORRE NADA


dynamicForest
    linkCutTree->lctLevel = 0;
addEdge
    int level = random()%2;
--> PERCORRE APENAS ALGUNS NÓS DE NIVEL 0

*/

void addEdge(LCT lc, int i, int j) {
    // evert(lc->nodes[i]);
    // link(lc->nodes[i], lc->nodes[j]);

    // começo com level = ceil(lg n)
    int level = 1;

    // // faço um maketree para criar a aresta ij, e adiciono o nivel da aresta
    Node ij = makeTree(level);

    // // Se o nível da aresta for o nível da lct 
    if (level == lc->lctLevel) ij->n_levelEdges = 1;

    link(ij, lc->nodes[j]);
    evert(lc->nodes[i]);
    link(lc->nodes[i], ij);
}

// Não verifico se i-j é uma aresta
void deleteEdge(LCT lc, int i, int j) {

    // A rotina evert aqui é para garantir que o i seja o pai de j na LCT.
    evert(lc->nodes[i]);

    // Após isso, o cut(j) é garantido que corto a aresta i-j e não outra.
            // Antes, não teríamos essa garantia. Porque i poderia ser filho de j na LCT. Assim, não cortaria a aresta i-j, mas sim j-parent(j).
    cut(lc->nodes[j]);
}

int connected(LCT lc, int i, int j) {
    if (findroot(lc->nodes[i]) == findroot(lc->nodes[j])) return 1;
    return 0;
}

int sizeTree(LCT lc, int i) {
    access(lc->nodes[i]);
    return sizeLct(lc->nodes[i]);
}


void inorderTraversal(LCT lc, int i) {
    printf("inorderTraversal ");
    access(lc->nodes[i]);
    percursoNode(lc->nodes[i]);
    printf("\n\n");
}


// Queremos nós preferenciais raiz de árvores que possuem nós do mesmo nível.
// Iremos rebaixar nível, e 

// percorre a splay tree enraizada em v em inordem.
static void percursoNode(Node v) {
    if (v == NULL) return;
    
    // versão que era mais atual 
    if (v->n_levelEdges == 0) {
        printf("************ ERRO: Célula invalida no percursoNode ***********\n");
        return;
    }
        
    // Vou verificar se o contador do nível é maior ou igual a 1
    // Se é, eu chamo percursoNode, caso contrário não chamo
    percursoNode(v->children[0]);
    printf("%d ", v->val);

    // Vou verificar se o contador do nível é maior ou igual a 1
    // Se é, eu chamo percursoNode, caso contrário não chamo
    percursoNode(v->children[1]);

    // lista dos filhos não preferenciais
    // enquanto tiver gente na lista
    Celula p = (v->lista).next;

    while(p != &(v->lista) ) {
        splay(p->no);
        percursoNode(p->no);
        p = p->next;
    }
}

 
static void *mallocSafe(size_t nbytes) {
    void *p = malloc(nbytes);
    if (p == NULL) {
        printf("Erro: alocação de memória falhou no módulo forest.\n");
        exit(0);
    }
    return p;
}
