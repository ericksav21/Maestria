#include "genetic.hpp"

Genetic::Genetic(int pop_size, int a, int b, int no_generations, string func_type, int cross_type) {
	this->pop_size = pop_size;
	this->a = a;
	this->b = b;
	this->no_generations = no_generations;
	this->func_type = func_type;
	this->cross_type = cross_type;
	this->mutation_rate = 1.0 / (double)(var_size);

	this->par_generations.push_back(5);
	this->par_generations.push_back(no_generations >> 1);
	this->par_generations.push_back(no_generations - 5);
}

Genetic::~Genetic() {}

void Genetic::print_pop(vector<vector<int> > pop) {
	for(int i = 0; i < pop.size(); i++) {
		for(int j = 0; j < pop[0].size(); j++) {
			cout << pop[i][j] << " ";
		}
		cout << endl;
	}
}

double Genetic::get_f(vector<double> x) {
	if(func_type == "f1") {
		return sphere(x);
	}
	else if(func_type == "f2") {
		return ellipsoid(x);
	}
	else if(func_type == "f3") {
		return zakharov(x);
	}
	else if(func_type == "f4") {
		return rosenbrock(x);
	}
	else if(func_type == "f5") {
		return ackley(x);
	}
	else if(func_type == "f6") {
		return griewank(x);
	}
	else {
		return rastrigin(x);
	}
}

vector<vector<int> > Genetic::generate_pop() {
	vector<vector<int> > pop(pop_size, vector<int>(var_size * dim, 0));
	for(int i = 0; i < pop.size(); i++) {
		for(int j = 0; j < pop[0].size(); j++) {
			pop[i][j] = rand() % 2;
		}
	}

	return pop;
}

vector<int> Genetic::get_fittest(vector<vector<int> > pop, vector<Individual> s) {
	vector<int> best;
	//double score = 100000000000.0;
	double score = DBL_MAX;
	for(int i = 0; i < tournament_size; i++) {
		vector<int> aux = pop[i];

		for(int j = 0; j < s.size(); j++) {
			if(aux == s[j].get_bv()) {
				double fit = s[j].get_fitness();
				if(fit < score) {
					score = fit;
					best = s[j].get_bv();
				}
			}
		}
	}

	return best;
}

vector<int> Genetic::tournament_selection(vector<vector<int> > pop) {
	//Torneo binario
	vector<vector<int> > candidates(tournament_size);
	int ind1 = 0, ind2 = 0;
	while(ind1 == ind2) {
		ind1 = rand_in_range(0, pop.size() - 1);
		ind2 = rand_in_range(0, pop.size() - 1);
	}

	candidates[0] = pop[ind1];
	candidates[1] = pop[ind2];

	vector<double> x1 = phenotype_mapping(candidates[0]);
	vector<double> x2 = phenotype_mapping(candidates[1]);
	if(get_f(x1) < get_f(x2)) {
		return candidates[0];
	}
	else {
		return candidates[1];
	}
}

vector<vector<int> > Genetic::crossover_1p(vector<int> v1, vector<int> v2) {
	vector<vector<int> > res(2);

	//Iterar sobre la dimensión
	for(int j = 0; j < dim; j++) {
		//En esta parte se obtiene la variable j.
		vector<int> v_aux1(var_size, 0);
		vector<int> v_aux2(var_size, 0);
		for(int k = 0; k < var_size; k++) {
			v_aux1[k] = v1[var_size * j + k];
			v_aux2[k] = v2[var_size * j + k];
		}
		//Ver si se cruza esta variable
		double p = (double)rand() / (double)RAND_MAX;
		if(p > crossover_var_rate) {
			//No se cruza
			for(int k = 0; k < var_size; k++) {
				res[0].push_back(v_aux1[k]);
				res[1].push_back(v_aux2[k]);
			}
			continue;
		}
		//Decidir el punto de corte
		int cu_point = rand_in_range(1, var_size - 2);
		//Actualizar los hijos
		for(int k = 0; k < cu_point; k++) {
			res[0].push_back(v_aux1[k]);
			res[1].push_back(v_aux2[k]);
		}
		for(int k = cu_point; k < var_size; k++) {
			res[0].push_back(v_aux2[k]);
			res[1].push_back(v_aux1[k]);
		}
	}

	return res;
}

