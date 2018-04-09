#include "genetic.hpp"

Genetic::Genetic(int pop_size, int a, int b, int no_evaluations, string func_type) {
	this->pop_size = pop_size;
	this->a = a;
	this->b = b;
	this->no_evaluations = no_evaluations;
	this->func_type = func_type;
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

vector<int> Genetic::tournament_selection(vector<vector<int> > pop, vector<Individual> s) {
	vector<int> ids(pop_size);
	for(int i = 0; i < pop_size; i++) {
		ids[i] = i;
	}
	random_shuffle(ids.begin(), ids.end());

	vector<vector<int> > candidates(tournament_size);
	for(int i = 0; i < tournament_size; i++) {
		candidates[i] = pop[ids[i]];
	}
	//Hacer el torneo
	return get_fittest(candidates, s);
}

vector<int> Genetic::crossover(vector<int> v1, vector<int> v2) {
	int d = v1.size();
	int co_point = rand_in_range(1, d - 2);
	vector<int> res(d, 0);
	double p = (double)rand() / (double)RAND_MAX;

	for(int i = 0; i < co_point; i++) {
		if(p < 0.5) {
			res[i] = v1[i];
		}
		else {
			res[i] = v2[i];
		}
	}
	for(int i = co_point; i < d; i++) {
		if(p < 0.5) {
			res[i] = v2[i];
		}
		else {
			res[i] = v1[i];
		}
	}

	return res;
}

vector<int> Genetic::mutation(vector<int> bv) {
	vector<int> res = bv;
	for(int i = 0; i < bv.size(); i++) {
		int p = rand_in_range(1, 100);
		if(p <= (int)(mutation_rate * 100.0)) {
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
	int same_ind_no = 10;
	vector<vector<int> > new_pop(pop_size);
	//Obtener el mejor elemento
	vector<Individual> S = evaluate_pop(pop_act);
	for(int i = 0; i < same_ind_no; i++) {
		new_pop[i] = S[i].get_bv();
	}

	//Cruza
	for(int i = same_ind_no; i < pop_size; i++) {
		vector<int> p1 = tournament_selection(pop_act, S);
		vector<int> p2 = tournament_selection(pop_act, S);
		new_pop[i] = mutation(crossover(p1, p2));
	}

	best_fitness = S[0].get_fitness();
	cout << "Mejor fitness de la generación: " << best_fitness << endl;
	return new_pop;
}

double Genetic::get_fitness_cnt() {
	return fitness_cnt;
}

double Genetic::get_bets_fitness() {
	return best_fitness;
}

void Genetic::run(int no, string out_dir) {
	double tol = 1e-3;
	fitness_cnt = 0;
	best_fitness = DBL_MAX;
	vector<vector<int> > pop(pop_size);
	pop = generate_pop();

	ostringstream ost;
	ost << out_dir << "/data_fitness_";
	ost << no;
	ost << ".txt";
	ofstream fout(ost.str().c_str());
	int iter_cnt = 5, iter_reg_val = iter_cnt;

	int cnt = 1;
	while(best_fitness >= tol && fitness_cnt <= no_evaluations) {
		cout << "Generación " << cnt << endl;
		vector<vector<int> > new_pop = evolve_pop(pop);
		cout << "Número de evaluaciones de la función: " << fitness_cnt << endl << endl;
		pop.clear();
		pop = new_pop;
		if(cnt == iter_cnt) {
			fout << "Iter = " << cnt << endl;
			for(int i = 0; i < pop_size; i++) {
				for(int j = 0; j < pop[0].size(); j++) {
					fout << pop[i][j] << " ";
				}
				fout << endl;
			}
			fout << get_f(phenotype_mapping(pop[0])) << endl << endl;
			iter_cnt += iter_reg_val;
		}
		cnt++;
	}

	fout.close();
	cout << "Terminado. Mejor fitness encontrado: " << best_fitness << "\nNúmero de evaluaciones: " << fitness_cnt << endl;
	cout << "Número de generaciones: " << cnt - 1 << endl;
	cout << "Vector encontrado:" << endl;
	vector<double> x = phenotype_mapping(pop[0]);
	for(int i = 0; i < x.size(); i++) {
		cout << x[i] << " ";
	}
	cout << endl;
}