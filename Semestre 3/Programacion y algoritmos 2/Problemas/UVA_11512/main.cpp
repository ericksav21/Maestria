#include <bits/stdc++.h>

#define ALPHABET_SIZE 4
#define MAXN 1005

using namespace std;

char s_res[MAXN], sc_aux[MAXN];
int max_dp, max_sz;

typedef struct trieNode {
	trieNode *children[ALPHABET_SIZE];
	int end_strings;
} NODE;

int get_index(char c) {
	if(c == 'A') return 0;
	else if(c == 'C') return 1;
	else if(c == 'G') return 2;
	else return 3;
}

char get_letter(int idx) {
	if(idx == 0) return 'A';
	else if(idx == 1) return 'C';
	else if(idx == 2) return 'G';
	else return 'T';
}

NODE *create_node() {
	NODE *res = new NODE;
	res->end_strings = 0;

	for(int i = 0; i < ALPHABET_SIZE; i++) {
		res->children[i] = NULL;
	}

	return res;
}

void insert(NODE *root, char *s, int a, int n) {
	NODE *p_crawl = root;
	for(int i = a; i < n; i++) {
		int index = get_index(s[i]);
		if(!p_crawl->children[index]) {
			p_crawl->children[index] = create_node();
		}
		p_crawl = p_crawl->children[index];
		p_crawl->end_strings++;
	}
}

void free_all(NODE *root) {
	if(!root) return;
	for(int i = 0; i < ALPHABET_SIZE; i++) {
		if(root->children[i]) {
			free_all(root->children[i]);
		}
	}
	delete root;
}

void dfs(NODE *root, int c) {
	if(root->end_strings >= 2) {
		if(c > max_dp) {
			max_dp = c;
			max_sz = root->end_strings;
			for(int i = 0; i < c; i++) {
				s_res[i] = sc_aux[i];
			}
		}
	}
	for(int i = 0; i < ALPHABET_SIZE; i++) {
		if(root->children[i]) {
			sc_aux[c] = get_letter(i);
			dfs(root->children[i], c + 1);
		}
	}
}

int main() {
	int n, sz;
	char s[MAXN], s_aux[MAXN];
	NODE *root;
	scanf("%d", &n);

	while(n--) {
		root = create_node();
		scanf("%s", s);
		sz = strlen(s);
		for(int i = 0; i < sz; i++) {
			insert(root, s, i, sz);
		}
		max_dp = INT_MIN;
		max_sz = 0;
		memset(s_res, 0, sizeof(s_res));
		dfs(root, 0);

		if(max_dp == INT_MIN) {
			printf("No repetitions found!\n");
		}
		else {
			for(int i = 0; i < MAXN; i++) {
				if(s_res[i] == 0) break;
				printf("%c", s_res[i]);
			}
			printf(" %d\n", max_sz);
		}
		free_all(root);
		root = NULL;
	}
}