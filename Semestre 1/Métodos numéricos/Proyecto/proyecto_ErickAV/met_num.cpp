#include "met_num.h"

int** pderivative_x(IMG *img) {
	int width = img->width;
	int height = img->height;
	int **res = create_matrix(width, height, int);
	for(int i = 0; i < height; i++) {
		for(int j = 1; j < width - 1; j++) {
			res[i][j] = (img->mat[i][j + 1] - img->mat[i][j - 1]) / 2;
		}
		res[i][0] = img->mat[i][0];
		res[i][width - 1] = img->mat[i][width - 1];
	}

	return res;
}

int** pderivative_y(IMG *img) {
	int width = img->width;
	int height = img->height;
	int **res = create_matrix(height, width, int);
	for(int i = 0; i < width; i++) {
		for(int j = 1; j < height - 1; j++) {
			res[j][i] = (img->mat[j + 1][i] - img->mat[j - 1][i]) / 2;
		}
		res[0][i] = img->mat[0][i];
		res[height - 1][i] = img->mat[height - 1][i];
	}

	return res;
}

int** pderivative_t(IMG *img1, IMG *img2) {
	int width = img1->width;
	int height = img1->height;
	int **res = create_matrix(height, width, int);
	for(int i = 0; i < height; i++) {
		for(int j = 0; j < width; j++) {
			res[i][j] = (img2->mat[i][j] - img1->mat[i][j]) / 2;
		}
	}

	return res;
}

void get_derivatives(IMG *img1, IMG *img2, int **dx, int **dy, int ***dt) {
	int width = img1->width;
	int height = img1->height;

	int **dx1 = pderivative_x(img1);
	int **dy1 = pderivative_y(img1);
	int **dx2 = pderivative_x(img2);
	int **dy2 = pderivative_y(img2);

	dx = add_mat(dx1, dx2, dx, height, width);
	dy = add_mat(dy1, dy2, dy, height, width);

	for(int i = 0; i < height; i++) {
		for(int j = 0; j < width; j++) {
			if(dx[i][j] > 255)
				dx[i][j] = 255;
			if(dy[i][j] > 255)
				dy[i][j] = 255;
		}
	}
	(*dt) = pderivative_t(img1, img2);

	free_matrix(dx1);
	free_matrix(dy1);
	free_matrix(dx2);
	free_matrix(dy2);
}

void Horn_Schunck(IMG *img1, IMG *img2, double ***vx, double ***vy, int iter, double lambda) {
	int width = img1->width;
	int height = img1->height;

	//Obtener las derivadas parciales
	int **dx = create_matrix(height, width, int);
	int **dy = create_matrix(height, width, int);
	int **dt;
	get_derivatives(img1, img2, dx, dy, &dt);
	
	int k = 0;
	double **vx1 = create_matrix(height, width, double);
	double **vy1 = create_matrix(height, width, double);
	while(k < iter) {
		printf("Iteración %d.\n", (k + 1));
		for(int i = 0; i < height; i++) {
			for(int j = 0; j < width; j++) {
				vx1[i][j] = vy1[i][j] = 0.0;
			}
		}

		for(int i = 1; i < height - 1; i++) {
			for(int j = 1; j < width - 1; j++) {
				//Obtener la vecindad de pixeles
				double vsx = 0.0, vsy = 0.0;
				int ns = 8;
				for(int c = -1; c <= 1; c++) {
					for(int h = -1; h <= 1; h++) {
						if(c == 0 && h == 0)
							continue;
						vsx += (*vx)[i + c][j + h];
						vsy += (*vy)[i + c][j + h];
					}
				}
				//printf("%lf %lf\n", vsx, vsy);

				double numx = -dx[i][j] * dy[i][j] * (*vy)[i][j] - dt[i][j] * dx[i][j] + lambda * vsx;
				double numy = -dx[i][j] * dy[i][j] * (*vx)[i][j] - dt[i][j] * dy[i][j] + lambda * vsy;

				double denx = lambda * (double)ns + (dx[i][j] * dx[i][j]);
				double deny = lambda * (double)ns + (dy[i][j] * dy[i][j]);

				vx1[i][j] = numx / denx;
				vy1[i][j] = numy / deny;
			}
		}

		for(int i = 1; i < height - 1; i++) {
			for(int j = 1; j < width - 1; j++) {
				(*vx)[i][j] = vx1[i][j];
				(*vy)[i][j] = vy1[i][j];
			}
		}

		k++;
	}

	printf("Terminado\n");

	free_matrix(dx);
	free_matrix(dy);
	free_matrix(dt);
	free_matrix(vx1);
	free_matrix(vy1);
}