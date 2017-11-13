#ifndef UTILS_H
#define UTILS_H

#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include "patient.hpp"
#include "doctor.hpp"
#include "nurse.hpp"
#include "hospital.hpp"

using namespace std;

class Utils {
public:
	Utils();
	~Utils();
	static int time_to_int(string time);
	static string int_to_time(int sc);
	static string trim(string str);
	static vector<string> read_data(char *files_name);
	static void init_hospital(vector<string> data, Hospital *h);
};

#endif