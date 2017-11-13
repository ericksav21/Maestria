#ifndef DOCTOR_H
#define DOCTOR_H

#include <iostream>
#include <string>
#include <vector>

#include "person.hpp"
#include "patient.hpp"

using namespace std;

class Doctor : public Person {
private:
	vector<Patient> patients;
	vector<int> patient_vs;
public:
	Doctor(string name, char gender, double height, double weight);
	~Doctor();
	void set_patients_vs(vector <int> vs);
	void add_patient(Patient p);
	void get_info(Patient p);
	int clasify();
	string get_condition(int f);
	vector<Patient> get_patients();
	bool has_patient(string name);
};

#endif