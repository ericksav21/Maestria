#include "evaluator.hpp"

void random_solution(vector<GRID> &sudoku) {
	for(int g = 0; g < sudoku.size(); g++) {
		random_shuffle(sudoku[g].perm.begin(), sudoku[g].perm.end());
	}
}

int fitness(vector<GRID> sudoku) {
	int n = sudoku.size();
	int err = 0;
	vector<vector<int> > table = reconstruct_table(sudoku, false);
	vector<int> used_r(n + 1, 0), used_c(n + 1, 0);
	//Se aprovecha el doble for, para verificar fila y columna
	for(int i = 0; i < n; i++) {
		fill(used_r.begin(), used_r.end(), 0);
		fill(used_c.begin(), used_c.end(), 0);
		for(int j = 0; j < n; j++) {
			if(used_r[table[i][j]]) {
				err += used_r[table[i][j]];
			}
			if(used_c[table[j][i]]) {
				err += used_c[table[j][i]];
			}
			bool is_cons_r = false;
			bool is_cons_c = false;
			for(int g = 0; g < n; g++) {
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
	int n = sudoku.size();
	vector<vector<int> > table = reconstruct_table(sudoku, true);
	vector<pair<int, int> > rows_info;

	//Ver cuáles filas tienen más espacios vacíos
	for(int i = 0; i < n; i++) {
		int cnt = 0;
		for(int j = 0; j < n; j++) {
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
		vector<pair<int, int> >::iterator upper = upper_bound(rows_info.begin(), rows_info.end(), make_pair(mmin_r, n + 1));
		if(upper - rows_info.begin() < rows_info.size()) {
			range = (upper - rows_info.begin()) - 1;
		}

		//Elegir una fila al azar
		int r_index = rand_in_range(0, range);
		int row = rows_info[r_index].second;
		vector<bool> setted_in_row(n + 1, false);
		for(int c = 0; c < n; c++) {
			if(table[row][c] != -1) setted_in_row[table[row][c]] = true;
		}
		for(int c = 0; c < n; c++) {
			vector<bool> setted_in_col(n + 1, false);
			if(table[row][c] == -1) {
				fill(setted_in_col.begin(), setted_in_col.end(), false);
				for(int r = 0; r < n; r++) {
					if(table[r][c] != -1) setted_in_col[table[r][c]] = true;
				}
				int g_id = GRID::get_grid_id(row, c, n);
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
	int n = sudoku.size();
	int fitness_min = fitness(sudoku);
	vector<pair<int, pair<int, int> > > neighbors;

	while(true) {
		neighbors.clear();
		for(int r_grid = 0; r_grid < n; r_grid++) {
			//Generar los vecinos para el bloque seleccionado
			int ns = sudoku[r_grid].perm.size();
			for(int i = 0; i < ns - 1; i++) {
				for(int j = i + 1; j < ns; j++) {
					neighbors.push_back(make_pair(r_grid, make_pair(i, j)));
				}
			}
		}
		random_shuffle(neighbors.begin(), neighbors.end());
		bool is_critical = true;
		for(int k = 0; k < neighbors.size(); k++) {
			int r_grid = neighbors[k].first;
			int a = neighbors[k].second.first;
			int b = neighbors[k].second.second;

			swap(sudoku[r_grid].perm[a], sudoku[r_grid].perm[b]);
			int fitness_act = fitness(sudoku);
			if(fitness_act < fitness_min) {
				fitness_min = fitness_act;
				is_critical = false;
				break;
			}
			swap(sudoku[r_grid].perm[a], sudoku[r_grid].perm[b]);
		}
		if(is_critical) {
			break;
		}
	}

	return sudoku;
}

/*----- DP Section -----*/
vector<int> local_search_dp(vector<GRID> sudoku, int gid) {
	int INF = 1000000;
	int ss = sudoku.size();
	int N = sudoku[gid].perm.size();
	vector<vector<int> > cost = get_cost_table(sudoku, gid);
	vector<vector<pair<int, int> > > idx(N + 1, vector<pair<int, int> >((int)pow(2, N) + 1));

	int dp[N + 1][(int)pow(2, N) + 1];
	for(int i = 0; i <= N; i++) {
		for(int j = 0; j <= (int)pow(2, N); j++) {
			dp[i][j] = INF;
		}
	}
	dp[0][0] = 0;

	for(int i = 1; i <= N; i++) {
		for(int j = 0; j < (int)pow(2, N); j++) {
			if(dp[i - 1][j] < INF) {
				for(int k = 0; k < N; k++) {
					if((j & (1 << k)) == 0) {
						int d = sudoku[gid].perm[k];
						if(dp[i - 1][j] + cost[d][i] < dp[i][j | (1 << k)]) {
							dp[i][j | (1 << k)] = dp[i - 1][j] + cost[d][i];
							idx[i][j | (1 << k)] = make_pair(j, k);
						}
					}
				}
			}
		}
	}

	vector<int> rep, repn;
	int bfr = (int)pow(2, N) - 1;
	for(int i = N; i >= 1; i--) {
		rep.push_back(idx[i][bfr].second);
		bfr = idx[i][bfr].first;
	}
	reverse(rep.begin(), rep.end());
	for(int i = 0; i < rep.size(); i++) {
		repn.push_back(sudoku[gid].perm[rep[i]]);
	}

	return repn;
}

vector<GRID> local_search_optimal(vector<GRID> sudoku) {
	int n = sudoku.size();
	vector<int> grids(n);
	for(int i = 0; i < n; i++) grids[i] = i;
	int fitness_min = fitness(sudoku);

	while(true) {
		random_shuffle(grids.begin(), grids.end());

		vector<int> bperm;
		for(int i = 0; i < n; i++) {
			int grid = grids[i];
			bperm = local_search_dp(sudoku, grid);
			for(int j = 0; j < bperm.size(); j++) {
				sudoku[grid].perm[j] = bperm[j];
			}
		}
		int fitness_act = fitness(sudoku);
		//No hubo mejoras, es un óptimo local.
		if(fitness_min == fitness_act) {
			break;
		}
		fitness_min = fitness_act;
	}

	return sudoku;
}
/*----- End DP Section -----*/