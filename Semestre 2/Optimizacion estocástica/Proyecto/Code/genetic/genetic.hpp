#ifndef GENETIC_HPP
#define GENETIC_HPP

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

class Genetic {
private:
	Graph *g;
	//Máxima capacidad de los subárboles y peso de los nodos.
	int k, c, root;
	int ex_no = 0;
	double mutation_rate;
	int best_fitness, pop_size;
	string files_name;

	DSU get_dsu(vector<int> &p);
	vector<int> generate_ind();
	vector<int> crossover(vector<int> &p, vector<int> &q);
	vector<int> mutation(vector<int> &p);
	vector<vector<int> > generate_pop();
	vector<int> tournament_selection(vector<vector<int> > &pop);

	vector<vector<int> > evolve_pop(vector<vector<int> > &pop);

public:
	Genetic(Graph g, int k, int c, int root, int pop_size, double mutation_rate);
	~Genetic();
	int fitness(vector<int> &ind);
	void run();
	void set_filesname(string files_name);
	void set_ex_no(int ex_no);
};

#endif