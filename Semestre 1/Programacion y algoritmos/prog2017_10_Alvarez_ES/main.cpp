#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

#include "neural.hpp"
#include "graphics.hpp"

using namespace std;

int main(int argc, char **argv) {
	srand(time(NULL));
	//srand(582743);

	vector<TrainingElement> t = read_data(768, "train.data");
	vector<int> layers;
	layers.push_back(8);
	layers.push_back(3);
	layers.push_back(1);
	create_img_png(layers, 1024, 768, "Red.png");
	/*NeuralNetwork nn(layers, 0.3, 100);
	nn.set_training_set(t);
	double res = nn.train();
	cout << res << endl;
	for(int i = 0; i < 20; i++) {
		LinearAlgebra linear;
		int ind = rand() % 768;
		TrainingElement ti = t[ind];
		vector<double> x = ti.in, y_des = ti.out;
		vector<double> y_act = nn.clasify(x);
		cout << "Clasificación número de elemento: " << ind << endl;
		cout << "Entrada: " << endl;
		linear.print_vector(x);
		cout << "\nSalida de la red: " << endl;
		linear.print_vector(y_act);
		cout << "\nSalida deseada: " << endl;
		linear.print_vector(y_des);
		cout << endl;
	}

	nn.print_nn();*/

	return 0;
}