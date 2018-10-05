#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <cstring>
#include <cmath>

#define MAXN 10004
#define LIM 1000
#define pb push_back
#define mp make_pair
#define fst first
#define snd second

using namespace std;

struct Point {
	int x, y;

	Point() {
		x = y = 0;
	}

	Point(int _x, int _y) {
		x = _x;
		y = _y;
	}

	~Point() {}
};

struct Node {
	Point pos;
	int data;

	Node() {
		data = 0;
	}

	Node(Point _pos, int _data) {
		pos = _pos;
		data = _data;
	}
};

class Quadtree {
private:
	Point top_left, bot_right;
	Node *n;
	Quadtree *top_left_tree;
	Quadtree *top_right_tree;
	Quadtree *bot_left_tree;
	Quadtree *bot_right_tree;

public:
	Quadtree() {
		top_left = Point(0, 0);
		bot_right = Point(0, 0);
		n = NULL;
		top_left_tree = NULL;
		top_right_tree = NULL;
		bot_left_tree = NULL;
		bot_right_tree = NULL;
	}

	Quadtree(Point _top, Point _bot) {
		top_left = _top;
		bot_right = _bot;
		n = NULL;
		top_left_tree = NULL;
		top_right_tree = NULL;
		bot_left_tree = NULL;
		bot_right_tree = NULL;
	}

	~Quadtree() {}
	
	void insert(Node*);
	Node *search(Point);
	bool is_boundary(Point);
};

bool Quadtree::is_boundary(Point p) {
	return (p.x >= top_left.x && p.x <= bot_right.x &&
		p.y >= top_left.y && p.y <= bot_right.y);
}

void Quadtree::insert(Node *node) {
	if(!node) return;

	if(!is_boundary(node->pos)) return;

	if(abs(top_left.x - bot_right.x) <= 1
		&& abs(top_left.y - bot_right.y) <= 1) {
		if(!n) n = node;
		return;
	}

	if((top_left.x + bot_right.x) / 2 >= node->pos.x) {
		if((top_left.y + bot_right.y) / 2 >= node->pos.y) {
			if(!top_left_tree) {
				top_left_tree = new Quadtree(
					Point(top_left.x, top_left.y),
					Point((top_left.x + bot_right.x) / 2, (top_left.y + bot_right.y) / 2)
				);
			}
			top_left_tree->insert(node);
		}
		else {
			if(!bot_left_tree) {
				bot_left_tree = new Quadtree(
					Point(top_left.x, (top_left.y + bot_right.y) / 2),
					Point((top_left.x + bot_right.x) / 2, bot_right.y)
				);
			}
			bot_left_tree->insert(node);
		}
	}
	else {
		if((top_left.y + bot_right.y) / 2 >= node->pos.y) {
			if(!top_right_tree) {
				top_right_tree = new Quadtree(
					Point((top_left.x + bot_right.x) / 2, top_left.y),
					Point(bot_right.x, (top_left.y + bot_right.y) / 2)
				);
			}
			top_right_tree->insert(node);
		}
		else {
			if(!bot_right_tree) {
				bot_right_tree = new Quadtree(
					Point((top_left.x + bot_right.x) / 2, (top_left.y + bot_right.y) / 2),
					Point(bot_right.x, bot_right.y)
				);
			}
			bot_right_tree->insert(node);
		}
	}
}

Node* Quadtree::search(Point p) {
	if(!is_boundary(p)) return NULL;

	if(n != NULL) return n;

	if((top_left.x + bot_right.x) / 2 >= p.x) {
		if((top_left.y + bot_right.y) / 2 >= p.y) {
			if(!top_left_tree) {
				return NULL;
			}
			return top_left_tree->search(p);
		}
		else {
			if(!bot_left_tree) {
				return NULL;
			}
			return bot_left_tree->search(p);
		}
	}
	else {
		if((top_left.y + bot_right.y) / 2 >= p.y) {
			if(!top_right_tree) {
				return NULL;
			}
			return top_right_tree->search(p);
		}
		else {
			if(!bot_right_tree) {
				return NULL;
			}
			return bot_right_tree->search(p);
		}
	}
}

double dist(Point a, Point b) {
	double aa = (b.x - a.x) * (b.x - a.x);
	double bb = (b.y - a.y) * (b.y - a.y);
	return sqrt(bb + aa);
}

vector<pair<int, pair<int, int> > > points;

int main() {
	int n, x, y, z;
	Quadtree qt(Point(-LIM, -LIM), Point(LIM, LIM));
	while(cin >> n && n) {
		points.clear();
		for(int i = 0; i < n; i++) {
			cin >> x >> y >> z;
			points.pb(mp(x, mp(y, z)));
		}
		sort(points.begin(), points.end());

		for(int i = 0; i < n; i++) {
			cout << points[i].fst << " " << points[i].snd.fst << " " << points[i].snd.snd << "\n";
		}
	}

	return 0;
}