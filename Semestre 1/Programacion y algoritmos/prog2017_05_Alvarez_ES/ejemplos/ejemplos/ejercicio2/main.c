#include "apuntadores.h"

int main(int argc, char *argv[])
{
  int n=9, samples=10;
  double *x=(double *)malloc(sizeof(double)*n);
  llenaVector(x,samples);
  calculaModa(x, samples);
  return 0;
}
