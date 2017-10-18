#include <stdio.h>
#include <string.h>
#include <time.h>

#include "imagen.h"
#include "lista_ligada.h"
#include "rectas.h"

int main(int argc, char **argv) {
	srand(time(NULL));
	FILE *fangles = fopen("angulos.txt", "w");
	FILE *flens = fopen("longitudes.txt", "w");
	printf("Procesando...\n");

	for(int i = 1; i <= 21; i++) {
		NODEPTR lines = NULL;
		char files_name[40], out_name[30];

		sprintf(files_name, "frame_%drata3_bin.pgm", i);
		sprintf(out_name, "out%d.pgm", i);

		IMG *img = read_img(files_name);
		IMG *resized = resize_img(img);
		IMG *sk = skeletonize(resized);
		PIXEL p1, p2;
		NODEPTR path = NULL;

		clean_skeletonize(sk, &p1, &p2, &path);
		lines = get_lines(resized, p1, p2, path, i);
		int lsz = list_size(lines);
		print_img(resized, out_name);
		double *angles = get_angles(lines);
		double *lens = get_lens(lines);
		append_angles(angles, lsz - 1, i, fangles);
		append_lens(lens, lsz - 1, i, flens);

		free_img(img);
		free_img(sk);
		free_img(resized);
		free_list(path);
		free_vector(angles);
	}

	printf("Terminado.\n");
	fclose(fangles);
	fclose(flens);

	return 0;
}