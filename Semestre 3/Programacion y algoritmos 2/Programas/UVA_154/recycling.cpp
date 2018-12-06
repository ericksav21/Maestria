#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <climits>

#define MAXN 105

using namespace std;

vector<char> table[MAXN];

int get_id(char c) {
	if(c == 'r') return 0;
	else if(c == 'o') return 1;
	else if(c == 'y') return 2;
	else if(c == 'g') return 3;
	else return 4;
}

vector<char> process_string(string &str) {
	int j = 2;
	vector<char> res(5);
	for(int i = 0; i < 5; i++) {
		res[get_id(str[j - 2])] = str[j];
		j += 4;
	}

	return res;
}

int main(int argc, char **argv) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	string str;
	bool flag = true;
	while(true) {
		for(int i = 0; i < MAXN; i++) {
			table[i].clear();
		}
		int i = 0;
		while(true) {
			getline(cin, str);
			if(str[0] == 'e') {
				break;
			}
			else if(str[0] == '#') {
				flag = false;
				break;
			}
			else {
				table[i] = process_string(str);
				i++;
			}
		}
		if(!flag) break;
		int min_diff = INT_MAX, sol = -1;
		for(int j = 0; j < i; j++) {
			int diff_sum = 0;
			for(int k = 0; k < i; k++) {
				if(j == k) continue;
				int differences = 0;
				for(int l = 0; l < 5; l++) {
					if(table[j][l] != table[k][l]) differences++;
				}
				diff_sum += differences;
			}
			if(diff_sum < min_diff) {
				min_diff = diff_sum;
				sol = j;
			}
		}
		cout << (sol + 1) << "\n";
	}

	return 0;
}