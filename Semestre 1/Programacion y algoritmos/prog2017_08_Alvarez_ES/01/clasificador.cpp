#include "clasificador.h"

int in_table(vector<REG> table, string str) {
	for(int i = 0; i < table.size(); i++) {
		if(table[i].str == str)
			return i;
	}

	return -1;
}

double clasify(vector<WORD> text, vector<REG> table, bool is_spam) {
	//Obtener la suma de las frecuencias
	int cnt_spam = 0, cnt_nospam = 0;
	for(int i = 0; i < table.size(); i++) {
		cnt_spam += table[i].freq_s;
		cnt_nospam += table[i].freq_ns;
	}

	double perc = 1.0;
	for(int i = 0; i < text.size(); i++) {
		string word = text[i].str;
		int ind = in_table(table, word);
		if(ind == -1)
			continue;
		if(is_spam) {
			perc *= ((double)table[ind].freq_s / (double)cnt_spam);
		}
		else {
			perc *= ((double)table[ind].freq_ns / (double)cnt_nospam);
		}
	}

	return perc;
}