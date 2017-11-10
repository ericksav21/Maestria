#include "nurse.hpp"

Nurse::Nurse(string name, char gender, double height, double weight) : Person(name, gender, height, weight) {}

Nurse::~Nurse() {}

void Nurse::check_vital_signs(Patient p, Doctor d) {
	d.set_patients_vs(p.get_vital_signs());
}