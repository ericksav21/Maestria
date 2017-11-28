#include "detector.hpp"

Detector::Detector(Image img) {
	this->img = new Image(img.get_mat());
	srand(time(NULL));

	//Inicializar la lista de puntos blancos
	for(int i = 0; i < img.get_height(); i++) {
		for(int j = 0; j < img.get_width(); j++) {
			if(img.get_val(i, j)) {
				//Punto blanco
				white_points.push_back(Point(i, j));
			}
		}
	}

	sort(white_points.begin(), white_points.end(), PointComparator());
}

Detector::~Detector() {}

vector<int> Detector::get_sub_vector(vector<int> v, int i, int j) {
	vector<int> res;
	for(int k = i; k <= j; k++)
		res.push_back(v[k]);

	return res;
}

vector<int> Detector::to_binary(int n) {
	vector<int> res;
	string binary = bitset<8>(n).to_string();
	for(int i = 0; i < binary.size(); i++) {
		res.push_back(binary[i] - '0');
	}

	return res;
}

int Detector::to_int(vector<int> v) {
	stringstream ss;
	for(int i = 0; i < v.size(); i++) {
		ss << v[i];
	}
	return bitset<8>(ss.str()).to_ulong();
}

Image Detector::get_image() {
	return *img;
}

vector<Point> Detector::get_white_points() {
	return white_points;
}

void Detector::print_white_points() {
	for(int i = 0; i < white_points.size(); i++) {
		cout << white_points[i].get_i() << " " << white_points[i].get_j() << endl;
	}
}

void Detector::set_UMDA_parameters(int pop_size, int fitness, int no_generations, int nfeat, int no_bits) {
	this->pop_size = pop_size;
	this->fitness = fitness;
	this->no_generations = no_generations;
	this->nfeat = nfeat;
	this->no_bits = no_bits;
}

vector<int> Detector::generate_bin(vector<double> P) {
	int cnt = 0;
	int n = P.size();
	vector<int> bv(n, 0);
	//Generar
	for(int i = 0; i < n; i++) {
		int r = rand() % 100;
		if(r < (int)(P[i] * 100.0)) {
			bv[i] = 1;
			cnt++;
		}
		else {
			bv[i] = 0;
		}
	}
	//Reparar
	while(cnt != nfeat) {
		for(int i = 0; i < n; i++) {
			int r = rand() % 100;
			if(bv[i] == 0 && cnt < nfeat) {
				if(r < (int)(P[i] * 100.0)) {
					bv[i] = 1;
					cnt++;
				}
			}
			else if(bv[i] == 1 && cnt > nfeat) {
				if(r >= (int)(P[i] * 100.0)) {
					bv[i] = 0;
					cnt--;
				}
			}
		}
	}

	return bv;
}

int Detector::Hadamard(Image a, Image b) {
	int res = 0;
	for(int i = 0; i < a.get_height(); i++) {
		for(int j = 0; j < a.get_width(); j++) {
			int val = a.get_val(i, j) * b.get_val(i, j);
			if(val != 0) {
				res++;
			}
		}
	}

	return res;
}

vector<int> evaluate_pop() {

}

vector<Point> Detector::UMDA() {
	//Tamaño de la lista de pixeles
	int pixel_sz = white_points.size();

	//Mejor vector
	vector<Point> res;
	
	//Inicializar el vector de probabilidades
	vector<double> P(no_bits, 0.5);

	//Generar la población inicial
	vector<vector<int> > pop(pop_size);
	for(int i = 0; i < pop_size; i++) {
		while(true) {
			vector<int> bv = generate_bin(P);

			//Validar que los índices de ese vector estén dentro del rango de la lista
			int aux1 = to_int(get_sub_vector(bv, 0, 7));
			int aux2 = to_int(get_sub_vector(bv, 8, 15));
			int aux3 = to_int(get_sub_vector(bv, 16, 23));

			if((aux1 >= 0 && aux1 < pixel_sz) &&
			   (aux2 >= 0 && aux2 < pixel_sz) &&
			   (aux3 >= 0 && aux3 < pixel_sz)) {

				pop[i] = bv;
				break;
			}
		}
	}

	//Evaluar la población
	

	return res;
}