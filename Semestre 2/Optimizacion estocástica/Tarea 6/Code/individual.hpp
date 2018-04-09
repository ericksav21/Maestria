#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <fstream>
#include <sstream>
#include <vector>
#include <utility>
#include <bitset>
#include <string.h>
#include <algorithm>

#include "util.hpp"

using namespace std;

class Individual {
private:
	vector<GRID> sudoku;
	int fit;
public:
	Individual(vector<GRID> sudoku, int fit);
	~Individual();
	vector<GRID> get_sudoku() const;
	int get_fitness() const;
	void set_fitness(int new_fit);
};

class IndividualComparator {
public:
	bool operator()(const Individual &a, const Individual &b) {
		return a.get_fitness() < b.get_fitness();
	}	
};

#endif