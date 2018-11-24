#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <climits>

#define MAXN 10005
#define INF 1e18

using namespace std;

typedef long long ll;

ll dp[105][MAXN], arr[MAXN];
int n, k;

ll function(int k, int n, ll x) {
	ll power = (arr[k] - x) * (arr[k] - x);
	return dp[k - 1][n - 1] + power;
}

class LiChao {
private:
	ll tree[4 * MAXN];

public:
	LiChao();
	~LiChao();
	
	void add_f(int node, int lo, int hi, int val) {
		int mid = (lo + hi) / 2;
		int lc = 2 * node, rc = lc + 1;
		ll f_vl = function(val, lo);
		ll f_vm = function(val, mid);
		ll f_tl = function(tree[node], lo);
		ll f_tm = function(tree[node], mid);

		bool left = f_vl < f_tl;
		bool mid = f_vm < f_tm;

		if(mid) {
			swap(tree[node], val);
		}
		if(r - l == 1) {
			return;
		}
		if(left != mid) {
			add_f(lc, lo, mid, val);
		}
		else {
			add_f(rc, mid, hi, val);
		}
	}

	ll get(int node, int lo, int hi, int val) {
		int mid = (lo + hi) / 2;
		int lc = 2 * node, rc = lc + 1;

		if(r - l == 1) {
			return function(tree[node], val);
		}
		if(x < mid) {
			return min(function(tree[node], val), get(lc, lo, mid, val));
		}
		return min(function(tree[node], val), get(rc, mid, hi, val));
	}
};

ll solve(int k, int n) {
	for(int i = 1; i <= n; i++) {
		dp[1][i] = (arr[i] - arr[1]) * (arr[i] - arr[1]);
	}
	/*for(int i = 1; i <= k; i++) {
		dp[i][i] = 0;
	}*/

	ll power;
	for(int k_i = 2; k_i <= k; k_i++) {
		for(int i = k_i; i <= n; i++) {
			for(int j = k_i; j <= i; j++) {
				power = (arr[i] - arr[j]) * (arr[i] - arr[j]);
				dp[k_i][i] = min(dp[k_i][i], dp[k_i - 1][j - 1] + power);
			}
		}
	}

	return dp[k][n];
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> k;
	cout << n << " " << k << "\n";
	for(int i = 1; i <= n; i++) {
		cin >> arr[i];
	}
	for(int i = 0; i < 105; i++) {
		for(int j = 0; j < MAXN; j++) {
			dp[i][j] = INF;
		}
	}
	cout << solve(k, n) << "\n";

	return 0;
}