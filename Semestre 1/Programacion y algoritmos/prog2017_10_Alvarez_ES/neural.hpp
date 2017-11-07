#ifndef NEURAL_H
#define NEURAL_H

#include <cstdlib>
#include <vector>
#include <cmath>
#include <algorithm>
#include <sstream>
#include <string>
#include <fstream>

#include "linear.hpp"

using namespace std;

struct TrainingElement {
	vector<double> in;
	vector<double> out;		
	
	TrainingElement(vector<double> in_, vector<double> out_) {
		in = in_;
		out = out_;
	}	
};

vector<TrainingElement> read_data(int no_rows, char *files_name);

class Neuron {
public:
	Neuron();
	~Neuron();
	static double activation_f(double x);
	static double activation_fp(double x);
};

class Layer {
private:
	vector<double> input, output;
	vector<double> err;
public:
	Layer(int n);
	~Layer();
	int n;
	vector<double> bias, bias_err;
	void set_input(int i, double v);
	void set_output(int i, double v);
	void set_err(int i, double v);
	void init_bias(int n);
	vector<double> get_input();
	vector<double> get_output();
	vector<double> get_err();
};

class NeuralNetwork {
private:
	struct Weight {
		vector<vector<double> > mat;
		int in, out;

		Weight(int in_, int out_) {
			in = in_;
			out = out_;
			mat.resize(in);
			for(int i = 0; i < in; i++) {
				mat[i].resize(out);
				for(int j = 0; j < out; j++) {
					mat[i][j] = rand() / static_cast<double>(RAND_MAX);
				}
			}
		}
	};

	//Número de capas
	int no_layers;
	//Número de iteraciones
	int iter;
	//Valor de aprendizaje
	double learning_rate;
	//Tamaños de las capas
	vector<int> layers_size;
	//Capas ocultas
	vector<Layer> layers;
	//Matrices de pesos
	vector<Weight> weights;
	//Conjunto de entrenamiento
	vector<TrainingElement> training_set;

public:
	NeuralNetwork(vector<int> layers_size, double lr, int iter);
	~NeuralNetwork();
	void init();
	void print_nn();
	void add_hidden_layer(int dim);
	void set_learning_rate(double lr);
	void set_training_set(vector<TrainingElement> ts);
	void compute_layer_input(int l);
	void compute_layer_output(int l);
	vector<double> clasify(vector<double> x);
	void compute_layer_err(int l);
	void update_weights(int l);
	double train();
};

#endif