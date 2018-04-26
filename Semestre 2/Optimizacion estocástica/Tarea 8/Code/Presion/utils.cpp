#include "utils.hpp"

int rand_in_range(int a, int b) {
	return rand() % (b - a + 1) + a;
}

bool is_eq(vector<int> x) {
	bool res = true;
	int n = x[0];
	for(int i = 1; i < x.size(); i++) {
		if(x[i] != n) {
			res = false;
			break;
		}
	}

	return res;
}

vector<int> generate_pop(int n) {
	vector<int> res(n);
	for(int i = 0; i < n; i++) {
		res[i] = rand_in_range(1, 10);
	}

	return res;
}

int binary_tournament(vector<int> x) {
	int i1 = 0, i2 = 0;
	int d = x.size();
	while(i1 == i2) {
		i1 = rand_in_range(1, d - 1);
		i2 = rand_in_range(1, d - 1);
	}

	return max(x[i1], x[i2]);
}

int roulette(vector<int> x) {
	double sum = 0.0, prob_offset = 0.0;
	int d = x.size();
	vector<double> prob(d);
	for(int i = 0; i < d; i++) {
		sum += (double)x[i];
	}
	double p = (double)rand() / (double)RAND_MAX;
	p *= sum;
	for(int i = 0; i < d; i++) {
		p -= (double)x[i];
		if(p < 0) {
			return x[i];
		}
	}

	return x[d - 1];
}

vector<int> process(vector<int> x, int selection_type) {
	int n = 1;
	int d = x.size();
	while(true) {
		vector<int> new_x(d);
		for(int i = 0; i < d; i++) {
			int aux;
			if(selection_type == 1) {
				aux = binary_tournament(x);
			}
			else {
				aux = roulette(x);	
			}
			new_x[i] = aux;
		}
		x = new_x;
		if(is_eq(x)) {
			break;
		}
		n++;
	}

	vector<int> res(2);
	res[0] = n;
	res[1] = x[0];

	return res;
}