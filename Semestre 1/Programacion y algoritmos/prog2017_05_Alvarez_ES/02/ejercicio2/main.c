#include "apuntadores.h"

int main(int argc, char *argv[]) {

	int n = 9, samples = 10;
	double *x = (double *)malloc(sizeof(double)*n);
	llenaVector(x, n);
	for(int i = 0; i < n; i++)
		printf("%lf ", x[i]);

	double moda = calculaModa(x, n);
	
	printf("\n%lf\n", moda);

	free(x);
	
	return 0;
}
