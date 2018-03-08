#include "util.hpp"

int rand_in_range(int a, int b) {
	return rand() % (b - a + 1) + a;
}

GRID new_grid(bool empty, int n) {
	GRID res;
	if(!empty) {
		for(int i = 1; i <= n; i++) {
			res.perm.push_back(i);
		}
	}

	return res;
}

vector<vector<int> > read_instance(char *files_name, int n) {
	vector<vector<int> > table(n);
	for(int i = 0; i < n; i++) {
		table[i].resize(n, 0);
	}

	ifstream ifs(files_name);
	string line;
	if(ifs.is_open()) {
		int act;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				ifs >> act;
				table[i][j] = (act != 0 ? act : -1);
			}
		}
		ifs.close();
	}
	else {
		cout << "Error al abrir el archivo: " << string(files_name) << ".\n";
	}

	return table;
}

vector<vector<int> > reconstruct_table(vector<GRID> sudoku, bool no_solution) {
	int n = sudoku.size();
	vector<vector<int> > res(n);
	for(int i = 0; i < n; i++) {
		res[i].resize(n, -1);
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
	vector<int> g_used(n, 0);
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			if(res[i][j] == -1) {
				int gid = GRID::get_grid_id(i, j, n);
				res[i][j] = sudoku[gid].perm[g_used[gid]];
				g_used[gid]++;
			}
		}
	}

	return res;
}

vector<GRID> reconstruct_sudoku(vector<vector<int> > table, int n) {
	vector<GRID> v;
	for(int i = 0; i < n; i++) {
		GRID gact = new_grid(false, n);
		v.push_back(gact);
	}

	int act;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			act = table[i][j];
			if(act != -1) {
				int id = GRID::get_grid_id(i, j, n);
				v[id].perm.erase(remove(v[id].perm.begin(), v[id].perm.end(), act),
								v[id].perm.end());

				v[id].setted.push_back(act);
				v[id].setted_pos.push_back(make_pair(i, j));
			}
		}
	}

	return v;
}

vector<GRID> reconstruct_sudoku(vector<vector<int> > table, vector<GRID> sudoku) {
	int n = sudoku.size();
	vector<GRID> v;
	for(int i = 0; i < n; i++) {
		GRID gact = new_grid(true, n);
		v.push_back(gact);
	}

	int act;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			act = table[i][j];
			int g_id = GRID::get_grid_id(i, j, n);
			bool is_default = false;
			for(int s = 0; s < sudoku[g_id].setted.size(); s++) {
				pair<int, int> ppos = sudoku[g_id].setted_pos[s];
				if(i == ppos.first && j == ppos.second) {
					is_default = true;
					v[g_id].setted.push_back(act);
					v[g_id].setted_pos.push_back(make_pair(i, j));
					break;
				}
			}
			if(!is_default) {
				v[g_id].perm.push_back(act);
			}
		}
	}

	return v;
}

vector<vector<int> > get_cost_table(vector<GRID> sudoku, int gid) {
	int n = sudoku.size();
	int gs = sqrt(n);
	vector<vector<int> > table = reconstruct_table(sudoku, false);
	vector<vector<int> > res(n + 1, vector<int>(sudoku[gid].perm.size() + 1, 0));
	pair<int, int> pinit = GRID::get_table_pos(gid, n);
	int i_init = pinit.first, j_init = pinit.second;

	//Iterar sobre el grid
	int cid = 1;
	for(int i = i_init; i < i_init + gs; i++) {
		for(int j = j_init; j < j_init + gs; j++) {
			bool is_default = false;

			//Ver si la casilla (i, j) no tiene un número por defecto
			for(int k = 0; k < sudoku[gid].setted_pos.size(); k++) {
				pair<int, int> spos = sudoku[gid].setted_pos[k];
				if(spos.first == i && spos.second == j) {
					is_default = true;
					break;
				}
			}
			if(is_default) {
				continue;
			}
			//En esta casilla podemos checar todas las combinaciones de números
			//Iterar sobre los números de la permutación
			for(int k = 0; k < sudoku[gid].perm.size(); k++) {
				int d = sudoku[gid].perm[k];
				int cost = 0;

				//Iterar en la fila
				for(int x = 0; x < n; x++) {
					if(x == j) {
						continue;
					}
					if(table[i][x] == d) {
						//Checar si el dígito es por defecto
						int gaux_id = GRID::get_grid_id(i, x, n);
						if(gaux_id == gid) {
							continue;
						}
						bool flag = false;
						for(int t = 0; t < sudoku[gaux_id].setted.size(); t++) {
							if(d == sudoku[gaux_id].setted[t]) {
								flag = true;
								break;
							}
						}
						if(!flag)
							cost++;
						else
							cost += 50;
					}
				}
				//Iterar en la columna
				for(int y = 0; y < n; y++) {
					if(y == i) {
						continue;
					}
					if(table[y][j] == d) {
						//Checar si el dígito es por defecto
						int gaux_id = GRID::get_grid_id(y, j, n);
						if(gaux_id == gid) {
							continue;
						}
						bool flag = false;
						for(int t = 0; t < sudoku[gaux_id].setted.size(); t++) {
							if(d == sudoku[gaux_id].setted[t]) {
								flag = true;
								break;
							}
						}
						if(!flag)
							cost++;
						else
							cost += 50;
					}
				}

				res[d][cid] = cost;
			}
			cid++;
		}
	}

	return res;
}

/*----- DP Section -----*/
vector<pair<int, int> > set_bits_off(int k, int n) {
	vector<pair<int, int> > res;
	for(int i = 0; i < n; i++) {
		if(k & (1 << i)) {
			res.push_back(make_pair(k & ~(1 << i), i));
		}
	}

	return res;
}
/*----- End DP Section -----*/

void print_sudoku(vector<GRID> instance) {
	for(int g = 0; g < instance.size(); g++) {
		cout << "Grid: " << (g + 1) << endl;
		cout << "Permutación: ";
		for(int j = 0; j < instance[g].perm.size(); j++) {
			cout << instance[g].perm[j] << " ";
		}
		cout << endl;
		cout << "Valores por defecto: ";
		for(int j = 0; j < instance[g].setted.size(); j++) {
			cout << instance[g].setted[j] << "(" << instance[g].setted_pos[j].first <<
					", " << instance[g].setted_pos[j].second << ") ";
		}
		cout << endl << endl;
	}
}