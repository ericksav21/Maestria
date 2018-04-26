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

bool is_eq(vector<int> x);

vector<int> generate_pop(int n);

int binary_tournament(vector<int> x);

int roulette(vector<int> x);

vector<int> process(vector<int> x, int selection_type);

#endif