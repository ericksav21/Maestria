#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include "point.hpp"

using namespace std;

string trim(string str);

vector<string> read_csv_line(istream &in, char delimiter);

void read_data(char *files_name, vector<Point> &data);

#endif