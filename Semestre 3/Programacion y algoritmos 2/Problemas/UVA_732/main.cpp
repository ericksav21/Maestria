#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <string>
#include <cstring>

using namespace std;

string org, dest;

void bt(string act, string res, string stack, string sol, int n) {
	if(n == org.size() * 2) {
		if(res == dest) {
			cout << sol << "\n";
			return;
		}
	}

	if(act.size()) {
		// Se puede hacer push
		string new_sol = sol + (n == 0 ? "i" : " i");
		bt(act.substr(1, act.size() - 1), res, stack + act[0], new_sol, n + 1);
	}

	bool flag = true;
	if(res.size() > 0) {
		for(int i = 0; i < res.size(); i++) {
			if(res[i] != dest[i]) {
				flag = false;
				break;
			}
		}
	}
	if(stack.size() && flag) {
		// Se puede hacer pop
		string new_sol = sol + (n == 0 ? "o" : " o");
		bt(act, res + stack[stack.size() - 1], stack.substr(0, stack.size() - 1), new_sol, n + 1);
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	while(cin >> org >> dest) {
		int sz1 = org.size();
		int sz2 = dest.size();

		cout << "[\n";
		if(sz1 != sz2) {
			cout << "]\n";
			continue;
		}

		bt(org, "", "", "", 0);
		cout << "]\n";
	}

	return 0;
}