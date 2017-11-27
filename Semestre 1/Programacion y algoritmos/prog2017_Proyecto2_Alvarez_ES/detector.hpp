#ifndef DETECTOR_H
#define DETECTOR_H

#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <map>
#include <cmath>
#include <string>
#include <cstring>
#include <utility>
#include <sstream>

#include "util.hpp"
#include "point.hpp"
#include "image.hpp"

using namespace std;

class Detector {
private:
	vector<Point> white_points;
	Image *img;
public:
	Detector(Image img);
	~Detector();
	Image get_image();
	vector<Point> get_white_points();
};

#endif