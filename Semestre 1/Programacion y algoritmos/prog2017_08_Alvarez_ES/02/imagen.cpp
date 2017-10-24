#include "imagen.h"

int** read_img(string files_name, int *fwidth, int *fheight) {
	ifstream file(files_name.c_str());

	if(!file.is_open()) {
		cout << "Error, no se pudo abrir el archivo." << endl;
		return NULL;
	}
	string str;
	int scale, width, height, val;
	file >> str;
	file >> width >> height >> scale;
	int **res = create_matrix_i(height, width, 0);
	for(int i = 0; i < height; i++) {
		for(int j = 0; j < width; j++) {
			file >> val;
			res[i][j] = val;
		}
	}
	*fwidth = width;
	*fheight = height;
	file.close();

	return res;
}

void print_img(int **img, int width, int height, string files_name) {
	ofstream file(files_name.c_str());
	//Escribir los headers necesarios
	file << "P2\n";
	file << width << " " << height << "\n";
	file << "255\n";
	for(int i = 0; i < height; i++) {
		for(int j = 0; j < width; j++) {
			file << img[i][j] << "\n";
		}
	}

	file.close();
}

vector<POINT> get_neighbors(int **img, int width, int height, int i, int j) {
	POINT p_aux;
	vector<POINT> neigh;

	if(i - 1 >= 0 && j - 1 >= 0 && img[i - 1][j - 1]) {
		p_aux.i = i - 1; p_aux.j = j - 1;
		neigh.push_back(p_aux);
	}
	if(i - 1 >= 0 && img[i - 1][j]) {
		p_aux.i = i - 1; p_aux.j = j;
		neigh.push_back(p_aux);
	}
	if(i - 1 >= 0 && j + 1 < width && img[i - 1][j + 1]) {
		p_aux.i = i - 1; p_aux.j = j + 1;
		neigh.push_back(p_aux);
	}
	if(j + 1 < width && img[i][j + 1]) {
		p_aux.i = i; p_aux.j = j + 1;
		neigh.push_back(p_aux);
	}
	if(i + 1 < height && j + 1 < width && img[i + 1][j + 1]) {
		p_aux.i = i + 1; p_aux.j = j + 1;
		neigh.push_back(p_aux);
	}
	if(i + 1 < height && img[i + 1][j]) {
		p_aux.i = i + 1; p_aux.j = j;
		neigh.push_back(p_aux);
	}
	if(i + 1 < height && j - 1 >= 0 && img[i + 1][j - 1]) {
		p_aux.i = i + 1; p_aux.j = j - 1;
		neigh.push_back(p_aux);
	}
	if(j - 1 >= 0 && img[i][j - 1]) {
		p_aux.i = i; p_aux.j = j - 1;
		neigh.push_back(p_aux);
	}

	return neigh;
}

int bfs(int **img, int width, int height, int ii, int jj, int **visited) {
	int cnt = 1;
	queue<POINT> q;
	visited[ii][jj] = 2;
	POINT p_ini;
	p_ini.i = ii; p_ini.j = jj;
	q.push(p_ini);

	while(!q.empty()) {
		POINT p_act = q.front();
		q.pop();

		int i = p_act.i, j = p_act.j;
		vector<POINT> neigh = get_neighbors(img, width, height, i, j);	

		for(int c = 0; c < neigh.size(); c++) {
			POINT p_i = neigh[c];
			if(!visited[p_i.i][p_i.j]) {
				cnt++;
				visited[p_i.i][p_i.j] = 2;
				q.push(p_i);
			}
		}
	}

	return cnt;
}

void update_img(int **src, int **org, int **dest, int width, int height, bool update_max) {
	for(int i = 0; i < height; i++) {
		for(int j = 0; j < width; j++) {
			if(src[i][j] == 2) {
				org[i][j] = 0;
				if(update_max)
					dest[i][j] = 255;
			}
			else if(update_max) {
				dest[i][j] = 0;
			}
		}
	}
}