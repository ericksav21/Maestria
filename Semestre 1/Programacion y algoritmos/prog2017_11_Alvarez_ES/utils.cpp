#include "utils.hpp"

Utils::Utils() {}

Utils::~Utils() {}

int Utils::time_to_int(string time) {
	int res = 0, h, m, s;
	if (sscanf(time.c_str(), "%d:%d:%d", &h, &m, &s) >= 2) {
		res = h * 3600 + m * 60 + s;
	}

	return res;
}

string Utils::int_to_time(int sc) {
    int hour = sc / 3600;
    int minute = (sc / 60) % 60;
    int second = sc % 60;

    char res[30];
    sprintf(res, "%.2d:%.2d:%.2d", hour, minute, second);
    return string(res);
}

string Utils::trim(string str) {
	size_t first = str.find_first_not_of(' ');
    if (string::npos == first) {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

vector<string> Utils::read_data(char *files_name) {
    vector<string> v;
    ifstream in;
    in.open(files_name);
    string line, delimiter = "|";
    if (in.is_open()) {
        while (!in.eof()) {
            getline(in, line);
            size_t pos = 0;
            string token;
            while ((pos = line.find(delimiter)) != string::npos) {
                token = line.substr(0, pos);
                token = Utils::trim(token);
                if(token.size() > 0 && token[0] != '\n')
                    v.push_back(token);
                line.erase(0, pos + delimiter.length());
            }
            if(line.size() > 0) {
                v.push_back(line);
            }
        }
    }
    in.close();

    return v;
}

void Utils::init_hospital(vector<string> data, Hospital *h) {
    int c = 0;
    while(c < data.size()) {
        string init_time = data[c++];
        string name = data[c++];
        string nss = data[c++];
        string init_t_time = data[c++];
        char gender = data[c++][0];
        double hp = atof(data[c++].c_str()), lp = atof(data[c++].c_str());
        double height = atof(data[c++].c_str()), weight = atof(data[c++].c_str());
        string end_t_time = data[c++];
        vector<int> vs;
        for(int i = 0; i < 12; i++) {
            vs.push_back(atoi(data[c++].c_str()));
        }
        string dn = data[c++];
        //Crear el paciente
        Patient p(name, gender, height, weight, nss, hp, lp, init_time, end_t_time);
        p.set_vital_signs(vs);
        //Ver si la persona es doctor o enfermera
        if(dn.find("Dr.") == 0) {
            Doctor d(dn, 'M', 0, 0);
            Nurse n_aux("", 'F', 0, 0);
            int k = h->has_doctor(d);
            if(k == -1) {
                h->add_doctor(d);
            }
            h->new_patient(p, d, n_aux, Utils::time_to_int(init_t_time), true);
        }
        else {
            Nurse n(dn, 'F', 0, 0);
            Doctor d_aux("", 'M', 0, 0);
            int k = h->has_nurse(n);
            if(k == -1) {
                h->add_nurse(n);
            }
            h->new_patient(p, d_aux, n, Utils::time_to_int(init_t_time), false);
        }
    }
}