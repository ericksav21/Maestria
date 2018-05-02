#include <iostream>
#include <cstdio>
#include <string>

#include "utils.hpp"
#include "differential.hpp"

using namespace std;

int main(int argc, char **argv) {
	Differential de(200, -10, 15, "f1", 10000);
	de.run();

	return 0;
}