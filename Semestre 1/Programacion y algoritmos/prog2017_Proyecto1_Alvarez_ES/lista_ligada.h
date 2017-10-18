#ifndef LISTA_LIGADA_H
#define LISTA_LIGADA_H

#include <stdio.h>
#include <stdlib.h>

#include "estructuras.h"

typedef struct node {
	PIXEL pixel;
	struct node *next;
} NODE;

typedef NODE* NODEPTR;

NODEPTR create_node(PIXEL pixel);

NODEPTR add_node(NODEPTR root, PIXEL pixel);

NODEPTR remove_node(NODEPTR root, int i);

NODEPTR free_node(NODEPTR node);

NODEPTR list_copy(NODEPTR org, NODEPTR dest);

int list_size(NODEPTR root);

NODEPTR list_get(NODEPTR root, int n);

void print_list(NODEPTR root);

int is_list_empty(NODEPTR root);

void free_list(NODEPTR root);

#endif