#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>

#define MAXN 1000010
#define pb push_back
#define mp make_pair

typedef long long LL;

using namespace std;

int p[MAXN];

void initDSU(int n) {
  for(int i = 0; i < n; i++) {
    p[i] = i;
  }
}

int find(int x) {
  if(p[x] == x) {
    return x;
  }

  return p[x] = find(p[x]);
}

void Union(int x, int y) {
  int rx = find(x);
  int ry = find(y);

  if(rx != ry) {
    p[rx] = ry;
  }
}

bool sameComponent(int x, int y) {
  return find(x) == find(y);
}

LL getMSTcost(vector<pair<LL, pair<int, int> > > &edges) {
  sort(edges.begin(), edges.end());
  LL res = 0L;

  for(int i = 0; i < edges.size(); i++) {
    int u = edges[i].second.first;
    int v = edges[i].second.second;
    LL w = edges[i].first;

    if(!sameComponent(u, v)) {
      res += w;
      Union(u, v);
    }
  }

  return res;
}

int main(int argc, char **argv) {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int n, m, u, v;
  LL w, cost1;
  vector<pair<LL, pair<int, int> > > edges;

  bool isFirst = true;
  while(cin >> n) {
    if(!isFirst) {
      cout << "\n";
    }
    isFirst = false;
    initDSU(n + 1);
    edges.clear();
    cost1 = 0L;

    for(int i = 0; i < n - 1; i++) {
      cin >> u >> v >> w;
      cost1 += w;
    }
    cin >> m;
    for(int i = 0; i < m; i++) {
      cin >> u >> v >> w;
      edges.pb(mp(w, mp(u, v)));
    }
    cin >> m;
    for(int i = 0; i < m; i++) {
      cin >> u >> v >> w;
      edges.pb(mp(w, mp(u, v)));
    }
    cout << cost1 << "\n";
    cout << getMSTcost(edges) << "\n";
  }

  return 0;
}
