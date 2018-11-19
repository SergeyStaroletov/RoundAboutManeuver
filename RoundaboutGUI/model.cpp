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
double X1(double t, double om, double d1_0, double d2_0, double x1_0) {
  return d1_0 * sin(om * t) / om + d2_0 * cos(om * t) / om + x1_0 * om -
         d2_0 / om;
}

double X2(double t, double om, double d1_0, double d2_0, double x2_0) {
  return d2_0 * sin(om * t) / om - d1_0 * cos(om * t) / om + x2_0 * om +
         d1_0 / om;
}

double D1(double t, double om, double d1_0, double d2_0) {
  return d1_0 * cos(om * t) - d2_0 * sin(om * t);
}

double D2(double t, double om, double d1_0, double d2_0) {
  return d1_0 * sin(om * t) + d2_0 * cos(om * t);
}

double Y1(double t, double omy, double e1_0, double e2_0, double y1_0) {
  return e1_0 * sin(omy * t) / omy + e2_0 * cos(omy * t) / omy + y1_0 * omy -
         e2_0 / omy;
}

double Y2(double t, double omy, double e1_0, double e2_0, double y2_0) {
  return e2_0 * sin(omy * t) / omy - e1_0 * cos(omy * t) / omy + y2_0 * omy +
         e1_0 / omy;
}

double E1(double t, double omy, double e1_0, double e2_0) {
  return e1_0 * cos(omy * t) - e2_0 * sin(omy * t);
}

double E2(double t, double omy, double e1_0, double e2_0) {
  return e1_0 * sin(omy * t) + e2_0 * cos(omy * t);
}

bool check_safety(double x1, double x2, double y1, double y2,
                  double protectedzone) {
  return ((x1 - y1) * (x1 - y1) + (x2 - y2) * (x2 - y2) >=
          protectedzone * protectedzone);
}
