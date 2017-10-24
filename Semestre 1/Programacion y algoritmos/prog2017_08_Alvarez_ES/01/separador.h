#ifndef SEPARADOR_H
#define SEPARADOR_H

#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include <cctype>

using namespace std;

typedef struct word {
	string str;
	int freq;
} WORD;

typedef struct reg {
	string str;
	int freq_s, freq_ns;
} REG;

int in_dict(vector<WORD> dict, string str);

WORD new_word(string str);

REG new_reg(string str, int freq_s, int freq_ns);

bool is_number(char c);

bool is_letter(char c);

bool is_char_valid(char c);

string validate_str(string word);

string to_lower(string str);

vector<WORD> read_from_file(string files_name);

vector<REG> intersection(vector<WORD> a, vector<WORD> b);

void print_dict(vector<WORD> dict);

void print_dict(vector<REG> dict);

#endif