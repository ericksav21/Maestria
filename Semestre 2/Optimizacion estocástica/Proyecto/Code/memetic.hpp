#ifndef MEMETIC_HPP
#define MEMETIC_HPP

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
#include <string>
#include <fstream>
#include <ctime>
#include <cstdlib>

#include "graph.hpp"

using namespace std;

class Memetic {
private:
	Graph *g;
	//Máxima capacidad de los subárboles y peso de los nodos.
	int k, c;

	vector<int> generate_ind();

public:
	Memetic(Graph g, int k, int c);
	~Memetic();
	
};

#endif