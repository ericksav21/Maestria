#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>

#include "utils.hpp"

using namespace std;

int main(int argc, char **argv) {
	if(argc < 3) {
		cout << "Error. Ejecuta: " << string(argv[0]) << " [Archivo 1] [Archivo 2]." << endl;
		return 0;
	}

	string f1 = string(argv[1]);
	string f2 = string(argv[2]);

	vector<double> d1 = read_file(f1);
	vector<double> d2 = read_file(f2);
	statistical_test(d1, d2, 0.05);

	return 0;
}