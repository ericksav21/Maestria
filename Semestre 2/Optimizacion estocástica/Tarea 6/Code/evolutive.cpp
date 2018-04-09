#include "evolutive.hpp"

Evolutive::Evolutive(vector<GRID> sudoku, int pop_size, double DI, double end_time) {
	this->sudoku = sudoku;
	this->pop_size = pop_size;
	this->DI = DI;
	this->end_time = end_time;
}

Evolutive::~Evolutive() {}

int Evolutive::get_best_fitness() {
	return this->best_fitness;
}

vector<vector<GRID> > Evolutive::generate_pop() {
	vector<vector<GRID> > pop(pop_size);
	for(int i = 0; i < pop_size; i++) {
		pop[i] = sudoku;
		random_solution(pop[i]);
	}

	return pop;
}

vector<GRID> Evolutive::crossover(vector<GRID> p1, vector<GRID> p2) {
	int d = p1.size();
	vector<GRID> son(d);
	for(int i = 0; i < d; i++) {
		double p = (double)rand() / (double)RAND_MAX;
		if(p < 0.5) {
			son[i] = p1[i];
		}
		else {
			son[i] = p2[i];
		}
	}

	return son;
}

vector<GRID> Evolutive::mutation(vector<GRID> sudoku) {
	int d = sudoku.size();
	vector<GRID> son = sudoku;
	for(int i = 0; i < d; i++) {
		map<int, bool> swaped;
		for(int j = 0; j < son[i].perm.size(); j++) {
			double p = (double)rand() / (double)RAND_MAX;
			if(p <= mutation_rate) {
				vector<int> ind;
				for(int k = 0; k < son[i].perm.size(); k++) {
					if(k == j) {
						continue;
					}
					ind.push_back(k);
				}
				random_shuffle(ind.begin(), ind.end());
				swap(son[i].perm[j], son[i].perm[ind[0]]);
			}
		}
	}

	return son;
}

vector<GRID> Evolutive::tournamentSelection(vector<vector<GRID> > pop) {
	vector<int> ind(pop.size());
	for(int i = 0; i < pop.size(); i++) {
		ind[i] = i;
	}
	random_shuffle(ind.begin(), ind.end());
	if(fitness(pop[ind[0]]) < fitness(pop[ind[1]])) {
		return pop[ind[0]];
	}
	else {
		return pop[ind[1]];
	}
}

int Evolutive::hamming(vector<GRID> v1, vector<GRID> v2) {
	vector<int> j1, j2;
	int d = v1.size();
	for(int i = 0; i < d; i++) {
		for(int j = 0; j < v1[i].perm.size(); j++) {
			j1.push_back(v1[i].perm[j]);
		}
		for(int j = 0; j < v2[i].perm.size(); j++) {
			j2.push_back(v2[i].perm[j]);
		}
	}
	int cnt = 0;
	for(int i = 0; i < j1.size(); i++) {
		if(j1[i] != j2[i]) {
			cnt++;
		}
	}

	return cnt;
}

vector<Individual> Evolutive::evaluate_pop(vector<vector<GRID> > pop) {
	vector<Individual> new_pop;
	for(int i = 0; i < pop.size(); i++) {
		vector<GRID> v_act = pop[i];
		int fit = fitness(v_act);
		Individual ind(v_act, fit);
		new_pop.push_back(ind);
	}
	sort(new_pop.begin(), new_pop.end(), IndividualComparator());

	return new_pop;
}

vector<vector<GRID> > Evolutive::evolve_pop(vector<vector<GRID> > pop) {
	int d = pop.size();
	vector<vector<GRID> > new_pop;

	for(int i = 0; i < d; i++) {
		new_pop.push_back(pop[i]);
	}
	int cnt = 0;
	while(cnt < d) {
		vector<GRID> p1 = tournamentSelection(pop);
		vector<GRID> p2 = tournamentSelection(pop);
		double p = (double)rand() / (double)RAND_MAX;
		if(p <= crossover_rate) {
			vector<GRID> son = mutation(crossover(p1, p2));
			new_pop.push_back(local_search(son));
			cnt++;
		}
	}

	return new_pop;
}

