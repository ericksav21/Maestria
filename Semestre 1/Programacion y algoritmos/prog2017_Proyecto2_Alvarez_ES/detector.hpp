#ifndef DETECTOR_H
#define DETECTOR_H

#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <map>
#include <cmath>
#include <bitset>
#include <string>
#include <cstring>
#include <utility>
#include <sstream>

#include "util.hpp"
#include "point.hpp"
#include "individual.hpp"
#include "image.hpp"

using namespace std;

class Detector {
private:
	vector<Point> white_points;
	Image *img;
	//Para el UMDA
	int pop_size, no_generations;
	double selection_rate;
	int nbits;

	vector<int> get_sub_vector(vector<int> v, int i, int j);
	vector<int> to_binary(int n);
	int to_int(vector<int> v);
	void generate_points(vector<int> v, double &xc, double &yc, int &dir, double &p);
	Image generate_parabola(int width, int height, double xc, double yc, int dir, double p);
	vector<int> generate_bin(vector<double> P);
	void generate_pop(vector<double> P, vector<vector<int> > &pop, int start);
	vector<Individual> evaluate_pop(vector<vector<int> > pop);
	void update_prob(vector<double> &P, vector<Individual> evaluated);

	//Evaluadores
	int weighted_points(Image a, Point c, int p, int dir);
	int Hadamard(Image a, Image b);
public:
	Detector(Image img);
	~Detector();
	Image get_image();
	vector<Point> get_white_points();
	void print_white_points();
	void set_UMDA_parameters(int pop_size, int no_generations, double selection_rate);
	vector<Point> UMDA();
};

#endif