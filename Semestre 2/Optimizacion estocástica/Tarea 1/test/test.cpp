#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <ctime>
#include <string>
#include <ctime>
#include <cstring>
#include <vector>

using namespace std;

int rand_in_range(int a, int b) {
	return rand() % (b - a + 1) + a;
}

int main(int argc, char **argv) {
	ofstream file;
	srand(time(NULL));

	int n = atoi(argv[1]);
	file.open(argv[2], ofstream::out | ofstream::app);
	vector<int> v(100);
	while(n--) {
		v.clear();
		for(int i = 0; i < 100; i++) {
			v[i] = rand_in_range(1, 10);
		}
		int sum = 0;
		for(int i = 0; i < 100; i++) {
			sum += v[i];
		}
		file << "La suma es: " << sum << endl;
	}
	file.close();

	return 0;
}