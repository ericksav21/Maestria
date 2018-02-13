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
	if(argc < 3) {
		cout << "Error. Ejecuta: " << string(argv[0]) << " [Instancia sudoku] [Out file].\n";
		return 0;
	}

	srand(time(0));
	clock_t ck_1, ck_2, ck_3;
	ofstream file(argv[2]);

	vector<vector<int> > instance = read_instance(argv[1]);
	vector<GRID> sudoku = reconstruct_sudoku(instance);
	int initial_fitness = fitness(sudoku);

	ck_1 = clock();
	//Heurística constructiva
	vector<GRID> constructed = constructive_heuristic(sudoku);

	//Generación aleatoria, modifica la instancia del sudoku por referencia
	//random_solution(sudoku);

	//Búsqueda local
	ck_2 = clock();
	vector<GRID> solution = local_search(constructed);
	ck_3 = clock();
	file << "Fitness inicial: " << initial_fitness << endl;
	file << "Fitness de la heurística constructiva: " << fitness(constructed) << endl;
	file << "Fitness de la búsqueda local: " << fitness(solution) << endl;
	file << "Tiempo heurística c. (seg): " << double(ck_2 - ck_1) / CLOCKS_PER_SEC << endl;
	file << "Tiempo de la búsqueda local (seg): " << double(ck_3 - ck_2) / CLOCKS_PER_SEC << endl;
	file << "Tiempo total (seg): " << double(ck_3 - ck_1) / CLOCKS_PER_SEC << endl;

	file.close();
	return 0;
}