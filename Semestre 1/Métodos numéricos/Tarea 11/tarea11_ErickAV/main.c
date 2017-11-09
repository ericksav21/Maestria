#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "memo.h"
#include "met_num.h"

int main(int argc, char **argv) {
	if(argc < 5) {
		printf("Error. Ejecuta: %s [Límite inferior] [Límite superior] [N] [Funcion].\n", argv[0]);
		return 0;
	}
	double a = atof(argv[1]), b = atof(argv[2]);
	int n = atoi(argv[3]), ft = atoi(argv[4]);
	
	double area = 0.0, res = 0.0, err = 0.0;
	if(ft == 1) {
		area = eval(f1, n, a, b);
		res = F1(a, b);
		err = fabs(res - area) / fabs(res);
	}
	else {
		area = eval(f2, n, a, b);
		res = F2(a, b);
		err = fabs(res - area) / fabs(res);
	}

	printf("Límites de integración: [%lf, %lf], valor de n: %d\n", a, b, n);
	printf("Estimación del área: %g\n", area);
	printf("Solución analítica: %g\n", res);
	printf("Error relativo: %.5e\n", err);

	return 0;
}