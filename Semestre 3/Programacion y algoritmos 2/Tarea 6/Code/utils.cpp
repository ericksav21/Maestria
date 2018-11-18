#include "utils.hpp"

int rand_in_range(int a, int b) {
	return rand() % (b - a + 1) + a;
}

/*
	Este método obtiene los puntos de un archivo de texto
*/
vector<point> get_points(string file_name) {
	ifstream file(file_name.c_str());
	vector<point> res;
	int n, xi, yi;
	if(file.is_open()) {
		file >> n;
		for(int i = 0; i < n; i++) {
			file >> xi >> yi;
			res.push_back(point(xi, yi)); 
		}
		file.close();
	}
	else {
		cout << "No se pudo abrir el archivo.\n";
	}

	return res;
}

/*
	Este método genera puntos aleatorios y diferentes
*/
void generate_random_points(int test_case, int n, int linf, int lsup) {
	stringstream ss;
	ss << test_case;
	string file_name = "test_" + ss.str() + ".txt";
	ofstream file(file_name.c_str());
	set<point> st;
	point p_aux;
	file << n << "\n";

	for(int i = 0; i < n; i++) {
		int xi = 0, yi = 0;
		p_aux = make_pair(xi, yi);
		while(st.find(p_aux) != st.end()) {
			xi = rand_in_range(linf, lsup);
			yi = rand_in_range(linf, lsup);
			p_aux = make_pair(xi, yi);
		}
		file << xi << " " << yi << "\n";
		p_aux = make_pair(xi, yi);
		st.insert(p_aux);
	}

	file.close();
}

/*
	Este método guarda los puntos en un archivo de texto
*/
void save_forces_in_file(vector<int> &forces, string file_name) {
	int n = forces.size();
	ofstream file(file_name.c_str());
	for(int i = 0; i < n; i++) {
		file << "Punto " << (i + 1) << ": " << forces[i] << "\n";
	}
	file.close();
}