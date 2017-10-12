#ifndef LISTA_LIGADA_H
#define LISTA_LIGADA_H

#include <stdlib.h>

#include "estructuras.h"

typedef struct node {
	PIXEL pixel;
	struct node *next;
} NODE;

typedef NODE* NODEPTR;

NODEPTR create_node(PIXEL pixel);

NODEPTR add_node(NODEPTR root, PIXEL pixel);

NODEPTR free_node(NODEPTR node);

int list_size(NODEPTR root);

void free_list(NODEPTR root);

#endif