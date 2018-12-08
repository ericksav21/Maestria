#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <cmath>

#define MAXN 1121

using namespace std;

int n, k;
bool sieve[MAXN];
vector<int> primes;
int dp[188][MAXN][15];

int solve(int id, int sum, int t) {
	if(sum == 0) {
		if(t == k) return 1;
		else return 0;
	}
	else if(t == k) {
		if(sum == 0) return 1;
		else return 0;
	}
	else if(id == 187) {
		if(sum == 0 && t == k) return 1;
		else return 0;
	}
	else if(sum - primes[id] < 0 || sum < 0 || t >= k || (t == k && sum > 0) || id > 187) {
		return 0;
	}
	else if(dp[id][sum][t] != -1) {
		return dp[id][sum][t];
	}
	else {
		dp[id][sum][t] = solve(id + 1, sum, t) + solve(id + 1, sum - primes[id], t + 1);
		return dp[id][sum][t];
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	memset(sieve, true, sizeof(sieve));
	int sq = (int)sqrt(MAXN);
	sieve[0] = sieve[1] = false;
	for(int i = 2; i <= sq; i++) {
		if(sieve[i]) {
			for(int j = i * i; j < MAXN; j += i) {
				sieve[j] = false;
			}
		}
	}

	for(int i = 2; i < MAXN; i++) {
		if(sieve[i]) {
			primes.push_back(i);
		}
	}

	while(cin >> n >> k) {
		if(n == 0 && k == 0) break;
		memset(dp, -1, sizeof(dp));

		cout << solve(0, n, 0) << "\n";
	}

	return 0;
}