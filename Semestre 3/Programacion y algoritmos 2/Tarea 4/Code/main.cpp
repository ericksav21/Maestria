#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
#include <utility>
#include <cstring>
#include <cmath>
#include <climits>

#define MAXN 10004
#define LIM 1010
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

	bool operator==(const Point &other) const {
		return x == other.x && y == other.y;
	}

	~Point() {}
};

bool operator<(const Point &left, const Point &right) {
	return left.x < right.x;
}

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

	void set_boundaries(Point _top, Point _bot) {
		top_left = _top;
		bot_right = _bot;
	}
	
	void ask_quad();
	void insert(Node*);
	Node *search(Point);
	void search_area(Point&, Point&, vector<pair<int, pair<int, int> > >&);
	void delete_point(Point&);
	bool is_boundary(Point&);
	void clear_tree();
};

/*
	Borrado en forma recursiva del QuadTree
*/
void Quadtree::clear_tree() {
	if(top_left_tree) top_left_tree->clear_tree();
	if(top_right_tree) top_right_tree->clear_tree();
	if(bot_left_tree) bot_left_tree->clear_tree();
	if(bot_right_tree) bot_right_tree->clear_tree();
	delete top_left_tree;
	delete top_right_tree;
	delete bot_left_tree;
	delete bot_right_tree;
	top_left_tree = top_right_tree = bot_left_tree = bot_right_tree = NULL;
	if(n) {
		delete n;
		n = NULL;
	}
	top_left = Point(0, 0);
	bot_right = Point(0, 0);
}

bool Quadtree::is_boundary(Point &p) {
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

/*
	La búsqueda se hace como en un SegmentTree
*/
void Quadtree::search_area(Point &_top, Point &_bot, vector<pair<int, pair<int, int> > > &points) {
	//No hay intersección
	if(_top.x > bot_right.x || top_left.x > _bot.x ||
		_top.y > bot_right.y || top_left.y > _bot.y) {
		return;
	}
	else if(top_left.x >= _top.x && bot_right.x <= _bot.x &&
		top_left.y >= _top.y && bot_right.y <= _bot.y) {

		//Completamente adentro
		if(n != NULL) {
			//X, Y, Z en ese orden
			points.pb(mp(n->data, mp(n->pos.x, n->pos.y)));
			//points.push_back(n->pos);
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

void Quadtree::delete_point(Point &p) {
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

int dist(int x1, int y1, int z1, int x2, int y2, int z2) {
	int aa = ((x2 - x1) * (x2 - x1));
	int bb = ((y2 - y1) * (y2 - y1));
	int cc = ((z2 - z1) * (z2 - z1));

	return (aa + bb + cc);
}

vector<pair<int, pair<int, int> > > points;
pair<int, pair<int, int> > pd1, pd2;
int id_p1, id_p2;
int min_d;

void get_min_dist(Quadtree &qt) {
	id_p1 = 0; id_p2 = 1;
	int id_act, id_suc = 0;
	Node nn(Point(points[0].snd.fst, points[0].snd.snd), points[0].fst);
	Node mm(Point(points[1].snd.fst, points[1].snd.snd), points[1].fst);
	min_d = dist(points[0].fst, points[0].snd.fst, points[0].snd.snd,
				points[1].fst, points[1].snd.fst, points[1].snd.snd);
	qt.insert(&nn);
	qt.insert(&mm);
	vector<pair<int, pair<int, int> > > suc_points;
	int xi, yi, zi, x_ant, y_ant, z_ant;

	for(id_act = 2; id_act < points.size(); id_act++) {
		xi = points[id_act].fst; yi = points[id_act].snd.fst; zi = points[id_act].snd.snd;
		while(true) {
			//Obtener un punto anterior
			x_ant = points[id_suc].fst; y_ant = points[id_suc].snd.fst; z_ant = points[id_suc].snd.snd;
			if(x_ant < xi - min_d) {
				Point p_del(y_ant, z_ant);
				qt.delete_point(p_del);
				id_suc++;
			}
			else {
				break;
			}
		}
		suc_points.clear();
		Point _top(yi - min_d, zi - min_d);
		Point _bot(yi + min_d, zi + min_d);
		qt.search_area(_top, _bot, suc_points);

		for(int i = 0; i < suc_points.size(); i++) {
			pair<int, pair<int, int> > p_suc_act = suc_points[i];
			x_ant = p_suc_act.fst; y_ant = p_suc_act.snd.fst; z_ant = p_suc_act.snd.snd;
			int act_d = dist(xi, yi, zi, x_ant, y_ant, z_ant);
			if(act_d < min_d) {
				min_d = act_d;
				id_p1 = id_act;
				for(int j = 0; j < points.size(); j++) {
					if(x_ant == points[j].fst && y_ant == points[j].snd.fst && z_ant == points[j].snd.snd) {
						id_p2 = j;
						break;
					}
				}
			}
		}
		nn = Node(Point(yi, zi), xi);
		qt.insert(&nn);
	}
}

int main() {
	int n, x, y, z;
	double res;
	Quadtree qt(Point(-LIM, -LIM), Point(LIM, LIM));

	while(scanf("%d", &n) && n) {
		points.clear();
		res = 0.0;
		priority_queue<int, vector<int>, greater<int> > pq;
		for(int idx = 0; idx < n; idx++) {
			scanf("%d %d %d", &x, &y, &z);
			points.pb(mp(x, mp(y, z)));
		}
		sort(points.begin(), points.end());

		int i = 0;
		while(i < 6 && points.size() > 1) {
			get_min_dist(qt);
			pq.push(min_d);

			for(int j = 0; j < points.size(); j++) {
				if(j == id_p2 || j == id_p1) continue;
				pair<int, pair<int, int> > p_act = points[j];
				x = p_act.fst; y = p_act.snd.fst; z = p_act.snd.snd;
				int act_d = dist(points[id_p1].fst, points[id_p1].snd.fst, points[id_p1].snd.snd, x, y, z);
				pq.push(act_d);
			}
			points.erase(points.begin() + id_p1);
			qt.clear_tree();
			qt.set_boundaries(Point(-LIM, -LIM), Point(LIM, LIM));
			i++;
		}

		for(int i = 0; i < 6; i++) {
			res += sqrt(pq.top()); pq.pop();
		}

		printf("%.2f\n", res);
	}

	return 0;
}