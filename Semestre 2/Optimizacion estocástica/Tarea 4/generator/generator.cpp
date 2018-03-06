#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main() {
	ofstream file("tasks.txt");
	string name;
	string dir = "/home/user_demo/ErickAlvarez/Tarea2";
	string output_r = dir + "/main " + dir + "/instances/";
	while(cin >> name) {
		string output = output_r + name + ".txt";
		for(int i = 1; i <= 100; i++) {
			string aux = output;
			aux += " " + to_string(i) + " " + dir + "/" + name + "/Results_" + to_string(i) + ".txt";
			file << aux << endl;
		}
	}

	file.close();
	return 0;
}
