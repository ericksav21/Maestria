#include <iostream>
#include <cstring>
#include <vector>

#include "memo.h"
#include "separador.h"
#include "clasificador.h"

using namespace std;

int main(int argc, char **argv) {
	if(argc < 4) {
		cout << "Error. Ejecuta: " << argv[0] << " [Archivo Spam] [Archivo No Spam] [Archivo a evaluar]." << endl;
		return 0;
	}

	string spams_file(argv[1]), nospams_file(argv[2]), test_file(argv[3]);
	vector<WORD> spam_dict = read_from_file(spams_file);
	vector<WORD> nospam_dict = read_from_file(nospams_file);
	vector<WORD> test_dict = read_from_file(test_file);
	vector<REG> table = intersection(spam_dict, nospam_dict);
	double span_perc = clasify(test_dict, table, true);
	double nospan_perc = clasify(test_dict, table, false);

	cout << "Porcentaje de span: " << span_perc << ", Porcentaje de no span: " << nospan_perc << endl;

	return 0;
}