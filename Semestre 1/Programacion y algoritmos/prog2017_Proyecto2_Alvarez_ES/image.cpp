#include "image.hpp"

Image::Image(string files_name) {
	read_from_file(files_name);
}

Image::Image(vector<vector<int> > mat) {
	this->mat = mat;
	this->width = mat[0].size();
	this->height = mat.size();
	this->scale = 255;
}

Image::~Image() {}

void Image::read_from_file(string files_name) {
	stringstream ss;
	ss << Util::get_path() << "/" << files_name;
	string files_path = ss.str();
	ifstream in(files_path.c_str());
	if(in.is_open()) {
		string format;
		in >> format;
		in >> width >> height >> scale;
		mat.resize(height);

		for(int i = 0; i < height; i++) {
			for(int j = 0; j < width; j++) {
				int aux;
				in >> aux;
				mat[i].push_back(aux);
			}
		}

		in.close();
	}
	else {
		cout << "Error al abrir el archivo: " << files_name << "." << endl;
	}
}

vector<vector<int> > Image::get_mat() {
	return mat;
}

int Image::get_width() {
	return width;
}

int Image::get_height() {
	return height;
}

int Image::get_val(int i, int j) {
	return mat[i][j];
}

void Image::set_mat(vector<vector<int> > mat) {
	this->mat = mat;

	//Al cambiar la matriz hay que actualizar el ancho y el alto
	this->width = mat[0].size();
	this->height = mat.size();
}

void Image::set_val(int i, int j, int val) {
	mat[i][j] = val;
}

int Image::A_test(int i, int j) {
	int cnt = 0;
	if(!mat[i - 1][j] && mat[i - 1][j + 1] != 0) cnt++;
	if(!mat[i - 1][j + 1] && mat[i][j + 1] != 0) cnt++;
	if(!mat[i][j + 1] && mat[i + 1][j + 1] != 0) cnt++;
	if(!mat[i + 1][j + 1] && mat[i + 1][j] != 0) cnt++;
	if(!mat[i + 1][j] && mat[i + 1][j - 1] != 0) cnt++;
	if(!mat[i + 1][j - 1] && mat[i][j - 1] != 0) cnt++;
	if(!mat[i][j - 1] && mat[i - 1][j - 1] != 0) cnt++;
	if(!mat[i - 1][j - 1] && mat[i - 1][j] != 0) cnt++;

	return cnt;
}

int Image::B_test(int i, int j) {
	int cnt = 0;
	for(int r = -1; r <= 1; r++) {
		for(int c = -1; c <= 1; c++) {
			if(r == 0 && c == 0) continue;
			if(mat[i + r][j + c] != 0) {
				cnt++;
			}
		}
	}

	return cnt;
}

void Image::skeletonize() {
	vector<Point> points;
	bool change = false;

	do {
		change = false;
		points.clear();
		for(int i = 1; i < height - 1; i++) {
			for(int j = 1; j < width - 1; j++) {
				if(mat[i][j] != 0) {
					int b_res = B_test(i, j);
					int a_res = A_test(i, j);
					if((b_res >= 2 && b_res <= 6) &&
						a_res == 1 &&
						//P2 * P4 * P6
						(mat[i - 1][j] * mat[i][j + 1] * mat[i + 1][j] == 0) &&
						 mat[i][j + 1] * mat[i + 1][j] * mat[i][j - 1] == 0) {

						//Cambio en el pixel
						points.push_back(Point(i, j));
						change = true;
					}
				}
			}
		}
		for(int i = 0; i < points.size(); i++) {
			mat[points[i].get_i()][points[i].get_j()] = 0;
		}

		points.clear();
		for(int i = 1; i < height - 1; i++) {
			for(int j = 1; j < width - 1; j++) {
				if(mat[i][j] != 0) {
					int b_res = B_test(i, j);
					int a_res = A_test(i, j);
					if((b_res >= 2 && b_res <= 6) &&
						a_res == 1 &&
						//P2 * P4 * P8
						(mat[i - 1][j] * mat[i][j + 1] * mat[i][j - 1] == 0) &&
						 mat[i - 1][j] * mat[i + 1][j] * mat[i][j - 1] ==  0) {

						//Cambio en el pixel
						points.push_back(Point(i, j));
						change = true;
					}
				}
			}
		}
		for(int i = 0; i < points.size(); i++) {
			mat[points[i].get_i()][points[i].get_j()] = 0;
		}
	} while(change);
}

void Image::print() {
	for(int i = 0; i < height; i++) {
		for(int j = 0; j < width; j++) {
			cout << mat[i][j] << " ";
		}
		cout << endl;
	}
}

void Image::save(string files_name, bool use_path) {
	if(use_path) {
		stringstream ss;
		ss << Util::get_path() << "/" << files_name;
		files_name = ss.str();
	}
	ofstream out(files_name.c_str());
	out << "P2" << endl;
	out << width << " " << height << endl;
	out << scale << endl;
	for(int i = 0; i < height; i++) {
		for(int j = 0; j < width; j++) {
			out << mat[i][j] << " ";
		}
		out << endl;
	}

	out.close();
}