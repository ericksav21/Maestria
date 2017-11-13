#include "patient.hpp"

Patient::Patient(string name, char gender, double height, double weight, string nss, double hp, double lp, string init_time, string end_t_time) : Person(name, gender, height, weight) {
	this->nss = nss;
	this->init_time = init_time;
	this->end_t_time = end_t_time;
	this->high_pressure = hp;
	this->low_pressure = lp;
	this->vital_signs.resize(12);
}

Patient::~Patient() {}

string Patient::get_nss() {
	return nss;
}

double Patient::get_high_pressure() {
	return high_pressure;
}

double Patient::get_low_pressure() {
	return low_pressure;
}

string Patient::get_init_time() {
	return init_time;
}

string Patient::get_end_t_time() {
	return end_t_time;
}

vector<int> Patient::get_vital_signs() {
	return vital_signs;
}

void Patient::set_nss(string nss) {
	this->nss = nss;
}

void Patient::set_high_pressure(double hp) {
	this->high_pressure = hp;
}

void Patient::set_low_pressure(double lp) {
	this->low_pressure = lp;
}

void Patient::set_vital_signs(vector<int> vital_signs) {
	this->vital_signs.clear();
	this->vital_signs = vital_signs;
}