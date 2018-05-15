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
	double mutation_rate = 0.01, crossover_rate = 0.9, crossover_var_rate = 1.0;
	int tournament_size = 2, pop_size;
	int a, b;
	int no_generations;
	int var_size = 18;
	int dim = 10;
	int fitness_cnt;
	int schemes_cnt;
	int cross_type;
	string scheme;
	double best_fitness, mean_fitness;

	void print_pop(vector<vector<int> > pop);
	double get_f(vector<double> x);
	vector<vector<int> > generate_pop();
	vector<int> get_fittest(vector<vector<int> > pop, vector<Individual> s);
	vector<int> tournament_selection(vector<vector<int> > pop);
	vector<vector<int> > crossover_1p(vector<int> v1, vector<int> v2);
	vector<vector<int> > crossover_2p(vector<int> v1, vector<int> v2);
	void crossover_1p_complete(vector<int> v1, vector<int> v2);
	void crossover_2p_complete(vector<int> v1, vector<int> v2);
	void count_schemes(vector<vector<int> > pop);

	vector<int> mutation(vector<int> bv);
	vector<double> phenotype_mapping(vector<int> ind);
	vector<Individual> evaluate_pop(vector<vector<int> > pop);
	vector<vector<int> > evolve_pop(vector<vector<int> > pop_act);

public:
	Genetic(int pop_size, int a, int b, int no_generations, string func_type, int cross_type);
	~Genetic();
	double get_fitness_cnt();
	double get_bets_fitness();
	void add_scheme(string scheme);
	void get_schemes_cnt();
	void run(int no);
};

#endif
