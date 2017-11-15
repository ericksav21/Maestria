#include "hospital.hpp"

Hospital::Hospital() {
	guard = new Guard("Pedro Lopez", 'M', 180, 90);
}

Hospital::~Hospital() {
	delete guard;
}

void Hospital::new_patient(Patient p, Doctor d, Nurse n, int init_t_time, bool is_doc) {
	//Ponemos el paciente en cola para esperar al triage
	pq.push(make_pair(init_t_time, p));
	//Determinamos a qué doctor o enfermera corresponde el paciente
	if(is_doc) {
		for(int i = 0; i < doctors.size(); i++) {
			if(doctors[i].get_name() == d.get_name()) {
				doctors[i].add_patient(p);
			}
		}
	}
	else {
		for(int i = 0; i < nurses.size(); i++) {
			if(nurses[i].get_name() == n.get_name()) {
				nurses[i].add_patient(p);
			}
		}
	}
}

void Hospital::add_doctor(Doctor d) {
	doctors.push_back(d);
}

void Hospital::add_nurse(Nurse n) {
	nurses.push_back(n);
}

int Hospital::has_doctor(Doctor d) {
	for(int i = 0; i < doctors.size(); i++) {
		if(doctors[i].get_name() == d.get_name()) {
			return i;
		}
	}

	return -1;
}

int Hospital::has_nurse(Nurse n) {
	for(int i = 0; i < nurses.size(); i++) {
		if(nurses[i].get_name() == n.get_name()) {
			return i;
		}
	}

	return -1;
}

void Hospital::set_dr_patient(Patient p, int i) {
	doctors[i].add_patient(p);
}

void Hospital::set_ns_patient(Patient p, int i) {
	nurses[i].add_patient(p);
}

void Hospital::process(Patient p_nxt, Doctor *d) {
	cout << "Lo atiende: " << d->get_name() << endl;
	//Se hace la clasificación
	d->get_info(p_nxt);
	d->set_patients_vs(p_nxt.get_vital_signs());
	int c = d->clasify();
	cout << "Se ha clasificado al paciente con resultado: " << d->get_condition(c) << endl;
	cout << "Hora de término del triage: " << p_nxt.get_end_t_time() << endl;
	cout << "Firma: " << d->get_name() << endl << endl;
}

void Hospital::process(Patient p_nxt, Nurse *n) {
	cout << "Lo atiende: " << n->get_name() << endl;
	//Se hace la clasificación
	n->get_info(p_nxt);
	n->set_patients_vs(p_nxt.get_vital_signs());
	int c = n->clasify();
	cout << "Se ha clasificado al paciente con resultado: " << n->get_condition(c) << endl;
	cout << "Hora de término del triage: " << p_nxt.get_end_t_time() << endl;
	cout << "Firma: " << n->get_name() << endl << endl;
}

void Hospital::triage() {
	while(!pq.empty()) {
		int p_init_t = pq.top().first;
		Patient p_nxt = pq.top().second;
		pq.pop();

		//El guardia registra la entrada del paciente
		guard->check_patients_arrive_time(p_nxt);
		cout << "Paciente: " << p_nxt.get_name() << ", inicia proceso de triage a las: ";
		cout << Utils::int_to_time(p_init_t) << endl;
		//Ver quien atiende al paciente
		bool is_doc = false;
		Doctor *d;
		Nurse *n;
		for(int i = 0; i < doctors.size(); i++) {
			if(doctors[i].has_patient(p_nxt.get_name())) {
				is_doc = true;
				d = &(doctors[i]);
				break;
			}
		}
		if(!is_doc) {
			//Busca la enfermera
			for(int i = 0; i < nurses.size(); i++) {
				if(nurses[i].has_patient(p_nxt.get_name())) {
					n = &(nurses[i]);
					break;
				}
			}
			process(p_nxt, n);
		}
		else {
			process(p_nxt, d);
		}
		hours.push_back(Utils::time_to_int(p_nxt.get_end_t_time()) - p_init_t);
	}
}

void Hospital::print_triage_info() {
	double mean = 0.0, sd = 0.0;
	for(int i = 0; i < hours.size(); i++) {
		double act = hours[i] / 60;
		mean += act;
	}
	mean /= hours.size();
	for(int i = 0; i < hours.size(); i++) {
		double act = hours[i] / 60;
		sd += pow(act - mean, 2);
	}
	sd /= hours.size();
	sd = sqrt(sd);

	cout << "Media (minutos): " << mean << endl;
	cout << "Desviación estándar (minutos): " << sd << endl;
}