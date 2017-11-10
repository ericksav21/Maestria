#ifndef NURSE_H
#define NURSE_H

#include <string>
#include <vector>

#include "person.hpp"
#include "patient.hpp"
#include "doctor.hpp"

using namespace std;

class Nurse : public Person {

public:
	Nurse(string name, char gender, double height, double weight);
	~Nurse();
	void check_vital_signs(Patient p, Doctor d);
};

#endif