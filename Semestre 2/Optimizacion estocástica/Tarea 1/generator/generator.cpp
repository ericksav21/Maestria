#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <ctime>

using namespace std;

int rand_in_range(int a, int b) {
	return rand() % (b - a + 1) + a;
}

int main() {
	ofstream file("tasks.txt");
	for(int i = 1; i <= 1000; i++) {
		int n = rand_in_range(100000, 10000000);
		file << "/home/user_demo/ErickAlvarez/Test1/test " << n << " /home/user_demo/ErickAlvarez/Test1/tmp/salida" << i << ".txt\n";
	}
	file.close();

	return 0;
}