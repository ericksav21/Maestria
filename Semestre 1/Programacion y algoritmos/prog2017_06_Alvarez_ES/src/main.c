#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "memo.h"
#include "frecuencias.h"
#include "separador.h"
#include "metricas_calidad.h"
#include "funciones.h"
#include "generador.h"

int main(int argc, char **argv) {
	ARGSOBJ *args = (ARGSOBJ *)malloc(sizeof(ARGSOBJ));
	strcpy(args->quality_metric, "accuracy");
	args->seed = time(NULL);

	if(!read_args(argc, argv, args)) {
		free(args);
		return 0;
	}
	srand(args->seed);

	FOBJ *params = mem_obj_alloc(args);

	params = set_quality_metric(params, args->quality_metric);
	
	printf("\n**---------- Generador binario ----------**\n");
	int *best_vb = get_best_bv(args, params);
	printf("Mejor vector binario:\n");
	for(int i = 0; i < args->nwords; i++) {
		printf("%d ", best_vb[i]);
	}
	printf("\nCalidad producida por el vector: %lf%%\n", metric_eval(params, best_vb) * 100.0);

	//Liberar memoria
	free(args);
	params = free_obj_mem(params);
	free(params);
	delete_arr1d((void *)best_vb);

	return 0;
}
