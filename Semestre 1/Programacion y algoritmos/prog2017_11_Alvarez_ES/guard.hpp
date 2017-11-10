#ifndef GUARD_H
#define GUARD_H

#include <string>

#include "patient.hpp"

using namespace std;

class Guard : public Person {
public:
	Guard(string name, char gender, double height, double weight);
	~Guard();
	void check_patients_arrive_time(Patient p);
};

#endif