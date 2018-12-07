#include <iostream>
#include <cstring>

using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	string up, down, msg;
	getline(cin, down);
	getline(cin, up);
	while(cin >> msg) {
		int n = msg.size(), dir = 0;
		for(int i = 0; i < n; i += 5) {
			int val = 0;
			if(msg[i] == '1') val += 16;
			if(msg[i + 1] == '1') val += 8;
			if(msg[i + 2] == '1') val += 4;
			if(msg[i + 3] == '1') val += 2;
			if(msg[i + 4] == '1') val++;
			if(val == 31) {
				dir = 1;
				continue;
			}
			else if(val == 27) {
				dir = 0;
				continue;
			}
			if(!dir) {
				cout << down[val];
			}
			else {
				cout << up[val];
			}
		}
		cout << "\n";
	}

	return 0;
}