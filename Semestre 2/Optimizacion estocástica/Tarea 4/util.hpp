#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cmath>

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

	static int get_grid_id(int i, int j, int n) {
		int gs = sqrt(n);
		int res = 0;
		//Checar primera fila
		for(int k = 1; k < gs; k++) {
			if(j >= gs * k && j <= (gs * k) + (gs - 1)) {
				res = k;
				break;
			}
		}
		//Checar las demás
		for(int k = 1; k < gs; k++) {
			if(i >= gs * k && i <= (gs * k) + (gs - 1)) {
				res += gs * k;
				break;
			}
		}

		return res;
	}

	/*static int get_grid_id(int i, int j, int n) {
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
	}*/
} GRID;

int rand_in_range(int a, int b);

GRID new_grid(bool empty, int n);

vector<vector<int> > read_instance(char *files_name, int n);

vector<vector<int> > reconstruct_table(vector<GRID> sudoku, bool no_solution);

vector<GRID> reconstruct_sudoku(vector<vector<int> > table, int n);

vector<GRID> reconstruct_sudoku(vector<vector<int> > table, vector<GRID> sudoku);

void print_sudoku(vector<GRID> instance);

#endif