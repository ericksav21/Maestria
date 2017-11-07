#include "neural.hpp"

vector<TrainingElement> read_data(int no_rows, char *files_name) {
	ifstream file(files_name);
	vector<TrainingElement> res;

	if(!file.is_open()) {
		cout << "Error, no se pudo abrir el archivo." << endl;
		return res;
	}
	string str;
	for(int i = 0; i < no_rows; i++) {
		vector<double> in, out;
		for(int j = 0; j < 8; j++) {
			file >> str;
			double aux = atof(str.c_str());
			in.push_back(aux);
		}
		file >> str;
		double aux = atof(str.c_str());
		out.push_back(aux);
		TrainingElement te(in, out);
		res.push_back(te);
	}

	file.close();

	return res;
}

/*----- Neurona -----*/
double Neuron::activation_f(double x) {
	//Función sigmoide
	return 1.0 / (1.0 + exp(-x));

	//Función tangente hiperbólica
	//return (exp(val) - exp(-val)) / (exp(val) + exp(-val));
	/*if(x > 0.0)
		return 1.0;
	else
		return 0.0;*/
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
}

Layer::~Layer() {}

void Layer::init_bias(int n) {
	bias.resize(n);
	bias_err.resize(n);

	for(int i = 0; i < n; i++) {
		//Inicializar bias
		bias[i] = rand() / static_cast<double>(RAND_MAX);
		bias_err[i] = 0.0;
	}
}

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
NeuralNetwork::NeuralNetwork(vector<int> layers_size, double lr, int iter) {
	this->layers_size = layers_size;
	this->iter = iter;
	learning_rate = lr;
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
			layers[i].init_bias(layers_size[i + 1]);
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
		cout << "\nBIAS:" << endl;
		linear.print_vector(layers[i].bias);
		cout << "\nBIAS Err:" << endl;
		linear.print_vector(layers[i].bias_err);
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

void NeuralNetwork::set_learning_rate(double lr) {
	learning_rate = lr;
}

void NeuralNetwork::compute_layer_input(int l) {
	//Se asume que la capa es oculta (l > 0 y l < Ln - 1)
	Weight w = weights[l - 1];
	for(int i = 0; i < layers[l].n; i++) {
		double val = 0.0;
		for(int j = 0; j < layers[l - 1].n; j++) {
			val += layers[l - 1].get_output()[j] * w.mat[j][i]; //?
		}
		//val += layers[l - 1].bias[i];
		layers[l].set_input(i, val);
	}
}

void NeuralNetwork::set_training_set(vector<TrainingElement> ts) {
	training_set.clear();
	training_set = ts;
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
	//Computar error del BIAS
	for(int i = 0; i < layers[l].bias.size(); i++) {
		double auxb = 0.0, valb = 0.0;
		for(int j = 0; j < layers[l + 1].n; j++) {
			auxb += layers[l].bias[i] * layers[l + 1].get_err()[j];
		}
		valb = Neuron::activation_fp(1.0) * auxb;
		layers[l].bias_err[i] = valb;
	}
}

void NeuralNetwork::update_weights(int l) {
	Weight *w = &weights[l - 1];
	for(int i = 0; i < w->out; i++) {
		for(int j = 0; j < w->in; j++) {
			double aux = learning_rate * (layers[l].get_err()[i] * layers[l - 1].get_output()[j]);
			w->mat[j][i] += aux;
		}
		double auxb = learning_rate * (layers[l].get_err()[i] * Neuron::activation_f(1.0));
		layers[l - 1].bias[i] += auxb;
	}
}

double NeuralNetwork::train() {
	double train_err = 0.0;
	int t;
	for(t = 0; t < training_set.size(); t++) {
		cout << "Epoca " << (t + 1) << endl;
		TrainingElement te = training_set[t];
		vector<double> x = te.in;
		vector<double> y_des = te.out;
		vector<double> y_act = clasify(x);

		//Calc global err
		double err = 0.0;
		for(int i = 0; i < y_act.size(); i++) {
			err += pow(y_des[i] - y_act[i], 2);
		}
		train_err += (err * err);

		int llsz = layers_size.size() - 1;
		double aux = 0.0;
		for(int i = 0; i < layers_size[llsz]; i++) {
			aux = y_des[i] - y_act[i];
			layers[llsz].set_err(i, aux);
		}

		//Backpropagation
		for(int l = layers_size.size() - 2; l >= 0; l--) {
			compute_layer_err(l);
		}
		for(int l = 1; l < layers_size.size(); l++) {
			update_weights(l);
		}

	}

	return sqrt(train_err);
}