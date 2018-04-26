#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <utility>
#include <algorithm>
#include <cfloat>
#include <unistd.h>

#include "utils.hpp"

using namespace std;

int main(int argc, char **argv) {
	srand(time(NULL));

	int var_size = 18;
	int dim = 2;
	vector<int> p1, p2;
	for(int i = 0; i < (var_size * dim); i++) {
		p1.push_back(1);
		p2.push_back(0);
	}
	for(int i = 19; i < (var_size * dim); i++) {
		p2[i] = 1;
	}
	p1[18] = 0;

	//crossover_1p_complete(p1, p2);
	crossover_2p_complete(p1, p2);

	return 0;
}