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

	double eval_av = 0.0, eval_sd = 0.0;
	double err_av = 0.0, err_sd = 0.0;
	vector<double> eval_vect, err_vect;

	for(int i = 1; i <= no_exec; i++) {
		cout << "Función " << func_type << ", iteración: " << i << endl;
		srand(time(NULL));

		int no_generations = (int)ceil(150000.0 / (double)pop_size);
		Genetic g(pop_size, a, b, no_generations, func_type, cross_type);
		g.run(i);
		double no_eval_act = g.get_fitness_cnt();
		double err_act = g.get_bets_fitness();
		eval_av += no_eval_act;
		err_av += err_act;
		eval_vect.push_back(no_eval_act);
		err_vect.push_back(err_act);
		sleep(1.5);
	}

	eval_av /= (double)no_exec; err_av /= (double)no_exec;
	for(int i = 0; i < no_exec; i++) {
		eval_sd += pow(eval_vect[i] - eval_av, 2);
		err_sd += pow(err_vect[i] - err_av, 2);
	}
	eval_sd = sqrt(eval_sd / (double)no_exec);
	err_sd = sqrt(err_sd / (double)no_exec);
	string files_name = out_dir + "/res_info.txt";
	ofstream fout(files_name.c_str());
	fout << "Promedio de evaluaciones de la función: " << eval_av << endl;
	fout << "Promedio de error: " << err_av << endl;
	fout << "Desviación estándar de evaluaciones de la función: " << eval_sd << endl;
	fout << "Desviación estándar del error: " << err_sd << endl;
	fout.close();
	cout << "Terminado. Archivo res_info.txt generado.\n";

	return 0;
}