#include <iostream>
#include <algorithm>
#include <climits>

using namespace std;

int get(int *data, int n) {
	for (int d = n - 1; d >= 0; --d)
        for (int a = 0; a < n; ++a) if (a != d)
            for (int b = a + 1; b < n; ++b) if (b != d)
                for (int c = b + 1; c < n; ++c) if (c != d)
                    if (data[d] == data[a] + data[b] + data[c])
                        return data[d];

    return INT_MAX;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n;
	while(cin >> n) {
		if(n == 0) break;

		int data[n];
		for(int i = 0; i < n; i++) {
			cin >> data[i];
		}
		sort(data, data + n);
		int koko = get(data, n);
		if(koko == INT_MAX) {
			cout << "no solution\n";
		}
		else {
			cout << koko << "\n";
		}
	}

	return 0;
}