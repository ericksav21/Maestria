#ifndef PERSON_H
#define PERSON_H

#include <string>

using namespace std;

class Person {
private:
	string name;
	char gender;
	double height;
	double weight;
	
public:
	Person(string name, char gender, double height, double weight);
	~Person();
	string get_name();
	char get_gender();
	double get_height();
	double get_weight();
	void set_name(string name);
	void set_gender(char gender);
	void set_height(double height);
	void set_weight(double weight);
};

#endif