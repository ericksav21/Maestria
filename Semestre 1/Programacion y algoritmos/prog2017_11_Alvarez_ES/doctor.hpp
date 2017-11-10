#ifndef DOCTOR_H
#define DOCTOR_H

#include <string>
#include <vector>

#include "person.hpp"
#include "patient.hpp"

using namespace std;

class Doctor : public Person {
private:
	vector<int> patient_vs;
public:
	Doctor(string name, char gender, double height, double weight);
	~Doctor();
	void set_patients_vs(vector <int> vs);
	int clasify();
};

#endif