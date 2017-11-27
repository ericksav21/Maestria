#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>

#include "util.hpp"
#include "image.hpp"
#include "detector.hpp"
#include "graphics.hpp"

using namespace std;

int main(int argc, char **argv) {
	Image img("GMF2_1.pgm");
	img.skeletonize();
	Graphics g(img.get_width(), img.get_height(), "res.png");
	g.copy_img(img);
	g.save(false);
	//img.save("Jeje.pgm", false);
	return 0;
}