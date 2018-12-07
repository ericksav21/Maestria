#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>

#define MAXN 105

using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t, u, v, di;
	int a, b, c;
	int shorcuts[MAXN];
	cin >> t;
	while(t--) {
		for(int i = 0; i < MAXN; i++) {
			shorcuts[i] = -1;
		}
		cin >> a >> b >> c;
		int players_pos[a];
		for(int i = 0; i < a; i++) {
			players_pos[i] = 1;
		}
		for(int i = 0; i < b; i++) {
			cin >> u >> v;
			shorcuts[u] = v;
		}
		int player_no = 0;
		bool is_ended = false;
		for(int i = 0; i < c; i++) {
			cin >> di;
			if(is_ended) continue;
			int pos_act = players_pos[player_no];
			pos_act += di;
			if(pos_act >= 100) {
				pos_act = 100;
				is_ended = true;
			}
			else if(shorcuts[pos_act] != -1) {
				pos_act = shorcuts[pos_act];
			}
			players_pos[player_no] = pos_act;
			if(pos_act == 100) is_ended = true;
			player_no = (player_no + 1) % a;
		}
		for(int i = 0; i < a; i++) {
			cout << "Position of player " << (i + 1) << " is " << players_pos[i] << ".\n";
		}
	}

	return 0;
}