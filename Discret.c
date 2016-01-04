#include <stdlib.h>
#include "Discret.h"

extern double dx, dy, idx2, idx, idy2, idy, gama;

//Discretizations for F
/**Discretizações para F**/
    double u2_x2(int i, int j, double Ap, double Bp, double Cp){
        double res;

        res=(Ap - 2.0*Bp + Cp)*idx2;

        return res;
    }

    double u2_y2(int i, int j, double Dp, double Bp, double Ep){
        double res;

        res=(Dp-2.0*Bp+Ep)*idy2;

        return res;
    }

    double u2(int i, int j, double Bp, double Ap, double Cp){
        double res;

        res=((((Bp + Ap))/2)*(((Bp + Ap))/2) - (((Bp + Cp))/2)*(((Bp+ Cp))/2))*idx    +
          gama*idx*0.25*( fabs(Bp+Ap)*(Bp-Ap)  - fabs(Cp+Bp)*(Cp-Bp));

        return res;
    }

    double uv_y(int i, int j, double bp, double ap, double Bp, double Dp, double ep, double qp, double Ep){
        double res;

        res=((bp + ap)*(Bp + Dp) +  gama*fabs(bp + ap)*(Bp - Dp)-
            (ep + qp)*(Ep + Bp) - gama*fabs(ep + qp)*(Ep - Bp))
            *(0.25*idy);

        return res;
    }

//Discretizations for G
/**Discretizações para G**/
    double v2_x2(int i, int j, double ap, double bp, double cp){
        double res;

        res=(ap-2*bp+cp)*idx2;

        return res;
    }

    double v2_y2(int i, int j, double dp, double bp, double ep){
        double res;

        res=(dp-2*bp+ep)*idy2;

        return res;
    }

    double v2(int i, int j, double bp, double dp, double ep){
        double res;

        res=((((bp+ dp))/2)*(((bp+ dp))/2) - (((ep + bp))/2)*(((ep + bp))/2))*idy
        + gama*0.25*idy*(fabs(bp+dp)*(bp-dp)  -  fabs(ep+bp)*(ep-bp));

        return res;
    }

    double uv_x(int i, int j, double Bp, double Dp, double bp, double ap, double Cp, double Qp, double cp){
        double res;

         res = ((Bp + Dp)*(bp + ap)+
                    gama*fabs(Bp + Dp)*(bp - ap)-
                    (Cp + Qp)*(cp + bp)-
		    gama*fabs(Cp + Qp)*(cp - bp))
                    *(0.25*idx);

        return res;
    }

