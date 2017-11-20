#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

#include "kmeans.hpp"

using namespace std;

int main(int argc, char **argv) {
	if(argc < 3) {
		cout << "Error. Ejecuta: " << string(argv[0]) << " [Archivo CSV] [No. clusters]." << endl;
		return 0;
	}
	srand(time(NULL));

	return 0;
}