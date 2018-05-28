#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <utility>
#include <algorithm>
#include <cfloat>
#include <unistd.h>

#include "utils.hpp"
#include "genetic.hpp"

using namespace std;

int main(int argc, char **argv) {
	if(argc < 9) {
		cout << "Error. Ejecute: " << string(argv[0]) << " [Tamaño de la población] [a] [b] [Función] [Tipo de cruza] [No. de generaciones] [No. de ejecuciones] [Dir. de salida]" << endl;
		return 0;
	}
	int pop_size = atoi(argv[1]);
	int a = atoi(argv[2]);
	int b = atoi(argv[3]);
	string func_type = string(argv[4]);
	int cross_type = atoi(argv[5]);
	int no_generations = atoi(argv[6]);
	int no_exec = atoi(argv[7]);
	string out_dir = string(argv[8]);

	double err_av = 0.0, err_sd = 0.0;
	vector<double> err_vect;
	double best_fitness = DBL_MAX;
	double worst_fitness = 0.0;

	for(int i = 1; i <= no_exec; i++) {
		cout << "Función " << func_type << ", iteración: " << i << endl;
		srand(time(NULL));

		Genetic g(pop_size, a, b, no_generations, func_type, cross_type);
		g.run(i);

		double err_act = g.get_bets_fitness();
		best_fitness = min(best_fitness, err_act);
		worst_fitness = max(worst_fitness, err_act);
		err_av += err_act;
		err_vect.push_back(err_act);
		sleep(1.5);
	}

	err_av /= (double)no_exec;
	for(int i = 0; i < no_exec; i++) {
		err_sd += pow(err_vect[i] - err_av, 2);
	}
	err_sd = sqrt(err_sd / (double)no_exec);
	string files_name = out_dir + "/res_info.txt";
	string files_name_2 = out_dir + "/best.txt";
	ofstream fout_1(files_name_2.c_str());
	for(int i = 0; i < err_vect.size(); i++) {
		fout_1 << err_vect[i] << endl;
	}
	fout_1.close();
	
	ofstream fout(files_name.c_str());
	fout << "Promedio de error: " << err_av << endl;
	fout << "Desviación estándar del error: " << err_sd << endl;
	fout << "Mediana del error: " << get_median(err_vect) << endl;
	fout << "Mejor fitness encontrado: " << best_fitness << endl;
	fout << "Peor fitness encontrado: " << worst_fitness << endl;
	fout.close();
	cout << "\nTerminado. Archivo res_info.txt generado.\n";

	return 0;
}