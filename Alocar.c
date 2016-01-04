#include <stdlib.h>
#include "Alocar.h"

//Função para alocar matrizes iM x jM
//Function to alloc iMxjM arrays
double **Matriz(int iM, int jM){
    double **M; int i;

    M = malloc(iM * sizeof(double *));
    for (i = 0; i < iM; i++)
        M[i] = malloc(jM * sizeof(double));

    return M;
}

//Função para alocar matriz inteira iM x jM para flags
//Function to alloc iM x jM int flag array
int **FlagMatriz(int iM, int jM){
    int **M; int i;

    M = malloc(iM * sizeof(int *));
    for (i = 0; i < iM; i++)
        M[i] = malloc(jM * sizeof(int));

    return M;
}

//Função para alocar matriz iM x jM de char
//Function to alloc iM x jM char array
char **CharMatriz(int iM, int jM){
    char **M; int i;

    M = (char**) malloc(iM * sizeof(char *)*iM);
    for (i = 0; i < iM; i++)
        M[i] = (char*)malloc(jM * sizeof(char));

    return M;
}
