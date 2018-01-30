#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <ctime>
#include <string>
#include <ctime>
#include <cstring>

using namespace std;

int rand_in_range(int a, int b) {
	return rand() % (b - a + 1) + a;
}

int main(int argc, char **argv) {
	ofstream file;
	srand(time(NULL));
	file.open(argv[2], ofstream::out | ofstream::app);
	file << "El parámetro es: " << string(argv[1]) << endl;
	file.close();

	return 0;
}