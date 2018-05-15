#include <iostream>
#include <cstdio>
#include <cfloat>
#include <string>
#include <algorithm>
#include <unistd.h>

#include "utils.hpp"
#include "differential.hpp"

using namespace std;

int main(int argc, char **argv) {
	if(argc < 8) {
		printf("Error. Ejecuta: %s [Tamaño de población] [Linf] [Lsup] [Tipo de función] [Iter max] [No ejec] [Dir. de salida].\n", argv[0]);
		return 0;
	}

	int pop_size = atoi(argv[1]);
	double linf = atof(argv[2]);
	double lsup = atof(argv[3]);
	string func_type = string(argv[4]);
	int iter_max = atoi(argv[5]);
	int no_exec = atoi(argv[6]);
	string out_dir = string(argv[7]);

	double best = DBL_MAX, worst = DBL_MIN;
	double avg = 0.0, sd = 0.0;
	vector<double> data;
	for(int i = 0; i < no_exec; i++) {
		srand(time(NULL));
		Differential de(pop_size, linf, lsup, func_type, iter_max);
		de.run();
		double act = de.get_best();
		data.push_back(act);
		avg += act;
		best = min(best, act);
		worst = max(worst, act);
		sleep(1.5);
	}
	avg /= (double)no_exec;
	//Obtener la desviación estándar
	for(int i = 0; i < no_exec; i++) {
		sd += (data[i] - avg) * (data[i] - avg);
	}
	sd = sqrt(sd / (double)no_exec);
	string files_name = out_dir + "/res_info.txt";
	ofstream fout(files_name.c_str());
	fout << "Promedio de error: " << avg << endl;
	fout << "Desviación estándar del error: " << sd << endl;
	fout << "Mediana del error: " << get_median(data) << endl;
	fout << "Mejor fitness encontrado: " << best << endl;
	fout << "Peor fitness encontrado: " << worst << endl;
	fout.close();
	cout << "Terminado. Archivo res_info.txt generado.\n";

	return 0;
}
