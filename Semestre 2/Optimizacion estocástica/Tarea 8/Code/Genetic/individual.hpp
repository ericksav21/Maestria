#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class Individual {
private:
	vector<int> bv;
	double fitness;

public:
	Individual(vector<int> bv, double fitness);
	~Individual();
	vector<int> get_bv() const;
	double get_fitness() const;
};

class IndividualComparator {
public:
	bool operator()(const Individual &a, const Individual &b) {
		return a.get_fitness() < b.get_fitness();
	}	
};

#endif