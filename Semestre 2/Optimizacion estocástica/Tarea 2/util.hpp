#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

//Almacena los elementos faltantes de un cuadro
typedef struct grid {
	vector<int> perm, setted;
	vector<pair<int, int> > setted_pos;

	void clean() {
		perm.clear();
		setted.clear();
		setted_pos.clear();
	}

	static int get_grid_id(int i, int j) {
		int res = 0;
		if(j >= 3 && j <= 5) {
			res = 1;
		}
		else if(j >= 6 && j <= 8) {
			res = 2;
		}

		if(i >= 3 && i <= 5) {
			res += 3;
		}
		else if(i >= 6 && i <= 8) {
			res += 6;
		}

		return res;
	}
} GRID;

GRID new_grid();

vector<GRID> read_instance(char *files_name);

void print_instance(vector<GRID> instance);

#endif