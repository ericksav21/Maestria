#include "point.hpp"

Point::Point() {
	this->i = this->j = 0;
}

Point::Point(int i, int j) {
	this->i = i;
	this->j = j;
}

Point::~Point() {}

double Point::distance(Point o) const {
	//Calcula la distancia de este punto con respecto a 'o'
	double res = pow(i - o.get_i(), 2) + pow(j - o.get_j(), 2);
	return sqrt(res);
}

double Point::distance() const {
	//Se asume la distancia con respecto al origen
	return distance(Point(0, 0));
}

int Point::get_i() {
	return i;
}

int Point::get_j() {
	return j;
}

void Point::set_i(int i) {
	this->i = i;
}

void Point::set_j(int j) {
	this->j = j;
}