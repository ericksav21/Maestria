#include "rectas.h"

int rand_in_range(int a, int b) {
	return rand() % (b - a + 1) + a;
}

double distance(PIXEL p1, PIXEL p2) {
	return sqrt(pow(p2.j - p1.j, 2) + pow(p2.i - p1.i, 2));
}

void dfs(IMG *ori, PIXEL p_ini, NODEPTR *extreme_points, NODEPTR *path) {
	NODEPTR stack = NULL;
	int **mark = create_matrix(ori->height, ori->width, int);
	for(int i = 0; i < ori->height; i++) {
		for(int j = 0; j < ori->width; j++) {
			mark[i][j] = 0;
		}
	}

	stack = add_node(stack, p_ini);
	int k = 1;
	double dist = 0.0;
	PIXEL p_ant = p_ini;
	while(!is_list_empty(stack)) {
		PIXEL p_act = list_get(stack, k - 1)->pixel;
		stack = remove_node(stack, k - 1);
		k--;

		PIXEL neigh[8];
		int cnt = 0, i = p_act.i, j = p_act.j;
		if(ori->mat[i - 1][j - 1]) {
			neigh[cnt].i = i - 1; neigh[cnt++].j = j - 1;
		}
		if(ori->mat[i - 1][j]) {
			neigh[cnt].i = i - 1; neigh[cnt++].j = j;
		}
		if(ori->mat[i - 1][j + 1]) {
			neigh[cnt].i = i - 1; neigh[cnt++].j = j + 1;
		}
		if(ori->mat[i][j + 1]) {
			neigh[cnt].i = i; neigh[cnt++].j = j + 1;
		}
		if(ori->mat[i + 1][j + 1]) {
			neigh[cnt].i = i + 1; neigh[cnt++].j = j + 1;
		}
		if(ori->mat[i + 1][j]) {
			neigh[cnt].i = i + 1; neigh[cnt++].j = j;
		}
		if(ori->mat[i + 1][j - 1]) {
			neigh[cnt].i = i + 1; neigh[cnt++].j = j - 1;
		}
		if(ori->mat[i][j - 1]) {
			neigh[cnt].i = i; neigh[cnt++].j = j - 1;
		}

		//Validar distancia
		dist = distance(p_ant, p_act);
		if(dist > 6.1) {
			break;
		}
		p_ant.i = p_act.i; p_ant.j = p_act.j;

		(*path) = add_node(*path, p_act);
		if(cnt == 1) {
			(*extreme_points) = add_node(*extreme_points, neigh[0]);
		}
		for(int i = 0; i < cnt; i++) {
			PIXEL aux;
			aux.i = neigh[i].i; aux.j = neigh[i].j;
			if(!mark[aux.i][aux.j]) {
				stack = add_node(stack, aux);
				mark[aux.i][aux.j] = 1;
				k++;
			}
		}
	}

	free_matrix(mark);
	free_list(stack);
}

void clean_skeletonize(IMG *ori, PIXEL *p1, PIXEL *p2, NODEPTR *n_path) {
	PIXEL p_ini, p_end;
	NODEPTR extreme_points = NULL, path = NULL;
	for(int i = 1; i < ori->height - 1; i++) {
		int band = 0;
		for(int j = 1; j < ori->width - 1; j++) {
			if(ori->mat[i][j]) {
				p_ini.i = i;
				p_ini.j = j;
				band = 1;
				break;
			}
		}
		if(band)
			break;
	}
	for(int i = ori->height - 1; i >= 1; i--) {
		int band = 0;
		for(int j = ori->width - 1; j >= 1; j--) {
			if(ori->mat[i][j]) {
				p_end.i = i;
				p_end.j = j;
				band = 1;
				break;
			}
		}
		if(band)
			break;
	}

	dfs(ori, p_ini, &extreme_points, n_path);
	int k = list_size(extreme_points), psz = list_size(*n_path);
	double dist = -1;
	(*p1) = p_ini;
	(*p2) = p_end;

	free_list(extreme_points);
}

