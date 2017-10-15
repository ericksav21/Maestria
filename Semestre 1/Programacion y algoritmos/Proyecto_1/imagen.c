#include "imagen.h"

double distance(PIXEL p1, PIXEL p2) {
	return sqrt(pow(p2.j - p1.j, 2) + pow(p2.i - p1.i, 2));
}

IMG create_img(int width, int height) {
	IMG res;
	res.width = width;
	res.height = height;
	res.mat = create_matrix(height, width, int);

	return res;
}

IMG read_img(char *files_name) {
	FILE *in;
	char dump[128];
	int width, height, scale;

	if(!(in = fopen(files_name, "r"))) {
		printf("No se pudo abrir la imagen.\n");
		IMG v;
		v.width = -1;
		v.height = -1;
		return v;
	}

	//Se lee el P2 o alguna otra cadena que contenga la imagen
	fscanf(in, "%s", dump);
	fscanf(in, "%d %d", &width, &height);
	fscanf(in, "%d", &scale);

	IMG res = create_img(width, height);

	int act;
	for(int i = 0; i < height; i++) {
		for(int j = 0; j < width; j++) {
			fscanf(in, "%d", &act);
			res.mat[i][j] = act;
		}
	}

	fclose(in);

	return res;
}

void print_img(IMG img, char *files_name) {
	FILE *out;
	out = fopen(files_name, "w");
	fprintf(out, "P2\n");
	fprintf(out, "%d %d\n255\n", img.width, img.height);

	for(int i = 0; i < img.height; i++) {
		for(int j = 0; j < img.width; j++) {
			fprintf(out, "%d\n", img.mat[i][j]);
		}
	}

	fclose(out);
}

IMG copy_img(IMG img) {
	IMG res;
	res.width = img.width;
	res.height = img.height;
	res.mat = create_matrix(img.height, img.width, int);
	for(int i = 0; i < img.height; i++) {
		for(int j = 0; j < img.width; j++) {
			res.mat[i][j] = img.mat[i][j];
		}
	}

	return res;
}

void free_img(IMG obj) {
	free_matrix(obj.mat);
}

IMG resize_img(IMG img) {
	IMG res;

	//Recortar la imagen
	int minX = img.width + 1, minY = img.height + 1, maxX = -1, maxY = -1;
	int act;

	for(int i = 0; i < img.height; i++) {
		for(int j = 0; j < img.width; j++) {
			act = img.mat[i][j];
			if(act != 0) {
				if(j < minX)
					minX = j;
				if(j > maxX)
					maxX = j;
				if(i < minY)
					minY = i;
				if(i > maxY)
					maxY = i;
			}
		}
	}

	int new_width = (maxX - minX + 1);
	int new_height = (maxY - minY + 1);

	res.width = new_width + 2;
	res.height = new_height + 2;
	res.mat = create_matrix(new_height + 2, new_width + 2, int);

	for(int i = 0; i < res.width; i++) {
		res.mat[0][i] = res.mat[res.width - 1][i] = 0;
	}
	for(int i = 1, x = minY; i < res.height - 1; i++, x++) {
		res.mat[i][0] = res.mat[i][res.width - 1] = 0;
		for(int j = 1, y = minX; j < res.width - 1; j++, y++) {
			res.mat[i][j] = img.mat[x][y];
		}
	}
	
	return res;
}

void draw_line(IMG img, int x0, int y0, int x1, int y1) {
    int dx = x1 - x0;
    int dy = y1 - y0;

    img.mat[x0][y0] = 50;
    //this.dibujaPunto(x0, y0);
    if (abs(dx) > abs(dy)) {  // pendiente < 1
        float m = (float) dy / (float) dx;
        float b = y0 - m * x0;
        if(dx < 0)
            dx = -1;
        else
            dx = 1;
        while (x0 != x1) {
            x0 += dx;
            y0 = round(m * x0 + b);
            img.mat[x0][y0] = 50;
        }
    }
    else if (dy != 0) {                          // pendiente >= 1
        float m = (float) dx / (float) dy;
        float b = x0 - m * y0;
        if(dy < 0)
            dy = -1;
        else
            dy = 1;
        while (y0 != y1) {
            y0 += dy;
            x0 = round(m * y0 + b);
            img.mat[x0][y0] = 50;
        }
    }
}

