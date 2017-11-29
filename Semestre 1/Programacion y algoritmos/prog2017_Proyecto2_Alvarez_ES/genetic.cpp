#include "genetic.hpp"

Genetic::Genetic(Image img) {
	this->tournament_size = 5;
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

	int n = white_points.size();
	nbits = 0;
	while(n > 0) {
		nbits++;
		n = n >> 1;
	}
}

Genetic::~Genetic() {
	if(img)
		delete img;
}

void Genetic::set_parameters(int pop_size, int no_generations, double uniform_rate, double mutation_rate) {
	this->pop_size = pop_size;
	this->no_generations = no_generations;
	this->uniform_rate = uniform_rate;
	this->mutation_rate = mutation_rate;
}

int Genetic::Hadamard(Image a, Image b) {
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

vector<int> Genetic::get_sub_vector(vector<int> v, int i, int j) {
	vector<int> res;
	for(int k = i; k <= j; k++)
		res.push_back(v[k]);

	return res;
}

vector<int> Genetic::to_binary(int n) {
	vector<int> res;
	string binary = bitset<12>(n).to_string();
	for(int i = 0; i < binary.size(); i++) {
		res.push_back(binary[i] - '0');
	}

	return res;
}

int Genetic::to_int(vector<int> v) {
	int sum = 0, tmp = 1;
	for(int i = 0; i < nbits; i++) {
		sum += v[i] * tmp;
		tmp *= 2;
	}

	return sum;
}

void Genetic::generate_points(vector<int> v, double &xc, double &yc, int &dir, double &p) {
	int n1 = to_int(get_sub_vector(v, 0, nbits - 1));
	int n2 = to_int(get_sub_vector(v, nbits, (nbits * 2) - 1));
	int n3 = to_int(get_sub_vector(v, nbits * 2, (nbits * 3) - 1));

	int xi = white_points[n1].get_i(), yi = white_points[n1].get_j();
	int xj = white_points[n2].get_i(), yj = white_points[n2].get_j();
	int xk = white_points[n3].get_i(), yk = white_points[n3].get_j();

	//Generar los coeficientes
	double den = (double)((yi - yj) * (yi - yk) * (yj - yk));
	double A = (double)(yk * (xj - xi) + yj * (xi - xk) + yi * (xk - xj)) / den;
	double B = (double)(pow(yk, 2) * (xi - xj) + pow(yj, 2) * (xk - xi) + pow(yi, 2) * (xj - xk)) / den;
	double C = (double)(yj * yk * (yj - yk) * xi + yk * yi * (yk - yi) * xj + yi * yj * (yi - yj) * xk);
	C /= den;

	dir = (A > 0 ? 1 : -1);
	xc = C - ((B * B) / (4.0 * A));
	yc = -B / (2.0 * A);
	p = 1.0 / (2.0 * A);
}

Image Genetic::generate_parabola(int width, int height, double xc, double yc, int dir, double p) {
	int bound = width * 2;
	Image res(width, height, 0);
	res.draw_parabola(Point((int)xc, (int)yc), abs((int)p), bound, dir, 255);

	return res;
}

bool Genetic::is_right_vector(vector<int> v) {
	int pixel_sz = white_points.size();
	//Validar que los índices de ese vector estén dentro del rango de la lista
	int aux1 = to_int(get_sub_vector(v, 0, nbits - 1));
	int aux2 = to_int(get_sub_vector(v, nbits, (nbits * 2) - 1));
	int aux3 = to_int(get_sub_vector(v, nbits * 2, (nbits * 3) - 1));

	if((aux1 >= 0 && aux1 < pixel_sz) &&
	   (aux2 >= 0 && aux2 < pixel_sz) &&
	   (aux3 >= 0 && aux3 < pixel_sz)) {

		//Verificar que no coincidan las y's generadas
		int yi = white_points[aux1].get_j();
		int yj = white_points[aux2].get_j();
		int yk = white_points[aux3].get_j();

		if(yi != yj && yi != yk && yj != yk) {
			return true;
		}
	}

	return false;
}

void Genetic::generate_pop(vector<vector<int> > &pop) {
	for(int i = 0; i < pop_size; i++) {
		vector<int> ind(nbits * 3);
		while(true) {
			for(int k = 0; k < nbits * 3; k++) {
				ind[k] = (int)rand() % 2;
			}
			if(is_right_vector(ind)) {
				break;
			}
		}
		pop[i] = ind;
	}
}

vector<int> Genetic::get_fittest(vector<vector<int> > pop_t, vector<Individual> &S) {
	vector<int> best;
	int score = -1;
	for(int i = 0; i < tournament_size; i++) {
		vector<int> aux = pop_t[i];
		//Buscar su Fittnes
		for(int j = 0; j < S.size(); j++) {
			if(aux == S[j].get_bv()) {
				int fit = S[j].get_quality();
				if(fit > score) {
					score = fit;
					best = S[j].get_bv();
				}
			}
		}
	}

	return best;
}

vector<int> Genetic::tournamet_selection(vector<vector<int> > &pop, vector<Individual> &S) {
	vector<vector<int> > pop_t(tournament_size);
	for(int i = 0; i < tournament_size; i++) {
		int random_id = (int)rand() % pop_size;
		pop_t[i] = pop[random_id];
	}

	return get_fittest(pop_t, S);
}

vector<int> Genetic::crossover(vector<int> v1, vector<int> v2) {
	vector<int> res;
	while(true) {
		res.clear();
		for(int i = 0; i < v1.size(); i++) {
			int r = (int)rand() % 100;
			if(r <= (int)(uniform_rate * 100.0)) {
				res.push_back(v1[i]);
			}
			else {
				res.push_back(v2[i]);
			}
		}
		if(is_right_vector(res)) {
			break;
		}
	}

	return res;
}

vector<int> Genetic::mutate(vector<int> v) {
	vector<int> res = v;
	for(int i = 0; i < v.size(); i++) {
		int r = (int)rand() % 100;
		if(r <= (int)(mutation_rate * 100.0)) {
			res[i] = (res[i] == 1 ? 0 : 1);
		}
	}
	if(is_right_vector(res))
		return res;
	return v;
}

vector<Individual> Genetic::evaluate_pop(vector<vector<int> > &pop) {
	vector<Individual> res;
	for(int i = 0; i < pop_size; i++) {
		Individual ind_act;
		vector<int> v_act = pop[i];
		ind_act.set_bv(v_act);
		double xc, yc, p;
		int dir;
		generate_points(v_act, xc, yc, dir, p);

		Image img_act = generate_parabola(img->get_width(), img->get_height(), xc, yc, dir, p);
		int quality = Hadamard(*img, img_act);
		ind_act.set_quality(quality);
		res.push_back(ind_act);
	}
	sort(res.begin(), res.end(), IndividualComparator());

	return res;
}

vector<vector<int> > Genetic::evolve_pop(vector<vector<int> > &pop) {
	vector<vector<int> > new_pop(pop_size);
	//Obtener el mejor elemento
	vector<Individual> S = evaluate_pop(pop);
	new_pop[0] = S[0].get_bv();
	cout << S[0].get_quality() << endl;

	//Cruza
	for(int i = 1; i < pop_size; i++) {
		vector<int> ind_1 = tournamet_selection(pop, S);
		vector<int> ind_2 = tournamet_selection(pop, S);
		new_pop[i] = crossover(ind_1, ind_2);
	}

	//Mutación
	for(int i = 1; i < pop_size; i++) {
		new_pop[i] = mutate(new_pop[i]);
	}

	return new_pop;
}

//Genético
void Genetic::run() {
	//Generar la población inicial
	vector<vector<int> > pop(pop_size);
	generate_pop(pop);

	for(int i = 1; i <= no_generations; i++) {
		cout << "Generación " << i << endl;
		vector<vector<int> > np = evolve_pop(pop);
		pop.clear();
		pop = np;
	}

	double xc, yc, p;
	int dir;
	generate_points(pop[0], xc, yc, dir, p);

	char name[25];
	sprintf(name, "Final.pgm");

	Image img_act = generate_parabola(img->get_width(), img->get_height(), xc, yc, dir, p);
	for(int i = 0; i < img->get_height(); i++) {
		for(int j = 0; j < img->get_width(); j++) {
			if(img->get_val(i, j))
				img_act.set_val(i, j, 255);
		}
	}
	img_act.save(string(name), false);
}