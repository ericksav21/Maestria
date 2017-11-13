#ifndef GUARD_H
#define GUARD_H

#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "patient.hpp"

using namespace std;

class Guard : public Person {
private:
	vector<pair<string, string> > checklist;
public:
	Guard(string name, char gender, double height, double weight);
	~Guard();
	void check_patients_arrive_time(Patient p);
};

#endif