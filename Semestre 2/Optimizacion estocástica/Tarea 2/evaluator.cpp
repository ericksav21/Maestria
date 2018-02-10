#include "evaluator.hpp"

vector<vector<int> > reconstruct_sudoku(vector<GRID> sudoku, bool no_solution) {
	vector<vector<int> > res(9);
	for(int i = 0; i < 9; i++) {
		res[i].resize(9, -1);
	}

	//Números fijos
	for(int g = 0; g < sudoku.size(); g++) {
		for(int s = 0; s < sudoku[g].setted.size(); s++) {
			pair<int, int> ppos = sudoku[g].setted_pos[s];
			int i = ppos.first;
			int j = ppos.second;

			res[i][j] = sudoku[g].setted[s];
		}
	}

	if(no_solution) {
		return res;
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

void random_solution(vector<GRID> &sudoku) {
	for(int g = 0; g < sudoku.size(); g++) {
		random_shuffle(sudoku[g].perm.begin(), sudoku[g].perm.end());
	}
}

int fitness(vector<GRID> sudoku) {
	int err = 0;
	vector<vector<int> > table = reconstruct_sudoku(sudoku, false);
	vector<int> used_r(10, 0), used_c(10, 0);
	for(int i = 0; i < 9; i++) {
		fill(used_r.begin(), used_r.end(), 0);
		fill(used_c.begin(), used_c.end(), 0);
		for(int j = 0; j < 9; j++) {
			if(used_r[table[i][j]]) {
				err += used_r[table[i][j]];
			}
			if(used_c[table[j][i]]) {
				err += used_c[table[j][i]];
			}
			bool is_cons_r = false;
			bool is_cons_c = false;
			for(int g = 0; g < sudoku.size(); g++) {
				for(int s = 0; s < sudoku[g].setted.size(); s++) {
					pair<int, int> ppos = sudoku[g].setted_pos[s];
					if(i == ppos.first && j == ppos.second) {
						is_cons_r = true;
					}
					if(j == ppos.first && i == ppos.second) {
						is_cons_c = true;
					}
				}
				if(is_cons_r && is_cons_c) break;
			}

			used_r[table[i][j]] += (is_cons_r ? 50 : 1);
			used_c[table[j][i]] += (is_cons_c ? 50 : 1);
		}
	}

	return err;
}

void constructive_heuristic(vector<GRID> &sudoku) {
	vector<vector<int> > table = reconstruct_sudoku(sudoku, true);
	vector<int> cols_info(9, 0);

	for(int i = 0; i < 9; i++) {
		for(int j = 0; j < 9; j++) {
			
		}
	}
}