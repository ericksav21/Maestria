#include <stdio.h>
#include <math.h>

#include <gsl/gsl_math.h>
#include <gsl/gsl_ieee_utils.h>
#include <fenv.h> 

void funcion1(double x) {
	double x0 = x;
	for(int i=1; i<=60; ++i) {
		double c = (double)i;
		printf("%28.20e            ", c);
		gsl_ieee_printf_double(&c);

		x = sqrt(x);

		printf("\n\n%28.20e            ", x);
		gsl_ieee_printf_double(&x);
		printf("\n");

		if(x==x0) break;
		else x0 = x;
	}
}

int main(void)  {
	double em = DBL_EPSILON;

	printf("Em:                Decimal                                     Binario\n");
	printf("%28.20e            ", em);
	gsl_ieee_printf_double(&em);

	double a = 1.0 + em;
	printf("\n\nA:                 Decimal                                     Binario\n");
	printf("%28.20e            ", a);
	gsl_ieee_printf_double(&a);

	double b = 1.0 - em / 2.0;
	printf("\n\nB:                 Decimal                                     Binario\n");
	printf("%28.20e            ", b);
	gsl_ieee_printf_double(&b);

	printf("\n\n2:             Decimal                                                      Binario\n");
	funcion1(2.0);
	printf("\n\n");
	printf("\n\n10e10:         Decimal                                                      Binario\n");
	funcion1(10e10);

	return 0;
}
