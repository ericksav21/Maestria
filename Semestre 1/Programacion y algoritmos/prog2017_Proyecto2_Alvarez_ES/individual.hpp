#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include <iostream>
#include <vector>

using namespace std;

class Individual {
private:
	vector<int> bv;
	int quality;
public:
	Individual();
	Individual(vector<int> bv, int quality);
	~Individual();
	void set_bv(vector<int> bv);
	void set_quality(int quality);
	vector<int> get_bv();
	int get_quality() const;
};

class IndividualComparator {
public:
	bool operator()(const Individual &a, const Individual &b) {
		return a.get_quality() > b.get_quality();
	}
};

#endif