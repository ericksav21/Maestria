#ifndef K_MEANS_H
#define K_MEANS_H

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <map>
#include <utility>

#include "point.hpp"

using namespace std;

class KMeans {
private:
	int no_clusters, iter;
	double threshold;
	vector<Point> points, centroids;
	vector<vector<Point> > comp;
public:
	KMeans(vector<Point> points, int no_clusters, int iterations, double threshold);
	~KMeans();
	vector<Point> get_points();
	int rand_in_range(int a, int b);
	double distance(Point a, Point b);
	void init_centroids();
	int nearest_centroid(Point p);
	void run();
	void print_centroids();
	void print_points();
};

#endif