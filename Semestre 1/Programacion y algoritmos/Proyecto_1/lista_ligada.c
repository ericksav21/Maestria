#include "lista_ligada.h"

NODEPTR create_node(PIXEL pixel) {
	NODEPTR res;
	res = (NODEPTR)malloc(sizeof(NODE));
	
	res->pixel.i = pixel.i;
	res->pixel.j = pixel.j;
	res->next = NULL;

	return res;
}

NODEPTR add_node(NODEPTR root, PIXEL pixel) {
	//El nodo tiene al menos un elemento
	NODEPTR new_node = create_node(pixel);
	NODEPTR last = root;
	if(root == NULL) {
		root = new_node;
		return root;
	}
	while(last->next != NULL) {
		last = last->next;
	}
	last->next = new_node;
	return root;
}

NODEPTR remove_node(NODEPTR root, int i) {
	NODEPTR tmp = root, prev;
	int k = 0;
	if(tmp != NULL && k == i) {
		root = tmp->next;
		free_node(tmp);
		return root;
	}
	while(tmp != NULL && k != i) {
		prev = tmp;
		tmp = tmp->next;
		k++;
	}
	if(tmp == NULL)
		return root;
	prev->next = tmp->next;
	free_node(tmp);
	return root;
}

NODEPTR free_node(NODEPTR node) {
	free(node);
	node = NULL;

	return node;
}

NODEPTR list_copy(NODEPTR org, NODEPTR dest) {
	//free_list(dest);
	if(!org)
		return NULL;

	dest = add_node(dest, org->pixel);
	dest->next = list_copy(org->next, dest->next);
	return dest;
}

int list_size(NODEPTR root) {
	int cnt = 0;
	NODEPTR nxt = root;
	while(nxt) {
		cnt++;
		nxt = nxt->next;
	}

	return cnt;
}

NODEPTR list_get(NODEPTR root, int n) {
	int len = list_size(root), i;
	NODEPTR nxt = root;
	if(len <= n) {
		return NULL;
	}

	for(i = 0; i < n; i++)
		nxt = nxt->next;

	return nxt;
}

int is_list_empty(NODEPTR root) {
	return (list_size(root) == 0);
}

void print_list(NODEPTR root) {
	if(root) {
		NODEPTR nxt = root;
		while(nxt) {
			printf("i:%d j:%d\n", nxt->pixel.i, nxt->pixel.j);
			nxt = nxt->next;
		}
	}
}

void free_list(NODEPTR root) {
	NODEPTR tmp;
	while (root != NULL) {
		tmp = root;
		root = root->next;
		free(tmp);
	}
}