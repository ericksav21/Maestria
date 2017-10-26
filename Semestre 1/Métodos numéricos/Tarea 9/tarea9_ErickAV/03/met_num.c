#include "met_num.h"

double get_EPS() {
    double Eps = 1.0;
 
    while (1.0 + Eps / 2.0 != 1.0)
        Eps /= 2.0;

    return Eps;
}

double prod(double *x, double xc, int i) {
	if(i == 0)
		return 1.0;
	double res = 1.0;
	for(int j = 0; j < i; j++) {
		res *= (xc - x[j]);
	}

	return res;
}