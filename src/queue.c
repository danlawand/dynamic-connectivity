#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

static void *mallocSafe(size_t);

Queue q;

void queueInit() {
    q = mallocSafe(sizeof(*q));
    Celula head = mallocSafe(sizeof(*head));
    q->size = 0;
    q->head = head;
    q->head->next = q->head;
    q->head->prev = q->head;
}

void pushQueue(Node v) {
    Celula new_cel = mallocSafe(sizeof(*new_cel));
    new_cel->no = v;
    new_cel->next = q->head->next;
    new_cel->prev = q->head;
    q->head->next->prev = new_cel;
    q->head->next = new_cel;
    q->size++;

}

Node popQueue() {
    Celula temp;
    temp = q->head->prev;
    Node no = temp->no;

    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;

    temp->next = NULL;
    temp->prev = NULL;
    temp->no = NULL;
    temp = NULL;
    q->size--;
    return no;  
}

int emptyQueue() {
    if (q->size == 0) return 1;
    return 0;
}

static void *mallocSafe(size_t nbytes) {
	void *p = malloc(nbytes);
	if (p == NULL) {
		printf("Erro: alocação de memória falhou no módulo node.\n");
		exit(0);
	}
	return p;
}
