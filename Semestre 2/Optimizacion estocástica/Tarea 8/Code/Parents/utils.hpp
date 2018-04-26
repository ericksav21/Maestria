#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

int rand_in_range(int a, int b);

double bin_to_real(vector<int> bin, int a, int b);

vector<double> phenotype_mapping(vector<int> ind);

void crossover_1p_complete(vector<int> v1, vector<int> v2);

void crossover_2p_complete(vector<int> v1, vector<int> v2);

#endif