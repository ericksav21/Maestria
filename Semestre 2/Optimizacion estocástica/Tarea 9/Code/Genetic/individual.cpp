#include "individual.hpp"

Individual::Individual(vector<int> bv, double fitness) {
	this->bv = bv;
	this->fitness = fitness;
}

Individual::~Individual() {}

vector<int> Individual::get_bv() const {
	return bv;
}

double Individual::get_fitness() const {
	return fitness;
}