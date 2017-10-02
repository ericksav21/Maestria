#include "promedio.h"

double get_avr(int n) {
	if(n == 1)
		return 1.0;
	return get_avr(n - 1) + 0.5;
}