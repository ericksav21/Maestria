#include "kmeans.hpp"

Point::Point() {
	x = y = 0.0;
}

Point::Point(double x, double y) {
	this->x = x;
	this->y = y;
}

Point::~Point() {}

double Point::get_x() {
	return x;
}

double Point::get_y() {
	return y;
}

void Point::set_x(double x) {
	this->x = x;
}

void Point::set_y(double y) {
	this->y = y;
}

//Kmeans
KMeans::KMeans(vector<Point> points, int no_clusters) {
	this->points = points;
	this->no_clusters = no_clusters;
	//this->centroids.resize(no_clusters);
}

KMeans::~KMeans() {}

int KMeans::rand_in_range(int a, int b) {
	return rand() % (b - a + 1) + a;
}

double KMeans::distance(Point a, Point b) {
	return sqrt(pow(a.get_x() - b.get_x(), 2) + pow(a.get_y() - b.get_y(), 2));
}

void KMeans::init_centroids() {
	//Hay que recorrer todos los puntos para determinar las fronteras en X y en Y
	double minX = INF, minY = INF, maxX = -INF, maxY = -INF;

	for(int i = 0; i < points.size(); i++) {
		Point act = points[i];
		if(act.get_x() < minX) {
			minX = act.get_x();
		}
		if(act.get_y() < minY) {
			minY = act.get_y();
		}
		if(act.get_x() > maxX) {
			maxX = act.get_x();
		}
		if(act.get_y() > maxY) {
			maxY = act.get_y();
		}
	}

	int k = 0;
	while(k < no_clusters) {
		double auxX = (double)rand_in_range(minX, maxX);
		double auxY = (double)rand_in_range(minY, maxY);
		bool is_valid = true;

		for(int j = 0; j < centroids.size(); j++) {
			if(centroids[j].get_x() == auxX || centroids[j].get_y() == auxY) {
				is_valid = false;
				break;
			}
		}
		if(!is_valid)
			continue;

		Point res(auxX, auxY);
		centroids.push_back(res);
		k++;
	}
}