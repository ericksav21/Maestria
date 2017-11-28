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
#include "image.hpp"

using namespace std;

class Detector {
private:
	vector<Point> white_points;
	Image *img;
	//Para el UMDA
	int pop_size, fitness, no_generations, nfeat, no_bits;
	double selection_rate;

	vector<int> get_sub_vector(vector<int> v, int i, int j);
	vector<int> to_binary(int n);
	int to_int(vector<int> v);
	vector<int> generate_bin(vector<double> P);
	vector<int> evaluate_pop();
	int Hadamard(Image a, Image b);
public:
	Detector(Image img);
	~Detector();
	Image get_image();
	vector<Point> get_white_points();
	void print_white_points();
	void set_UMDA_parameters(int pop_size, int fitness, int no_generations, int nfeat, int no_bits);
	vector<Point> UMDA();
};

#endif