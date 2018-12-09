#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>

using namespace std;

typedef long long LL;

vector<int> p;

void initDSU(int n) {
  p.clear();
  for(int i = 0; i < n; i++) {
    p.push_back(i);
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

LL getMSTcost(vector<pair<LL, pair<int, int> > > &edges, LL cost) {
  LL res = cost;
  sort(edges.begin(), edges.end());
  for(int i = edges.size() - 1; i >= 0; i--) {
    int u = edges[i].second.first;
    int v = edges[i].second.second;
    LL w = edges[i].first;
    if(!sameComponent(u, v)) {
      res -= w;
      Union(u, v);
    }
  }

  return res;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int t, n, m, u, v;
  LL w, cost;
  vector<pair<LL, pair<int, int> > > edges;

  cin >> t;
  while(t--) {
    cin >> n >> m;
    edges.clear();
    initDSU(n + 5);
    cost = 0L;
    for(int i = 0; i < m; i++) {
      cin >> u >> v >> w;
      edges.push_back(make_pair(w, make_pair(u, v)));
      cost += w;
    }
    cout << getMSTcost(edges, cost) << "\n";
  }

  return 0;
}