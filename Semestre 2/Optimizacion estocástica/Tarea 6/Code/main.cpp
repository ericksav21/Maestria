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
#include "evolutive.hpp"

using namespace std;

int main(int argc, char **argv) {
	if(argc < 6) {
		cout << "Error. Ejecuta: " << string(argv[0]) << " [Tamaño del sudoku] [Instancia sudoku] [Out file] [Tiempo (seg)] [DI].\n";
		return 0;
	}

	srand(time(NULL));
	int n = atoi(argv[1]);
	clock_t ck_1, ck_2, ck_3, ck_4;
	string out_file = string(argv[3]);
	double time_length = atof(argv[4]), DI = atof(argv[5]);

	vector<vector<int> > instance = read_instance(argv[2], n);
	vector<GRID> sudoku = reconstruct_sudoku(instance, n);

	int initial_fitness = fitness(sudoku);

	ck_1 = clock();
	vector<GRID> solution;
	cout << "Procesando..." << endl << endl;

	Evolutive ev(sudoku, 100, DI, time_length, out_file);
	ev.run();
	int best_fitness = ev.get_best_fitness();
	ck_2 = clock();
	double current_time = double(ck_2 - ck_1) / CLOCKS_PER_SEC;

	ofstream file(out_file.c_str());
	file << "Terminado . Mejor fitness encontrado: " << best_fitness << endl;
	file << "Tiempo transcurrido (seg): " << current_time << endl;
	file.close();
	cout << "Terminado: " << string(argv[2]) << endl;

	/*cout << "Solución encontrada:" << endl;
	print_table(solution);
	cout << endl;*/

	return 0;
}