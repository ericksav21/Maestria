#ifndef PATIENT_H
#define PATIENT_H

#include <string>
#include <vector>

#include "person.hpp"

using namespace std;

class Patient : public Person {
private:
	string nss;
	string init_time, end_t_time;
	double high_pressure, low_pressure;
	vector<int> vital_signs;
public:
	Patient(string name, char gender, double height, double weight, string nss, double hp, double lp, string init_time, string end_t_time);
	~Patient();
	string get_nss();
	double get_high_pressure();
	double get_low_pressure();
	string get_init_time();
	string get_end_t_time();
	vector<int> get_vital_signs();
	void set_nss(string nss);
	void set_high_pressure(double hp);
	void set_low_pressure(double lp);
	void set_vital_signs(vector<int> vital_signs);
};

#endif