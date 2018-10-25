#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <cmath>
#include <utility>
#include <cstring>
#include <string>
#include <fstream>

#include "utils.hpp"

using namespace std;

vector<int> get_points_strength_naive(vector<point> &points) {
	int n = points.size();
	vector<int> res(n, 0);
	for(int i = 0; i < n; i++) {
		int cnt = 0;
		for(int j = 0; j < n; j++) {
			if(i == j) continue;
			if(points[i].x >= points[j].x && points[i].y >= points[j].y) {
				cnt++;
			}
		}
		res[i] = cnt;
	}

	return res;
}

vector<int> get_points_strength_DaC(vector<point> &points) {
	vector<int> res;
	
	return res;
}

int main(int argc, char **argv) {
	if(argc < 2) {
		cout << "Error. Ejecuta: " << string(argv[0]) << " [Nombre archivo].\n";
		return 0;
	}

	srand(time(NULL));

	string file_name = string(argv[1]);
	vector<point> points = get_points(file_name.c_str());
	int n = points.size();

	//Execute O(n^2) algorithm
	vector<int> strength_points1 = get_points_strength_naive(points);
	for(int i = 0; i < n; i++) {
		cout << "Punto " << (i + 1) << ": " << strength_points1[i] << "\n";
	}

	return 0;
}