 
#include "apuntadores.h"
void llenaVector(double *x,int n)
{
    for (int i=0; i<n; i++){
    x[rand()%n]++;
     printf("%p\n",&(((int*)x)[i]) );
    }
}

double calculaModa(double *x, int n)
{
  double mode;
  mode=x[0];
  for (int i=0; i<n; i++)
    if (mode<x[i])
        mode=x[i];
  return mode;
}
