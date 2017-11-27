#include "detector.hpp"

Detector::Detector(Image img) {
	this->img = new Image(img.get_mat());
	srand(time(NULL));

	//Inicializar la lista de puntos blancos
	for(int i = 0; i < img.get_height(); i++) {
		for(int j = 0; j < img.get_width(); j++) {
			if(img.get_val(i, j)) {
				//Punto blanco
				white_points.push_back(Point(i, j));
			}
		}
	}
}

Detector::~Detector() {}

Image Detector::get_image() {
	return *img;
}

vector<Point> Detector::get_white_points() {
	return white_points;
}