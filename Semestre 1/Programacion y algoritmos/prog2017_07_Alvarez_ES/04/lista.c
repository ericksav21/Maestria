#include "lista.h"

NODEPTR create_node(char *str) {
	NODEPTR res;
	res = (NODEPTR)malloc(sizeof(NODE));
	
	int len = (int)strlen(str);
	res->str = (char *)malloc((len + 1) * sizeof(char));
	strcpy(res->str, str);
	res->freq = 1;
	res->next = NULL;

	return res;
}

NODEPTR add_node(NODEPTR root, char *str) {
	//El nodo tiene al menos un elemento
	if(root) {
		NODEPTR nxt = root, lst = NULL;
		while(1) {
			int cmp = strcmp(nxt->str, str);
			if(cmp == 0) {
				nxt->freq++;
				break;
			}
			//La palabra es mayor que
			//la del nodo
			if(cmp < 0) {
				if(nxt->next) {
					lst = nxt;
					nxt = nxt->next;
				}
				//Llegamos al final de la lista
				//Insertamos
				else {
					nxt->next = create_node(str);
					break;
				}
			}
			//La palabra es menor. Insertamos
			else {
				if(!lst) {
					NODEPTR aux = create_node(str);
					aux->next = root;
					root = aux;
				}
				else {
					lst->next = create_node(str);
					lst->next->next = nxt;
				}
				break;
			}
		}
	}
	else {
		root = create_node(str);
	}

	return root;
}

void print_list(NODEPTR root) {
	if(root) {
		NODEPTR nxt = root;
		while(nxt) {
			printf("%s %d\n", nxt->str, nxt->freq);
			nxt = nxt->next;
		}
	}
}

void print_list_in_file(NODEPTR root, char *files_name) {
	FILE *out;
	out = fopen(files_name, "w");

	if(root) {
		NODEPTR nxt = root;
		while(nxt) {
			fprintf(out, "%s %d\n", nxt->str, nxt->freq);
			nxt = nxt->next;
		}
	}
	fclose(out);
}

NODEPTR free_node(NODEPTR node) {
	free(node->str);
	free(node);
	node = NULL;

	return node;
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