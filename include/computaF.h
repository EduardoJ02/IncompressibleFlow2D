#ifndef COMPUTAF_H_INCLUDED
#define COMPUTAF_H_INCLUDED

#define A u[i+1][j]
#define B u[i][j]
#define C u[i-1][j]
#define D u[i][j+1]
#define E u[i][j-1]

#define a v[i+1][j]
#define b v[i][j]
#define e v[i][j-1]
#define q v[i+1][j-1]

#define Esquerda 1
#define Superior 2
#define Inferior 4
#define Direita 8


#define Esquerdas flag[i][j]==Esquerda || flag[i][j]==Esquerda+Superior || flag[i][j]==Esquerda+Inferior
#define Direitas flag[i][j]==Direita || flag[i][j]==Direita+Superior || flag[i][j]==Direita+Inferior

#define Superiores flag[i][j]==Superior || flag[i][j]==Superior+Direita || flag[i][j]==Superior+Esquerda
#define Inferiores flag[i][j]==Inferior || flag[i][j]==Inferior+Direita ||flag[i][j]==Inferior+Esquerda


extern double iRe, gama, dt, idx2, idx, idy2, idy, U_s;
extern double **u, **v;
extern int **flag;

double F(int i, int j, double **u, double **v);
double Fc(int i, int j, double **u, double **v);

#endif
