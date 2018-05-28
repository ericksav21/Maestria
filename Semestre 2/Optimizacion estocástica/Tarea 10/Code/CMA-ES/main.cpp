#include <iostream>
#include <cstdio>
#include <cfloat>
#include <string>
#include <algorithm>
#include <unistd.h>
#include <vector>

#include "handler.hpp"

using namespace std;

int main(int argc, char **argv) {
	if(argc < 9) {
		printf("Error. Ejecuta: %s [Dimensión] [Linf] [Lsup] [Tipo de función] [Iter max] [No ejec] [Sigma] [Dir. de salida].\n", argv[0]);
		return 0;
	}

	int dim = atoi(argv[1]);
	double linf = atof(argv[2]);
	double lsup = atof(argv[3]);
	string func_type = string(argv[4]);
	int eval_max = atoi(argv[5]);
	int no_exec = atoi(argv[6]);
	double sigma = atof(argv[7]);
	string out_dir = string(argv[8]);

	double best = DBL_MAX, worst = DBL_MIN;
	double avg = 0.0, sd = 0.0;
	vector<double> data;
	for(int i = 0; i < no_exec; i++) {
		srand(time(NULL));
		cout << "Función " << func_type << ", iteración: " << (i + 1) << endl;
		double act = exec(dim, func_type, eval_max, linf, lsup, sigma);
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
	string files_name_2 = out_dir + "/best.txt";
	ofstream fout_1(files_name_2.c_str());
	for(int i = 0; i < data.size(); i++) {
		fout_1 << data[i] << endl;
	}
	fout_1.close();

	ofstream fout(files_name.c_str());
	fout << "Promedio de error: " << avg << endl;
	fout << "Desviación estándar del error: " << sd << endl;
	fout << "Mediana del error: " << get_median(data) << endl;
	fout << "Mejor fitness encontrado: " << best << endl;
	fout << "Peor fitness encontrado: " << worst << endl;
	fout.close();
	//cout << "\nTerminado. Archivo res_info.txt generado.\n";

	return 0;
}
