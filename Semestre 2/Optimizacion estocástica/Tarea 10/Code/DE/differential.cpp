#include "differential.hpp"

Differential::Differential(int pop_size, double linf, double lsup, string func_type, int iter_max) {
	this->pop_size = pop_size;
	this->linf = linf;
	this->lsup = lsup;
	this->func_type = func_type;
	this->iter_max = iter_max;
}

Differential::~Differential() {}

double Differential::get_f(vector<double> x) {
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

void Differential::print_pop(vector<pair<vector<double>, double > > pop) {
	for(int i = 0; i < pop_size; i++) {
		vector<double> vaux = pop[i].first;
		for(int j = 0; j < dim; j++) {
			cout << vaux[j] << " ";
		}
		cout << "Val: " << pop[i].second << endl;
	}
}

vector<pair<vector<double>, double > > Differential::generate_pop() {
	vector<pair<vector<double>, double > > pop;
	for(int i = 0; i < pop_size; i++) {
		vector<double> vaux(dim, 0.0);
		for(int j = 0; j < dim; j++) {
			double r = (double)rand() / (double)RAND_MAX;
			vaux[j] = r * (lsup - linf) + linf;
		}
		double feval = get_f(vaux);
		pop.push_back(make_pair(vaux, feval));
	}

	return pop;
}

void Differential::set_CR(double cr) {
	this->cr = cr;
}

double Differential::get_best() {
	return this->best;
}

void Differential::run() {
	//Generar la población
	vector<pair<vector<double>, double > > pop = generate_pop();
	best = DBL_MAX;
	int idx = -1;
	for(int i = 0; i < iter_max; i++) {
		vector<pair<vector<double>, double > > new_pop;
		for(int j = 0; j < pop.size(); j++) {
			//Generar los 3 índices distintos
			int r1 = 0, r2 = 0, r3 = 0;
			do {
				r1 = rand_in_range(1, pop.size() - 1);
			} while(r1 == j);
			do {
				r2 = rand_in_range(1, pop.size() - 1);
			} while(r2 == r1 || r2 == j);
			do {
				r3 = rand_in_range(1, pop.size() - 1);
			} while(r3 == r2 || r3 == r1 || r3 == j);

			double r = (double)rand() / (double)RAND_MAX;
			int krand = (int)floor(r * (double)dim) + 1;
			vector<double> nnew(dim);

			for(int k = 0; k < dim; k++) {
				double p = (double)rand() / (double)RAND_MAX;
				if(p <= cr || k == krand) {
					nnew[k] = pop[r1].first[k] + F * (pop[r2].first[k] - pop[r3].first[k]);
				}
				else {
					nnew[k] = pop[j].first[k];
				}
			}

			double feval = get_f(nnew);
			if(feval < pop[j].second) {
				new_pop.push_back(make_pair(nnew, feval));
			}
			else {
				new_pop.push_back(make_pair(pop[j].first, pop[j].second));
			}
		}
		pop = new_pop;
		for(int j = 0; j < pop.size(); j++) {
			if(pop[j].second < best) {
				best = pop[j].second;
				idx = j;
			}
		}
		//cout << "Iteración " << (i + 1) << endl;
		//cout << "Mejor fitness de la población: " << best << ", idx: " << idx << endl << endl;
	}
	cout << "Terminado:" << endl;
	vector<double> x_res = pop[idx].first;
	for(int i = 0; i < x_res.size(); i++) {
		cout << x_res[i] << " ";
	}
	cout << endl;
}