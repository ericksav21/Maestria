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

vector<double> confidence_interval(vector<double> a) {
	int m = 1000;
	double alpha = 0.025;
	vector<double> samp;
	for(int i = 0; i < m; i++) {
		int r = rand_in_range(0, a.size() - 1);
		samp.push_back(a[r]);
	}
	sort(samp.begin(), samp.end());
	int k = floor(alpha * m);
	double z_low = samp[k];
	double z_up = samp[m - k];
	vector<double> res = {z_low, z_up};

	return res;
}

int statistical_test(vector<double> d1, vector<double> d2, double alpha) {
	double m1 = get_mean(d1);
	double m2 = get_mean(d2);
	double theta = fabs(m1 - m2);
	cout << "Theta: " << theta << endl;

	int m = 5000;
	int v_sz = 1000;
	vector<double> phi, c;
	c.insert(c.end(), d1.begin(), d1.end());
	c.insert(c.end(), d2.begin(), d2.end());
	for(int i = 0; i < m; i++) {
		vector<double> samp, x, y;
		for(int j = 0; j < c.size(); j++) {
			int r = rand_in_range(0, c.size() - 1);
			samp.push_back(c[r]);
		}
		for(int j = 0; j < d1.size(); j++) {
			x.push_back(samp[j]);
		}
		for(int j = d1.size() + 1; j < c.size(); j++) {
			y.push_back(samp[j]);
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