#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class Util {
private:
	static string path;
public:
	static string get_path();
	static void set_path(string new_path);
};

#endif