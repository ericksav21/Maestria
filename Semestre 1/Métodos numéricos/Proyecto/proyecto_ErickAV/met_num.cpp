#include "met_num.h"

double** pderivative_x(IMG *img) {
	int width = img->width;
	int height = img->height;
	double **res = create_matrix(width, height, double);
	for(int i = 0; i < height; i++) {
		for(int j = 1; j < width - 1; j++) {
			res[i][j] = (img->mat[i][j + 1] - img->mat[i][j - 1]) / 2.0;
		}
		res[i][0] = img->mat[i][0];
		res[i][width - 1] = img->mat[i][width - 1];
	}

	return res;
}

double** pderivative_y(IMG *img) {
	int width = img->width;
	int height = img->height;
	double **res = create_matrix(height, width, double);
	for(int i = 0; i < width; i++) {
		for(int j = 1; j < height - 1; j++) {
			res[j][i] = (img->mat[j + 1][i] - img->mat[j - 1][i]) / 2.0;
		}
		res[0][i] = img->mat[0][i];
		res[height - 1][i] = img->mat[height - 1][i];
	}

	return res;
}

double** pderivative_t(IMG *img1, IMG *img2) {
	int width = img1->width;
	int height = img1->height;
	double **res = create_matrix(height, width, double);
	for(int i = 0; i < height; i++) {
		for(int j = 0; j < width; j++) {
			res[i][j] = (img2->mat[i][j] - img1->mat[i][j]) / 2.0;
		}
	}

	return res;
}

void get_derivatives(IMG *img1, IMG *img2, double ***dx, double ***dy, double ***dt) {
	//int width = img1->width;
	//int height = img1->height;

	(*dx) = pderivative_x(img1);
	(*dy) = pderivative_y(img1);
	(*dt) = pderivative_t(img1, img2);

	/*double **dx1 = pderivative_x(img1);
	double **dy1 = pderivative_y(img1);
	double **dx2 = pderivative_x(img2);
	double **dy2 = pderivative_y(img2);*/

	//dx = add_mat(dx1, dx2, dx, height, width);
	//dy = add_mat(dy1, dy2, dy, height, width);

	/*for(int i = 0; i < height; i++) {
		for(int j = 0; j < width; j++) {
			if(dx[i][j] > 255)
				dx[i][j] = 255;
			if(dy[i][j] > 255)
				dy[i][j] = 255;
		}
	}*/

	/*free_matrix(dx1);
	free_matrix(dy1);
	free_matrix(dx2);
	free_matrix(dy2);*/
}

int check_convergence(double **vx, double **vy, double **vx1, double **vy1, int width, int height, double tol) {
	double **ex = create_matrix(height, width, double);
	double **ey = create_matrix(height, width, double);

	for(int i = 0; i < height; i++) {
		for(int j = 0; j < width; j++) {
			ex[i][j] = vx1[i][j] - vx[i][j];
			ey[i][j] = vy1[i][j] - vy[i][j];
		}
	}

	double nx = 0.0, ny = 0.0;
	for(int i = 0; i < height; i++) {
		for(int j = 0; j < width; j++) {
			nx += (ex[i][j] * ex[i][j]);
			ny += (ey[i][j] * ey[i][j]);
		}
	}
	nx = sqrt(nx);
	ny = sqrt(ny);

	free_matrix(ex);
	free_matrix(ey);

	printf("%g %g\n", nx, ny);

	if(nx < tol && ny < tol)
		return 1;
	else
		return 0;
}

void Horn_Schunck(IMG *img1, IMG *img2, double ***vx, double ***vy, int iter, double lambda) {
	double tol = 0.1;
	int width = img1->width;
	int height = img1->height;

	//Obtener las derivadas parciales
	double **dx, **dy, **dt;
	get_derivatives(img1, img2, &dx, &dy, &dt);
	
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

				double numx = -dx[i][j] * dy[i][j] * (*vy)[i][j] - dt[i][j] * dx[i][j] + lambda * vsx;
				double numy = -dx[i][j] * dy[i][j] * (*vx)[i][j] - dt[i][j] * dy[i][j] + lambda * vsy;

				double denx = lambda * (double)ns + (dx[i][j] * dx[i][j]);
				double deny = lambda * (double)ns + (dy[i][j] * dy[i][j]);

				vx1[i][j] = numx / denx;
				vy1[i][j] = numy / deny;
			}
		}

		if(check_convergence((*vx), (*vy), vx1, vy1, width, height, tol)) {
			break;
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

void quiver(IMG *out, double **vx, double **vy, int width, int height) {
	double l_max = -10;

	for(int y = 0; y < height; y += 15) {
		for(int x = 0; x < width; x += 15) {
			double dx = vx[y][x];
			double dy = vy[y][x];

			double l = sqrt(dx * dx + dy * dy);
			if(l > l_max)
				l_max = l;
		}
	}

	for(int y = 0; y < height; y += 15) {
		for(int x = 0; x < width; x += 15) {
			double dx = vx[y][x];
			double dy = vy[y][x];

			pixel p;
			p.i = y; p.j = x;
			double l = sqrt(dx * dx + dy * dy);
			if(l > 0) {
				double spinSize = 5.0 * l / l_max;
				pixel p2;
				p2.i = p.i + (int)dy; p2.j = p.j + (int)dx;

				draw_line(out, p.i, p.j, p2.i, p2.j);
				double angle = atan2((double)p.i - p2.i, (double)p.j - p2.j);

				p.i = (int)(p2.i + spinSize * sin(angle + M_PI / 4.0));
				p.j = (int)(p2.j + spinSize * cos(angle + M_PI / 4.0));
				draw_line(out, p.i, p.j, p2.i, p2.j);

				p.i = (int)(p2.i + spinSize * sin(angle - M_PI / 4.0));
				p.j = (int)(p2.j + spinSize * cos(angle - M_PI / 4.0));
				draw_line(out, p.i, p.j, p2.i, p2.j);
			}
		}
	}
}