#include "individual.hpp"

Individual::Individual() {
	this->quality = 0;
}

Individual::Individual(vector<int> bv, int quality) {
	this->bv = bv;
	this->quality = quality;
}

Individual::~Individual() {}

void Individual::set_bv(vector<int> bv) {
	this->bv = bv;
}

void Individual::set_quality(int quality) {
	this->quality = quality;
}

vector<int> Individual::get_bv() {
	return bv;
}

int Individual::get_quality() const {
	return quality;
}