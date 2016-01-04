#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Alocar.h"
#include "Imprimir.h"
#include "Arquivos.h"
#include "Discret.h"
#include "computaF.h"
#include "computaG.h"
#include "computaP.h"

//Variáveis Globais
//Global Variables
double xlength, ylength, dx, dy, idx2, idy2, idx, idy, dt, idt;
int i,j, k, iM, jM, n=0;
double Re, iRe, gama, eps, U_s;
int **flag;

int main(){

    double t=0, t_f=15, alfa;
    int it, itM;
    double omega;

    //Lê as dimensões do problema a partir do arquivo
    //Reads the problem dimension from file
    leArquivoDim();
    printf("\n\nLinhas iM = %d\n", iM);
    printf("Colunas jM = %d", jM);


/**Variáveis do Problema****************************************************************************************/
    //Problem configuration
    xlength=1.0; ylength=1.0;
    dt=0.02; alfa=0.5;
    eps=0.001; omega=1.7; gama=0.9;
    itM=100;
    Re=400;
    U_s=1;

    dx=xlength/iM;
    dy=ylength/jM;

    idx2=1/(dx*dx);
    idy2=1/(dy*dy);
    idx=1/dx;
    idy=1/dy;
    idt=1/dt;
    iRe=1/Re;
/**Variáveis do Problema****************************************************************************************/

/**Alocação das Matrizes Iniciais*******************************************************************/
    //Allocates initial arrays
    flag=FlagMatriz(iM, jM);
    leArquivo();

    double **u;     u=Matriz(iM+1, jM);
    double **mF;    mF=Matriz(iM+1, jM);
    for (i = 0; i < iM+1; i++) {
      for (j = 0; j < jM; j++){
            u[i][j] = 0;
            mF[i][j]= 0;
        }
    }

    double **v;    v=Matriz(iM, jM+1);
    double **mG;   mG=Matriz(iM, jM+1);
    for (i = 0; i < iM; i++) {
      for (j = 0; j < jM+1; j++){
         v[i][j] = 0;
         mG[i][j]= 0;
      }
    }

    double **mP;    mP=Matriz(iM, jM);
    double **mdP;   mdP=Matriz(iM, jM);
    for (i = 0; i < iM; i++) {
      for (j = 0; j < jM; j++){
         mP[i][j] = 0;
         mdP[i][j]= 0;
      }
    }

    double **mP_ant;    mP_ant=Matriz(iM, jM);
    double **residual;  residual=Matriz(iM, jM);

/**Alocação das Matrizes Iniciais*******************************************************************/

    //Função para calcular o elemento máximo de uma matriz
    //Function to compute the maximum element of an array
    double Maximo(double **M){
        double Max=M[0][0];
        for (i = 1; i < iM; i++)
              for (j = 1; j < jM; j++)
                  if (Max < M[i][j])
                     Max = M[i][j];
        return Max;
    }

/**Determina dt************************************************************************************/
//Determines the time step according to the stability condition
//Determina um passo dt que satisfaça a condição de estabilidade
void passoTempo(void){

    double uMax;uMax=Maximo(u);
    double vMax;vMax=Maximo(v);
    double dtmin;

    if ((dx)/abs(uMax) < (dy)/abs(vMax))
        dtmin = (dx)/abs(uMax);
    else
        dtmin = (dy)/abs(vMax);

    if ((Re/2)*1/(idx2 + idy2) < dtmin)
        dtmin=(Re/2)*1/(idx2 + idy2);

    dt=alfa*dtmin;

    return dt;
}

/**Determina dt************************************************************************************/

void computaFGdP(void){

    //Computes F and G velocities in the interior and in the boundary points
    //Computa velocidades F e G nos pontos de interior e de contorno
    for (i = 0; i<iM; i++) {
      for (j = 0; j<jM; j++){
            if (flag[i][j]==0){
                mF[i][j] = F(i,j, u, v);
                mG[i][j] = G(i,j, u, v);
            } else {
                mF[i][j] = Fc(i,j, u, v);
                mG[i][j] = Gc(i,j, u, v);
            }
      }
    }

    //Computes the right-hand side of the pressure equation
    //Calcula o lado direito da equação de pressão
    for (i = 0; i<iM; i++)
      for (j = 0; j<jM; j++)
            mdP[i][j]=(mF[i+1][j] - mF[i][j])*idx + (mG[i][j+1] - mG[i][j])*idy;
}

/**Calcula u e v no nível de tempo seguinte*************************/
    //Computes U and V in the next time level
    void Passo(void){

    for (i = 0; i < iM-1; i++)
      for (j = 0; j < jM; j++)
            u[i+1][j] = mF[i+1][j] - dt*idx*(mP[i+1][j]-mP[i][j]);

    for (i = 0; i < iM; i++)
      for (j = 0; j < jM-1; j++)
            v[i][j+1] = mG[i][j+1] - dt*idy*(mP[i][j+1]-mP[i][j]);

    }
/**Calcula u e v no nível de tempo seguinte*************************/


/***************Algoritmo  ********************/
while (t<t_f){
//while (n<2){

    //Can also run on a fixed time step dt as long as it satisfies the stability condition
    //Também pode-se tomar um passo de tempo dt fixo contanto que satisfaça a condição de estabilidade
    passoTempo();
    t=t+dt;
    printf("\nTempo: %2f",t);
    printf("\n");

    computaFGdP();

    computaP(mP, mdP, mP_ant, residual, mF, mG, u, v);

    Passo();

    n++;
}

    //Escreve arquivo contendo os resultados
    //Writes file containing the results
    escreveArquivo(u,v);

    free(u);free(v);free(mF);free(mG);free(mdP);free(mP);

    return 0;
}

