#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

#define MAXN 10005
#define INF 1000005

using namespace std;

typedef long long ll;

ll dp[105][MAXN], arr[MAXN];
int n, k;

ll solve(int k, int n) {
	for(int j = 0; j < n; j++) {
		dp[1][j] = (arr[j] - arr[0]) * (arr[j] - arr[0]);
	}
	for(int k_i = 2; k_i <= k; k_i++) {
		for(int i = k_i - 1; i <= n; i++) {
			for(int j = k_i; j <= i; j++) {
				ll power = (arr[j] - arr[i]) * (arr[j] - arr[i]);
				dp[k_i][j] = min(dp[k_i][j], dp[k_i - 1][j - 1] + power);
			}
		}
	}

	return dp[k][n];
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> k;
	for(int i = 0; i < n; i++) {
		cin >> arr[i];
	}
	memset(dp, INF, sizeof(dp));
	cout << solve(k, n - 1) << "\n";

	return 0;
}