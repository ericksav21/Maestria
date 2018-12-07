#include <iostream>
#include <string>

using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	string s, s1;
	while(cin >> s) {
		if(s == "END") break;
		int i = 1, lst;
		while(true) {
			int no_digits = s.size();
			s1 = to_string(no_digits);
			if(s1 == s) {
				break;
			}
			s = s1;
			i++;
		}

		cout << i << "\n";
	}

	return 0;
}