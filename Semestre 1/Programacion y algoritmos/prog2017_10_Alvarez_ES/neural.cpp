#include "neural.hpp"

/*----- Neurona -----*/
double Neuron::activation_f(double x) {
	//Función sigmoide
	return 1.0 / (1.0 + exp(-x));

	//Función tangente hiperbólica
	//return (exp(val) - exp(-val)) / (exp(val) + exp(-val));
}

double Neuron::activation_fp(double x) {
	return Neuron::activation_f(x) * (1.0 - Neuron::activation_f(x));
}

/*----- Capa -----*/
Layer::Layer(int n) {
	this->n = n;
	input.resize(n);
	output.resize(n);
	err.resize(n);

	for(int i = 0; i < n; i++) {
		input[i] = output[i] = err[i] = 0.0;
	}

	//Inicializar bias
	bias = rand() / static_cast<double>(RAND_MAX);
}

Layer::~Layer() {}

vector<double> Layer::get_input() {
	return input;
}

vector<double> Layer::get_output() {
	return output;
}

vector<double> Layer::get_err() {
	return err;
}

/*----- Red neuronal -----*/
NeuralNetwork::NeuralNetwork(vector<int> layers_size, double lr, double cr, int iter) {
	this->layers_size = layers_size;
	this->iter = iter;
	learning_rate = lr;
	conver_rate = cr;
	no_layers = layers_size.size();

	init();
}

NeuralNetwork::~NeuralNetwork() {}

void NeuralNetwork::init() {
	//Añadir las capas y los pesos
	int sz = layers_size.size();
	for(int i = 0; i < sz; i++) {
		add_hidden_layer(layers_size[i]);
		if(i < sz - 1) {
			weights.push_back(Weight(layers_size[i], layers_size[i + 1]));
		}
	}
}

void NeuralNetwork::add_hidden_layer(int dim) {
	layers.push_back(Layer(dim));
}

void NeuralNetwork::compute_layer_input(int l) {
	//Se asume que la capa es oculta (l > 0 y l < Ln - 1)
	Weight w = weights[l - 1];
	for(int i = 0; i < layers[l].n; i++) {
		layers[l].get_input()[i] = 0.0;
		for(int j = 0; j < layers[l - 1].n; j++) {
			layers[l].get_input()[i] += layers[l - 1].get_output()[j] * w.mat[i][j] + layers[l - 1].bias; //?
		}
	}
}

void NeuralNetwork::compute_layer_output(int l) {
	for(int i = 0; i < layers[l].n; i++) {
		layers[l].get_output()[i] = Neuron::activation_f(layers[l].get_input()[i]);
	}
}

void NeuralNetwork::clasify(vector<double> x) {

}

void NeuralNetwork::train() {

}