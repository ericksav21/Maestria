#ifndef EVALUATOR_H
#define EVALUATOR_H

#include <iostream>
#include <cstdlib>
#include <cmath>
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

vector<pair<int, pair<int, int> > > get_neighbors(vector<GRID> sudoku);

vector<GRID> local_search(vector<GRID> sudoku);

/*----- DP Section -----*/

vector<int> local_search_dp(vector<GRID> sudoku, int gid);

vector<GRID> local_search_optimal(vector<GRID> sudoku);

/*----- End DP Section -----*/

/*----- Simulated Annealing Section -----*/

typedef struct sa_data {
	string files_name;
	double t_max, t_min;
	double time_max, rho;
	int iter_max;
} SA_DATA;

SA_DATA new_sa_data(string files_name, double t_max, double t_min, double time_max, double rho);

vector<GRID> simulated_annealing(vector<GRID> sudoku, SA_DATA data);

/*----- End Simulated Annealing Section -----*/

#endif