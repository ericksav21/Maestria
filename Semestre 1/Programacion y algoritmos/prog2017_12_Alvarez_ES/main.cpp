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
	if(argc < 3) {
		cout << "Error. Ejecuta: " << string(argv[0]) << " [Archivo CSV] [No. clusters]." << endl;
		return 0;
	}
	srand(time(NULL));
	vector<Point> data;
	read_data(argv[1], data);
	KMeans km(data, atoi(argv[2]), 100);
	km.run();
	km.print_points();

	Graphics g(1024, 768, "png");
	g.create_background();
	g.draw_grid();
	g.set_points(Graphics::normalize_points(km.get_points(), 1150));
	g.save_img();

	return 0;
}