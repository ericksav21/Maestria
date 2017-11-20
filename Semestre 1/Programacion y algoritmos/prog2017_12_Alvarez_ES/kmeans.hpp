#ifndef K_MEANS_H
#define K_MEANS_H

#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <vector>

#define INF 1000000

using namespace std;

class Point {
private:
	double x, y;
public:
	Point();
	Point(double x, double y);
	~Point();
	double get_x();
	double get_y();
	void set_x(double x);
	void set_y(double y);
};

class KMeans {
private:
	int no_clusters;
	vector<Point> points, centroids;
public:
	KMeans(vector<Point> points, int no_clusters);
	~KMeans();
	int rand_in_range(int a, int b);
	double distance(Point a, Point b);
	void init_centroids();
};

#endif