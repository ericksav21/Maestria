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
	int k;

	vector<int> generate_ind();

public:
	Memetic(Graph g, int k);
	~Memetic();
	
};

#endif