void get_path(IMG ori, IMG *dest, int **mark, PIXEL p_ini, PIXEL **extreme_points, int *k) {
	PIXEL neigh[8];
	int cnt = 0, i = p_ini.i, j = p_ini.j;
	if(ori.mat[i - 1][j - 1] /*&& !mark[i - 1][j - 1]*/) {
		neigh[cnt].i = i - 1; neigh[cnt++].j = j - 1;
	}
	if(ori.mat[i - 1][j] /*&& !mark[i - 1][j]*/) {
		neigh[cnt].i = i - 1; neigh[cnt++].j = j;
	}
	if(ori.mat[i - 1][j + 1] /*&& !mark[i - 1][j + 1]*/) {
		neigh[cnt].i = i - 1; neigh[cnt++].j = j + 1;
	}
	if(ori.mat[i][j + 1] /*&& !mark[i][j + 1]*/) {
		neigh[cnt].i = i; neigh[cnt++].j = j + 1;
	}
	if(ori.mat[i + 1][j + 1] /*&& !mark[i + 1][j + 1]*/) {
		neigh[cnt].i = i + 1; neigh[cnt++].j = j + 1;
	}
	if(ori.mat[i + 1][j] /*&& !mark[i + 1][j]*/) {
		neigh[cnt].i = i + 1; neigh[cnt++].j = j;
	}
	if(ori.mat[i + 1][j - 1] /*&& !mark[i + 1][j - 1]*/) {
		neigh[cnt].i = i + 1; neigh[cnt++].j = j - 1;
	}
	if(ori.mat[i][j - 1] /*&& !mark[i][j - 1]*/) {
		neigh[cnt].i = i; neigh[cnt++].j = j - 1;
	}

	mark[i][j] = 1;
	if(cnt == 1) {
		(*extreme_points) = (PIXEL *)realloc(*extreme_points, ((*k) + 1) * sizeof(PIXEL));
		(*extreme_points)[(*k) - 1].i = neigh[0].i;
		(*extreme_points)[(*k) - 1].j = neigh[0].j;
		(*k)++;
	}
	for(int c = 0; c < cnt; c++) {
		PIXEL aux;
		aux.i = neigh[c].i; aux.j = neigh[c].j;
		if(!mark[aux.i][aux.j]) {
			get_path(ori, dest, mark, aux, extreme_points, k);
		}
	}
	dest->mat[i][j] = 255;
}

IMG clean_skeletonize(IMG ori) {
	IMG res = create_img(ori.width, ori.height);
	PIXEL p_ini;
	PIXEL *extreme_points = (PIXEL *)malloc(sizeof(PIXEL));
	int **mark = create_matrix(ori.height, ori.width, int), k = 1;
	for(int i = 0; i < ori.height; i++) {
		for(int j = 0; j < ori.width; j++) {
			mark[i][j] = 0;
		}
	}
	for(int i = 1; i < ori.height - 1; i++) {
		int band = 0;
		for(int j = 1; j < ori.width - 1; j++) {
			if(ori.mat[i][j]) {
				p_ini.i = i;
				p_ini.j = j;
				band = 1;
				break;
			}
		}
		if(band)
			break;
	}

	get_path(ori, &res, mark, p_ini, &extreme_points, &k);
	PIXEL p1, p2;
	double dist = -1;
	for(int i = 0; i < k - 2; i++) {
		for(int j = 1; j < k - 1; j++) {
			double aux = distance(extreme_points[i], extreme_points[j]);
			if(aux > dist) {
				dist = aux;
				p1.i = extreme_points[i].i; p1.j = extreme_points[i].j;
				p2.i = extreme_points[j].i; p2.j = extreme_points[j].j;
			}
		}
	}

	draw_line(res, p1.i, p1.j, p2.i, p2.j);

	free_matrix(mark);
	free(extreme_points);

	return res;
}

