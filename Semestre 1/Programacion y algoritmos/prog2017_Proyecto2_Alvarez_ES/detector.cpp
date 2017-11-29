#include "detector.hpp"

Detector::Detector(Image img) {
	this->img = new Image(img.get_mat());
	srand(time(NULL));

	//Inicializar la lista de puntos blancos
	for(int i = 0; i < img.get_height(); i++) {
		for(int j = 0; j < img.get_width(); j++) {
			if(img.get_val(i, j)) {
				//Punto blanco
				white_points.push_back(Point(i, j));
			}
		}
	}

	int n = white_points.size();
	nbits = 0;
	while(n > 0) {
		nbits++;
		n = n >> 1;
	}

	//sort(white_points.begin(), white_points.end(), PointComparator());
}

Detector::~Detector() {
	if(img)
		delete img;
}

vector<int> Detector::get_sub_vector(vector<int> v, int i, int j) {
	vector<int> res;
	for(int k = i; k <= j; k++)
		res.push_back(v[k]);

	return res;
}

vector<int> Detector::to_binary(int n) {
	vector<int> res;
	string binary = bitset<12>(n).to_string();
	for(int i = 0; i < binary.size(); i++) {
		res.push_back(binary[i] - '0');
	}

	return res;
}

int Detector::to_int(vector<int> v) {
	int sum = 0, tmp = 1;
	for(int i = 0; i < nbits; i++) {
		sum += v[i] * tmp;
		tmp *= 2;
	}

	return sum;
}

Image Detector::get_image() {
	return *img;
}

vector<Point> Detector::get_white_points() {
	return white_points;
}

void Detector::print_white_points() {
	for(int i = 0; i < white_points.size(); i++) {
		cout << white_points[i].get_i() << " " << white_points[i].get_j() << endl;
	}
}

void Detector::set_UMDA_parameters(int pop_size, int no_generations, double selection_rate) {
	this->pop_size = pop_size;
	this->no_generations = no_generations;
	this->selection_rate = selection_rate;
}

void Detector::generate_points(vector<int> v, double &xc, double &yc, int &dir, double &p) {
	int n1 = to_int(get_sub_vector(v, 0, nbits - 1));
	int n2 = to_int(get_sub_vector(v, nbits, (nbits * 2) - 1));
	int n3 = to_int(get_sub_vector(v, nbits * 2, (nbits * 3) - 1));

	int xi = white_points[n1].get_i(), yi = white_points[n1].get_j();
	int xj = white_points[n2].get_i(), yj = white_points[n2].get_j();
	int xk = white_points[n3].get_i(), yk = white_points[n3].get_j();

	//Generar los coeficientes
	double den = (double)((yi - yj) * (yi - yk) * (yj - yk));
	double A = (double)(yk * (xj - xi) + yj * (xi - xk) + yi * (xk - xj)) / den;
	double B = (double)(pow(yk, 2) * (xi - xj) + pow(yj, 2) * (xk - xi) + pow(yi, 2) * (xj - xk)) / den;
	double C = (double)(yj * yk * (yj - yk) * xi + yk * yi * (yk - yi) * xj + yi * yj * (yi - yj) * xk);
	C /= den;

	dir = (A > 0 ? 1 : -1);
	xc = C - ((B * B) / (4.0 * A));
	yc = -B / (2.0 * A);
	p = 1.0 / (2.0 * A);
}

Image Detector::generate_parabola(int width, int height, double xc, double yc, int dir, double p) {
	int bound = width * 2;
	Image res(width, height, 0);
	res.draw_parabola(Point((int)xc, (int)yc), abs((int)p), bound, dir, 255);

	return res;
}

vector<int> Detector::generate_bin(vector<double> P) {
	int cnt = 0;
	int n = P.size();
	vector<int> bv(n, 0);
	//Generar
	for(int i = 0; i < n; i++) {
		int r = rand() % 100;
		if(r < (int)(P[i] * 100.0)) {
			bv[i] = 1;
			cnt++;
		}
		else {
			bv[i] = 0;
		}
	}

	return bv;
}

int Detector::Hadamard(Image a, Image b) {
	int res = 0;
	for(int i = 0; i < a.get_height(); i++) {
		for(int j = 0; j < a.get_width(); j++) {
			int val = a.get_val(i, j) * b.get_val(i, j);
			if(val != 0) {
				res++;
			}
		}
	}

	return res;
}

