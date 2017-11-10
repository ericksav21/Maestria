#include "person.hpp"

Person::Person(string name, char gender, double height, double weight) {
	this->name = name;
	this->gender = gender;
	this->height = height;
	this->weight = weight;
}

Person::~Person() {}

string Person::get_name() {
	return name;
}

char Person::get_gender() {
	return gender;
}

double Person::get_height() {
	return height;
}

double Person::get_weight() {
	return weight;
}

void Person::set_name(string name) {
	this->name = name;
}

void Person::set_gender(char gender) {
	this->gender = gender;
}

void Person::set_height(double height) {
	this->height = height;
}

void Person::set_weight(double weight) {
	this->weight = weight;
}