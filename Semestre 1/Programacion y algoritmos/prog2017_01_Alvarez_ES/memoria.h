
#ifndef MEMORIA_H
#define MEMORIA_H
#include <stdlib.h>

#define MATRIZ(TIPO,NR,NC) (TIPO**)matriz08062016(sizeof(TIPO), NR, NC)
#define LIBERAMATRIZ(MAT) liberamatriz08062016((void**)MAT);
#define VECTOR(TIPO,N) (TIPO**)vector08062016(sizeof(TIPO),N)
#define LIBERAVECTOR(VEC) liberavector08062016((void*)VEC);

void **matriz08062016(int tamtipo, int nr, int nc)
{
   void **mat;
   
   mat=malloc(sizeof(void*)*nr);
   mat[0]=malloc(tamtipo*nr*nc);
   void *tem=mat[0];
   for (int i=1; i<nr; i++){
	   tem+=nc*tamtipo;
      mat[i]=tem;
    }  
return mat;	
}

void liberamatriz08062016(void **mat)
{
free(mat[0]);
free(mat);
}

void *vector08062016(int tamtipo, int n)
{
   void *mat;
   mat=malloc(tamtipo*n);
return mat;	
}

void liberavector08062016(void **vec)
{
free(vec);
}



#endif

