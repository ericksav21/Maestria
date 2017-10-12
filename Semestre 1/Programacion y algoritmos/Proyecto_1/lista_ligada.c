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
	if(root) {
		NODEPTR nxt = root, lst = NULL;
		while(nxt->next)
			nxt = nxt->next;
		nxt->next = create_node(pixel);
	}
	else {
		root = create_node(pixel);
	}

	return root;
}

NODEPTR free_node(NODEPTR node) {
	free(node);
	node = NULL;

	return node;
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

void free_list(NODEPTR root) {
	if(root) {
		NODEPTR nxt = root->next;
		while(nxt->next) {
			free_node(root);
			root = nxt;
			nxt = nxt->next;
		}
		if(nxt)
			free_node(nxt);
		if(root)
			free_node(root);
	}
}