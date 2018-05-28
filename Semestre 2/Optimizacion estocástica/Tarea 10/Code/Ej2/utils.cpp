#include "utils.hpp"

vector<double> read_file(string file_name) {
	ifstream f;
	f.open(file_name.c_str());
	vector<double> res;
	double n;
	while (f >> n) {
		res.push_back(n);
    }

	f.close();

	return res;
}

double get_mean(vector<double> x) {
	double res = 0.0;
	for(int i = 0; i < x.size(); i++) {
		res += x[i];
	}
	res /= (double)x.size();

	return res;
}

int rand_in_range(int a, int b) {
	return rand() % (b - a + 1) + a;
}

int statistical_test(vector<double> d1, vector<double> d2, double alpha) {
	double m1 = get_mean(d1);
	double m2 = get_mean(d2);
	double theta = fabs(m1 - m2);
	cout << "Theta: " << theta << endl;

	int m = 5000;
	int v_sz = 1000;
	vector<double> phi;
	for(int i = 0; i < m; i++) {
		vector<double> x, y;
		for(int j = 0; j < v_sz; j++) {
			int r1 = rand_in_range(0, d1.size() - 1);
			int r2 = rand_in_range(0, d2.size() - 1);
			x.push_back(d1[r1]);
			y.push_back(d1[r2]);
		}
		double mx = get_mean(x);
		double my = get_mean(y);
		phi.push_back(fabs(mx - my));
		//cout << "Phi_i: " << phi[i] << endl;
	}
	int cnt = 0;
	for(int i = 0; i < phi.size(); i++) {
		if(phi[i] > theta) {
			cnt++;
		}
	}
	double p_val = (double)cnt / (double)m;
	cout << "P value: " << p_val << endl;
	if(p_val > alpha) {
		cout << "Se acepta H0" << endl << endl;
		return 0;
	}
	else {
		cout << "Se rechaza H0" << endl << endl;
		if(m1 < m2) {
			return 1;
		}
		else {
			return 2;
		}
	}
}