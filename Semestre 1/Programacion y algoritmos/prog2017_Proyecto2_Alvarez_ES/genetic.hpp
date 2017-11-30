#ifndef GENETIC_H
#define GENETIC_H

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
#include "base.hpp"
#include "point.hpp"
#include "individual.hpp"
#include "image.hpp"

using namespace std;

class Genetic : public Base {
private:
	//Para el Genético
	double uniform_rate, mutation_rate;
	int tournament_size;
	bool is_right_vector(vector<int> v);

	//Genético
	void generate_pop(vector<vector<int> > &pop);
	vector<int> crossover(vector<int> v1, vector<int> v2);
	vector<int> mutate(vector<int> v);
	vector<Individual> evaluate_pop(vector<vector<int> > &pop);
	vector<int> get_fittest(vector<vector<int> > pop_t, vector<Individual> &S);
	vector<int> tournamet_selection(vector<vector<int> > &pop, vector<Individual> &S);
	vector<vector<int> > evolve_pop(vector<vector<int> > &pop);
public:
	Genetic(Image img, bool verb);
	~Genetic();
	void set_parameters(int pop_size, int no_generations, double uniform_rate, double mutation_rate);
	void run(string out);
};

#endif