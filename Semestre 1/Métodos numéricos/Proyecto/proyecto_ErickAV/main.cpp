#include <stdio.h>

#include "image.h"
#include "matriz_vector.h"
#include "met_num.h"

int main(int argc, char **argv) {
	if(argc < 3) {
		printf("Error. Ejecuta: %s [Ruta imagen 1] [Ruta imagen 2]\n", argv[0]);
		return 0;
	}

	IMG *img1 = read_img(argv[1]);
	IMG *img2 = read_img(argv[2]);
	int width = img1->width;
	int height = img1->height;

	double **vx = create_matrix(height, width, double);
	double **vy = create_matrix(height, width, double);
	for(int i = 0; i < height; i++) {
		for(int j = 0; j < width; j++) {
			vx[i][j] = vy[i][j] = 0.0;
		}
	}

	Horn_Schunck(img1, img2, &vx, &vy, 10000, 1.9);

	IMG *out = create_img(width, height);
	quiver(out, vx, vy, width, height);
	print_img(out, "out.pgm");

	free_img(img1);
	free_img(img2);
	free_img(out);
	free_matrix(vx);
	free_matrix(vy);

    return 0;
}