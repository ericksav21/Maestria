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
	if(argc < 8) {
		cout << "Error. Ejecute: " << string(argv[0]) << " [Tamaño de la población] [a] [b] [Función] [Tipo de cruza] [No. de ejecuciones] [Dir. de salida]" << endl;
		return 0;
	}
	int pop_size = atoi(argv[1]);
	int a = atoi(argv[2]);
	int b = atoi(argv[3]);
	string func_type = string(argv[4]);
	int cross_type = atoi(argv[5]);
	int no_exec = atoi(argv[6]);
	string out_dir = string(argv[7]);

	double err_av = 0.0, err_sd = 0.0;
	vector<double> err_vect;
	double best_fitness = DBL_MAX;
	double worst_fitness = 0.0;

	for(int i = 1; i <= no_exec; i++) {
		cout << "Función " << func_type << ", iteración: " << i << endl;
		srand(time(NULL));

		int no_generations = 100;
		Genetic g(pop_size, a, b, no_generations, func_type, cross_type);

		//Agregar el esquema a monitorear
		//g.add_scheme("0****1111111111111");
		//g.add_scheme("100000000****000000");
		//g.add_scheme("100000000****000001");
		//g.add_scheme("0111****11111111110");
		g.add_scheme("0**111101111101***");
		g.run(i);
		vector<int> scheme = g.get_schemes_cnt();
		ofstream fout("sphere_sc6.txt");
		for(int i = 0; i < scheme.size(); i++) {
			fout << (i + 1) << " " << scheme[i] << endl;
		}
		fout.close();

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
	ofstream fout(files_name.c_str());
	fout << "Promedio de error: " << err_av << endl;
	fout << "Desviación estándar del error: " << err_sd << endl;
	fout << "Mediana del error: " << get_median(err_vect) << endl;
	fout << "Mejor fitness encontrado: " << best_fitness << endl;
	fout << "Peor fitness encontrado: " << worst_fitness << endl;
	fout.close();
	cout << "Terminado. Archivo res_info.txt generado.\n";

	return 0;
}