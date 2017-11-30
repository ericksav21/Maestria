#include "base.hpp"

Base::Base(Image img, bool verb) {
	this->img = new Image(img.get_mat());
	this->verb = verb;

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
	nbits += 3;
}

Base::~Base() {
	if(img)
		delete img;
}

vector<int> Base::get_sub_vector(vector<int> v, int i, int j) {
	vector<int> res;
	for(int k = i; k <= j; k++)
		res.push_back(v[k]);

	return res;
}

vector<int> Base::to_binary(int n) {
	vector<int> res;
	string binary = bitset<12>(n).to_string();
	for(int i = 0; i < binary.size(); i++) {
		res.push_back(binary[i] - '0');
	}

	return res;
}

int Base::to_int(vector<int> v) {
	int sum = 0, tmp = 1;
	for(int i = 0; i < nbits; i++) {
		sum += v[i] * tmp;
		tmp *= 2;
	}

	return sum;
}

Image Base::get_image() {
	return *img;
}

vector<Point> Base::get_white_points() {
	return white_points;
}

void Base::print_white_points() {
	for(int i = 0; i < white_points.size(); i++) {
		cout << white_points[i].get_i() << " " << white_points[i].get_j() << endl;
	}
}

void Base::generate_points(vector<int> v, double &xc, double &yc, int &dir, double &p) {
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

Image Base::generate_parabola(int width, int height, double xc, double yc, int dir, double p) {
	int bound = width * 2;
	Image res(width, height, 0);
	res.draw_parabola(Point((int)xc, (int)yc), abs((int)p), bound, dir, 255);

	return res;
}

double Base::Hadamard(Image a, Image b) {
	double res = 0.0;
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

double Base::weighted_points(Image a, Point c, int p, int dir) {
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
	double res = 0.0;
	//Antes del foco
	while((y < p) && (cnt <= bound)) {
		if((y + yc >= 0 && y + yc < height) &&
		   (x + xc >= 0 && x + xc < width))
			if(a.get_val(y + yc, x + xc))
				res += 1.1;

		if((yc - y >= 0 && yc - y < height) &&
		   (x + xc >= 0 && x + xc < width))
			if(a.get_val(yc - y, x + xc))
				res += 1.1;
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
			if(a.get_val(y + yc, x + xc))
				res += 1;

		if((yc - y >= 0 && yc - y < height) &&
		   (x + xc >= 0 && x + xc < width))
			if(a.get_val(yc - y, x + xc))
				res += 1;
		
		if(d <= 0) {
			y++;
			d += 4 * y;
		}
		x += dir;
		cnt++;
		d -= p4;
	}
	return res;
}

void Base::save_img(vector<int> v, string out) {
	double xc, yc, p;
	int dir;
	generate_points(v, xc, yc, dir, p);
	string res = "out/";
	int i = 0;
	while(out[i] != '.') {
		res += out[i];
		i++;
	}
	res = res + ".png";
	Image img_act = generate_parabola(img->get_width(), img->get_height(), xc, yc, dir, p);
	vector<Point> ppoints = img_act.get_white_points();
	Graphics g(img_act.get_width(), img_act.get_height(), res);
	g.copy_img(*img);
	g.copy_points(ppoints);
	g.save(false);
}