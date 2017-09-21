#include <stdio.h>
#include "apuntadores.h"

int main(int argc, char *argv[])
{
  double x=3.5,y=-12.6;
  printf("Direcciones antes de x=%p y=%p\n",&x,&y);
  printf("Contenidos antes de x=%g y=%g\n\n", x, y);

  smax(&x, &y);

  printf("Direcciones despues de x=%p y=%p\n",&x,&y);
  printf("Contenidos despues de x=%g y=%g\n", x, y);

  return 0;
}
