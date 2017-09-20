#include "apuntadores.h"

void swap(double *x, double *y) {
	printf("%p %p\n", x, y);
	printf("%g %g\n", x[0], y[0]);
	double *tem = x;
	x = y;
	y = x;
	printf("Ptr desp swap %p %p\n", x, y);
	printf("%p %p\n", x[0], y[0]);
}

void smax(double smax, double smin) {
	printf("%p %p\n", &smax, &smin);
	printf("%g %g\n", smax, smin);
	if(smax < smin)
		swap(&smax, &smin);
	printf("%p %p\n", &smax, &smin);
	printf("%g %g\n", smax, smin);
}