int Detector::weighted_points(Image a, Point c, int p, int dir) {
	vector<Point> pp1, pp2;
	//Se usa el algoritmo de generación de parábolas para determinar los puntos
	int x, y, cnt, d, p2, p4, width = a.get_width(), height = a.get_height();
	int bound = width * 2;
	int xc = c.get_i();
	int yc = c.get_j();
	p2 = 2 * p;
	p4 = 2 * p2;
	x = 0, y = 0;
	d = 1 - p;
	cnt = 0;
	while((y < p) && (cnt <= bound)) {
		if((y + yc >= 0 && y + yc < height) &&
		   (x + xc >= 0 && x + xc < width))
			pp1.push_back(Point(y + yc, x + xc));

		if((yc - y >= 0 && yc - y < height) &&
		   (x + xc >= 0 && x + xc < width))
			pp2.push_back(Point(yc - y, x + xc));
		if(d >= 0) {
			x += dir;
			cnt++;
			d -= p2;
		}
		y++;
		d += 2 * y + 1;
	}
	if(d == 1) d = 1 - p4;
	else d = 1 - p2;
	while(cnt <= bound) {
		if((y + yc >= 0 && y + yc < height) &&
		   (x + xc >= 0 && x + xc < width))
			pp1.push_back(Point(y + yc, x + xc));

		if((yc - y >= 0 && yc - y < height) &&
		   (x + xc >= 0 && x + xc < width))
			pp2.push_back(Point(yc - y, x + xc));
		
		if(d <= 0) {
			y++;
			d += 4 * y;
		}
		x += dir;
		cnt++;
		d -= p4;
	}
	int c1 = 0, c2 = 0;
	for(int i = 0; i < pp1.size(); i++) {
		int xa = pp1[i].get_i(), ya = pp1[i].get_j();
		if(a.get_val(xa, ya)) c1++;
	}
	for(int i = 0; i < pp2.size(); i++) {
		int xa = pp2[i].get_i(), ya = pp2[i].get_j();
		if(a.get_val(xa, ya)) c2++;
	}

	return (int)pow(c1 - c2, 2);
}

void Detector::generate_pop(vector<double> P, vector<vector<int> > &pop, int start) {
	int pixel_sz = white_points.size();
	for(int i = start; i < pop_size; i++) {
		while(true) {
			vector<int> bv = generate_bin(P);

			//Validar que los índices de ese vector estén dentro del rango de la lista
			int aux1 = to_int(get_sub_vector(bv, 0, nbits - 1));
			int aux2 = to_int(get_sub_vector(bv, nbits, (nbits * 2) - 1));
			int aux3 = to_int(get_sub_vector(bv, nbits * 2, (nbits * 3) - 1));

			if((aux1 >= 0 && aux1 < pixel_sz) &&
			   (aux2 >= 0 && aux2 < pixel_sz) &&
			   (aux3 >= 0 && aux3 < pixel_sz)) {

				//Verificar que no coincidan las y's generadas
				int yi = white_points[aux1].get_j();
				int yj = white_points[aux2].get_j();
				int yk = white_points[aux3].get_j();

				if(yi != yj && yi != yk && yj != yk) {
					pop[i] = bv;
					break;
				}
			}
		}
	}
}

vector<Individual> Detector::evaluate_pop(vector<vector<int> > pop) {
	vector<Individual> res;
	for(int i = 0; i < pop_size; i++) {
		Individual ind_act;
		vector<int> v_act = pop[i];
		ind_act.set_bv(v_act);
		double xc, yc, p;
		int dir;
		generate_points(v_act, xc, yc, dir, p);

		Image img_act = generate_parabola(img->get_width(), img->get_height(), xc, yc, dir, p);
		int quality = Hadamard(*img, img_act);
		//int quality = weighted_points(*img, Point(xc, yc), p, dir);
		//cout << quality << endl;
		ind_act.set_quality(quality);
		res.push_back(ind_act);
	}
	sort(res.begin(), res.end(), IndividualComparator());

	return res;
}

void Detector::update_prob(vector<double> &P, vector<Individual> evaluated) {
	int sr = (int)(selection_rate * evaluated.size());
	for(int i = 0; i < P.size(); i++) {
		double sum = 1.0;
		//double sum = 0.0;
		for(int j = 0; j < sr; j++) {
			sum += evaluated[j].get_bv()[i];
		}
		sum /= (sr + 2);
		//sum /= sr;
		P[i] = sum;
	}
}

vector<Point> Detector::UMDA() {
	vector<vector<int> > pop(pop_size);
	//Tamaño de la lista de pixeles
	int pixel_sz = white_points.size();

	//Mejor vector
	vector<Point> res;
	
	//Inicializar el vector de probabilidades
	vector<double> P(nbits * 3, 0.5);

	//Generar la población inicial
	generate_pop(P, pop, 0);

	//Evaluar la población
	vector<Individual> evaluated = evaluate_pop(pop);

	//Actualizar el vector de probabilidades
	update_prob(P, evaluated);
	pop[0] = evaluated[0].get_bv();

	for(int i = 1; i < no_generations; i++) {
		cout << "Generación " << i << endl;
		evaluated.clear();
		generate_pop(P, pop, 1);
		evaluated = evaluate_pop(pop);
		update_prob(P, evaluated);
		pop[0] = evaluated[0].get_bv();

		/*cout << evaluated[0].get_quality() << endl;
		for(int j = 0; j < P.size(); j++) {
			cout << P[j] << " ";
		}
		cout << endl;*/
	}

	double xc, yc, p;
	int dir;
	generate_points(pop[0], xc, yc, dir, p);

	char name[25];
	sprintf(name, "Final.pgm");

	Image img_act = generate_parabola(img->get_width(), img->get_height(), xc, yc, dir, p);
	for(int i = 0; i < img->get_height(); i++) {
		for(int j = 0; j < img->get_width(); j++) {
			if(img->get_val(i, j))
				img_act.set_val(i, j, 255);
		}
	}
	img_act.save(string(name), false);

	return res;
}