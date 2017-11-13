#ifndef NURSE_H
#define NURSE_H

#include <string>
#include <vector>

#include "person.hpp"
#include "patient.hpp"
#include "doctor.hpp"

using namespace std;

class Nurse : public Doctor {

public:
	Nurse(string name, char gender, double height, double weight);
	~Nurse();
};

#endif