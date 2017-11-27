#include "util.hpp"

string Util::path = "data";

string Util::get_path() {
	return path;
}

void Util::set_path(string new_path) {
	path = new_path;
}