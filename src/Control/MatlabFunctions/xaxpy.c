/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * xaxpy.c
 *
 * Code generation for function 'xaxpy'
 *
 */

/* Include files */
#include "xaxpy.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void b_xaxpy(int n, float a, const float x[16], int ix0, float y[4], int iy0)
{
  int i;
  int ix;
  int iy;
  int k;
  if (!(a == 0.0F)) {
    ix = ix0 - 1;
    iy = iy0 - 1;
    i = n - 1;
    for (k = 0; k <= i; k++) {
      y[iy] += a * x[ix];
      ix++;
      iy++;
    }
  }
}

void c_xaxpy(int n, float a, const float x[4], int ix0, float y[16], int iy0)
{
  int i;
  int ix;
  int iy;
  int k;
  if (!(a == 0.0F)) {
    ix = ix0 - 1;
    iy = iy0 - 1;
    i = n - 1;
    for (k = 0; k <= i; k++) {
      y[iy] += a * x[ix];
      ix++;
      iy++;
    }
  }
}

void xaxpy(int n, float a, int ix0, float y[16], int iy0)
{
  int i;
  int ix;
  int iy;
  int k;
  if (!(a == 0.0F)) {
    ix = ix0 - 1;
    iy = iy0 - 1;
    i = n - 1;
    for (k = 0; k <= i; k++) {
      y[iy] += a * y[ix];
      ix++;
      iy++;
    }
  }
}

/* End of code generation (xaxpy.c) */
