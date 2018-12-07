#include <iostream>
#include <cstring>
#include <map>

#define MAXN 35
#define INF 10000

using namespace std;

int graph[MAXN][MAXN];
int dist[MAXN][MAXN];
map<string, int> nodeNames;

void floydWarshall(int n) {
	for(int i = 0; i < n; i++)
		dist[i][i] = 0;

	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++) {
			if(i == j)
				continue;
			dist[i][j] = graph[i][j];
		}

	for(int k = 0; k < n; k++)
		for(int i = 0; i < n; i++)
			for(int j = 0; j < n; j++)
				if(dist[i][j] > dist[i][k] + dist[k][j])
					dist[i][j] = dist[i][k] + dist[k][j];
}

int main() {
	int t, v, e, q, sz;
	cin >> t;

	cout << "SHIPPING ROUTES OUTPUT\n\n";

	for(int k = 1; k <= t; k++) {
		cin >> v >> e >> q;

		memset(graph, INF, sizeof(graph));
		memset(dist, INF, sizeof(dist));
		nodeNames.clear();

		int c = 0;
		string nodeA, nodeB;
		for(int i = 0; i < v; i++) {
			cin >> nodeA;
			nodeNames[nodeA] = c++;
		}
		for(int i = 0; i < e; i++) {
			cin >> nodeA >> nodeB;
			int ori = nodeNames[nodeA];
			int dest = nodeNames[nodeB];

			graph[ori][dest] = 1;
			graph[dest][ori] = 1;
		}

		floydWarshall(v);
		cout << "DATA SET  " << k << "\n\n";

		for(int i = 0; i < q; i++) {
			cin >> sz >> nodeA >> nodeB;
			int ori = nodeNames[nodeA];
			int dest = nodeNames[nodeB];

			if(dist[ori][dest] >= INF)
				cout << "NO SHIPMENT POSSIBLE\n";
			else
				cout << "$" << (dist[ori][dest] * sz * 100) << "\n";
		}

		cout << "\n";
	}

	cout << "END OF OUTPUT\n";

	return 0;
}