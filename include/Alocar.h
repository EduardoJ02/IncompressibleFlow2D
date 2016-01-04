#ifndef ALOCAR_H_INCLUDED
#define ALOCAR_H_INCLUDED

//Função para alocar matrizes iM x jM
double **Matriz(int iM, int jM);
//Função para alocar matriz inteira para flags
int **FlagMatriz(int iM, int jM);
//Função para alocar matriz de char
char **CharMatriz(int iM, int jM);

#endif
