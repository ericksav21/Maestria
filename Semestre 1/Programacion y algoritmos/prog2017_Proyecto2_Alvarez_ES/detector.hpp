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
#include <fstream>
#include <sstream>

#include "util.hpp"
#include "base.hpp"
#include "point.hpp"
#include "individual.hpp"
#include "image.hpp"

using namespace std;

class Detector : public Base {
private:
	//Para el UMDA
	double selection_rate;
	vector<int> generate_bin(vector<double> P);
	void generate_pop(vector<double> P, vector<vector<int> > &pop, int start);
	vector<Individual> evaluate_pop(vector<vector<int> > pop);
	void update_prob(vector<double> &P, vector<Individual> evaluated);

public:
	Detector(Image img, bool verb);
	~Detector();
	void set_UMDA_parameters(int pop_size, int no_generations, double selection_rate);
	void UMDA(string out);
};

#endif