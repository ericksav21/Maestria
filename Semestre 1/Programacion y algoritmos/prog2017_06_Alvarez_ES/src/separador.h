#ifndef SEPARADOR_H
#define SEPARADOR_H

#include <stdio.h>

int is_separator(char c);

int is_number(char c);

int is_letter(char c);

int is_char_valid(char c);

int separate(FILE *in, int start_int);

#endif
