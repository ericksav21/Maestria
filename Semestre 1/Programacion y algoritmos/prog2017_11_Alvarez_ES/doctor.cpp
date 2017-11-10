#include "doctor.hpp"

Doctor::Doctor(string name, char gender, double height, double weight) : Person(name, gender, height, weight) {
	patient_vs.resize(12);
}

Doctor::~Doctor() {}

void Doctor::set_patients_vs(vector <int> vs) {
	patient_vs.clear();
	patient_vs = vs;
}

int Doctor::clasify() {
	return 0;
}