PIXEL get_leftmost_pixel(int *start_line, NODEPTR path, int psz) {
	PIXEL pmin;
	PIXEL res;
	int i;
	pmin.i = pmin.j = 1000;
	for(i = (*start_line); i < psz; i++) {
		PIXEL p_aux = list_get(path, i)->pixel;
		if(p_aux.j > pmin.j/* && p_aux.j - pmin.j > 3*/)
			break;

		pmin = p_aux;
		res.i = p_aux.i;
		res.j = p_aux.j;
	}
	*start_line = i;
	return res;
}

PIXEL get_rightmost_pixel(int *start_line, NODEPTR path, int psz) {
	PIXEL pmax; 
	int i;
	PIXEL res;
	pmax.i = pmax.j = 0;
	for(i = (*start_line); i < psz; i++) {
		PIXEL p_aux = list_get(path, i)->pixel;
		if(p_aux.j < pmax.j/* && pmax.j - p_aux.j > 3*/)
			break;

		pmax = p_aux;
		res.i = p_aux.i;
		res.j = p_aux.j;
	}
	*start_line = i;
	return res;
}

NODEPTR get_lines(IMG *img, PIXEL p1, PIXEL p2, NODEPTR n_path, int ind) {
	NODEPTR outs = NULL;
	NODEPTR discretized = NULL;
	int psz = list_size(n_path);

	int band = 0;
	for(int i = 0; i < psz; i += 1) {
		if(i >= psz)
			break;
		PIXEL p_path = list_get(n_path, i)->pixel;
		discretized = add_node(discretized, p_path);
	}

	//Usar el algoritmo RPD para encontrar los mejores puntos
	double eps = 7.0;
	int dsz = list_size(discretized);
	int lsz;
	while(1) {
		outs = NULL;
		RDP(discretized, dsz, &outs, eps);
		lsz = list_size(outs);

		if(lsz <= 8) {
			break;
		}
		free_list(outs);
		eps += 0.1;
	}

	for(int i = 0; i < lsz; i++) {
		PIXEL *p_end = &list_get(outs, i)->pixel;
		int r = rand_in_range(1, 3);
		p_end->j += r;
	}
	PIXEL pm1, pm2, pm3;
	int idx = 1;
	pm1 = get_leftmost_pixel(&idx, outs, lsz);
	pm2 = get_rightmost_pixel(&idx, outs, lsz);
	pm3 = get_leftmost_pixel(&idx, outs, lsz);

	NODEPTR res = NULL;
	res = add_node(res, p1);
	res = add_node(res, pm1);
	res = add_node(res, pm2);
	res = add_node(res, pm3);
	res = add_node(res, p2);

	draw_line(img, p1.i, p1.j, pm1.i, pm1.j);
	draw_line(img, pm1.i, pm1.j, pm2.i, pm2.j);
	draw_line(img, pm2.i, pm2.j, pm3.i, pm3.j);
	draw_line(img, pm3.i, pm3.j, p2.i, p2.j);

	free_list(outs);
	free_list(discretized);

	return res;
}

double ortho_dist(PIXEL pt, PIXEL l_start, PIXEL l_end) {
	double dx = l_end.j - l_start.j;
	double dy = l_end.i - l_start.i;
	double m = sqrt(dx * dx + dy * dy);
	if(m > 0.0) {
		dx /= m;
		dy /= m;
	}

	double pvx = pt.j - l_start.j;
	double pvy = pt.i - l_start.i;
	double inner = dx * pvx + dy * pvy;
	double sx = inner * dx;
	double sy = inner * dy;
	double ax = pvx - sx;
	double ay = pvy - sy;

	return sqrt(ax * ax + ay * ay);
}

