#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <fstream>
#include <ctime>
#include <cstdlib>

#include "graph.hpp"
#include "genetic.hpp"

using namespace std;

int main(int argc, char **argv) {
	if(argc < 7) {
		cout << "Error. Ejecuta: " << string(argv[0]) << " [Nombre del archivo] [Q] [c] [Tam. pob.] [MR] [Dir. sal.]" << endl;
		return 0;
	}

	string files_name = string(argv[1]);
	int q = atoi(argv[2]);
	int c = atoi(argv[3]);
	int pop_size = atoi(argv[4]);
	double mr = atof(argv[5]);
	string out_dir = string(argv[6]);
	//Graph g = read_graph(files_name);
	Graph g = read_graph_2(files_name);

	for(int i = 1; i <= 30; i++) {
		srand(time(NULL));
		Genetic gen(g, q, c, g.no_nodes - 1, pop_size, mr);
		gen.set_filesname(out_dir);
		gen.set_ex_no(i);
		gen.run();
	}

	return 0;
}