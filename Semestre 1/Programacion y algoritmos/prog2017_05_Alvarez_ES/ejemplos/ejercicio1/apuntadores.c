#include <stdio.h>
#include "apuntadores.h"

void swap(double *x, double *y) {
  printf("Direcciones antes de swap x=%p y=%p\n",x,y);
  printf("Contenidos antes de swap x=%g y=%g\n\n", x[0],y[0]);
  double tem=*x;
  *x=*y;
  *y=tem;
  printf("Direcciones despues de swap x=%p y=%p\n",x,y);
  printf("Contenidos despues de swap x=%g y=%g\n\n", x[0],y[0]);
}

void smax(double *setmax, double *setmin) {
  printf("Direcciones antes de smax max=%p min=%p\n", setmax, setmin);
  printf("Contenidos antes de smax max=%g min=%g\n\n", *setmax, *setmin);
  if (*setmax > *setmin)
    swap(setmax, setmin);
  printf("Direcciones antes de smax max=%p min=%p\n", setmax, setmin);
  printf("Contenidos antes de smax max=%g min=%g\n\n", *setmax, *setmin);
}