#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>

#include "util.hpp"
#include "point.hpp"
#include "image.hpp"
#include "detector.hpp"
#include "genetic.hpp"
#include "graphics.hpp"

using namespace std;

int main(int argc, char **argv) {
	//Image img(string(argv[1]));
	Image img("GMF2_4.pgm");
	//img.skeletonize();
	/*Detector d(img);
	d.set_UMDA_parameters(50, 100, 0.6);
	d.UMDA();*/
	Genetic ge(img);
	ge.set_parameters(10, 100, 0.5, 0.015);
	ge.run();
	//Graphics g(img.get_width(), img.get_height(), "res.png");
	//g.copy_img(img);
	//g.save(false);
	return 0;
}