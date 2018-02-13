#include "evaluator.hpp"

void random_solution(vector<GRID> &sudoku) {
	for(int g = 0; g < sudoku.size(); g++) {
		random_shuffle(sudoku[g].perm.begin(), sudoku[g].perm.end());
	}
}

int fitness(vector<GRID> sudoku) {
	int err = 0;
	vector<vector<int> > table = reconstruct_table(sudoku, false);
	vector<int> used_r(10, 0), used_c(10, 0);
	//Se aprovecha el doble for, para verificar fila y columna
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

vector<GRID> constructive_heuristic(vector<GRID> sudoku) {
	//Construimos la tabla pero sin agregar las permutaciones
	vector<vector<int> > table = reconstruct_table(sudoku, true);
	vector<pair<int, int> > rows_info;

	//Ver cuáles filas tienen más espacios vacíos
	for(int i = 0; i < 9; i++) {
		int cnt = 0;
		for(int j = 0; j < 9; j++) {
			if(table[i][j] == -1) {
				cnt++;
			}
		}
		//Contador fila, en ese orden para poder hacer sort
		rows_info.push_back(make_pair(cnt, i));
	}
	sort(rows_info.begin(), rows_info.end());
	
	while(rows_info.size() > 0) {
		//Ver cuántas son las filas con menor número de huecos
		int range = 0;
		int mmin_r = rows_info[0].first;
		vector<pair<int, int> >::iterator upper = upper_bound(rows_info.begin(), rows_info.end(), make_pair(mmin_r, 10));
		if(upper - rows_info.begin() < rows_info.size()) {
			range = (upper - rows_info.begin()) - 1;
		}

		//Elegir una fila al azar
		int r_index = rand_in_range(0, range);
		int row = rows_info[r_index].second;
		vector<bool> setted_in_row(10, false);
		for(int c = 0; c < 9; c++) {
			if(table[row][c] != -1) setted_in_row[table[row][c]] = true;
		}
		for(int c = 0; c < 9; c++) {
			vector<bool> setted_in_col(10, false);
			if(table[row][c] == -1) {
				fill(setted_in_col.begin(), setted_in_col.end(), false);
				for(int r = 0; r < 9; r++) {
					if(table[r][c] != -1) setted_in_col[table[r][c]] = true;
				}
				int g_id = GRID::get_grid_id(row, c);
				//Poner un dígito en caso de disponibilidad
				bool able = false;
				int digit;
				for(int s = 0; s < sudoku[g_id].perm.size(); s++) {
					digit = sudoku[g_id].perm[s];
					if(!setted_in_row[digit] && !setted_in_col[digit]) {
						able = true;
						table[row][c] = digit;
						break;
					}
				}
				if(!able) {
					//Debido a que cualquier dígito genera conflicto en esta celda
					//Ponemos el que sea
					digit = sudoku[g_id].perm[rand_in_range(0, sudoku[g_id].perm.size() - 1)];
					table[row][c] = digit;
				}
				setted_in_row[digit] = true;
				sudoku[g_id].perm.erase(remove(sudoku[g_id].perm.begin(),
										sudoku[g_id].perm.end(), digit), sudoku[g_id].perm.end());
			}
		}
		rows_info.erase(rows_info.begin() + r_index);
	}

	return reconstruct_sudoku(table, sudoku);
}

vector<GRID> local_search(vector<GRID> sudoku) {
	bitset<9> grid_visited;
	int visited_cnt = 0;
	int fitness_min = fitness(sudoku);
	while(visited_cnt < 9) {
		int r_grid = rand_in_range(0, 8);
		while(grid_visited.test(r_grid)) {
			r_grid = rand_in_range(0, 8);
		}
		grid_visited[r_grid] = 1;
		visited_cnt++;

		//Generar los vecinos para el bloque seleccionado
		int ns = sudoku[r_grid].perm.size();
		vector<pair<int, int> > nperms;
		for(int i = 0; i < ns - 1; i++) {
			for(int j = i + 1; j < ns; j++) {
				nperms.push_back(make_pair(i, j));
			}
		}
		//Esto para elegir los vecinos de manera aleatoria
		random_shuffle(nperms.begin(), nperms.end());
		for(int i = 0; i < nperms.size(); i++) {
			int a = nperms[i].first, b = nperms[i].second;
			swap(sudoku[r_grid].perm[a], sudoku[r_grid].perm[b]);
			int fitness_act = fitness(sudoku);
			if(fitness_act < fitness_min) {
				fitness_min = fitness_act;
				visited_cnt = 0;
				grid_visited.reset();
				break;
			}
			swap(sudoku[r_grid].perm[a], sudoku[r_grid].perm[b]);
		}
	}

	return sudoku;
}