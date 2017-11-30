#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <map>

#include "util.hpp"
#include "parameter.hpp"
#include "point.hpp"
#include "image.hpp"
#include "detector.hpp"
#include "genetic.hpp"
#include "graphics.hpp"

using namespace std;

int main(int argc, char **argv) {
	Parameter par(argc, argv);
	if(argc < 6) {
		if(argc >= 2 && string(argv[1]) == "--help") {
			par.print_help();
			return 0;
		}
		cout << "Error. Ejecute " << string(argv[0]) << " --help para ver la ayuda del sistema." << endl;
		return 0;
	}
	map<string, string> parameters = par.process();
	Image img(parameters["file"]);
	string algo_type = parameters["algo"];
	int seed = time(NULL), psize = stoi(parameters["psize"]), ngenerations = stoi(parameters["ngenerations"]);
	bool verb = parameters.count("verb");
	double srate = 0.6, urate = 0.5, mrate = 0.015;
	if(parameters.count("seed")) seed = stoi(parameters["seed"]);
	srand(seed);

	if(algo_type == "UMDA") {
		cout << "UMDA:" << endl << "Imagen: " << parameters["file"] << endl;
		srate = stod(parameters["srate"]);
		Detector d(img, verb);
		d.set_UMDA_parameters(psize, ngenerations, srate);
		d.UMDA(parameters["file"]);
	}
	if(algo_type == "Genetic" || algo_type == "Both") {
		cout << "Algoritmo Genético:" << endl << "Imagen: " << parameters["file"] << endl;
		urate = stod(parameters["urate"]);
		mrate = stod(parameters["mrate"]);
		if(algo_type == "Both") cout << endl;
		Genetic ge(img, verb);
		ge.set_parameters(psize, ngenerations, urate, mrate);
		ge.run(parameters["file"]);
	}
	
	return 0;
}