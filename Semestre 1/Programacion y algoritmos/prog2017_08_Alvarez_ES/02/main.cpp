#include <iostream>
#include <chrono>

#include "memo.h"
#include "imagen.h"

using namespace std;
using namespace std::chrono;

int main(int argc, char **argv) {
	if(argc < 2) {
		cout << "Error. Ejecuta: " << argv[0] << " [Archivo PGM]." << endl;
		return 0;
	}
	high_resolution_clock::time_point t1 = high_resolution_clock::now();

	string files_name(argv[1]);
	int width, height, cnt = 0, imax = 0;
	int **img = read_img(files_name, &width, &height);
	int **img_out = create_matrix_i(height, width, 0);

	for(int i = 0; i < height; i++) {
		for(int j = 0; j < width; j++) {
			if(img[i][j] != 0) {
				int **visited = create_matrix_i(height, width, 0);
				cnt++;
				int sz = bfs(img, width, height, i, j, visited);
				bool update_max = false;
				if(sz > imax) {
					update_max = true;
					imax = sz;
				}
				update_img(visited, img, img_out, width, height, update_max);

				delete_matrix_i(visited, height);
			}
		}
	}

	print_img(img_out, width, height, "out.pgm");
	delete_matrix_i(img, height);
	delete_matrix_i(img_out, height);

	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	duration<double> time_span = duration_cast<duration<double>>(t2 - t1);

	cout << "Tiempo transcurrido: " << time_span.count() << " segundos." << endl;
	cout << "Componentes conexas encontradas: " << cnt << endl;
	cout << "Tamaño de la componente más grande: " << imax << endl;

	return 0;
}