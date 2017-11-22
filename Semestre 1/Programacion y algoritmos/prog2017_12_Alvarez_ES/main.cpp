#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <vector>

#include "utils.hpp"
#include "point.hpp"
#include "kmeans.hpp"
#include "graphics.hpp"

using namespace std;

int main(int argc, char **argv) {
	if(argc < 7) {
		cout << "Error. Ejecuta: " << string(argv[0]) << " [Archivo CSV] [Col 1] [Col 2] [No. clusters] [Tolerancia] [No. iter]." << endl;
		return 0;
	}
	srand(time(NULL));
	vector<Point> data;
	int c1 = atoi(argv[2]), c2 = atoi(argv[3]);
	int no_clusters = atoi(argv[4]), iter = atoi(argv[6]);
	double tol = atof(argv[5]);
	if(no_clusters > 10) {
		cout << "Se limita el número de clusters a máximo 10." << endl;
		return 0;
	}

	read_data(argv[1], data, c1, c2);
	KMeans km(data, no_clusters, iter, tol);
	km.run();
	km.print_points();
	Graphics g;
	g.plot_data();

	return 0;
}