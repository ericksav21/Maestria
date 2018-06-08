#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <fstream>
#include <ctime>
#include <cstdlib>

#include "graph.hpp"
#include "memetic.hpp"

using namespace std;

int main(int argc, char **argv) {
	if(argc < 10) {
		cout << "Error. Ejecuta: " << string(argv[0]) << " [Nombre del archivo] [Q] [c] [Tam. pob.] [D] [CR] [MR] [Tiempo] [Dir. sal.]" << endl;
		return 0;
	}
	srand(time(NULL));
	string files_name = string(argv[1]);
	int q = atoi(argv[2]);
	int c = atoi(argv[3]);
	int pop_size = atoi(argv[4]);
	double D = atof(argv[5]);
	double cr = atof(argv[6]);
	double mr = atof(argv[7]);
	double end_time = atof(argv[8]);
	string out_dir = string(argv[9]);
	//Graph g = read_graph(files_name);
	Graph g = read_graph_2(files_name);
	//g.print_adj();
	//Memetic m(g, 3, 1, g.no_nodes - 1, 100, 10.0, 0.99, 0.5, 600.0);
	Memetic m(g, q, c, g.no_nodes - 1, pop_size, D, cr, mr, end_time);
	m.set_filesname(out_dir);
	m.run();

	return 0;
}