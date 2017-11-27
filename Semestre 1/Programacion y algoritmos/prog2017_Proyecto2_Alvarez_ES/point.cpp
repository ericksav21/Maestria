#include "point.hpp"

Point::Point() {
	this->i = this->j = 0;
}

Point::Point(int i, int j) {
	this->i = i;
	this->j = j;
}

Point::~Point() {}

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