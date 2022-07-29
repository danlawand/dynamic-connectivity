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
        nodes[i] = maketree(-1);
    }
    linkCutTree->nodes = nodes;
    linkCutTree->lctLevel = 0;

    return linkCutTree;
}


void addEdge(LCT lc, int i, int j) {
    evert(lc->nodes[i]);
    link(lc->nodes[i], lc->nodes[j]);

    // começo com level = ceil(lg n)
    // int level = 0;

    // // faço um maketree para criar a aresta ij, e adiciono o nivel da aresta
    // Node ij = makeTree(level);

    // // Se o nível da aresta for o nível da lct 
    // if (level == lc->lctLevel) ij->n_levelEdges = 1;

    // link(ij, lc->nodes[j]);
    // evert(lc->nodes[i]);
    // link(lc->nodes[i], ij);
}

// Não verifico se i-j é uma aresta
void deleteEdge(LCT lc, int i, int j) {
    // cut(lc->nodes[i]);


    // A rotina evert aqui é para garantir que o i seja o pai de j na LCT.
    // printf("\nEVERT no %d\n", lc->nodes[i]->val);
    evert(lc->nodes[i]);
    // for (int i = 0; i < n_vertices; i++) {
    //     printf("\n");
    //     analisaSplay(lc->nodes[i]);
    //     printf("\n");
    // }
    // Após isso, o cut(j) é garantido que corto a aresta i-j e não outra.
            // Antes, não teríamos essa garantia. Porque i poderia ser filho de j na LCT. Assim, não cortaria a aresta i-j, mas sim j-parent(j).
    // printf("\nCUT no %d\n", lc->nodes[j]->val);
    // if (lc->nodes[j]->parent != NULL) {
    //     printf("%d->parent: %d\n", lc->nodes[j]->val, lc->nodes[j]->parent->val);
    // }
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
static void percursoEdge(Node v) {
    if (v == NULL) return;


    
    // Vou verificar se o contador do nível é maior ou igual a 1
    // Se é, eu chamo percursoEdge, caso contrário não chamo
    percursoEdge(v->children[0]);

    //****************************
    // Tá errado isso. 
    // ***************************

    
    // int index = hashing(v->val, v->children[0]->val);
    // printf("%d ", v->edgeNodes[index]->edgeId);

    // Vou verificar se o contador do nível é maior ou igual a 1
    // Se é, eu chamo percursoEdge, caso contrário não chamo
    percursoEdge(v->children[1]);

    // lista dos filhos não preferenciais
    // enquanto tiver gente na lista
    Celula p = (v->lista).next;

    while(p != &(v->lista) ) {
        splay(p->no);
        percursoEdge(p->no);
        p = p->next;
    }
}

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





// void bfsTraversal(int v) {
//     access(nodes[v]);

//     Node current_node = nodes[v];
//     Node parent_node, right_node, left_node;
//     struct celula* nonPreferredChildrenList;
//     Celula aux;

//     int visited[N];
//     for (int i = 0; i < N; i++) {
//         visited[i] = 0;
//     }

//     queueInit();

//     visited[current_node->val] = 1;
//     pushQueue(current_node);
//     while(!emptyQueue()) {
//         current_node = popQueue();
//         printf("%d ",current_node->val);

//         // for each node adjecent to the current
//         parent_node = current_node->parent;
//         left_node = current_node->children[0];
//         right_node = current_node->children[1];
//         if (parent_node != NULL && !visited[parent_node->val]) {
//             visited[parent_node->val] = 1;
//             pushQueue(parent_node);
//         }
//         if (left_node != NULL && !visited[left_node->val]) {
//             visited[left_node->val] = 1;
//             pushQueue(left_node);
//         }
//         if (right_node != NULL && !visited[right_node->val]) {
//             visited[right_node->val] = 1;
//             pushQueue(right_node);
//         }

//         nonPreferredChildrenList = &current_node->lista;
//         if (nonPreferredChildrenList != NULL) {
//             // for each item inthis list
//             aux = nonPreferredChildrenList->next;
//             while (aux != nonPreferredChildrenList) {
//                 if (!visited[aux->no->val]) {
//                     visited[aux->no->val] = 1;
//                     pushQueue(aux->no);
//                 }
//             }
//         }
//     }
// }




// 
static void *mallocSafe(size_t nbytes) {
    void *p = malloc(nbytes);
    if (p == NULL) {
        printf("Erro: alocação de memória falhou no módulo forest.\n");
        exit(0);
    }
    return p;
}
