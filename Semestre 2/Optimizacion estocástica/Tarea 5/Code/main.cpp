#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <fstream>
#include <utility>
#include <sstream>
#include <unistd.h>

#include "util.hpp"
#include "evaluator.hpp"

using namespace std;

int main(int argc, char **argv) {
	if(argc < 9) {
		cout << "Error. Ejecuta: " << string(argv[0]) << " [Tamaño del sudoku] [Instancia sudoku] [Tipo de inicialización] [Out file] [Temp. máxima] [Temp. mínima] [Tiempo ej. máximo (seg)] [Rho].\n";
		return 0;
	}

	srand(time(NULL));
	int n = atoi(argv[1]);
	clock_t ck_1, ck_2, ck_3, ck_4;
	string out_file = string(argv[4]);

	vector<vector<int> > instance = read_instance(argv[2], n);
	vector<GRID> sudoku = reconstruct_sudoku(instance, n);
	ofstream file(out_file.c_str());

	int initial_fitness = fitness(sudoku);
	string init_type = string(argv[3]);

	ck_1 = clock();
	vector<GRID> constructed, solution;
	cout << "Procesando..." << endl << endl;
	SA_DATA data = new_sa_data(out_file, atof(argv[5]), atof(argv[6]), atof(argv[7]), atof(argv[8]));
	if(init_type == "heuristic") {
		//Heurística constructiva
		constructed = constructive_heuristic(sudoku);

		ck_2 = clock();
		solution = simulated_annealing(constructed, data);
	}
	else if(init_type == "random") {
		random_solution(sudoku);
		
		ck_2 = clock();
		solution = simulated_annealing(sudoku, data);
	}
	else {
		cout << "No se reconoció el tipo de inicialización.\n";
		return 0;
	}

	ck_3 = clock();

	cout << "Solución encontrada:" << endl;
	print_table(solution);
	cout << endl;

	file << "Fitness inicial (sin construcción): " << initial_fitness << endl;
	file << "Fitness de la construcción inicial: " << (init_type == "heuristic" ? fitness(constructed) : fitness(sudoku));
	file << (init_type == "heuristic" ? " (Heurística)" : " (Aleatoria)") << endl;
	file << "Fitness de la metaheurística de trayectoria: " << fitness(solution) << endl;
	file << "Tiempo de la construcción inicial. (seg): " << double(ck_2 - ck_1) / CLOCKS_PER_SEC << endl;
	file << "Tiempo de la metaheurística de trayectoria (seg): " << double(ck_3 - ck_2) / CLOCKS_PER_SEC << endl;
	file << "Tiempo total (seg): " << double(ck_3 - ck_1) / CLOCKS_PER_SEC << endl << endl;

	file.close();
	cout << "Archivo: " << out_file << " generado." << endl;

	return 0;
}