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
	//g.print_adj();
	//Memetic m(g, 5);
	DSU dsu(11);
	dsu.make_union(0, 1);
	dsu.make_union(0, 2);
	for(int i = 0; i < dsu.sz.size(); i++) {
		cout << dsu.sz[i] << " ";
	}
	cout << endl;

	return 0;
}