PIXEL find_leftmost_pxl(IMG img, int start_line) {
	PIXEL res;
	res.i = 0;
	res.j = img.width;
	int tol = 5;
	for(int i = start_line; i < img.height; i++) {
		//Encontrar el primer punto que esté más a la izquierda
		int pj = 0;
		for(int j = 0; j < img.width; j++) {
			if(img.mat[i][j] != 0) {
				pj = j;
				break;
			}
		}
		if(pj <= res.j) {
			res.i = i;
			res.j = pj;
		}
		else {
			//Obtener la distancia con el mayor para detectar cambio
			//De dirección
			int dist = abs(res.j - pj);
			if(dist > tol) {
				break;
			}
		}
	}

	return res;
}

PIXEL find_rightmost_pxl(IMG img, int start_line) {
	PIXEL res;
	res.i = 0;
	res.j = 0;
	int tol = 5;
	for(int i = start_line; i < img.height; i++) {
		//Encontrar el primer punto que esté más a la izquierda
		int pj = 0;
		for(int j = img.width - 1; j >= 0; j--) {
			if(img.mat[i][j] != 0) {
				pj = j;
				break;
			}
		}
		if(pj >= res.j) {
			res.i = i;
			res.j = pj;
		}
		else {
			//Obtener la distancia con el mayor para detectar cambio
			//De dirección
			int dist = abs(res.j - pj);
			if(dist > tol) {
				break;
			}
		}
	}

	return res;
}

void get_lines_1(IMG img, IMG org, int ind) {
	//Obtener el primer punto
	PIXEL p1;
	p1.i = 0;
	for(int i = 0; i < img.height; i++) {
		int band = 0;
		for(int j = 0; j < img.width; j++) {
			if(img.mat[i][j] != 0) {
				p1.i = i;
				p1.j = j;
				band = 1;
				break;
			}
		}
		if(band)
			break;
	}
	PIXEL p2 = find_leftmost_pxl(img, p1.i);
	PIXEL p3 = find_rightmost_pxl(img, p2.i);
	PIXEL p4 = find_leftmost_pxl(img, p3.i);
	PIXEL p5 = find_rightmost_pxl(img, p4.i);

	//Dibujar línea
	draw_line(org, p1.i, p1.j, p2.i, p2.j);
	draw_line(org, p2.i, p2.j, p3.i, p3.j);
	draw_line(org, p3.i, p3.j, p4.i, p4.j);
	draw_line(org, p4.i, p4.j, p5.i, p5.j);

	char out_name[30];
	sprintf(out_name, "out%d.pgm", ind);
	print_img(org, out_name);
}

int A_test(IMG img, int i, int j) {
	int cnt = 0;
	if(!img.mat[i - 1][j] && img.mat[i - 1][j + 1] != 0) cnt++;
	if(!img.mat[i - 1][j + 1] && img.mat[i][j + 1] != 0) cnt++;
	if(!img.mat[i][j + 1] && img.mat[i + 1][j + 1] != 0) cnt++;
	if(!img.mat[i + 1][j + 1] && img.mat[i + 1][j] != 0) cnt++;
	if(!img.mat[i + 1][j] && img.mat[i + 1][j - 1] != 0) cnt++;
	if(!img.mat[i + 1][j - 1] && img.mat[i][j - 1] != 0) cnt++;
	if(!img.mat[i][j - 1] && img.mat[i - 1][j - 1] != 0) cnt++;
	if(!img.mat[i - 1][j - 1] && img.mat[i - 1][j] != 0) cnt++;

	return cnt;
}

int B_test(IMG img, int i, int j) {
	int cnt = 0;
	//Bordes
	for(int r = -1; r <= 1; r++) {
		for(int c = -1; c <= 1; c++) {
			if(r == 0 && c == 0) continue;
			if(img.mat[i + r][j + c] != 0) {
				cnt++;
			}
		}
	}

	return cnt;
}