void RDP(NODEPTR points, int sz, NODEPTR *outs, double eps) {
	int k = 0, idx = 0;
	double d_max = 0.0;

	for(int i = 1; i < sz - 1; i++) {
		double d_act = ortho_dist(list_get(points, i)->pixel, list_get(points, 0)->pixel, list_get(points, sz - 1)->pixel);
		if(d_act > d_max) {
			d_max = d_act;
			idx = i;
		}
	}
	if(d_max > eps) {
		int flsz = (idx + 1), llsz = (sz - idx + 1);
		NODEPTR r1 = NULL, r2 = NULL;
		NODEPTR fl = NULL, ll = NULL;

		for(int i = 0; i <= idx; i++) {
			fl = add_node(fl, list_get(points, i)->pixel);
		}
		for(int i = 0, j = idx; j < sz; i++, j++) {
			ll = add_node(ll, list_get(points, j)->pixel);
		}

		RDP(fl, list_size(fl), &r1, eps);
		RDP(ll, list_size(ll), &r2, eps);

		for(int i = 0; i < list_size(r1); i++) {
			NODEPTR aux = list_get(r1, i);
			PIXEL p_aux;
			p_aux.i = aux->pixel.i;
			p_aux.j = aux->pixel.j;
			(*outs) = add_node((*outs), p_aux);
		}
		for(int i = 0; i < list_size(r2); i++) {
			NODEPTR aux = list_get(r2, i);
			PIXEL p_aux;
			p_aux.i = aux->pixel.i;
			p_aux.j = aux->pixel.j;
			(*outs) = add_node((*outs), p_aux);
		}

		free_list(r1);
		free_list(r2);
		free_list(fl);
		free_list(ll);
	}
	else {
		(*outs) = add_node(*outs, list_get(points, 0)->pixel);
		(*outs) = add_node(*outs, list_get(points, 1)->pixel);
	}
}

int A_test(IMG *img, int i, int j) {
	int cnt = 0;
	if(!img->mat[i - 1][j] && img->mat[i - 1][j + 1] != 0) cnt++;
	if(!img->mat[i - 1][j + 1] && img->mat[i][j + 1] != 0) cnt++;
	if(!img->mat[i][j + 1] && img->mat[i + 1][j + 1] != 0) cnt++;
	if(!img->mat[i + 1][j + 1] && img->mat[i + 1][j] != 0) cnt++;
	if(!img->mat[i + 1][j] && img->mat[i + 1][j - 1] != 0) cnt++;
	if(!img->mat[i + 1][j - 1] && img->mat[i][j - 1] != 0) cnt++;
	if(!img->mat[i][j - 1] && img->mat[i - 1][j - 1] != 0) cnt++;
	if(!img->mat[i - 1][j - 1] && img->mat[i - 1][j] != 0) cnt++;

	return cnt;
}

int B_test(IMG *img, int i, int j) {
	int cnt = 0;
	//Bordes
	for(int r = -1; r <= 1; r++) {
		for(int c = -1; c <= 1; c++) {
			if(r == 0 && c == 0) continue;
			if(img->mat[i + r][j + c] != 0) {
				cnt++;
			}
		}
	}

	return cnt;
}

IMG* skeletonize(IMG *ori) {
	IMG *dest = copy_img(ori);
	int width = ori->width, height = ori->height;
	int **mat = dest->mat;
	PIXEL *pixels_1 = (PIXEL *)calloc(width * height, sizeof(PIXEL));
	PIXEL *pixels_2 = (PIXEL *)calloc(width * height, sizeof(PIXEL));
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

double* get_angles(NODEPTR lines) {
	int lsz = list_size(lines);
	double *res = create_vector(lsz - 1, double);
	int cnt = 0;
	double val = 180.0 / M_PI;

	for(int i = 1; i < lsz; i++) {
		PIXEL p1 = list_get(lines, i - 1)->pixel;
		PIXEL p2 = list_get(lines, i)->pixel;
		res[cnt++] = atan2((double)(p2.j - p1.j), (double)(p2.i - p1.i)) * val + 90.0;
	}

	return res;
}

void append_angles(double *angles, int n, int ind, FILE *out) {
	fprintf(out, "%d ", ind);
	for(int i = 0; i < n; i++) {
		fprintf(out, "%lf ", angles[i]);
	}
	fprintf(out, "\n");
}

double* get_lens(NODEPTR lines) {
	int lsz = list_size(lines);
	double *res = create_vector(lsz - 1, double);
	int cnt = 0;

	for(int i = 1; i < lsz; i++) {
		PIXEL p1 = list_get(lines, i - 1)->pixel;
		PIXEL p2 = list_get(lines, i)->pixel;
		res[cnt++] = distance(p1, p2);
	}

	return res;
}

void append_lens(double *lens, int n, int ind, FILE *out) {
	fprintf(out, "%d ", ind);
	for(int i = 0; i < n; i++) {
		fprintf(out, "%lf ", lens[i]);
	}
	fprintf(out, "\n");
}