/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: xrotg.c
 *
 * MATLAB Coder version            : 5.1
 * C/C++ source code generated on  : 19-Nov-2020 19:15:25
 */

/* Include Files */
#include "xrotg.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */
/*
 * Arguments    : float *a
 *                float *b
 *                float *c
 *                float *s
 * Return Type  : void
 */
void xrotg(float *a, float *b, float *c, float *s)
{
  float absa;
  float absb;
  float ads;
  float bds;
  float roe;
  float scale;
  roe = *b;
  absa = (float)fabs(*a);
  absb = (float)fabs(*b);
  if (absa > absb) {
    roe = *a;
  }

  scale = absa + absb;
  if (scale == 0.0F) {
    *s = 0.0F;
    *c = 1.0F;
    *a = 0.0F;
    *b = 0.0F;
  } else {
    ads = absa / scale;
    bds = absb / scale;
    scale *= (float)sqrt(ads * ads + bds * bds);
    if (roe < 0.0F) {
      scale = -scale;
    }

    *c = *a / scale;
    *s = *b / scale;
    if (absa > absb) {
      *b = *s;
    } else if (*c != 0.0F) {
      *b = 1.0F / *c;
    } else {
      *b = 1.0F;
    }

    *a = scale;
  }
}

/*
 * File trailer for xrotg.c
 *
 * [EOF]
 */
