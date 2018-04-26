#include "utils.hpp"

int var_size = 18;
int dim = 2;
int a = -600, b = 600;

int rand_in_range(int a, int b) {
	return rand() % (b - a + 1) + a;
}

double bin_to_real(vector<int> bin, int a, int b) {
	int d = bin.size();
	int res = 0;
	double part = (double)(b - a) / (pow(2.0, d) - 1.0);
	int dec = 1;
	for(int i = d - 1; i >= 0; i--) {
		res += dec * bin[i];
		dec *= 2;
	}
	return (double)a + (double)res * part;
}

vector<double> phenotype_mapping(vector<int> ind) {
	vector<double> x(dim, 0.0);
	for(int j = 0; j < dim; j++) {
		vector<int> v_aux(var_size, 0);
		for(int k = 0; k < var_size; k++) {
			v_aux[k] = ind[var_size * j + k];
		}
		x[j] = bin_to_real(v_aux, a, b);
	}

	return x;
}

void crossover_1p_complete(vector<int> v1, vector<int> v2) {
	ofstream fout;
	fout.open("offspring_1p.txt");

	//Iterar sobre la dimensión
	vector<vector<int> > v_aux1(2, vector<int>(var_size, 0));
	vector<vector<int> > v_aux2(2, vector<int>(var_size, 0));
	//Guardar a los padres
	vector<double> p1 = phenotype_mapping(v1);
	vector<double> p2 = phenotype_mapping(v2);
	fout << p1[0] << " " << p1[1] << " " << 1 << endl;
	fout << p2[0] << " " << p2[1] << " " << 1 << endl;

	for(int j = 0; j < dim; j++) {
		for(int k = 0; k < var_size; k++) {
			v_aux1[j][k] = v1[var_size * j + k];
			v_aux2[j][k] = v2[var_size * j + k];
		}
	}
	for(int i = 1; i < var_size - 1; i++) {
		for(int j = 1; j < var_size - 1; j++) {
			vector<int> son1_v1, son1_v2;
			vector<int> son2_v1, son2_v2;
			for(int x = 0; x < i; x++) {
				son1_v1.push_back(v_aux1[0][x]);
				son2_v1.push_back(v_aux2[0][x]);
			}
			for(int x = 0; x < j; x++) {
				son1_v2.push_back(v_aux1[1][x]);
				son2_v2.push_back(v_aux2[1][x]);
			}
			for(int y = i; y < var_size; y++) {
				son1_v1.push_back(v_aux2[0][y]);
				son2_v1.push_back(v_aux1[0][y]);
			}
			for(int y = j; y < var_size; y++) {
				son1_v2.push_back(v_aux2[1][y]);
				son2_v2.push_back(v_aux1[1][y]);
			}
			vector<int> son1, son2;
			for(int k = 0; k < son1_v1.size(); k++) {
				son1.push_back(son1_v1[k]);
				son2.push_back(son2_v1[k]);
			}
			for(int k = 0; k < son2_v1.size(); k++) {
				son1.push_back(son1_v2[k]);
				son2.push_back(son2_v2[k]);
			}

			for(int k = 0; k < son1.size(); k++) {
				cout << son1[k] << " ";
			}
			cout << endl;
			for(int k = 0; k < son2.size(); k++) {
				cout << son2[k] << " ";
			}
			cout << endl;

			vector<double> s1 = phenotype_mapping(son1);
			vector<double> s2 = phenotype_mapping(son2);

			fout << s1[0] << " " << s1[1] << " " << 2 << endl;
			fout << s2[0] << " " << s2[1] << " " << 2 << endl;
		}
	}

	fout.close();
}

void crossover_2p_complete(vector<int> v1, vector<int> v2) {
	ofstream fout;
	fout.open("offspring_2p.txt");

	//Iterar sobre la dimensión
	vector<vector<int> > v_aux1(2, vector<int>(var_size, 0));
	vector<vector<int> > v_aux2(2, vector<int>(var_size, 0));
	//Guardar a los padres
	vector<double> p1 = phenotype_mapping(v1);
	vector<double> p2 = phenotype_mapping(v2);
	fout << p1[0] << " " << p1[1] << " " << 1 << endl;
	fout << p2[0] << " " << p2[1] << " " << 1 << endl;

	for(int j = 0; j < dim; j++) {
		for(int k = 0; k < var_size; k++) {
			v_aux1[j][k] = v1[var_size * j + k];
			v_aux2[j][k] = v2[var_size * j + k];
		}
	}
	for(int i = 1; i < var_size - 2; i++) {
		for(int j = i + 1; j < var_size - 1; j++) {
			
			for(int k = 1; k < var_size - 2; k++) {
				for(int l = k + 1; l < var_size - 1; l++) {
					vector<int> son1_v1, son1_v2;
					vector<int> son2_v1, son2_v2;

					//Llenar la variable 1
					for(int x = 0; x < i; x++) {
						son1_v1.push_back(v_aux1[0][x]);
						son2_v1.push_back(v_aux2[0][x]);
					}
					for(int x = i; x < j; x++) {
						son1_v1.push_back(v_aux2[0][x]);
						son2_v1.push_back(v_aux1[0][x]);
					}
					for(int x = j; x < var_size; x++) {
						son1_v1.push_back(v_aux1[0][x]);
						son2_v1.push_back(v_aux2[0][x]);
					}

					//Llenar la variable 2
					for(int x = 0; x < k; x++) {
						son1_v2.push_back(v_aux1[1][x]);
						son2_v2.push_back(v_aux2[1][x]);
					}
					for(int x = k; x < l; x++) {
						son1_v2.push_back(v_aux2[1][x]);
						son2_v2.push_back(v_aux1[1][x]);
					}
					for(int x = l; x < var_size; x++) {
						son1_v2.push_back(v_aux1[1][x]);
						son2_v2.push_back(v_aux2[1][x]);
					}

					//Llenar los hijos
					vector<int> son1, son2;
					for(int k = 0; k < son1_v1.size(); k++) {
						son1.push_back(son1_v1[k]);
						son2.push_back(son2_v1[k]);
					}
					for(int k = 0; k < son2_v1.size(); k++) {
						son1.push_back(son1_v2[k]);
						son2.push_back(son2_v2[k]);
					}

					for(int k = 0; k < son1.size(); k++) {
						cout << son1[k] << " ";
					}
					cout << endl;
					for(int k = 0; k < son2.size(); k++) {
						cout << son2[k] << " ";
					}
					cout << endl;

					vector<double> s1 = phenotype_mapping(son1);
					vector<double> s2 = phenotype_mapping(son2);

					fout << s1[0] << " " << s1[1] << " " << 2 << endl;
					fout << s2[0] << " " << s2[1] << " " << 2 << endl;

				}
			}

		}
	}

	fout.close();
}