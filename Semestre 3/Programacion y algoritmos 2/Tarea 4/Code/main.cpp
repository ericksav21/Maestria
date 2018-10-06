#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <cstring>
#include <cmath>
#include <climits>

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

	~Node() {}
};

class Quadtree {
private:
	Point top_left, bot_right;
	Node *n;
	Quadtree *top_left_tree;
	Quadtree *top_right_tree;
	Quadtree *bot_left_tree;
	Quadtree *bot_right_tree;

	bool clean_quadnode(Quadtree *quad);

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

	~Quadtree() {
		if(n) {
			delete n;
		}
	}
	
	void ask_quad();
	void insert(Node*);
	Node *search(Point);
	void search_area(Point, Point, vector<Point>&);
	void delete_point(Point);
	bool is_boundary(Point);
};

void Quadtree::ask_quad() {
	cout << top_left_tree << "\n";
	if(top_left_tree) {
		top_left_tree->ask_quad();
	}
}

bool Quadtree::is_boundary(Point p) {
	return (p.x >= top_left.x && p.x <= bot_right.x &&
		p.y >= top_left.y && p.y <= bot_right.y);
}

void Quadtree::insert(Node *node) {
	if(!node) return;

	if(!is_boundary(node->pos)) return;

	if(abs(top_left.x - bot_right.x) <= 1
		&& abs(top_left.y - bot_right.y) <= 1) {
		if(!n) n = new Node(node->pos, node->data);
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

void Quadtree::search_area(Point _top, Point _bot, vector<Point> &points) {
	//No hay intersección
	if(_top.x > bot_right.x || top_left.x > _bot.x ||
		_top.y > bot_right.y || top_left.y > _bot.y) {
		return;
	}
	else if(top_left.x >= _top.x && bot_right.x <= _bot.x &&
		top_left.y >= _top.y && bot_right.y <= _bot.y) {

		//Completamente adentro
		if(n != NULL) {
			points.push_back(n->pos);
			return;
		}
	}
	//Parcialmente dentro
	if(top_left_tree) top_left_tree->search_area(_top, _bot, points);
	if(top_right_tree) top_right_tree->search_area(_top, _bot, points);
	if(bot_left_tree) bot_left_tree->search_area(_top, _bot, points);
	if(bot_right_tree) bot_right_tree->search_area(_top, _bot, points);
}

bool Quadtree::clean_quadnode(Quadtree *quad) {
	int cnt = 0;
	if(quad->top_left_tree) cnt++;
	if(quad->top_right_tree) cnt++;
	if(quad->bot_left_tree) cnt++;
	if(quad->bot_right_tree) cnt++;

	return (cnt > 0);
}

void Quadtree::delete_point(Point p) {
	if(!is_boundary(p)) return;

	if(n != NULL) {
		delete n;
		n = NULL;
		return;
	}

	if((top_left.x + bot_right.x) / 2 >= p.x) {
		if((top_left.y + bot_right.y) / 2 >= p.y) {
			if(!top_left_tree) {
				return;
			}
			top_left_tree->delete_point(p);
			if(!clean_quadnode(top_left_tree)) {
				delete top_left_tree;
				top_left_tree = NULL;
			}
		}
		else {
			if(!bot_left_tree) {
				return;
			}
			bot_left_tree->delete_point(p);
			if(!clean_quadnode(bot_left_tree)) {
				delete bot_left_tree;
				bot_left_tree = NULL;
			}
		}
	}
	else {
		if((top_left.y + bot_right.y) / 2 >= p.y) {
			if(!top_right_tree) {
				return;
			}
			top_right_tree->delete_point(p);
			if(!clean_quadnode(top_right_tree)) {
				delete top_right_tree;
				top_right_tree = NULL;
			}
		}
		else {
			if(!bot_right_tree) {
				return;
			}
			bot_right_tree->delete_point(p);
			if(!clean_quadnode(bot_right_tree)) {
				delete bot_right_tree;
				bot_right_tree = NULL;
			}
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

		float min_d = (float)INT_MAX;
		int id_act, lst_sc = 0;
		cout << (int)ceil(min_d) << "\n";
		for(id_act = 1; id_act < points.size(); id_act++) {
			while(true) {
				break;
			}
		}
	}

	return 0;
}