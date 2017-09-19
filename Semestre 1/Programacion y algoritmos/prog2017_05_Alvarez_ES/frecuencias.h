#ifndef FRECUENCIAS_H
#define FRECUENCIAS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void str_to_lower(char *str);

int is_word_in_dict(char *str, char **dict, int word_size);

char** add_word_to_dict(char *str, char **dict, int dict_size, int pa, int *pinserted, int *realocated);

int** update_hist(int **hist, int pinserted, int dict_size, int realocated, int cur_file, int no_files);

double** convert_to_relative(int **hist, int *tot_per_block, int pa, int no_files);

void print_words(char **dict, double **hist, int pa, int cnt, int no_files);

double** generate_frec(char *files_name, int n_files, int *no_words);

#endif