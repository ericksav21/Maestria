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
	if(argc < 4) {
		cout << "Error. Ejecuta: " << string(argv[0]) << " [Tamaño del sudoku] [Instancia sudoku] [Tipo de inicialización] [Out file].\n";
		return 0;
	}

	srand(time(NULL));
	int n = atoi(argv[1]);
	clock_t ck_1, ck_2, ck_3, ck_4;
	string out_file = string(argv[4]);

	vector<vector<int> > instance = read_instance(argv[2], n);
	vector<GRID> sudoku = reconstruct_sudoku(instance, n);

	int initial_fitness = fitness(sudoku);
	string init_type = string(argv[3]);

	ofstream file(out_file.c_str());
	ck_1 = clock();
	vector<GRID> constructed, solution1, solution2;
	cout << "Procesando..." << endl << endl;
	if(init_type == "heuristic") {
		//Heurística constructiva
		constructed = constructive_heuristic(sudoku);

		ck_2 = clock();
		solution1 = local_search(constructed);
		ck_3 = clock();
		solution2 = local_search_optimal(constructed);
	}
	else if(init_type == "random") {
		random_solution(sudoku);
		ck_2 = clock();
		solution1 = local_search(sudoku);
		ck_3 = clock();
		solution2 = local_search_optimal(sudoku);
	}
	else {
		cout << "No se reconoció el tipo de inicialización.\n";
		return 0;
	}

	ck_4 = clock();

	cout << "Solución con bl. sencilla:" << endl;
	print_table(solution1);
	cout << endl << "Solución con bl. óptima:" << endl;
	print_table(solution2);
	cout << endl;

	file << "Fitness inicial (sin construcción): " << initial_fitness << endl;
	file << "Fitness de la construcción inicial: " << (init_type == "heuristic" ? fitness(constructed) : fitness(sudoku));
	file << (init_type == "heuristic" ? " (Heurística)" : " (Aleatoria)") << endl;
	file << "Fitness de la búsqueda local (Sencilla): " << fitness(solution1) << endl;
	file << "Fitness de la búsqueda local (Óptima): " << fitness(solution2) << endl;
	file << "Tiempo de la construcción inicial. (seg): " << double(ck_2 - ck_1) / CLOCKS_PER_SEC << endl;
	file << "Tiempo de la búsqueda local sencilla (seg): " << double(ck_3 - ck_2) / CLOCKS_PER_SEC << endl;
	file << "Tiempo de la búsqueda local óptima (seg): " << double(ck_4 - ck_3) / CLOCKS_PER_SEC << endl;
	file << "Tiempo total (seg): " << double(ck_4 - ck_1) / CLOCKS_PER_SEC << endl;

	file.close();
	cout << "Archivo: " << out_file << " generado." << endl;

	return 0;
}