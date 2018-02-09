#include "util.hpp"

GRID new_grid() {
	GRID res;
	for(int i = 1; i <= 9; i++) {
		res.perm.push_back(i);
	}

	return res;
}

vector<GRID> read_instance(char *files_name) {
	vector<GRID> v;
	ifstream ifs(files_name);
	string line;
	if(ifs.is_open()) {
		for(int i = 0; i < 9; i++) {
			GRID gact = new_grid();
			v.push_back(gact);
		}

		int act;
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				ifs >> act;
				if(act != 0) {
					int id = GRID::get_grid_id(i, j);
					v[id].perm.erase(remove(v[id].perm.begin(), v[id].perm.end(), act),
									v[id].perm.end());

					v[id].setted.push_back(act);
					v[id].setted_pos.push_back(make_pair(i, j));
				}
			}
		}
		ifs.close();
	}
	else {
		cout << "Error al abrir el archivo: " << string(files_name) << ".\n";
	}

	return v;
}

void print_instance(vector<GRID> instance) {
	for(int i = 0; i < instance.size(); i++) {
		cout << "Grid: " << (i + 1) << endl;
		cout << "Permutación: ";
		for(int j = 0; j < instance[i].perm.size(); j++) {
			cout << instance[i].perm[j] << " ";
		}
		cout << endl;
		cout << "Valores por defecto: ";
		for(int j = 0; j < instance[i].setted.size(); j++) {
			cout << instance[i].setted[j] << "(" << instance[i].setted_pos[j].first <<
					", " << instance[i].setted_pos[j].second << ") ";
		}
		cout << endl << endl;
	}
}