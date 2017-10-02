#include "impares.h"

//Retorna la suma desde 1 hasta n tomando
//sólo números impares
int get_odd_numbers(int n) {
	if(n == 1)
		return 1;
	//Por si el parámetro inicial es par
	if(n % 2 == 0)
		return get_odd_numbers(n - 1);
	else
		return n + get_odd_numbers(n - 2);
}