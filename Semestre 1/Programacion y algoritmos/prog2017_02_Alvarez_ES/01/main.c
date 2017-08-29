#include "fpunteros.h"

int main() {
	//Se genera una semilla basada en el tiempo de la máquina
	srand(time(NULL));
	char arr[1600];

	printf("%d\n", funcion_4(arr));
	return 0;
}
