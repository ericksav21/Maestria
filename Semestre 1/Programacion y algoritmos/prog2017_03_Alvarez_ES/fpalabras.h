#ifndef FPALABRAS_H
#define FPALABRAS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void str_to_lower(char *str);

char** copy_dict(char **src, char **dest, int src_size);

int is_word_in_dict(char *str, char **dict, int word_size);

char** add_word_to_dict(char *str, char **dict, int **hist, int dict_size, int pa, int *pinserted, int *realocated, int cur_file, int no_files);

void print_words(char **dict, int *hist, int pa, int cnt);

void proc();

#endif