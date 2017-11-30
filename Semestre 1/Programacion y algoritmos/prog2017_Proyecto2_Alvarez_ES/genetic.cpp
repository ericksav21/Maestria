#include "genetic.hpp"

Genetic::Genetic(Image img, bool verb) : Base(img, verb) {
	this->tournament_size = 3;
}

Genetic::~Genetic() {
}

void Genetic::set_parameters(int pop_size, int no_generations, double uniform_rate, double mutation_rate) {
	this->pop_size = pop_size;
	this->no_generations = no_generations;
	this->uniform_rate = uniform_rate;
	this->mutation_rate = mutation_rate;

	cout << "Tamaño de población " << pop_size << endl;
	cout << "Número de generaciones: " << no_generations << endl;
	cout << "Porcentaje de cruce: " << uniform_rate << endl;
	cout << "Porcentaje de mutación: " << mutation_rate << endl << endl;
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
		double quality = Hadamard(*img, img_act);
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
	if(verb)
		cout << "Mejor Fitness: " << S[0].get_quality() << endl << endl;

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
void Genetic::run(string out) {
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	//Generar la población inicial
	vector<vector<int> > pop(pop_size);
	generate_pop(pop);

	for(int i = 1; i <= no_generations; i++) {
		if(verb)
			cout << "Generación " << i << endl;
		vector<vector<int> > np = evolve_pop(pop);
		pop.clear();
		pop = np;
	}

	save_img(pop[0], out);

	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
	cout << "Ejecución finalizada.\n" << "Tiempo transcurrido: " << time_span.count() << " segundos." << endl << endl;
}