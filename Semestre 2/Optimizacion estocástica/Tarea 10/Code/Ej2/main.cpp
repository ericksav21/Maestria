#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>

#include "utils.hpp"

using namespace std;

int main(int argc, char **argv) {
	if(argc < 3) {
		cout << "Error. Ejecuta: " << string(argv[0]) << " [Dir. 1] [Dir. 2]." << endl;
		return 0;
	}

	string dir_1 = string(argv[1]);
	string dir_2 = string(argv[2]);

	int n = 7;
	string file_res = "results.txt";
	ofstream fout(file_res.c_str());
	for(int i = 1; i <= n; i++) {
		string files_name_1 = dir_1 + "/f" + to_string(i) + ".txt";
		string files_name_2 = dir_2 + "/f" + to_string(i) + ".txt";
		cout << files_name_1 << " " << files_name_2 << endl;
		
		vector<double> d1 = read_file(files_name_1);
		vector<double> d2 = read_file(files_name_2);
		int res = statistical_test(d1, d2, 0.05);
		fout << "Función " << i << ": ";
		if(res == 0) {
			fout << "Algoritmos son iguales.";
		}
		else if(res == 1) {
			fout << "Algoritmo 1 mejor que algoritmo 2.";
		}
		else {
			fout << "Algoritmo 2 mejor que algoritmo 1.";
		}
		fout << endl;
	}
	fout.close();

	return 0;
}