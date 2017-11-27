#ifndef POINT_H
#define POINT_H

#include <cmath>

using namespace std;

class Point {
private:
	int i, j;
public:
	Point();
	Point(int i, int j);
	~Point();
	double distance(Point o) const;
	double distance() const;
	int get_i();
	int get_j();
	void set_i(int i);
	void set_j(int j);
};

class PointComparator {
	bool operator()(const Point &a, const Point &b) {
		return a.distance() < b.distance();
	}
};

#endif