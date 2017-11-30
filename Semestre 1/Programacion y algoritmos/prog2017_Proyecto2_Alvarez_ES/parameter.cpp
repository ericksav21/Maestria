#include "parameter.hpp"

Parameter::Parameter(int argc, char **argv) {
	this->argc = argc;
	this->argv = new char*[argc + 1];
	for(int i = 0; i <= argc; i++) {
		this->argv[i] = argv[i];
	}
}

Parameter::~Parameter() {}

void Parameter::print_help() {
	cout << "Detector de parábolas, hecho por Erick Salvador Alvarez Valencia." << endl;
	cout << "Ayuda del sistema:" << endl;
	cout << "--seed o -S\t" << "Semilla generadora de números aleatorios.";
	cout << "--file o -F\t" << " Indica el nombre de la imagen que será procesada por el programa, la misma debe estar en formato PGM." << endl;
	cout << "--algo o -A\t" << " Algoritmo que se usará para el procesamiento: 'UMDA', 'Genetic' o 'Both'." << endl;
	cout << "--psize\t" << " Tamaño de la población (UMDA y Genético)." << endl;
	cout << "--ngenerations\t" << " Número de generaciones (UMDA y Genético)." << endl;
	cout << "--srate\t" << " Porcentaje de selección (UMDA)." << endl;
	cout << "--urate\t" << " Porcentaje de cruce (Genético)." << endl;
	cout << "--mrate\t" << " Porcentaje de mutación (Genético)." << endl;
	cout << "--verbose o -V\t" << " Modo explícito (texto)." << endl;
}

map<string, string> Parameter::process() {
	map<string, string> res;
	int i = 1;
	while(i < argc) {
		string p_act = string(argv[i]);
		if(p_act == "--seed" || p_act == "-S") {
			res["seed"] = string(argv[++i]);
		}
		else if(p_act == "--file" || p_act == "-F") {
			res["file"] = string(argv[++i]);
		}
		else if(p_act == "--algo" || p_act == "-A") {
			res["algo"] = string(argv[++i]);
		}
		else if(p_act == "--psize") {
			res["psize"] = string(argv[++i]);
		}
		else if(p_act == "--ngenerations") {
			res["ngenerations"] = string(argv[++i]);
		}
		else if(p_act == "--srate") {
			res["srate"] = string(argv[++i]);
		}
		else if(p_act == "--urate") {
			res["urate"] = string(argv[++i]);
		}
		else if(p_act == "--mrate") {
			res["mrate"] = string(argv[++i]);	
		}
		else if(p_act == "--verbose" || p_act == "-V") {
			res["verb"] = "1";	
		}
		else {
			cout << "Parámetro '" << p_act << "' no reconocido." << endl;
		}
		i++;
	}

	return res;
}