#ifndef EVOLUTIVE_H
#define EVOLUTIVE_H

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <fstream>
#include <sstream>
#include <vector>
#include <utility>
#include <set>
#include <map>
#include <bitset>
#include <string.h>
#include <climits>
#include <algorithm>
#include <unistd.h>

#include "util.hpp"
#include "individual.hpp"
#include "evaluator.hpp"

using namespace std;

bool pairCompare(const pair<int, Individual>& firstElem, const pair<int, Individual>& secondElem);

bool pairCompareByInd(const pair<int, Individual>& firstElem, const pair<int, Individual>& secondElem);

class Evolutive {
private:
	int pop_size;
	int pop_maintentance = 10;
	double crossover_rate = 0.8, mutation_rate = 0.01, DI;
	double end_time;
	int best_fitness;
	vector<GRID> sudoku, sol;
	string files_name;

	vector<vector<GRID> > generate_pop();
	vector<vector<GRID> > crossover(vector<GRID> &p1, vector<GRID> &p2);
	vector<GRID> mutation(vector<GRID> &sudoku);
	vector<GRID> tournamentSelection(vector<vector<GRID> > &pop);
	int hamming(vector<GRID> v1, vector<GRID> v2);
	void get_DCN(vector<pair<int, Individual> > &current_members, vector<Individual> &new_pop);
	vector<Individual> multi_dyn(vector<vector<GRID> > &pop, int n, clock_t ck_1);
	vector<pair<int, Individual> > evaluate_pop(vector<vector<GRID> > &pop);
	vector<vector<GRID> > evolve_pop(vector<vector<GRID> > &pop);
public:
	Evolutive(vector<GRID> sudoku, int pop_size, double DI, double end_time, string files_name);
	~Evolutive();
	int get_best_fitness();
	vector<GRID> get_sol();
	void run();
};

#endif
