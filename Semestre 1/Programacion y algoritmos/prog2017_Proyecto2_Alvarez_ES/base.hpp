#ifndef BASE_H
#define BASE_H

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
#include <chrono>

#include "util.hpp"
#include "point.hpp"
#include "graphics.hpp"
#include "individual.hpp"
#include "image.hpp"

using namespace std;
using namespace std::chrono;

class Base {
protected:
	vector<Point> white_points;
	Image *img;
	int pop_size, no_generations;
	int nbits;
	bool verb;

	vector<int> get_sub_vector(vector<int> v, int i, int j);
	vector<int> to_binary(int n);
	int to_int(vector<int> v);
	void generate_points(vector<int> v, double &xc, double &yc, int &dir, double &p);
	Image generate_parabola(int width, int height, double xc, double yc, int dir, double p);

	//Evaluadores
	double weighted_points(Image a, Point c, int p, int dir);
	double Hadamard(Image a, Image b);
	void save_img(vector<int> v, string out);
public:
	Base(Image img, bool verb);
	~Base();
	Image get_image();
	vector<Point> get_white_points();
	void print_white_points();
};

#endif