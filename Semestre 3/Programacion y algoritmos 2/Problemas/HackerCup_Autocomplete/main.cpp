#include <bits/stdc++.h>

#define ALPHABET_SIZE 26
#define MAXN 1000005

using namespace std;

typedef struct trieNode {
	trieNode *children[ALPHABET_SIZE];
} NODE;

NODE *get_node() {
	NODE *res = new NODE;
	for(int i = 0; i < ALPHABET_SIZE; i++) {
		res->children[i] = NULL;
	}

	return res;
}

int insert(NODE *root, string &s) {
	NODE *nt = root;
	int res = 0;
	for(int i = 0; i < s.size(); i++) {
		int l = s[i] - 'a';
		if(nt->children[l]) res++;
		else nt->children[l] = get_node();
		nt = nt->children[l];
	}
	if(res == s.size()) return res;
	return res + 1;
}

void delete_all(NODE *root) {
	if(!root) return;
	for(int i = 0; i < ALPHABET_SIZE; i++) {
		delete_all(root->children[i]);
	}
	delete root;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t, n, cnt;
	string s;
	NODE *root = NULL;

	cin >> t;
	for(int i = 1; i <= t; i++) {
		cin >> n;
		cnt = 0;
		root = get_node();
		for(int j = 0; j < n; j++) {
			cin >> s;
			int aux = insert(root, s);
			cnt += aux;
		}
		cout << "Case #" << i << ": " << cnt << "\n";
		delete_all(root);
		root = NULL;
	}

	return 0;
}