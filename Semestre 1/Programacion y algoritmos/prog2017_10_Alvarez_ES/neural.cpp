#include "neural.hpp"

/*----- Neurona -----*/
double Neuron::activation_f(double x) {
	//Función sigmoide
	return 1.0 / (1.0 + exp(-x));

	//Función tangente hiperbólica
	//return (exp(val) - exp(-val)) / (exp(val) + exp(-val));
}

//Derivada de la función de activación
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

void Layer::set_input(int i, double v) {
	this->input[i] = v;
}

void Layer::set_output(int i, double v) {
	this->output[i] = v;
}

void Layer::set_err(int i, double v) {
	this->err[i] = v;
}

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

void NeuralNetwork::print_nn() {
	LinearAlgebra linear;
	for(int i = 0; i < no_layers; i++) {
		cout << "Capa " << (i + 1);
		if(i == 0) cout << " (Entrada):" << endl;
		if(i == no_layers - 1) cout << " (Salida):" << endl;
		if(i != 0 && i != no_layers - 1) cout << " (Oculta):" << endl;

		//Pesos
		if(i < no_layers - 1) {
			cout << "Pesos:\n";
			Weight w = weights[i];
			for(int j = 0; j < layers_size[i]; j++) {
				for(int k = 0; k < layers_size[i + 1]; k++) {
					cout << w.mat[j][k] << " ";
				}
				cout << endl;
			}
		}
		cout << "\nBIAS: " << layers[i].bias << endl;
		cout << "\nEntrada:" << endl;
		linear.print_vector(layers[i].get_input());
		cout << "\nSalida:" << endl;
		linear.print_vector(layers[i].get_output());
		cout << "\nError:" << endl;
		linear.print_vector(layers[i].get_err());
		cout << endl;
	}
}

void NeuralNetwork::add_hidden_layer(int dim) {
	layers.push_back(Layer(dim));
}

void NeuralNetwork::compute_layer_input(int l) {
	//Se asume que la capa es oculta (l > 0 y l < Ln - 1)
	Weight w = weights[l - 1];
	for(int i = 0; i < layers[l].n; i++) {
		double val = 0.0;
		for(int j = 0; j < layers[l - 1].n; j++) {
			val += layers[l - 1].get_output()[j] * w.mat[j][i]; //?
		}
		val += layers[l - 1].bias;
		layers[l].set_input(i, val);
	}
}

void NeuralNetwork::compute_layer_output(int l) {
	for(int i = 0; i < layers[l].n; i++) {
		double val = Neuron::activation_f(layers[l].get_input()[i]);
		layers[l].set_output(i, val);
	}
}

vector<double> NeuralNetwork::clasify(vector<double> x) {
	int input_sz = layers_size[0];
	//Nos aseguramos que sea correcto el tamaño con la primer capa
	if(x.size() == input_sz) {
		//Caso especial, primera capa
		for(int i = 0; i < input_sz; i++) {
			layers[0].set_output(i, x[i]);
		}
		//Se procesan las demás capas
		for(int i = 1; i < this->no_layers; i++) {
			compute_layer_input(i);
			compute_layer_output(i);
		}
		//Se retorna el resultado en la última capa
		return layers[this->no_layers - 1].get_output();
	}

	return x;
}

void NeuralNetwork::compute_layer_err(int l) {
	Weight w = weights[l];
	for(int i = 0; i < layers[l].n; i++) {
		double aux = 0.0;
		for(int j = 0; j < layers[l + 1].n; j++) {
			aux += w.mat[i][j] * layers[l + 1].get_err()[j];
		}
		double val = Neuron::activation_fp(layers[l].get_input()[i]) * aux;
		layers[l].set_err(i, val);
	}
}

void NeuralNetwork::train(vector<double> t) {
	LinearAlgebra linear;
	vector<double> res = clasify(t);
	cout << "Resultado:" << endl;
	linear.print_vector(res);
	cout << endl;
}