#include <bits/stdc++.h>

#define INF 1000000

using namespace std;

int dp[20100], coin[110];

int main() {
    int t, n;
    cin >> t;
    while(t--) {
        int money;
        cin >> money >> n;
        for(int i = 0; i < n; i++) {
            cin >> coin[i];
        }
        memset(dp, INF, sizeof(dp));
        dp[0] = 0;
        for(int i = 0; i < n; i++) {
            for(int j = money; j > -1; j--) {
                dp[j + coin[i]] = min(dp[j] + 1, dp[j + coin[i]]);
            }
        }

        for(int i = money; i <= 30100; i++) {
            if(dp[i] < 10000) {
                cout << i << " " << dp[i] << "\n";
                break;
            }
        }
    }
}