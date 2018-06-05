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

#include "graph.hpp"

using namespace std;

class Memetic {
private:
	Graph *g;
	//Máxima capacidad de los subárboles y peso de los nodos.
	int k, c, root;

	vector<int> generate_ind();
	vector<int> crossover(vector<int> &p, vector<int> &q);

public:
	Memetic(Graph g, int k, int c, int root);
	~Memetic();
	int fitness(vector<int> &ind);
	
};

#endif