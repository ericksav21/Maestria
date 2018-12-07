#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define MAXN 30005

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;

typedef tree<
ll,
null_type,
less<int>,
rb_tree_tag,
tree_order_statistics_node_update>
ordered_set;

ll aa[MAXN];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t, m, n, id, k;
	cin >> t;
	for(int i = 0; i < t; i++) {
		if(i > 0) {
			cout << "\n";
		}
		ordered_set st;
		cin >> m >> n;
		for(int i = 1; i <= m; i++) {
			cin >> aa[i];
		}
		int p = 0, cur;
		for(int i = 1; i <= n; i++) {
			cin >> cur;
			while(p < cur) {
				st.insert(aa[++p]);
			}
			cout << *st.find_by_order(i - 1) << "\n";
		}
	}

	return 0;
}