vector<vector<int> > Genetic::crossover_2p(vector<int> v1, vector<int> v2) {
	int d = v1.size();
	vector<vector<int> > res(2);
	//Iterar sobre la dimensión
	for(int j = 0; j < dim; j++) {
		//En esta parte se obtiene la variable j.
		vector<int> v_aux1(var_size, 0);
		vector<int> v_aux2(var_size, 0);
		for(int k = 0; k < var_size; k++) {
			v_aux1[k] = v1[var_size * j + k];
			v_aux2[k] = v2[var_size * j + k];
		}
		//Ver si se cruza esta variable
		double p = (double)rand() / (double)RAND_MAX;
		if(p > crossover_var_rate) {
			//No se cruza
			for(int k = 0; k < var_size; k++) {
				res[0].push_back(v_aux1[k]);
				res[1].push_back(v_aux2[k]);
			}
			continue;
		}
		//Decidir los punto de corte
		int left = rand_in_range(1, var_size - 3);
		int right = rand_in_range(left, var_size - 2);
		//Actualizar los hijos
		for(int k = 0; k < left; k++) {
			res[0].push_back(v_aux1[k]);
			res[1].push_back(v_aux2[k]);
		}
		for(int k = left; k < right; k++) {
			res[0].push_back(v_aux2[k]);
			res[1].push_back(v_aux1[k]);
		}
		for(int k = right; k < var_size; k++) {
			res[0].push_back(v_aux1[k]);
			res[1].push_back(v_aux2[k]);
		}
	}

	return res;
}

void Genetic::crossover_1p_complete(vector<int> v1, vector<int> v2) {
	ofstream fout;
	fout.open("offspring_1p.txt", ios::out | ios::app);

	//Iterar sobre la dimensión
	vector<vector<int> > v_aux1(2, vector<int>(var_size, 0));
	vector<vector<int> > v_aux2(2, vector<int>(var_size, 0));
	//Guardar a los padres
	vector<double> p1 = phenotype_mapping(v1);
	vector<double> p2 = phenotype_mapping(v2);
	fout << p1[0] << " " << p1[1] << " " << 1 << " " << capture_offspring << endl;
	fout << p2[0] << " " << p2[1] << " " << 1 << " " << capture_offspring << endl;

	for(int j = 0; j < dim; j++) {
		for(int k = 0; k < var_size; k++) {
			v_aux1[j][k] = v1[var_size * j + k];
			v_aux2[j][k] = v2[var_size * j + k];
		}
	}
	for(int i = 1; i < var_size - 1; i++) {
		for(int j = 1; j < var_size - 1; j++) {
			vector<int> son;
			for(int k = 0; k < dim; k++) {
				
			}
		}
	}

	fout.close();
}

void Genetic::crossover_2p_complete(vector<int> v1, vector<int> v2) {
	ofstream fout;
	fout.open("offspring_2p.txt", ios::out | ios::app);
}

vector<int> Genetic::mutation(vector<int> bv) {
	vector<int> res = bv;
	for(int i = 0; i < bv.size(); i++) {
		double p = (double)rand() / (double)RAND_MAX;
		if(p <= mutation_rate) {
			res[i] = (res[i] == 1 ? 0 : 1);
		}
	}

	return res;
}

