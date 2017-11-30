#include "individual.hpp"

Individual::Individual() {
	this->quality = 0.0;
}

Individual::Individual(vector<int> bv, double quality) {
	this->bv = bv;
	this->quality = quality;
}

Individual::~Individual() {}

void Individual::set_bv(vector<int> bv) {
	this->bv = bv;
}

void Individual::set_quality(double quality) {
	this->quality = quality;
}

vector<int> Individual::get_bv() {
	return bv;
}

double Individual::get_quality() const {
	return quality;
}