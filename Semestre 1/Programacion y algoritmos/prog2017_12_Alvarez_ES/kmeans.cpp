#include "kmeans.hpp"

//Kmeans
KMeans::KMeans(vector<Point> points, int no_clusters, int iterations) {
	this->points = points;
	this->no_clusters = no_clusters;
	this->iter = iterations;

	init_centroids();
}

KMeans::~KMeans() {}

vector<Point> KMeans::get_points() {
	return points;
}

int KMeans::rand_in_range(int a, int b) {
	return rand() % (b - a + 1) + a;
}

double KMeans::distance(Point a, Point b) {
	return sqrt(pow(a.get_x() - b.get_x(), 2) + pow(a.get_y() - b.get_y(), 2));
}

void KMeans::init_centroids() {
	centroids.clear();
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

	minX = floor(minX); minY = floor(minY);
	maxX = ceil(maxX); maxY = ceil(maxY);
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

		Point res(auxX, auxY, k + 1);
		centroids.push_back(res);
		k++;
	}
}

int KMeans::nearest_centroid(Point p) {
	int id = 0;
	double dmin = INF;
	for(int i = 0; i < centroids.size(); i++) {
		Point c_act = centroids[i];
		double dist = distance(p, c_act);
		if(dist < dmin) {
			dmin = dist;
			id = c_act.get_id();
		}
	}

	return id;
}

void KMeans::run() {
	int t = 0;
	comp.resize(no_clusters + 1);
	while(true) {
		comp.clear();
		//print_centroids();
		//cout << endl;
		//Asociar cada punto a su centroide más cercano
		for(int i = 0; i < points.size(); i++) {
			Point *p_act = &(points[i]);
			int c_id = nearest_centroid(*p_act);

			p_act->set_id(c_id);
			comp[c_id].push_back(points[i]);
		}

		//Recalcular cada centroide
		for(int i = 0; i < centroids.size(); i++) {
			int id = centroids[i].get_id();
			int sz = comp[id].size();
			double mx = 0.0, my = 0.0;
			for(int j = 0; j < sz; j++) {
				mx += comp[id][j].get_x();
				my += comp[id][j].get_y();
			}
			mx /= (double)sz;
			my /= (double)sz;

			centroids[i].set_x(mx);
			centroids[i].set_y(my);
		}

		t++;
		if(t == iter)
			break;
	}
}

void KMeans::print_centroids() {
	for(int i = 0; i < centroids.size(); i++) {
		cout << "Centroide índice: " << centroids[i].get_id() << ", X:" << centroids[i].get_x() << ", Y: " << centroids[i].get_y() << endl;
	}
}

void KMeans::print_points() {
	ofstream out, out_c;
	out.open("data.txt");
	out_c.open("centroids.txt");
	vector<int> count(no_clusters + 1);
	for(int i = 0; i < points.size(); i++) {
		cout << "X: " << points[i].get_x() << ", Y: " << points[i].get_y() << ", id: " << points[i].get_id() << endl;
		count[points[i].get_id()]++;
		out << points[i].get_x() << " " << points[i].get_y() << endl;
	}
	for(int i = 0; i < centroids.size(); i++) {
		out_c << centroids[i].get_x() << " " << centroids[i].get_y() << endl;
	}
	out.close();
	out_c.close();
	cout << "Conteo:" << endl;
	for(int i = 1; i < count.size(); i++) {
		cout << "Id (" << i << "): " << count[i] << endl;
	}
}