#include <iostream>
#include <cstdio>
#include <string>

#include "utils.hpp"
#include "differential.hpp"

using namespace std;

int main(int argc, char **argv) {
	if(argc < 6) {
		printf("Error. Ejecuta: %s [Tamaño de población] [Linf] [Lsup] [Tipo de función] [Iter max].\n", argv[0]);
		return 0;
	}
	int pop_size = atoi(argv[1]);
	double linf = atof(argv[2]);
	double lsup = atof(argv[3]);
	string func_type = string(argv[4]);
	int iter_max = atoi(argv[5]);
	Differential de(pop_size, linf, lsup, func_type, iter_max);
	de.run();

	return 0;
}
