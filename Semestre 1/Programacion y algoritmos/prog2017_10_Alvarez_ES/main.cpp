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
	layers.push_back(2);
	layers.push_back(3);
	layers.push_back(1);
	NeuralNetwork nn();

	return 0;
}