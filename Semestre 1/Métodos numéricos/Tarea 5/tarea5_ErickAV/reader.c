#include "reader.h"

// Lectura del vector en el archivo cfile.
// Devuelve NULL si no se pudo abrir el archivo.
double *read_vector(char *cfile, int *nr) {
    double *vec;
    FILE *f1 = fopen(cfile, "rb");
    if(!f1) return(NULL);

    fread(nr, sizeof(int), 1, f1);
    vec = create_vector(*nr, double);
    if(vec == NULL)
    	return NULL;

    fread(vec, sizeof(double), *nr, f1);
    fclose(f1);
    return vec;
}

// Lectura de la matriz en el archivo cfile.
// Devuelve NULL si no se pudo abrir el archivo.
double **read_matrix(char *cfile, int *nr, int *nc) {
    double **mat;
    FILE *f1 = fopen(cfile, "rb");
    
    if(!f1)
    	return(NULL);

    // Lectura del tamaño de la matriz
    fread(nr, sizeof(int), 1, f1);
    fread(nc, sizeof(int), 1, f1);

    // Reservamos memoria
    mat = create_matrix(*nr, *nc, double);

    // Lectura de los datos
    fread(mat[0], sizeof(double), (*nr) * (*nc), f1);
    fclose(f1);
    return mat;
}

// Escritura del vector vec en el archivo cfile.
// Devuelve 0 en caso de exito y 1 si no.
int write_vector(double *vec, int dim, char *cfile) {
    FILE *f1 = fopen(cfile, "wb");
    
    if(!f1)
    	return 1;

    fwrite(&dim, sizeof(int), 1, f1);
    fwrite(vec, sizeof(double), dim, f1);
    
    fclose(f1);
    return 0;
}

// Escritura de la matriz mat en el archivo cfile.
// Devuelve 0 en caso de exito y 1 si no.
int write_matrix(double **mat, int nr, int nc, char *cfile) {
    FILE *f1 = fopen(cfile, "wb");
    
    if(!f1)
    	return 1;

    fwrite(&nr, sizeof(int), 1, f1);
    fwrite(&nc, sizeof(int), 1, f1);
    fwrite(mat[0], sizeof(double), nr * nc, f1);

    fclose(f1);
    return 0;
}