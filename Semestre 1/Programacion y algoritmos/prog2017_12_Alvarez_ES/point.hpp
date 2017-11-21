#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <vector>

class Point {
private:
	double x, y;
	//Cluster ID
	int id;
public:
	Point();
	Point(double x, double y);
	Point(double x, double y, int id);
	~Point();
	double get_x();
	double get_y();
	int get_id();
	void set_x(double x);
	void set_y(double y);
	void set_id(int id);
};

#endif