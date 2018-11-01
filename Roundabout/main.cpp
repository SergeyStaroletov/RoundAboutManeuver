#include <math.h>
#include <stdio.h>
#include <stdlib.h>

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

int main(int argc, char *argv[]) {
  double t = 0;

  double dt = 0.01;

  double c1 = -1.5, c2 = -0.2, c3 = -10.1, c4 = 0.1, c5 = 1.5, c6 = 0.1,
         c7 = 0.1, c8 = 8;
  double om = 1, omy = 1;

  double x1 = c1, x2 = c2, y1 = c5, y2 = c6, d1 = 0.5, d2 = +0.0105, e1 = 0,
         e2 = 0;

  double x1_old, x2_old, y1_old, y2_old, d1_old, d2_old, e1_old, e2_old;

  double protectedzone = 0.1;

  while (t <= 1) {
    x1_old = x1;
    x2_old = x2;
    y1_old = y1;
    y2_old = y2;
    d1_old = d1;
    d2_old = d2;
    e1_old = e1;
    e2_old = e2;

    x1 = X1(t, om, c1, c3, c4);
    x2 = X2(t, om, c2, c3, c4);
    y1 = Y1(t, e1_old, c5);
    y2 = Y2(t, e2_old, c6);
    d1 = D1(t, om, c3, c4);
    d2 = D2(t, om, c3, c4);
    e1 = E1(t, omy, c7, c8);
    e2 = E2(t, omy, c7, c8);

    printf("time = %f x1=%f y1=%f x2=%f y2=%f\n", t, x1, y1, x2, y2);

    if (!check_safety(x1, x2, y1, y2, protectedzone)) {
      printf("violation of enter safety! \n");
    }

    t += dt;
  }

  if (check_safety(x1, x2, y1, y2, protectedzone)) {
    double cc1 = 0.1;
    double cc2 = 0.2;

    // fix some positions
    d1 = ((-(om)) * ((x2) - (cc2)));
    d2 = ((om) * ((x1) - (cc1)));
    e1 = ((-(om)) * ((y2) - (cc2)));
    e2 = ((om) * ((y1) - (cc1)));

    printf("fix! \n");

    // go to maneur
    while (t <= 2) {
      x1_old = x1;
      x2_old = x2;
      y1_old = y1;
      y2_old = y2;
      d1_old = d1;
      d2_old = d2;
      e1_old = e1;
      e2_old = e2;

      x1 = X1(t, om, c1, c3, c4);
      x2 = X2(t, om, c2, c3, c4);
      y1 = Y1(t, e1_old, c5);
      y2 = Y2(t, e2_old, c6);
      d1 = D1(t, om, c3, c4);
      d2 = D2(t, om, c3, c4);
      e1 = E1(t, omy, c7, c8);
      e2 = E2(t, omy, c7, c8);

      printf("2time = %f x1=%f y1=%f x2=%f y2=%f\n", t, x1, y1, x2, y2);

      if (!check_safety(x1, x2, y1, y2, protectedzone)) {
        printf("violation of enter safety\n");
      }

      t += dt;
    }
  }

  return 0;
}
