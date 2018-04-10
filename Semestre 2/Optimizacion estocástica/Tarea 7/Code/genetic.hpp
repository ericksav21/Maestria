#ifndef GENETIC_H
#define GENETIC_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <utility>
#include <cfloat>
#include <algorithm>

#include "utils.hpp"
#include "individual.hpp"

using namespace std;

class Genetic {
private:
	string func_type;
	double mutation_rate = 0.01, crossover_rate = 0.8;
	int tournament_size = 2, pop_size;
	int a, b;
	int no_evaluations;
	int var_size = 15;
	int dim = 10;
	int fitness_cnt;
	double best_fitness;

	void print_pop(vector<vector<int> > pop);
	double get_f(vector<double> x);
	vector<vector<int> > generate_pop();
	vector<int> get_fittest(vector<vector<int> > pop, vector<Individual> s);
	vector<int> tournament_selection(vector<vector<int> > pop, vector<Individual> s);
	vector<vector<int> > crossover(vector<int> v1, vector<int> v2);
	vector<int> mutation(vector<int> bv);
	vector<double> phenotype_mapping(vector<int> ind);
	vector<Individual> evaluate_pop(vector<vector<int> > pop);
	vector<vector<int> > evolve_pop(vector<vector<int> > pop_act);

public:
	Genetic(int pop_size, int a, int b, int no_evaluations, string func_type);
	~Genetic();
	double get_fitness_cnt();
	double get_bets_fitness();
	void run(int no, string out_dir);
};

#endif
