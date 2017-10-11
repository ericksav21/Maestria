#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Si la macro NDEBUG no está definida entonces DEBUGPRINT imprimirá el mensaje
#ifndef NDEBUG
//Esta macro tiene número variable de argumentos, esto nos sirve para mandar todo
//argumento pasado a la función printf
#define DEBUGPRINT(format, ...) printf(format, __VA_ARGS__)
#else
//Debemos definir la macro de todas formas, si no, no compilará
#define DEBUGPRINT(format, ...)
#endif

//Aprovechamos la macro para pasar el tipo de dato solicitado.
#define VECTOR_TRASLADADO(tipo, I0, In) (tipo *)create_arr(I0, In, sizeof(tipo))

#define FREEVECTOR_TRASLADADO(Arr, tipo, I0) free_arr((void *)Arr, I0, sizeof(tipo))

void* create_arr(int i0, int in, size_t size_type) {
	int sz = (in - i0 + 1);
	void *arr = (void *)malloc(sz * size_type);
	DEBUGPRINT("Malloc devuelve: %p\n", arr);
	//Se recorre el puntero I0 veces para que empiece y termine correctamente en
	//el índice solicitado.
	arr = arr - i0 * size_type;
	return arr;
}

void free_arr(void *arr, int i0, size_t size_type) {
	//Hay que regresar el puntero a su posición inicial para liberarlo correctamente.
	arr = arr + i0 * size_type;
	DEBUGPRINT("Se devuelve el vector desde la posición: %p\n", arr);
	free(arr);
}

int main(int argc, char **argv) {
	if(argc < 3) {
		printf("Error. Ejecuta %s [I0] [In]\n", argv[0]);
		return 0;
	}

	int i0, in;
	i0 = atoi(argv[1]);
	in = atoi(argv[2]);
	double *arr = VECTOR_TRASLADADO(double, i0, in);
	DEBUGPRINT("El vector en la posición I0(%d): %p\n", i0, &arr[i0]);
	for(int i = i0; i <= in; i++)
		arr[i] = i + 0.5;

	for(int i = i0; i <= in; i++)
		printf("%lf ", arr[i]);
	printf("\n");

	FREEVECTOR_TRASLADADO(arr, double, i0);

	return 0;
}
