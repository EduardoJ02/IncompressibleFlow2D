#ifndef DISCRET_H_INCLUDED
#define DISCRET_H_INCLUDED

    double u2_x2(int i, int j, double Dp, double Bp, double Ep);

    double u2_y2(int i, int j, double Ap, double Bp, double Cp);

    double u2(int i, int j, double Bp, double Dp, double Ep);

    double uv_y(int i, int j, double bp, double dp, double Bp, double Ap, double cp, double qp, double Cp);



    double v2_x2(int i, int j, double dp, double bp, double ep);

    double v2_y2(int i, int j, double ap, double bp, double cp);

    double v2(int i, int j, double bp, double ap, double cp);

    double uv_x(int i, int j, double Bp, double Ap, double bp, double dp, double Ep, double Qp, double ep);

#endif
