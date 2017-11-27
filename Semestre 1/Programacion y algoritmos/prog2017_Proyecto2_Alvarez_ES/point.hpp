#ifndef POINT_H
#define POINT_H

using namespace std;

class Point {
private:
	int i, j;
public:
	Point();
	Point(int i, int j);
	~Point();
	int get_i();
	int get_j();
	void set_i(int i);
	void set_j(int j);
};

#endif