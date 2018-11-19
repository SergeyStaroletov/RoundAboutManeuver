#ifndef MODEL_H
#define MODEL_H

#include <stdio.h>
#include <stdlib.h>

double X1(double t, double om, double d1_0, double d2_0, double x1_0);

double X2(double t, double om, double d1_0, double d2_0, double x2_0);

double D1(double t, double om, double d1_0, double d2_0);

double D2(double t, double om, double d1_0, double d2_0);

double Y1(double t, double omy, double e1_0, double e2_0, double y1_0);

double Y2(double t, double omy, double e1_0, double e2_0, double y2_0);

double E1(double t, double omy, double e1_0, double e2_0);

double E2(double t, double omy, double e1_0, double e2_0);

bool check_safety(double x1, double x2, double y1, double y2,
                  double protectedzone);

#endif  // MODEL_H
