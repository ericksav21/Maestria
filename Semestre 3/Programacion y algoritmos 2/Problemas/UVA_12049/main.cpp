#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <utility>
#include <cstring>
#include <cmath>

using namespace std;

int n, m;
map<int, int> mp;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t, ai;
	cin >> t;
	while(t--) {
		mp.clear();
		cin >> n >> m;
		for(int i = 0; i < n; i++) {
			cin >> ai;
			mp[ai]++;
		}
		for(int i = 0; i < m; i++) {
			cin >> ai;
			mp[ai]--;
		}

		int cnt = 0;
		map<int, int>::iterator it;
		for(it = mp.begin(); it != mp.end(); it++) {
			if(it->second != 0) {
				cnt += abs(it->second);
			}
		}

		cout << cnt << "\n";
	}

	return 0;
}