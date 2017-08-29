#include "fpunteros.h"

//Retorna un entero aleatorio entre 'a' y 'b'
int rand_in_range(int a, int b) {
	return rand() % (b - a + 1) + a;
}

//Calcula el tamaño de un tipo de dato, esto lo hace generando un arreglo
//vacío de 2 posiciones y restando las direcciones de memoria casteadas
int funcion_1(int t) {
	//Se usa un tipo 'long int' ya que el cast de la dirección de memoria
	//Puede sobrepasar el valor del entero
        long int size;
        if(t == 0) {
                char arr[2];
                size = (long int)&arr[1] - (long int)&arr[0];
        }
        else if(t == 1) {
                int arr[2];
                size = (long int)&arr[1] - (long int)&arr[0];
        }
        else if(t == 2) {
                float arr[2];
                size = (long int)&arr[1] - (long int)&arr[0];
        }
        else {
                double arr[2];
                size = (long int)&arr[1] - (long int)&arr[0];
        }

	//Se castea a entero ya que el resultado no pasará de 8
        return (int)size;
}

//Llena un arreglo de chars hasta una cierta posición 'n'
//utilizando diferentes tipos de datos
void funcion_2(int t, int n, char *arr) {
	//Para el tipo char solo se requiere recorrer el arreglo y
	//llenarlo con valores ascii de entre 48 y 122
        if(t == 0) {
                int d = 48;
                for(int i = 0; i < n; i++) {
                        arr[i] = d;
                        d++;
                        if(d == 123)
                                d = 48;
                }
        }
	//Para el caso de enteros se facilita crear un puntero de enteros
	//y utilizar el mismo para almacenar valores enteros ya que este avanza
	//de 4 en 4 bytes
        else if(t == 1) {
                int *aux = (int *)arr;
                for(int i = 0; i < n; i++) {
                        *aux = i;
                        aux++;
                }
        }
	//Misma estrategia que en el caso anterior solo que esta vez se llenará
	//el arreglo con valores entre 0 y 1 utilizando un tamaño de paso de 1/(n-1)
	else if(t == 2) {
                float *aux = (float *)arr;
                float val = 0.0;
                for(int i = 0; i < n; i++) {
                        *aux = val;
                        aux++;
                        val += (1.0 / (float)(n - 1));
                }
        }
	//Igual que el caso anterior pero se usará un puntero de doubles ya que el avance
	//es de 8 bytes
        else if(t == 3){
                double *aux = (double *)arr;
                double val = 0.0;
                for(int i = 0; i < n; i++) {
                        *aux = val;
                        aux++;
                        val += (1.0 / (double)(n - 1));
		}
        }
}

//Recorre el arreglo hasta la posición n-1 e imprime sus valores de acuerdo
//al tipo. Esta función usa la estrategia de la anterior creando punteros
//de diferentes tipos
void funcion_3(int t, int n, char *arr) {
        if(t == 0) {
                for(int i = 0; i < n; i++)
                        printf("Pos %d: %c\n", i, arr[i]);
        }
        else if(t == 1) {
                int *aux = (int *)arr;
                for(int i = 0; i < n; i++) {
                        printf("Pos %d: %d\n", i, *aux);
                        aux++;
                }
        }
        else if(t == 2) {
                float *aux = (float *)arr;
                for(int i = 0; i < n; i++) {
                        printf("Pos %d: %f\n", i, *aux);
                        aux++;
                }
        }
        else {
                double *aux = (double *)arr;
                for(int i = 0; i < n; i++) {
                        printf("Pos %d: %lf\n", i, *aux);
                        aux++;
                }
        }
}

//Esta función muestra una posición generada aleatoriamente y pide al usuario
//que ingrese un desplazamiento (izquierda-derecha) de esa posición, en caso
//de ser correcto, llama a la función funcion_2 y funcion_3.
int funcion_4(char *arr) {
	int n, r_ty, r_in = 0;
	long int resp, expected;

	//Se calculan todos los rands necesarios
	r_ty = rand_in_range(0, 3);
	while(r_in == 0)
		r_in = rand_in_range(-3, 3);

	if(r_ty == 0) {
		printf("Tipo elegido: char\n");
		n = rand_in_range(1, 1599);
	}
	else if(r_ty == 1 || r_ty == 2) {
		if(r_ty == 1)
			printf("Tipo elegido: int\n");
		else
			printf("Tipo elegido: float\n");

		n = rand_in_range(1, 399);
	}
	else {
		printf("Tipo elegido: double\n");
		n = rand_in_range(1, 199);
	}

	//Se calcula la respuesta que debe ingresar el usuario
	expected = (long int)(&arr[n]) + (r_in * funcion_1(r_ty));

	printf("Ingresa un número en hexadecimal desplazado %d posiciones de la siguiente: %p\n", r_in, &arr[n]);
	printf("Valor: ");
	scanf("%lx", &resp);

	//Si la respuesta fue correcta se mandan llamar las funciones 2 y 3
	if(resp == expected) {
		printf("Correcto!\n");
		funcion_2(r_ty, n, arr);
		funcion_3(r_ty, n, arr);
	}
	//Caso contrario se termina la ejecución
	else {
		printf("Incorrecto! Valor esperado: 0x%lx\n", expected);
	}

	return r_ty;
}
