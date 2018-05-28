#include "handler.hpp"

/*----- Functions section -----*/
double sphere(double const *x, int n) {
	double res = 0.0;

	for(int i = 0; i < n; i++) {
		res += (x[i] * x[i]);
	}

	return res;
}

double ellipsoid(double const *x, int n) {
	double res = 0.0;

	for(int i = 0; i < n; i++) {
		res += pow(10.0, 6.0 * (i / (double)n - 1)) * (x[i] * x[i]);
	}

	return res;
}

double zakharov(double const *x, int n) {
	double s1 = 0.0, s2 = 0.0;

	for(int i = 0; i < n; i++) {
		s1 += (x[i] * x[i]);
		s2 += 0.5 * (double)(i + 1) * x[i];
	}

	return s1 + (s2 * s2) + pow(s2, 4.0);
}

double rosenbrock(double const *x, int n) {
	double res = 0.0;

	for(int i = 0; i < n - 1; i++) {
		res += (pow(x[i] - 1.0, 2) + 100.0 * pow(x[i + 1] - x[i] * x[i], 2));
	}

	return res;
}

double ackley(double const *x, int n) {
	double sp = sphere(x, n);
	double cs = 0.0;
	double div = 1.0 / (double)n;
	for(int i = 0; i < n; i++) {
		cs += cos(2.0 * M_PI * x[i]);
	}

	return -20.0 * exp(-0.2 * sqrt(div * sp)) - exp(div * cs) + 20.0 + M_E;
}

double griewank(double const *x, int n) {
	double sum = 0.0;
	double prod = 1.0;

	for(int i = 0; i < n; i++) {
		sum += ((x[i] * x[i]) / 4000.0);
		prod *= cos(x[i] / sqrt((double)i + 1.0));
	}

	return sum - prod + 1.0;
}

double rastrigin(double const *x, int n) {
	double sum = 0.0;

	for(int i = 0; i < n; i++) {
		sum += (x[i] * x[i] - 10.0 * cos(2.0 * M_PI * x[i]));
	}

	return 10.0 * n + sum;
}
/*----- End Functions section -----*/

double fitfun(double const *x, int n, string ftype) {
	if(ftype == "f1") {
		return sphere(x, n);
	}
	else if(ftype == "f2") {
		return ellipsoid(x, n);
	}
	else if(ftype == "f3") {
		return zakharov(x, n);
	}
	else if(ftype == "f4") {
		return rosenbrock(x, n);
	}
	else if(ftype == "f5") {
		return ackley(x, n);
	}
	else if(ftype == "f6") {
		return griewank(x, n);
	}
	else {
		//cout << "ras\n";
		return rastrigin(x, n);
	}
}

double get_median(vector<double> v) {
	vector<double> aux = v;
	sort(aux.begin(), aux.end());
	int mid = aux.size() / 2;
	if(aux.size() % 2 == 0) {
		return (aux[mid] + aux[mid - 1]) / 2.0;
	}
	else {
		return aux[mid];
	}
}

void generate_ind(double *x, int n, double linf, double lsup) {
	for(int i = 0; i < n; i++) {
		double r = (double)rand() / (double)RAND_MAX;
		x[i] = r * (lsup - linf) + linf;
	}
}

double exec(int dim, string ftype, int eval_max, double linf, double lsup, double sd) {
	CMAES<double> evo;
	double *arFunvals, *const*pop, *xfinal;
	int iter_max = (eval_max * dim) / evo.PopSize;
	cout << "Dimensión: " << dim << endl;
	cout << "Número de evaluaciones máximo: " << (eval_max * dim) << endl;
	cout << "Número de generaciones máximo: " << iter_max << endl;

	// Initialize everything
	double xstart[dim];
	double stddev[dim];
	generate_ind(xstart, dim, linf, lsup);
	for(int i = 0; i < dim; i++) {
		//xstart[i] = 0.5;
		stddev[i] = sd;
	}
	Parameters<double> parameters;
	parameters.init(dim, xstart, stddev);
	arFunvals = evo.init(parameters);

	int cnt = 0;
	while(cnt < iter_max) {
	//while(!evo.testForTermination()) {
		// Generate lambda new search points, sample population
		pop = evo.samplePopulation();

		for (int i = 0; i < evo.get(CMAES<double>::Lambda); i++) {
			arFunvals[i] = fitfun(pop[i], (int)evo.get(CMAES<double>::Dimension), ftype);
		}

		// update the search distribution used for sampleDistribution()
		evo.updateDistribution(arFunvals);
		cnt++;
	}
	//std::cout << "Algoritmo terminado:" << std::endl << evo.getStopMessage();
	//evo.writeToFile(CMAES<double>::WKResume, "resumeevo1.dat"); // write resumable state of CMA-ES

	// get best estimator for the optimum, xmean
	xfinal = evo.getNew(CMAES<double>::XMean);
	/*for(int i = 0; i < dim; i++) {
		cout << xfinal[i] << " ";
	}
	cout << endl << "Error: " << evo.get(CMAES<double>::Fitness) << endl;*/

	// do something with final solution and finally release memory
	delete[] xfinal;

	return evo.get(CMAES<double>::Fitness);
}