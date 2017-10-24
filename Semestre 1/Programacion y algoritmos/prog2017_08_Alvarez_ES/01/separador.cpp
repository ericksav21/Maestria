#include "separador.h"

int in_dict(vector<WORD> dict, string str) {
	for(int i = 0; i < dict.size(); i++) {
		if(dict[i].str == str)
			return i;
	}

	return -1;
}

WORD new_word(string str) {
	WORD wrd;
	wrd.str = str;
	wrd.freq = 1;

	return wrd;
}

REG new_reg(string str, int freq_s, int freq_ns) {
	REG reg;
	reg.str = str;
	reg.freq_s = freq_s;
	reg.freq_ns = freq_ns;

	return reg;
}

bool is_number(char c) {
	int aux = (int)c;
	if(aux >= 48 && aux <= 57)
		return true;
	return false;
}

bool is_letter(char c) {
	int aux = (int)c;
	if((aux >= 97 && aux <= 122) || (aux >= 65 && aux <= 90))
		return true;
	return false;
}

bool is_char_valid(char c) {
	if(is_number(c))
		return true;
	else if(is_letter(c))
		return true;

	return false;
}

string validate_str(string word) {
	string res = "";
	for(int i = 0; i < word.size(); i++) {
		if(is_char_valid(word[i])) {
			res += word[i];
		}
	}

	return res;
}

string to_lower(string str) {
	for(int i = 0; i < str.size(); i++) {
		str[i] = tolower(str[i]);
	}

	return str;
}

vector<WORD> read_from_file(string files_name) {
	ifstream file(files_name.c_str());
	vector<WORD> dict;

	if(!file.is_open()) {
		cout << "Error, no se pudo abrir el archivo." << endl;
		return dict;
	}
	string str;
	while(file >> str) {
		str = to_lower(str);
		str = validate_str(str);
		int ind = in_dict(dict, str);
		if(ind == -1) {
			dict.push_back(new_word(str));
		}
		else {
			dict[ind].freq++;
		}
	}
	file.close();

	return dict;
}

vector<REG> intersection(vector<WORD> a, vector<WORD> b) {
	vector<REG> res;
	for(int i = 0; i < a.size(); i++) {
		string aux = a[i].str;
		int ind = in_dict(b, aux);
		if(ind != -1) {
			res.push_back(new_reg(aux, a[i].freq, b[ind].freq));
		}
	}

	return res;
}

void print_dict(vector<WORD> dict) {
	for(int i = 0; i < dict.size(); i++) {
		cout << dict[i].str << ": " << dict[i].freq << endl;
	}
}

void print_dict(vector<REG> dict) {
	for(int i = 0; i < dict.size(); i++) {
		cout << dict[i].str << ": " << dict[i].freq_s << ", " << dict[i].freq_ns << endl;
	}
}