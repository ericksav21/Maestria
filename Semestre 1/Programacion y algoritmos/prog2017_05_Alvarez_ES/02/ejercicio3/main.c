#include "apuntadores.h"

int main(int argc, char *argv) {
  int nrow = 9, ncol = 9;
  unsigned char **mat = umatriz(10, 10);
  freeMat(mat, 10);
  return 0;
}
