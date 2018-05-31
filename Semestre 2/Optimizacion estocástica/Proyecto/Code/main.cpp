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
	srand(time(NULL));
	string files_name = string(argv[1]);
	Graph g = read_graph(files_name);
	//Graph g = read_graph_2(files_name);
	//g.print_adj();
	Memetic m(g, 5, 1);

	return 0;
}