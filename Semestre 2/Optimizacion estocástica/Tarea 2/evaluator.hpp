#ifndef EVALUATOR_H
#define EVALUATOR_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <utility>
#include <algorithm>

#include "util.hpp"

using namespace std;

vector<vector<int> > reconstruct_sudoku(vector<GRID> sudoku);

int fitness(vector<GRID> sudoku);

#endif