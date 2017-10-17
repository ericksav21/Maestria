#include <stdio.h>
#include <string.h>

#include "imagen.h"
#include "lista_ligada.h"
#include "rectas.h"

int main(int argc, char **argv) {
	/*char files_name[30];
	strcpy(files_name, argv[1]);*/
	//int b = atoi(argv[1]);

	for(int i = 1; i <= 21; i++) {
		NODEPTR lines = NULL;
		char files_name[30], out_name[30];
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
		double *angles = get_angles(lines);
		for(int a = 0; a < lsz - 1; a++) {
			printf("Angulo %d: %lf\n", a + 1, angles[a]);
		}
		printf("\n");

		free_img(img);
		free_img(sk);
		free_img(resized);
		free_list(path);
	}

	return 0;
}