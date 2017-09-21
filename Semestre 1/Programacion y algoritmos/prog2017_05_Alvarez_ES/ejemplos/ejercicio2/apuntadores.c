#include "apuntadores.h"

void llenaVector(double *x, int n) {
    for (int i = 0; i < n; i++){
      x[rand() % n]++;
      printf("%p\n", &(x[i]));
    }
}

double calculaModa(double *x, int n) {
  double aux, mode;
  aux = x[0]; mode = 0;
  for (int i = 1; i < n; i++)
    if (aux < x[i]) {
      aux = x[i];
      mode = i;
    }
  
  return mode;
}
