#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <fstream>
#include <sstream>

#include "util.hpp"
#include "point.hpp"

class Image {
private:
	int width, height, scale;
	vector<vector<int> > mat;

	void read_from_file(string files_name);
	int A_test(int i, int j);
	int B_test(int i, int j);
public:
	Image(int width, int height, int color);
	Image(string files_name);
	Image(vector<vector<int> > mat);
	~Image();
	vector<vector<int> > get_mat();
	int get_width();
	int get_height();
	int get_val(int i, int j);
	void set_mat(vector<vector<int> > mat);
	void set_val(int i, int j, int val);
	void skeletonize();
	void draw_line(Point a, Point b, int color);
	void draw_parabola(Point c, int p, int bound, int dir, int color);
	void print();
	void save(string files_name, bool use_path);
};

#endif