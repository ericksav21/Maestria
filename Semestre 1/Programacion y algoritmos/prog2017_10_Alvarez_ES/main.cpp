#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

#include "neural.hpp"

using namespace std;

int main(int argc, char **argv) {
	//srand(time(NULL));
	srand(582743);
	vector<int> layers;
	vector<double> t(2);
	layers.push_back(2);
	layers.push_back(3);
	layers.push_back(1);
	NeuralNetwork nn(layers, 0.1, 0.7, 100);
	t[0] = -5.3;
	t[1] = 2.8;
	//nn.print_nn();
	nn.train(t);
	nn.print_nn();

	return 0;
}