#include <bits/stdc++.h>

using namespace std;

bool is_palindrome(string &str) {
	int i = 0, j = str.size() - 1;
	while(i < j) {
		if(str[i] != str[j]) {
			return false;
		}
		i++; j--;
	}

	return true;
}

string filter(string &str) {
	string res = "";
	for(int i = 0; i < str.size(); i++) {
		if(isalpha(str[i])) {
			res += str[i];
		}
	}

	return res;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t;
	string str, pal;
	cin >> t;
	cin.ignore();
	for(int i = 1; i <= t; i++) {
		cout << "Case #" << i << ":\n";
		getline(cin, str);
		pal = filter(str);
		int sz = pal.size();
		int sq = (int)sqrt(sz);

		if(sz == 1) {
			cout << "1\n";
		}
		else if(!is_palindrome(pal) || sq * sq != sz) {
			cout << "No magic :(\n";
		}
		else {
			cout << sq << "\n";
		}
	}

	return 0;
}