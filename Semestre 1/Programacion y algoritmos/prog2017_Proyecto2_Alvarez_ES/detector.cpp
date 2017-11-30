#include "detector.hpp"

Detector::Detector(Image img, bool verb) : Base(img, verb) {
	//sort(white_points.begin(), white_points.end(), PointComparator());
}

Detector::~Detector() {}

void Detector::set_UMDA_parameters(int pop_size, int no_generations, double selection_rate) {
	this->pop_size = pop_size;
	this->no_generations = no_generations;
	this->selection_rate = selection_rate;

	cout << "Tamaño de población: " << pop_size << endl;
	cout << "Número de generaciones: " << no_generations << endl;
	cout << "Radio de selección: " << selection_rate << endl << endl;
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

	return bv;
}

void Detector::generate_pop(vector<double> P, vector<vector<int> > &pop, int start) {
	int pixel_sz = white_points.size();
	for(int i = start; i < pop_size; i++) {
		while(true) {
			vector<int> bv = generate_bin(P);

			//Validar que los índices de ese vector estén dentro del rango de la lista
			int aux1 = to_int(get_sub_vector(bv, 0, nbits - 1));
			int aux2 = to_int(get_sub_vector(bv, nbits, (nbits * 2) - 1));
			int aux3 = to_int(get_sub_vector(bv, nbits * 2, (nbits * 3) - 1));

			if((aux1 >= 0 && aux1 < pixel_sz) &&
			   (aux2 >= 0 && aux2 < pixel_sz) &&
			   (aux3 >= 0 && aux3 < pixel_sz)) {

				//Verificar que no coincidan las y's generadas
				int yi = white_points[aux1].get_j();
				int yj = white_points[aux2].get_j();
				int yk = white_points[aux3].get_j();

				if(yi != yj && yi != yk && yj != yk) {
					pop[i] = bv;
					break;
				}
			}
		}
	}
}

vector<Individual> Detector::evaluate_pop(vector<vector<int> > pop) {
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
		//double quality = weighted_points(*img, Point(xc, yc), p, dir);
		ind_act.set_quality(quality);
		res.push_back(ind_act);
	}
	sort(res.begin(), res.end(), IndividualComparator());

	return res;
}

void Detector::update_prob(vector<double> &P, vector<Individual> evaluated) {
	int sr = (int)(selection_rate * evaluated.size());
	for(int i = 0; i < P.size(); i++) {
		double sum = 1.0;
		//double sum = 0.0;
		for(int j = 0; j < sr; j++) {
			sum += evaluated[j].get_bv()[i];
		}
		sum /= (sr + 2);
		//sum /= sr;
		P[i] = sum;
	}
}

void Detector::UMDA(string out) {
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	vector<vector<int> > pop(pop_size);
	//Tamaño de la lista de pixeles
	int pixel_sz = white_points.size();
	
	//Inicializar el vector de probabilidades
	vector<double> P(nbits * 3, 0.5);

	//Generar la población inicial
	generate_pop(P, pop, 0);

	//Evaluar la población
	vector<Individual> evaluated = evaluate_pop(pop);

	//Actualizar el vector de probabilidades
	update_prob(P, evaluated);
	pop[0] = evaluated[0].get_bv();

	for(int i = 1; i < no_generations; i++) {
		if(verb)
			cout << "Generación " << i << endl;
		evaluated.clear();
		generate_pop(P, pop, 1);
		evaluated = evaluate_pop(pop);
		update_prob(P, evaluated);
		pop[0] = evaluated[0].get_bv();
		if(verb)
			cout << "Mejor Fitness: " << evaluated[0].get_quality() << endl << endl;
	}

	save_img(pop[0], out);
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
	cout << "Ejecución finalizada.\n" << "Tiempo transcurrido: " << time_span.count() << " segundos." << endl << endl;
}