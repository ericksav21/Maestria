#ifndef EVALUATOR_H
#define EVALUATOR_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>
#include <vector>
#include <utility>
#include <algorithm>

#include "util.hpp"

using namespace std;

vector<vector<int> > reconstruct_sudoku(vector<GRID> sudoku, bool no_solution);

void random_solution(vector<GRID> &sudoku);

int fitness(vector<GRID> sudoku);

void constructive_heuristic(vector<GRID> &sudoku);

#endif