#include <stdlib.h>
#include <math.h>
#include "computaP.h"

//Gauss-Seidel method to solve the pressure equation
//Método de Gauss-Seidel para resolver a equação de pressão
void computaP(double **mP, double **mdP, double **mP_ant, double **residual, double **mF, double **mG, double **u, double **v){


    int it, i, j, cont=0;
    double a, b, c, ia, rMax;

    rMax=1;

    a=2*dt*(idx2+idy2);
    ia=1/a;

//    for (it=1; it<2; it++){
do{
        for (i = 0; i < iM; i++) {
          for (j = 0; j < jM; j++)
             mP_ant[i][j] = mP[i][j];
        }

            for (i = 0; i < iM; i++) {
                for (j = 0; j < jM; j++){

                    if (flag[i][j]==0){

                            b=(-dt*idx2)*(A + B);
                            c=(-dt*idy2)*(C + D);
                            mP[i][j]=-ia*(b+c+mdP[i][j]);
                    }

                    else if (flag[i][j]==Esquerda+Superior){

                             b=(-dt*idx2)*(P_Sup + B);
                            c=(-dt*idy2)*(C + P_Esq);
                            mP[i][j]=-ia*(b+c+mdP[i][j]);

                    }
                    else if (flag[i][j]==Superior){

                             b=(-dt*idx2)*(P_Sup + B);
                            c=(-dt*idy2)*(C + D);
                            mP[i][j]=-ia*(b+c+mdP[i][j]);

                    }
                    else if (flag[i][j]==Superior+Direita){

                             b=(-dt*idx2)*(P_Sup + B);
                            c=(-dt*idy2)*(P_Dir + D);
                            mP[i][j]=-ia*(b+c+mdP[i][j]);

                    }
                    else if (flag[i][j]==Direita){

                             b=(-dt*idx2)*(A + B);
                            c=(-dt*idy2)*(P_Dir + D);
                            mP[i][j]=-ia*(b+c+mdP[i][j]);

                    }
                    else if (flag[i][j]==Direita+Inferior){

                             b=(-dt*idx2)*(A + P_Inf);
                            c=(-dt*idy2)*(P_Dir + D);
                            mP[i][j]=-ia*(b+c+mdP[i][j]);

                    }
                    else if (flag[i][j]==Inferior){

                             b=(-dt*idx2)*(A + P_Inf);
                            c=(-dt*idy2)*(C + D);
                            mP[i][j]=-ia*(b+c+mdP[i][j]);

                    }
                    else if (flag[i][j]==Inferior+Esquerda){

                             b=(-dt*idx2)*(A + P_Inf);
                            c=(-dt*idy2)*(C + P_Esq);
                            mP[i][j]=-ia*(b+c+mdP[i][j]);

                    }
                    else if (flag[i][j]==Esquerda){

                             b=(-dt*idx2)*(A + B);
                            c=(-dt*idy2)*(C + P_Esq);
                            mP[i][j]=-ia*(b+c+mdP[i][j]);
                    }
                }
            }
        rMax=0;
        for (i = 0; i < iM; i++) {
          for (j = 0; j < jM; j++){
             residual[i][j]=fabs(mP_ant[i][j]-mP[i][j]);
             if(residual[i][j]>rMax){
                rMax=residual[i][j];
             }


          }
        }
    }//while (rMax>0.00004);
    while (rMax>0.001);
    //while (rMax>0.00001);
    //
    //while (cont<10);
}
