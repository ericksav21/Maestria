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
#include <string.h>
#include <algorithm>

#include "util.hpp"

using namespace std;

void random_solution(vector<GRID> &sudoku);

int fitness(vector<GRID> sudoku);

vector<GRID> constructive_heuristic(vector<GRID> sudoku);

vector<GRID> local_search(vector<GRID> sudoku);

/*----- DP Section -----*/

vector<int> local_search_dp(vector<GRID> sudoku, int gid);

vector<GRID> local_search_optimal(vector<GRID> sudoku);

/*----- End DP Section -----*/

#endif