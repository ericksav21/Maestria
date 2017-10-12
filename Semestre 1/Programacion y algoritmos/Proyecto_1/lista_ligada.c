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
		NODEPTR nxt = root;
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

NODEPTR list_copy(NODEPTR org, NODEPTR dest) {
	free_list(dest);
	NODEPTR nxt_org = org;
	NODEPTR nxt_dest = dest;
	while(nxt_org) {
		nxt_dest = add_node(nxt_dest, nxt_org->pixel);
		nxt_org = nxt_org->next;
		nxt_dest = nxt_dest->next;
	}

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