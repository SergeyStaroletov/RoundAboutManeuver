#ifndef MODEL_H
#define MODEL_H

#include <stdio.h>
#include <stdlib.h>

double X1(double t, double om, double C1, double C3, double C4);
double X2(double t, double om, double C2, double C3, double C4);

double D1(double t, double om, double C3, double C4);

double D2(double t, double om, double C3, double C4);

double Y1(double t, double e1, double C5);
double Y2(double t, double e2, double C6);

double E1(double t, double omy, double C7, double C8);

double E2(double t, double omy, double C7, double C8);

bool check_safety(double x1, double x2, double y1, double y2,
                  double protectedzone);

#endif  // MODEL_H
