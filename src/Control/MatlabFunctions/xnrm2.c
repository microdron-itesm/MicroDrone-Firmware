/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * xnrm2.c
 *
 * Code generation for function 'xnrm2'
 *
 */

/* Include files */
#include "xnrm2.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */
float b_xnrm2(int n, const float x[4], int ix0)
{
  float absxk;
  float scale;
  float t;
  float y;
  int k;
  int kend;
  y = 0.0F;
  scale = 1.29246971E-26F;
  kend = (ix0 + n) - 1;
  for (k = ix0; k <= kend; k++) {
    absxk = fabsf(x[k - 1]);
    if (absxk > scale) {
      t = scale / absxk;
      y = y * t * t + 1.0F;
      scale = absxk;
    } else {
      t = absxk / scale;
      y += t * t;
    }
  }

  return scale * sqrtf(y);
}

float xnrm2(int n, const float x[16], int ix0)
{
  float absxk;
  float scale;
  float t;
  float y;
  int k;
  int kend;
  y = 0.0F;
  scale = 1.29246971E-26F;
  kend = (ix0 + n) - 1;
  for (k = ix0; k <= kend; k++) {
    absxk = fabsf(x[k - 1]);
    if (absxk > scale) {
      t = scale / absxk;
      y = y * t * t + 1.0F;
      scale = absxk;
    } else {
      t = absxk / scale;
      y += t * t;
    }
  }

  return scale * sqrtf(y);
}

/* End of code generation (xnrm2.c) */
