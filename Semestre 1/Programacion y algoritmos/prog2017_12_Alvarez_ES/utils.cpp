#include "utils.hpp"

string trim(string str) {
	size_t first = str.find_first_not_of(' ');
    if (string::npos == first) {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

vector<string> read_csv_line(istream &in, char delimiter) {
	stringstream ss;
	bool inquotes = false;
	vector<string> row;
	while(in.good()) {
		char c = in.get();
		if (!inquotes && c == '"') {
			inquotes = true;
		}
		else if (inquotes && c == '"') {
			if ( in.peek() == '"') {
				ss << (char)in.get();
			}
			else {
				inquotes = false;
			}
		}
		else if (!inquotes && c == delimiter) {
			row.push_back( ss.str() );
			ss.str("");
		}
		else if (!inquotes && (c == '\r' || c == '\n')) {
			if(in.peek() == '\n') { in.get(); }
			row.push_back( ss.str() );
			return row;
		}
		else {
			ss << c;
		}
	}
}

void read_data(char *files_name, vector<Point> &data, int c1, int c2) {
	ifstream in;
	vector<string> v;

	in.open(files_name);
	int k = 0;
	
    while(in.good()) {
    	vector<string> row = read_csv_line(in, ',');
    	if(k > 0) {
    		Point p(atof(row[c1 - 1].c_str()), atof(row[c2 - 1].c_str()));
    		data.push_back(p);
    	}
    	k++;
    }

	in.close();
}