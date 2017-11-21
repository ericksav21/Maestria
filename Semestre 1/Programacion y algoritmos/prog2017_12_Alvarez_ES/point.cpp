#include "point.hpp"

Point::Point() {
	x = y = 0.0;
	id = 0;
}

Point::Point(double x, double y) {
	this->x = x;
	this->y = y;
	this->id = 0;
}

Point::Point(double x, double y, int id) {
	this->x = x;
	this->y = y;
	this->id = id;
}

Point::~Point() {}

double Point::get_x() {
	return x;
}

double Point::get_y() {
	return y;
}

int Point::get_id() {
	return id;
}

void Point::set_x(double x) {
	this->x = x;
}

void Point::set_y(double y) {
	this->y = y;
}

void Point::set_id(int id) {
	this->id = id;
}