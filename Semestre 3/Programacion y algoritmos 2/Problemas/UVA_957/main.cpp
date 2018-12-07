#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

#define MAXN 100005

using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int y, n, pi;
	vector<int> data;

	while(cin >> y) {
		cin >> n;
		data.clear();
		for(int i = 0; i < n; i++) {
			cin >> pi;
			data.push_back(pi);
		}
		int max_popes = INT_MIN, pos = -1, start, end;
		vector<int>::iterator it;
		for(int i = 0; i < n; i++) {
			pi = data[i];
			//Buscar cuál es el primer valor en el arreglo que excede
			//el límite de tiempo de Y
			int end_period = pi + y - 1;
			it = upper_bound(data.begin(), data.end(), end_period);
			pos = it - data.begin();
			//Por si se llega al final del arreglo
			if(data[pos] > end_period || pos == n) pos--;
			int act_popes = pos - i + 1;
			if(act_popes > max_popes) {
				max_popes = act_popes;
				start = pi;
				end = data[pos];
			}
		}

		cout << max_popes << " " << start << " " << end << "\n";
	}

	return 0;
}