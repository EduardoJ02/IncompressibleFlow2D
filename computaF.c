#include <stdlib.h>
#include "computaF.h"
#include "Discret.h"

/**
Stencil for F in a staggered grid
Estêncil para F em uma malha deslocada

       |       |       |       |
       |       |       u       |       j+1
       |       |       |       |
-------|-------|---v*--|---v---|-------
       |       |       |       |
       |       u       u*      u       j
       |       |       |       |
-------|-------|---v---|---v---|-------
       |       |       |       |
       |       |       u       |       j-1
       |       |       |       |
-------|-------|-------|-------|-------
       |       |       |       |
       |       |       |       |
       |       |       |       |
              i-1      i      i+1

u*=u[i][j]
v*=v[i][j]

This code is set up with the boundary conditions for the Lid-Driven Cavity problem
Este código está configurado com as condições de contorno para o problema do Escoamento em uma Cavidade

Use this scheme to interpolate boundary velocities using the proper points in a staggered grid
Use este esquema para interpolar velocidades no contorno usando os pontos adequados na malha deslocada

**/

//Computes F in the interior points
//Computa F nos pontos interiores
double F(int i, int j, double **u, double **v){
    double Ff;

    Ff = u[i][j] + dt*(  (iRe)*((u2_x2(i,j, A, B, C) + u2_y2(i,j, D, B, E)))
                                       - u2(i,j, B, A, C)  - uv_y(i,j, b, a, B, D, e, q, E)  );
    return Ff;
}

//Computes F in the boundary points
//Computa F nos pontos nos contornos
double Fc(int i, int j, double **u, double **v){
    double Ff, Ap, Bp, Cp, Dp, Ep, ap, bp, ep, qp;

    Bp=B;
    bp=b;

    if(Esquerdas){/**i-1**/
        //Esquerda
        //i-1 dá problema
        //C=-A
        Cp=-A;
        //Ff=3;
    }else{
        Cp=C;
    }

    if (Direitas){/**i+1**/
            //Direita
            //i+1 dá problema
            //A=-C
            //a=-b;
            //q=-e;

            //tenho A=u(i+1,j);

        Ap=A;
        ap=-b;
        //qp=-e;
        //Ff=5;
    }else{
        Ap=A;
        ap=a;
        //qp=q;
    }


    if (Superiores){/**j+1**/
        //Superior
        //j+1
        //D=2*U_s-B
        if (flag[i][j]==Superior+Esquerda){
                Dp=-B;
        } else{
                Dp=2*U_s-B;
        }
        //Ff=2;
    }else{
        Dp=D;
    }

    if (Inferiores){/**j-1**/
            //Inferior
            //j-1 dá problema
            //E=-B
            //e=-v(i,j+1);
            //q=-v(i+1,j+1);

        Ep=-B;
        ep=-v[i][j+1];
        //qp=-v3D[i+1][j][k];
        //Ff=1;
    }else{
        Ep=E;
        ep=e;
        //qp=q;
    }


    /**j-1**/ /**i+1**/
    if ((Direitas) && (Inferiores)){
        qp=v[i][j+1];
    }else if ( ((Esquerdas) && (Inferiores)) || (Inferiores) ){
        qp=-v[i+1][j+1];
    }else if ( ((Superiores)&& (Direitas)) || (Direitas)){
        qp=-e;
    }
    else{
        qp=q;
    }

    if(flag[i][j]==99){
        Ff=0;
        return Ff;
    }

    Ff = u[i][j] + dt*(  (iRe)*((u2_x2(i,j, Ap, Bp, Cp) + u2_y2(i,j, Dp, Bp, Ep)))
                                       - u2(i,j, Bp, Ap, Cp)  - uv_y(i,j, bp, ap, Bp, Dp, ep, qp, Ep)  );

    return Ff;
}
