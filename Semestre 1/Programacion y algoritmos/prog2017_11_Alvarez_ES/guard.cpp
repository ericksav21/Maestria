#include "guard.hpp"

Guard::Guard(string name, char gender, double height, double weight) : Person(name, gender, height, weight) {}

Guard::~Guard() {}

void Guard::check_patients_arrive_time(Patient p) {
	checklist.push_back(make_pair(p.get_name(), p.get_init_time()));
	cout << "El guardia registró la hora de llegada del paciente: " << p.get_name() << " a las: " << p.get_init_time() << endl;
}