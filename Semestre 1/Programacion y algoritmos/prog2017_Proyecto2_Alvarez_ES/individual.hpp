#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include <iostream>
#include <vector>

using namespace std;

class Individual {
private:
	vector<int> bv;
	double quality;
public:
	Individual();
	Individual(vector<int> bv, double quality);
	~Individual();
	void set_bv(vector<int> bv);
	void set_quality(double quality);
	vector<int> get_bv();
	double get_quality() const;
};

class IndividualComparator {
public:
	bool operator()(const Individual &a, const Individual &b) {
		return a.get_quality() > b.get_quality();
	}
};

#endif