vector<pair<int, int> > Evolutive::get_DCN(vector<Individual> current_members, vector<Individual> new_pop) {
	vector<pair<int, int> > res;
	for(int i = 0; i < current_members.size(); i++) {
		int d_min = INT_MAX;
		for(int j = 0; j < new_pop.size(); j++) {
			int d_act = hamming(current_members[i].get_sudoku(), new_pop[j].get_sudoku());
			if(d_act < d_min) {
				d_min = d_act;
			}
		}
		res.push_back(make_pair(d_min, i));
	}

	return res;
}

vector<Individual> Evolutive::multi_dyn(vector<vector<GRID> > pop, int n, clock_t ck_1) {
	vector<Individual> current_members = evaluate_pop(pop);
	vector<Individual> new_pop;
	new_pop.push_back(current_members[0]);
	current_members.erase(current_members.begin());
	clock_t ck_2;

	while(new_pop.size() < n) {
		vector<pair<int, int> > DCN = get_DCN(current_members, new_pop);
		ck_2 = clock();
		double current_time = double(ck_2 - ck_1) / CLOCKS_PER_SEC;
		int D = (int)(DI - DI * (current_time / end_time));
		//Penalizar individuos con DCN menor que D
		vector<pair<int, int> > penalized;
		for(int i = 0; i < current_members.size(); i++) {
			if(DCN[i].first < D) {
				penalized.push_back(make_pair(i, current_members[i].get_fitness()));
				current_members[i].set_fitness(INT_MAX);
			}
		}
		//Calcular frente de pareto
		vector<int> pareto_front;
		sort(DCN.begin(), DCN.end());
		int fitness_max = INT_MAX;
		for(int i = DCN.size() - 1; i >= 0; i--) {
			int idx = DCN[i].second;
			if(current_members[idx].get_fitness() < fitness_max) {
				pareto_front.push_back(idx);
				fitness_max = current_members[idx].get_fitness();
			}
		}
		random_shuffle(pareto_front.begin(), pareto_front.end());
		int idx_to_add = pareto_front[0];
		new_pop.push_back(current_members[idx_to_add]);

		//Quitar la penalización
		for(int i = 0; i < penalized.size(); i++) {
			int idx = penalized[i].first;
			current_members[idx].set_fitness(penalized[i].second);
		}
		current_members.erase(current_members.begin() + idx_to_add);
	}

	return new_pop;
}

void Evolutive::run() {
	best_fitness = INT_MAX;
	vector<vector<GRID> > pop = generate_pop();
	for(int i = 0; i < pop.size(); i++) {
		pop[i] = local_search(pop[i]);
	}
	clock_t ck_1 = clock();
	int cnt = 1;
	while(true) {
		//cout << "Generación: " << cnt++ << endl;
		vector<vector<GRID> > ev_pop = evolve_pop(pop);
		vector<Individual> new_pop = multi_dyn(ev_pop, pop_size, ck_1);
		sort(new_pop.begin(), new_pop.end(), IndividualComparator());
		best_fitness = new_pop[0].get_fitness();
		//cout << "Mejor fitness de la generación: " << best_fitness << endl;
		pop.clear();
		for(int i = 0; i < new_pop.size(); i++) {
			pop.push_back(new_pop[i].get_sudoku());
		}
		if(best_fitness == 0) {
			break;
		}
		clock_t ck_2 = clock();
		double current_time = double(ck_2 - ck_1) / CLOCKS_PER_SEC;
		if(current_time > end_time) {
			break;
		}
		cnt++;
	}
	cout << "Terminado . Mejor fitness encontrado: " << best_fitness << endl;
	cout << "Número de generaciones: " << cnt << endl;
	clock_t ck_2 = clock();
	double current_time = double(ck_2 - ck_1) / CLOCKS_PER_SEC;
	cout << "Tiempo transcurrido (seg): " << current_time << endl;
}