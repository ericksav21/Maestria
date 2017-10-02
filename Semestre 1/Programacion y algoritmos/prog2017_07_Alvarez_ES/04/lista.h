#ifndef LISTA_H
#define LISTA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
	char *str;
	int freq;
	struct node *next;
} NODE;

typedef NODE* NODEPTR;

NODEPTR create_node(char *str);

NODEPTR add_node(NODEPTR root, char *str);

void print_list(NODEPTR root);

void print_list_in_file(NODEPTR root, char *files_name);

NODEPTR free_node(NODEPTR node);

void free_list(NODEPTR root);

#endif