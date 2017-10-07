#include "imagen.h"

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

	IMG res;
	res.width = width;
	res.height = height;
	res.mat = create_matrix(height, width, int);

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

void print_img(IMG img) {
	FILE *out;
	out = fopen("out.pgm", "w");
	fprintf(out, "P2\n");
	fprintf(out, "%d %d\n255\n", img.width, img.height);

	for(int i = 0; i < img.height; i++) {
		for(int j = 0; j < img.width; j++) {
			fprintf(out, "%d\n", img.mat[i][j]);
		}
	}

	fclose(out);
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

	res.width = new_width;
	res.height = new_height;
	res.mat = create_matrix(new_height, new_width, int);

	for(int i = 0, x = minY; i < new_height; i++, x++) {
		for(int j = 0, y = minX; j < new_width; j++, y++) {
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