#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <utility>
#include <cstring>
#include <string>
#include <fstream>

#define MAXN 1000000

#include "utils.hpp"

using namespace std;

struct Solution {
	point p;
	int id_org;
	int id_x;
	int force;

	Solution(point p, int id_org, int id_x, int force) {
		this->p = p;
		this->id_org = id_org;
		this->id_x = id_x;
		this->force = force;
	}
};

int forces_used[MAXN];

bool compare_by_x(const Solution &a, const Solution &b) {
	if(a.p.x < b.p.x) {
		return true;
	}
	if(a.p.x == b.p.x && a.p.y < b.p.y) {
		return true;
	}
	return false;
}

bool compare_by_y(const Solution &a, const Solution &b) {
	if(a.p.y < b.p.y) {
		return true;
	}
	if(a.p.y == b.p.y && a.p.x < b.p.x) {
		return true;
	}
	return false;
}

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

vector<Solution> solve_DaC(vector<Solution> &sorted_x_points, vector<Solution> sorted_y_points,
							int lo, int hi) {

	int n = hi - lo + 1;
	vector<Solution> res;

	if(n == 1) {
		Solution s_aux(sorted_x_points[lo].p,
						sorted_x_points[lo].id_org,
						sorted_x_points[lo].id_x,
						0);
		res.push_back(s_aux);
		return res;
	}

	int mid = (lo + hi) / 2;
	vector<Solution> left_y, right_y;
	for(int i = 0; i < sorted_y_points.size(); i++) {
		if(sorted_y_points[i].id_x >= lo && sorted_y_points[i].id_x <= mid) {
			left_y.push_back(sorted_y_points[i]);
		}
		else if(sorted_y_points[i].id_x > mid && sorted_y_points[i].id_x <= hi) {
			right_y.push_back(sorted_y_points[i]);
		}
	}

	vector<Solution> force_1 = solve_DaC(sorted_x_points, left_y, lo, mid);
	vector<Solution> force_2 = solve_DaC(sorted_x_points, right_y, mid + 1, hi);

	//sort(force_1.begin(), force_1.end(), compare_by_y);
	//sort(force_2.begin(), force_2.end(), compare_by_y);

	//Merge and recompute
	int i = 0, j = 0, cnt = 0;
	for(int k = 0; k < n; k++) {
		if(i == force_1.size()) {
			Solution s_aux(force_2[j].p, force_2[j].id_org, force_2[j].id_x, force_2[j].force + cnt);
			j++;
			res.push_back(s_aux);
		}
		else if(j == force_2.size()) {
			res.push_back(force_1[i++]);
		}
		else if(force_1[i].p.y > force_2[j].p.y) {
			Solution s_aux(force_2[j].p, force_2[j].id_org, force_2[j].id_x, force_2[j].force + cnt);
			j++;
			res.push_back(s_aux);
		}
		else {
			cnt++;
			res.push_back(force_1[i++]);
		}
	}

	for(int i = 0; i < res.size(); i++) {
		forces_used[res[i].id_x] = res[i].force;
	}
	for(int i = 0; i < sorted_y_points.size(); i++) {
		sorted_y_points[i].force = forces_used[sorted_y_points[i].id_x];
	}

	return sorted_y_points;
}

vector<int> get_points_strength_DaC(vector<point> &points) {
	int n = points.size();
	vector<Solution> sorted_x_points, sorted_y_points;
	for(int i = 0; i < n; i++) {
		Solution s_aux(points[i], i, 0, 0);
		sorted_x_points.push_back(s_aux);
	}
	sort(sorted_x_points.begin(), sorted_x_points.end(), compare_by_x);

	for(int i = 0; i < n; i++) {
		sorted_x_points[i].id_x = i;
	}
	sorted_y_points = sorted_x_points;
	sort(sorted_y_points.begin(), sorted_y_points.end(), compare_by_y);

	vector<Solution> forces = solve_DaC(sorted_x_points, sorted_y_points, 0, n - 1);
	vector<int> res(n);

	for(int i = 0; i < n; i++) {
		int point_no = forces[i].id_org;
		int force_val = forces[i].force;

		res[point_no] = force_val;
	}

	return res;
}

int main(int argc, char **argv) {
	if(argc < 3) {
		cout << "Error. La ejecucion debe tener al menos 3 parametros.\n";
		return 0;
	}

	srand(time(NULL));

	if(atoi(argv[1]) == 1) {
		int test_case = atoi(argv[2]);
		int n = atoi(argv[3]);
		int linf = atoi(argv[4]);
		int lsup = atoi(argv[5]);

		generate_random_points(test_case, n, linf, lsup);
		cout << "Archivo generado.\n";
	}
	else {
		clock_t begin, end;
		double elapsed_time;
		string file_name = string(argv[2]);
		vector<point> points = get_points(file_name.c_str());
		int n = points.size();

		//Execute O(n^2) algorithm
		begin = clock();
		vector<int> strength_points1 = get_points_strength_naive(points);
		end = clock();
		elapsed_time = (double)(end - begin) / (double)CLOCKS_PER_SEC;
		save_forces_in_file(strength_points1, "out_naive.txt");
		cout << "Tiempo transcurrido (algoritmo cuadratico): " << elapsed_time << "s.\n\n";

		//Execute O(n log n) algorithm
		begin = clock();
		vector<int> strength_points2 = get_points_strength_DaC(points);
		end = clock();
		elapsed_time = (double)(end - begin) / (double)CLOCKS_PER_SEC;
		save_forces_in_file(strength_points2, "out_DaC.txt");
		cout << "Tiempo transcurrido (algoritmo divide y venceras): " << elapsed_time << "s.\n";
	}

	return 0;
}