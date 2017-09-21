#include "apuntadores.h"

int main(int argc, char *argv)
{
  
  DMATRIZ A;
  DVECTOR x,b;
  A.data=NULL; A.nrow=0; A.ncol=0;
  x.data=NULL; x.n=0; 
  b.data=NULL; b.n=0;
  int nrow=10,ncol=10;
  A=dmatriz(nrow,ncol); //Solicita memoria
  x=vector(ncol); //Solicita memoria
  b=vector(ncol); //Solicita memoria
  A=llenaMat(A); //Llena con valores de 1...ncol cada renglon
  x=llenaVector(x); //Llena con 1's
  b=multiMatVec(A,x,b); //Multiplica A*x, si b no tiene memoria la requiere 
  A=freeDMat(A); //Libera la memoria de A
  x=freeVec(x); //Libera memoria de x
  b=freeVec(b);
  return 0;
}
