#include "individual.hpp"

Individual::Individual(vector<GRID> sudoku, int fit) {
	this->sudoku = sudoku;
	this->fit = fit;
}

Individual::~Individual() {}

vector<GRID> Individual::get_sudoku() const {
	return sudoku;
}

int Individual::get_fitness() const {
	return fit;
}

void Individual::set_fitness(int new_fit) {
	this->fit = new_fit;
}