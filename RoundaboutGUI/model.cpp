#include "model.h"

#include <math.h>

/* The solution for
              (x1') = (d1),
              (x2') = (d2),
              (d1') = ((-(om)) * (d2)),
              (d2') = ((om) * (d1)),
              (y1') = (e1),
              (y2') = (e2),
              (e1') = ((-(omy)) * (e2)),
              (e2') = ((omy) * (e1)),
              ((((x1) - (y1)) ^ (2)) + (((x2) - (y2)) ^ (2))) >=
   ((protectedzone) ^ (2))

*/
double X1(double t, double om, double C1, double C3, double C4) {
  return C1 + C4 * (cos(om * t) - 1) / om + C3 * sin(om * t) / om;
}
double X2(double t, double om, double C2, double C3, double C4) {
  return C2 + C3 * (1 - cos(om * t)) / om + C4 * sin(om * t) / om;
}
double D1(double t, double om, double C3, double C4) {
  return C3 * cos(om * t) - C4 * sin(om * t);
}
double D2(double t, double om, double C3, double C4) {
  return C4 * cos(om * t) + C3 * sin(om * t);
}

double Y1(double t, double e1, double C5) { return e1 * t + C5; }
double Y2(double t, double e2, double C6) { return e2 * t + C6; }

double E1(double t, double omy, double C7, double C8) {
  return C7 * cos(omy * t) - C8 * sin(omy * t);
}

double E2(double t, double omy, double C7, double C8) {
  return C8 * cos(omy * t) + C7 * sin(omy * t);
}

bool check_safety(double x1, double x2, double y1, double y2,
                  double protectedzone) {
  return ((x1 - y1) * (x1 - y1) + (x2 - y2) * (x2 - y2) >=
          protectedzone * protectedzone);
}
