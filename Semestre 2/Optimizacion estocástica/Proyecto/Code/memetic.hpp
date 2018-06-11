#ifndef MEMETIC_HPP
#define MEMETIC_HPP

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <cmath>
#include <string>
#include <fstream>
#include <climits>
#include <ctime>
#include <cstdlib>
#include <unistd.h>

#include "graph.hpp"

using namespace std;

bool pairCompare(const pair<int, vector<int> >& firstElem, const pair<int, vector<int> >& secondElem);

class Memetic {
private:
	Graph *g;
	//Máxima capacidad de los subárboles y peso de los nodos.
	int k, c, root;
	double crossover_rate, mutation_rate;
	double end_time, DI;
	int best_fitness, pop_size;
	string files_name;

	DSU get_dsu(vector<int> &p);
	bool ind_in_pop(vector<vector<int> > &pop, vector<int> &ind);
	vector<int> generate_ind();
	vector<int> crossover(vector<int> &p, vector<int> &q);
	vector<int> mutation(vector<int> &p);
	vector<vector<int> > generate_pop();
	vector<int> tournament_selection(vector<vector<int> > &pop);
	int hamming(vector<int> v1, vector<int> v2);
	vector<pair<int, vector<int> > > evaluate_pop(vector<vector<int> > &pop);
	vector<vector<int> > evolve_pop(vector<vector<int> > &pop);
	void get_DCN(vector<pair<int, vector<int> > > &current_members, vector<vector<int> > &new_pop);
	vector<vector<int> > multi_dyn(vector<vector<int> > &pop, int n, clock_t ck_1);

public:
	Memetic(Graph g, int k, int c, int root, int pop_size, double DI, double crossover_rate, double mutation_rate, double end_time);
	~Memetic();
	int fitness(vector<int> &ind);
	void set_filesname(string files_name);
	void run();
};

#endif
