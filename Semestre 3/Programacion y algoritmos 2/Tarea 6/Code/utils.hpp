#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <cmath>
#include <utility>
#include <cstring>
#include <fstream>
#include <sstream>
#include <set>

#define x first
#define y second

using namespace std;

typedef pair<int, int> point;

int rand_in_range(int a, int b);

vector<point> get_points(string file_name);

void generate_random_points(int test_case, int n, int linf, int lsup);

void save_forces_in_file(vector<int> &forces, string file_name);

#endif