#ifndef CLASIFICADOR_H
#define CLASIFICADOR_H

#include <iostream>
#include <vector>

#include "separador.h"

int in_table(vector<REG> table, string str);

double clasify(vector<WORD> text, vector<REG> table, bool is_spam);

#endif