#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <stdio.h>

int is_separator(char c);

int is_number(char c);

int is_letter(char c);

int is_char_valid(char c);

void proc(FILE *in, char *new_name);

#endif
