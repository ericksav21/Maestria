#ifndef HOSPITAL_H
#define HOSPITAL_H

#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <queue>
#include <cmath>
#include <chrono>
#include <thread>

#include "patient.hpp"
#include "doctor.hpp"
#include "guard.hpp"
#include "nurse.hpp"

using namespace std;

class Patient_cmp {
public:
	bool operator()(pair<int, Patient> p1, pair<int, Patient> p2) {
		return p1.first > p2.first;
	}
};

class Hospital {
private:
	vector<Doctor> doctors;
	vector<Nurse> nurses;
	vector<int> hours;
	priority_queue<pair<int, Patient>, vector<pair<int, Patient> >, Patient_cmp > pq;
	Guard *guard;
public:
	Hospital();
	~Hospital();
	void new_patient(Patient p, Doctor d, Nurse n, int init_t_time, bool is_doc);
	void add_doctor(Doctor d);
	void add_nurse(Nurse n);
	int has_doctor(Doctor d);
	int has_nurse(Nurse n);
	void set_dr_patient(Patient p, int i);
	void set_ns_patient(Patient p, int i);
	void process(Patient p_nxt, Doctor *d);
	void process(Patient p_nxt, Nurse *n);
	void triage();
	void print_triage_info();
};

#include "utils.hpp"

#endif