#ifndef PATIENT_H
#define PATIENT_H

#include <string>
#include <vector>

#include "person.hpp"

using namespace std;

class Patient : public Person {
private:
	string nss;
	vector<int> vital_signs;
public:
	Patient(string name, char gender, double height, double weight, string nss);
	~Patient();
	string get_nss();
	vector<int> get_vital_signs();
	void set_nss(string nss);
	void set_vital_signs(vector<int> vital_signs);
};

#endif