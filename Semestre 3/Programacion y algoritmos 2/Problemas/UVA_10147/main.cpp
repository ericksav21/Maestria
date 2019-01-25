#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <utility>
#include <cmath>

#define MAXN 1000

using namespace std;

typedef struct Point {
  int x, y;
} POINT;

POINT createPoint(int x, int y) {
  POINT res;
  res.x = x;
  res.y = y;

  return res;
}

double distance(POINT a, POINT b) {
  double xx = (double)(b.x - a.x) * (double)(b.x - a.x);
  double yy = (double)(b.y - a.y) * (double)(b.y - a.y);

  return sqrt(xx + yy);
}

typedef struct Edge {
  int u, v;
  double d;

  bool operator<(const Edge &other) const {
    return d < other.d;
  }
} EDGE;

EDGE createEdge(int u, int v, double d) {
  EDGE res;
  res.u = u;
  res.v = v;
  res.d = d;

  return res;
}

int p[MAXN], noComponents;

void initDSU(int n) {
  noComponents = 0;
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
    noComponents++;
  }
}

bool sameComponent(int x, int y) {
  return find(x) == find(y);
}

vector<pair<int, int> > connected;

void getMST(vector<EDGE> &edges) {
  sort(edges.begin(), edges.end());
  for(int i = 0; i < edges.size(); i++) {
    int u = edges[i].u;
    int v = edges[i].v;

    if(!sameComponent(u, v)) {
      connected.push_back(make_pair(u, v));
      Union(u, v);
    }
  }
}

int main(int argc, char **argv) {
  int t, n, m, u, v;
  double d;
  vector<POINT> towns;
  vector<EDGE> edges;

  cin >> t;
  bool isFirst = true;
  while(t--) {
    towns.clear();
    edges.clear();
    connected.clear();

    if(!isFirst) {
      cout << "\n";
    }
    isFirst = false;

    cin >> n;
    initDSU(MAXN);
    for(int i = 0; i < n; i++) {
      cin >> u >> v;
      POINT a = createPoint(u, v);
      towns.push_back(a);
    }

    for(int i = 1; i < n; i++) {
      for(int j = i + 1; j <= n; j++) {
        double d = distance(towns[i - 1], towns[j - 1]);
        EDGE e = createEdge(i, j, d);
        edges.push_back(e);
      }
    }

    cin >> m;
    for(int i = 0; i < m; i++) {
      cin >> u >> v;
      Union(u, v);
    }

    if(noComponents == n - 1) {
      cout << "No new highways need\n";
    }
    else {
      getMST(edges);
      sort(connected.begin(), connected.end());
      for(int i = 0; i < connected.size(); i++) {
        cout << connected[i].first << " " << connected[i].second << "\n";
      }
    }
  }

  return 0;
}