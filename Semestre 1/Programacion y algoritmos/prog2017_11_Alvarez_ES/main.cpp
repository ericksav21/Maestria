#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

#include "hospital.hpp"
#include "utils.hpp"

int main(int argc, char **argv) {
	if(argc < 2) {
		cout << "Error. Ejecuta: " << argv[0] << " [Nombre del archivo]." << endl;
		return 0;
	}
	
	vector<string> data = Utils::read_data(argv[1]);
	Hospital *h = new Hospital();
	Utils::init_hospital(data, h);
	cout << endl;
	h->triage();
	h->print_triage_info();

	delete h;
	return 0;
}