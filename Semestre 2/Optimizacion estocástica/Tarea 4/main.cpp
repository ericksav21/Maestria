#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <fstream>

#include "util.hpp"
#include "evaluator.hpp"

using namespace std;

int main(int argc, char **argv) {
	if(argc < 4) {
		cout << "Error. Ejecuta: " << string(argv[0]) << " [Instancia sudoku] [Tipo de inicialización] [Out file].\n";
		return 0;
	}

	srand(time(0));
	clock_t ck_1, ck_2, ck_3;
	ofstream file(argv[3]);

	int n = 9;
	vector<vector<int> > instance = read_instance(argv[1], n);
	vector<GRID> sudoku = reconstruct_sudoku(instance, n);
	int initial_fitness = fitness(sudoku);
	string init_type = string(argv[2]);

	ck_1 = clock();
	vector<GRID> constructed, solution;
	if(init_type == "heuristic") {
		//Heurística constructiva
		constructed = constructive_heuristic(sudoku);
		ck_2 = clock();
		solution = local_search(constructed);
	}
	else if(init_type == "random") {
		random_solution(sudoku);
		ck_2 = clock();
		solution = local_search(sudoku);
	}
	else {
		cout << "No se reconoció el tipo de inicialización.\n";
		return 0;
	}

	ck_3 = clock();
	file << "Fitness inicial: " << initial_fitness << endl;
	file << "Fitness de la construcción inicial: " << (init_type == "heuristic" ? fitness(constructed) : fitness(sudoku)) << endl;
	file << "Fitness de la búsqueda local: " << fitness(solution) << endl;
	file << "Tiempo heurística c. (seg): " << double(ck_2 - ck_1) / CLOCKS_PER_SEC << endl;
	file << "Tiempo de la búsqueda local (seg): " << double(ck_3 - ck_2) / CLOCKS_PER_SEC << endl;
	file << "Tiempo total (seg): " << double(ck_3 - ck_1) / CLOCKS_PER_SEC << endl;

	file.close();
	return 0;
}