#include "doctor.hpp"

Doctor::Doctor(string name, char gender, double height, double weight) : Person(name, gender, height, weight) {
	patient_vs.resize(12);
}

Doctor::~Doctor() {}

void Doctor::set_patients_vs(vector<int> vs) {
	patient_vs.clear();
	patient_vs = vs;
}

void Doctor::add_patient(Patient p) {
	patients.push_back(p);
}

void Doctor::get_info(Patient p) {
	cout << "Registro de información básica del paciente:" << endl;
	cout << "Nombre: " << p.get_name() << endl;
	cout << "Número de seguridad social: " << p.get_nss() << endl;
	cout << "Peso: " << p.get_weight() << endl;
	cout << "Altura: " << p.get_height() << endl;
	cout << "Presión alta: " << p.get_high_pressure() << endl;
	cout << "Presión baja: " << p.get_low_pressure() << endl;
}

int Doctor::clasify() {
	int sum = 0;
	for(int i = 0; i < patient_vs.size(); i++) {
		sum += patient_vs[i];
	}

	if(sum <= 5)
		return 0;
	if(sum >= 6 && sum <= 10)
		return 1;
	if(sum >= 11 && sum <= 20)
		return 2;
	if(sum >= 21 && sum <= 30)
		return 3;
	return 4;
}

string Doctor::get_condition(int f) {
	switch(f) {
		case 0:
			return "Sin urgencia";
		case 1:
			return "Urgencia menor";
		case 2:
			return "Urgencia";
		case 3:
			return "Emergencia inmediatamente";
		default:
			return "Reanimación inmediatamente";
	}
}

vector<Patient> Doctor::get_patients() {
	return patients;
}

bool Doctor::has_patient(string name) {
	for(int i = 0; i < patients.size(); i++) {
		if(patients[i].get_name() == name) {
			return true;
		}
	}

	return false;
}