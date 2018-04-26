#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <utility>
#include <algorithm>
#include <cfloat>
#include <unistd.h>

#include "utils.hpp"

using namespace std;

int main(int argc, char **argv) {
	srand(time(NULL));
	int m = 100, n = 50;
	double avg_bt = 0.0, avg_r = 0.0;
	vector<int> x = generate_pop(n);

	for (int i = 0; i < m; i++) {
		srand(time(NULL));
		vector<int> r1 = process(x, 1);
		vector<int> r2 = process(x, 2);

		cout << "Iteración " << (i + 1) << endl;
		cout << "Selección por torneo. N = " << r1[0] << ", Valor = " << r1[1] << endl;
		cout << "Ruleta. N = " << r2[0] << ", Valor = " << r2[1] << endl << endl;
		avg_bt += (double)r1[0];
		avg_r += (double)r2[0];
		sleep(1.5);
	}
	avg_bt /= (double)m;
	avg_r /= (double)m;

	cout << "Termiado." << endl << "Promedio N selección por torneo: " << avg_bt << endl;
	cout << "Promedio N ruleta: " << avg_r << endl;

	return 0;
}