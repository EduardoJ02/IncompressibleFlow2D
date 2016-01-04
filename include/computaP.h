#ifndef COMPUTAP_H_INCLUDED
#define COMPUTAP_H_INCLUDED

#include "Alocar.h"

#define P_Dir mP_ant[i][j]-dx*idt*(u[i+1][j]- mF[i+1][j])
#define P_Esq mP_ant[i][j]+dx*idt*(u[i][j]- mF[i][j])
#define P_Inf mP_ant[i][j]+dy*idt*(v[i][j]- mG[i][j])
#define P_Sup mP_ant[i][j]-dy*idt*(v[i][j+1]- mG[i][j+1])

#define A mP[i][j+1]
#define B mP_ant[i][j-1]
#define C mP[i+1][j]
#define D mP_ant[i-1][j]

#define Esquerda 1
#define Superior 2
#define Inferior 4
#define Direita 8

extern int **flag;
extern int iM, jM;
extern double idx2, idy2, dt, dx, dy, idt;

void computaP(double **mP, double **mdP, double **mP_ant, double **residual, double **mF, double **mG, double **u, double **v);

#endif
