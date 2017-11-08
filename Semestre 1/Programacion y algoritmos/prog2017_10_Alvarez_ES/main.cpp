#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>

#include "neural.hpp"
#include "graphics.hpp"

using namespace std;

int main(int argc, char **argv) {
	if(argc < 3) {
		cout << "Error. Ejecuta: " << string(argv[0]) << " [N] [Número de capas ocultas]." << endl;
		return 0;
	}
	int n = atoi(argv[1]);
	int capas = atoi(argv[2]);
	srand(time(NULL));

	vector<TrainingElement> t = read_data(n, "train.data");
	vector<int> layers;
	layers.push_back(8);
	for(int i = 0; i < capas; i++) layers.push_back(rand_in_range(2, 5));
	layers.push_back(1);
	//Crear la arquitectura de la red
	create_img_png(layers, 1024, 768, "Red.png");
	create_img_ps(layers, 1024, 768, "Red.ps");
	NeuralNetwork nn(layers, 0.01, 100);
	nn.set_training_set(t);
	for(int i = 0; i < n; i++) {
		LinearAlgebra linear;
		TrainingElement ti = t[i];
		vector<double> x = ti.in, y_des = ti.out;
		vector<double> y_act = nn.clasify(x);
		cout << "Clasificación número de elemento: " << (i + 1) << endl;
		cout << "Entrada: " << endl;
		linear.print_vector(x);
		cout << "\nSalida de la red: " << endl;
		linear.print_vector(y_act);
		cout << "\nSalida deseada: " << endl;
		linear.print_vector(y_des);
		cout << endl;
	}

	cout << "Estructura de la red:" << endl;
	nn.print_nn();

	return 0;
}