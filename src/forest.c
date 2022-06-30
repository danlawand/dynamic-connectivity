#include <stdlib.h>
#include "forest.h"
#include "queue.h"

#include <stdio.h>
static void *mallocSafe(size_t);
static void percurso(Node);

static Node *nodes;
static int N;

static int **adj;

// LCT vai ser um vetor de nós e nível
// Posso criar um struct chamado LCT que contém o vetor dos nós, e o valor do nível
LCT dynamicForest(int n) {
    LCT linkCutTree = mallocSafe(sizeof(LCT));

    N = n;

    nodes = mallocSafe(n * sizeof(Node));

    adj = mallocSafe(n*sizeof(int*));

    for (int i = 0; i < n; ++i) {
        // adj[i] = mallocSafe(n*sizeof(int));
        nodes[i] = maketree();
    }
    linkCutTree->nodes = nodes;
    linkCutTree->lctLevel = 0;

    // Adjacency list
    // for (int i = 0; i < n; ++i) {
    //     for (int j = 0; j < n; j++) {
    //         adj[i][j] = -1;
    //     }
    // }
    return nodes;
}

void addEdge(int i, int j) {
    evert(nodes[i]);
    link(nodes[i], nodes[j]);
    // adj[i][j] = 1;
    // adj[j][i] = 1;
}

void deleteEdge(int i, int j) {
    cut(nodes[i]);

    // evert no i
    // access j já está no cut
    // Com isso, eu sei quem tá em cima e quem ta embaixo.
    // E sei qauem

    // Tenho que garantir que quando eu chamo o cut, eu tô chamando o cara que tá embaixo

    // 
}

int connected(int i, int j) {
    if (findroot(nodes[i]) == findroot(nodes[j])) return 1;
    return 0;
}

int sizeTree(int i) {
    access(nodes[i]);
    return sizeLct(nodes[i]);
}

void inorderTraversal(int i) {
    printf("inorderTraversal ");
    access(nodes[i]);
    percurso(nodes[i]);
    printf("\n\n");
}

// percorre a splay tree enraizada em v em inordem.
static void percurso(Node v) {
    if (v == NULL) return;
    
    // Vou verificar se o contador do nível é maior ou igual a 1
    // Se é, eu chamo percurso, caso contrário não chamo
    percurso(v->children[0]);
    printf("%d ", v->val);

    // Vou verificar se o contador do nível é maior ou igual a 1
    // Se é, eu chamo percurso, caso contrário não chamo
    percurso(v->children[1]);

    // lista dos filhos não preferenciais
    // enquanto tiver gente na lista
    Celula p = (v->lista).next;

    while(p != &(v->lista) ) {
        splay(p->no);
        percurso(p->no);
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
