#include "imagen.h"

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

    img.mat[x0][y0] = 255;
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
            img.mat[x0][y0] = 255;
            //this.dibujaPunto(x0, y0);
        }
    } else if (dy != 0) {                          // pendiente >= 1
        float m = (float) dx / (float) dy;
        float b = x0 - m * y0;
        if(dy < 0)
            dy = -1;
        else
            dy = 1;
        while (y0 != y1) {
            y0 += dy;
            x0 = round(m * y0 + b);
            img.mat[x0][y0] = 255;
            //this.dibujaPunto(x0, y0);
        }
    }
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