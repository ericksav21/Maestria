#include "evaluator.hpp"

vector<vector<int> > reconstruct_sudoku(vector<GRID> sudoku) {
	vector<int> res(9);
	for(int i = 0; i < 9; i++) {
		res[i].resize(9, -1);
	}

	//Números fijos
	for(int g = 0; g < 9; g++) {
		for(int s = 0; s < sudoku[g].setted.size(); s++) {
			pair<int, int> ppos = sudoku[g].setted_pos[s];
			int i = ppos.first;
			int j = ppos.second;

			res[i][j] = sudoku[g].setted[s];
		}
	}

	//Permutaciones
	vector<int> g_used(9, 0);
	for(int i = 0; i < 9; i++) {
		for(int j = 0; j < 9; j++) {
			if(res[i][j] == -1) {
				int gid = GRID::get_grid_id(i, j);
				res[i][j] = sudoku[gid].perm[g_used[gid]];
				g_used[gid]++;
			}
		}
	}

	return res;
}

int fitness(vector<GRID> sudoku) {
	int err = 0;
	vector<vector<int> > table = reconstruct_sudoku(sudoku);
	vector<int> used(9, 0);
	for(int i = 0; i < 9; i++) {
		used.clear();
		for(int j = 0; j < 9; j++) {
			if(used[table[i][j]]) {
				err += used[table[i][j]];
			}
			//for(int g = 0; )
		}
	}

	return err;
}