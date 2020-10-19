/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * xdotc.c
 *
 * Code generation for function 'xdotc'
 *
 */

/* Include files */
#include "xdotc.h"
#include "rt_nonfinite.h"

/* Function Definitions */
float xdotc(int n, const float x[16], int ix0, const float y[16], int iy0)
{
  float d;
  int ix;
  int iy;
  int k;
  ix = ix0;
  iy = iy0;
  d = 0.0F;
  for (k = 0; k < n; k++) {
    d += x[ix - 1] * y[iy - 1];
    ix++;
    iy++;
  }

  return d;
}

/* End of code generation (xdotc.c) */