IMG skeletonize(IMG ori) {
	IMG dest = copy_img(ori);
	int width = ori.width, height = ori.height;
	int **mat = dest.mat;
	PIXEL *pixels_1 = (PIXEL *)malloc(width * height * sizeof(PIXEL));
	PIXEL *pixels_2 = (PIXEL *)malloc(width * height * sizeof(PIXEL));
	int changed_1, changed_2;

	do {
		changed_1 = 0;
		changed_2 = 0;

		for(int i = 1; i < height - 1; i++) {
			for(int j = 1; j < width - 1; j++) {
				if(mat[i][j] != 0) {
					int b_res = B_test(dest, i, j);
					int a_res = A_test(dest, i, j);
					if((b_res >= 2 && b_res <= 6) &&
						a_res == 1 &&
						//P2 * P4 * P6
						(mat[i - 1][j] * mat[i][j + 1] * mat[i + 1][j] == 0) &&
						 mat[i][j + 1] * mat[i + 1][j] * mat[i][j - 1] == 0) {

						//Cambio en el pixel
						pixels_1[changed_1].i = i;
						pixels_1[changed_1].j = j;
						changed_1++;
					}
				}
			}
		}
		for(int i = 0; i <= changed_1; i++) {
			mat[pixels_1[i].i][pixels_1[i].j] = 0;
		}

		for(int i = 1; i < height - 1; i++) {
			for(int j = 1; j < width - 1; j++) {
				if(mat[i][j] != 0) {
					int b_res = B_test(dest, i, j);
					int a_res = A_test(dest, i, j);
					if((b_res >= 2 && b_res <= 6) &&
						a_res == 1 &&
						//P2 * P4 * P8
						(mat[i - 1][j] * mat[i][j + 1] * mat[i][j - 1] == 0) &&
						 mat[i - 1][j] * mat[i + 1][j] * mat[i][j - 1] ==  0) {

						//Cambio en el pixel
						pixels_2[changed_2].i = i;
						pixels_2[changed_2].j = j;
						changed_2++;
					}
				}
			}
		}
		for(int i = 0; i <= changed_2; i++) {
			mat[pixels_2[i].i][pixels_2[i].j] = 0;
		}
	} while(changed_1 != 0 || changed_2 != 0);
	free(pixels_1);
	free(pixels_2);

	return dest;
}


/*IMG skeletonize_2(IMG ori) {
	IMG cpy = copy_img(ori);
	int neigh[8];
	
	while(1) {
		for(int i = 1; i < height - 1; i++) {
			for(int j = 1; j < width - 1; j++) {
				//Obtener vecinos
				neigh[0] = img.mat[i - 1][j - 1];
				neigh[1] = img.mat[i - 1][j];
				neigh[2] = img.mat[i - 1][j + 1];
				neigh[3] = img.mat[i][j + 1];
				neigh[4] = img.mat[i + 1][j + 1];
				neigh[5] = img.mat[i + 1][j];
				neigh[6] = img.mat[i + 1][j - 1];
				neigh[7] = img.mat[i][j - 1];

				//Aplicar filtros
				int f1 = (!neigh[0] && !neigh[1] && !neigh[2] && neigh[4] && neigh[5] && neigh[6]);
				int f2 = (!neigh[1] && !neigh[2] && !neigh[3] && neigh[5] && neigh[7]);
				int f3 = (!neigh[2] && !neigh[3] && !neigh[4] && neigh[6] && neigh[7] && neigh[0]);
				int f4 = (!neigh[3] && !neigh[4] && !neigh[5] && neigh[1] && neigh[7]);
				int f5 = (!neigh[4] && !neigh[5] && !neigh[6] && neigh[0] && neigh[1] && neigh[2]);
				int f6 = (!neigh[5] && !neigh[6] && !neigh[7] && neigh[1] && neigh[3]);
				int f7 = (!neigh[0] && !neigh[6] && !neigh[7] && neigh[2] && neigh[3] && neigh[4]);
				int f8 = (!neigh[0] && !neigh[1] && !neigh[7] && neigh[3] && neigh[5]);

				if(f1 && f2 && f3 && f4 && f5 && f6 && f7 && f8)
					cpy.mat[i][j] = 255;
			}
		}

		free_img(ori);
		ori = copy_img(cpy);
	}
}*/