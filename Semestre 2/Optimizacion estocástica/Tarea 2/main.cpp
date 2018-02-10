#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <cmath>

#include "util.hpp"
#include "evaluator.hpp"

using namespace std;

int main(int argc, char **argv) {
	if(argc < 2) {
		cout << "Error. Ejecuta: " << string(argv[0]) << " [Instancia sudoku].\n";
		return 0;
	}

	srand(time(0));
	vector<GRID> instance = read_instance(argv[1]);
	print_instance(instance);
	print_instance(instance);

	vector<vector<int> > table = reconstruct_sudoku(instance, false);
	for(int i = 0; i < table.size(); i++) {
		for(int j = 0; j < table.size(); j++) {
			cout << table[i][j] << " ";
		}
		cout << endl;
	}
	cout << fitness(instance) << endl;

	return 0;
}