vector<double> Genetic::phenotype_mapping(vector<int> ind) {
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

vector<Individual> Genetic::evaluate_pop(vector<vector<int> > pop) {
	vector<Individual> res;
	for(int i = 0; i < pop.size(); i++) {
		vector<int> v_act = pop[i];

		vector<double> x = phenotype_mapping(v_act);
		double fitness = get_f(x);
		fitness_cnt++;
		Individual ind_act(v_act, fitness);
		res.push_back(ind_act);
	}
	sort(res.begin(), res.end(), IndividualComparator());

	return res;
}

vector<vector<int> > Genetic::evolve_pop(vector<vector<int> > pop_act) {
	vector<vector<int> > new_pop(pop_size);

	int cnt = 0;
	while(true) {
		vector<int> p1 = tournament_selection(pop_act);
		vector<int> p2 = tournament_selection(pop_act);
		if(capture_offspring) {
			crossover_1p_complete(p1, p2);
			crossover_1p_complete(p1, p2);
			capture_offspring = 0;
		}
		double p = (double)rand() / (double)RAND_MAX;
		if(p <= crossover_rate) {
			vector<vector<int> > sons;
			if(cross_type == 1) {
				sons = crossover_1p(p1, p2);
			}
			else {
				sons = crossover_2p(p1, p2);
			}

			new_pop[cnt++] = mutation(sons[0]);
			if(cnt == pop_size) {
				break;
			}
			new_pop[cnt++] = mutation(sons[1]);
			if(cnt == pop_size) {
				break;
			}
		}
		else {
			new_pop[cnt++] = p1;
			if(cnt == pop_size) {
				break;
			}
			new_pop[cnt++] = p2;
			if(cnt == pop_size) {
				break;
			}
		}
	}
	vector<Individual> S_par = evaluate_pop(pop_act);
	vector<Individual> S_off = evaluate_pop(new_pop);
	vector<int> best_par = S_par[0].get_bv();
	if(S_par[0].get_fitness() < S_off[0].get_fitness()) {
		int ind = rand_in_range(0, pop_size - 1);
		new_pop[ind] = best_par;
		best_fitness = S_par[0].get_fitness();
		//cout << "Mejor fitness de la generación: " << S_par[0].get_fitness() << endl;
	}
	else {
		best_fitness = S_off[0].get_fitness();
		//cout << "Mejor fitness de la generación: " << S_off[0].get_fitness() << endl;
	}
	/*for(int i = 0; i < new_pop.size(); i++) {
		vector<double> x = phenotype_mapping(new_pop[i]);
		double fitness = get_f(x);
		mean_fitness += fitness;
	}
	mean_fitness /= (double)new_pop.size();*/

	return new_pop;
}

double Genetic::get_fitness_cnt() {
	return fitness_cnt;
}

double Genetic::get_bets_fitness() {
	return best_fitness;
}

void Genetic::run(int no) {
	double tol = 1e-3;
	fitness_cnt = 0;
	best_fitness = DBL_MAX;
	vector<vector<int> > pop(pop_size);
	pop = generate_pop();

	int cnt = 1;
	//ofstream fout("sphere_ev.txt");
	while(best_fitness >= tol && cnt <= no_generations) {
		mean_fitness = 0.0;
		//cout << "Generación " << cnt << endl;
		capture_offspring = 0;
		for(int k = 0; k < par_generations.size(); k++) {
			if(cnt == par_generations[k]) {
				capture_offspring = cnt;
				break;
			}
		}
		vector<vector<int> > new_pop = evolve_pop(pop);
		pop.clear();
		pop = new_pop;
		//fout << cnt << " " << mean_fitness << " " << best_fitness << endl;
		cnt++;
	}
	//fout.close();

	cout << "Terminado. Mejor fitness encontrado: " << best_fitness << endl;
	cout << "Número de generaciones: " << cnt - 1 << endl;
	cout << "Vector encontrado:" << endl;
	vector<double> x = phenotype_mapping(pop[0]);
	for(int i = 0; i < x.size(); i++) {
		cout << x[i] << " ";
	}
	cout << endl;
}
