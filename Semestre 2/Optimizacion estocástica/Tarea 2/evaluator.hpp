#ifndef EVALUATOR_H
#define EVALUATOR_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>
#include <vector>
#include <utility>
#include <bitset>
#include <algorithm>

#include "util.hpp"

using namespace std;

void random_solution(vector<GRID> &sudoku);

int fitness(vector<GRID> sudoku);

vector<GRID> constructive_heuristic(vector<GRID> sudoku);

vector<GRID> local_search(vector<GRID> sudoku);

#endif