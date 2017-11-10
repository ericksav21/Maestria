#include "patient.hpp"

Patient::Patient(string name, char gender, double height, double weight, string nss) : Person(name, gender, height, weight) {
	this->nss = nss;
	this->vital_signs.resize(12);
}

Patient::~Patient() {}

string Patient::get_nss() {
	return nss;
}

vector<int> Patient::get_vital_signs() {
	return vital_signs;
}

void Patient::set_nss(string nss) {
	this->nss = nss;
}

void Patient::set_vital_signs(vector<int> vital_signs) {
	this->vital_signs.clear();
	this->vital_signs = vital_signs;
}