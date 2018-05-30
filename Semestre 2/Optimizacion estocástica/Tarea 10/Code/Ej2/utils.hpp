#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <string>

using namespace std;

vector<double> read_file(string file_name);

double get_mean(vector<double> x);

int rand_in_range(int a, int b);

vector<double> confidence_interval(vector<double> a);

int statistical_test(vector<double> d1, vector<double> d2, double alpha);

#endif