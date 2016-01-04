#include <stdlib.h>
#include "computaG.h"
#include "Discret.h"

/**
Stencil for G in a staggered grid
Estêncil para G em uma malha deslocada

       |       |       |       |
       |       |       |       |       j+1
       |       |       |       |
-------|-------|---v---|-------|-------
       |       |       |       |
       |       u       u       |        j
       |       |       |       |
-------|---v---|---v*--|---v---|-------
       |       |       |       |
       |       u       u*      |       j-1
       |       |       |       |
-------|-------|---v---|-------|-------
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


double G(int i, int j, double **u, double **v){
    double Gf;

    Gf = v[i][j] + dt*( (iRe)*((v2_x2(i,j, a, b, c) + v2_y2(i,j, d, b, e)))
                   - uv_x(i,j, B, D, b, a, C, Q, c) - v2(i,j, b, d, e)  );
    return Gf;
}

double Gc(int i, int j, double **u, double **v){
    double Gf, Bp, Cp, Dp, Qp, ap, bp, cp, dp, ep;

    Bp=B;
    bp=b;

    //printf("\ni=%d j=%d k=%d\n", i,j,k);

    if(Esquerdas){/**i-1**/
        //i-1
            //c=-b
            //Q=-u(i+1,j+1)
            //C=-u(i+1,j)

        cp=-b;
        Cp=-u[i+1][j];

    }
    else{
        cp=c;
        Cp=C;
    }


    if (Direitas){/**i+1**/
        //Direita
            //i+1
            //a=-b;
        ap=-b;
    }else{
        ap=a;
    }

    if (Superiores){/**j+1**/
        //Superior
            //j+1
            //d=-e;
            //Q=-C;
            //D=-B;
            //tenho d=v(i,j+1);
            dp=d;
            Dp=-B;
    }else{
        dp=d;
        Dp=D;
    }

    if (Inferiores){/**j-1**/
        //j-1
            //e=-d;
            ep=-d;
    }else{
        ep=e;
    }


    /**j+1**/ /**i-1**/
    if ((Esquerdas) && (Superiores)){
        Qp=u[i+1][j];
    }else if ( ((Esquerdas) && (Inferiores)) || (Esquerdas)){
        Qp=-u[i+1][j+1];
    }else if ( ((Superiores)&& (Esquerdas)) || (Superiores)){
        Qp=-C;
    }
    else{
        Qp=Q;
    }

    if(flag[i][j]==99){
        Gf=0;
        return Gf;
    }


    Gf = v[i][j] + dt*( (iRe)*((v2_x2(i,j, ap, bp, cp) + v2_y2(i,j, dp, bp, ep)))
                     - uv_x(i,j, Bp, Dp, bp, ap, Cp, Qp, cp) - v2(i,j, bp, dp, ep)  );
    return Gf;
}
