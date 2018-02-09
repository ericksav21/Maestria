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

	vector<GRID> instance = read_instance(argv[1]);
	print_instance(instance);
	vector<int> row = create_row(instance, 1);

	for(int i = 0; i < row.size(); i++) {
		cout << row[i] << " ";
	}
	cout << endl;

	return 0;
}