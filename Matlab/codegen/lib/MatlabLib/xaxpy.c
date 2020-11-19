/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: xaxpy.c
 *
 * MATLAB Coder version            : 5.1
 * C/C++ source code generated on  : 19-Nov-2020 17:37:02
 */

/* Include Files */
#include "xaxpy.h"
#include "rt_nonfinite.h"

/* Function Definitions */
/*
 * Arguments    : int n
 *                float a
 *                const float x[16]
 *                int ix0
 *                float y[4]
 *                int iy0
 * Return Type  : void
 */
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

/*
 * Arguments    : int n
 *                float a
 *                const float x[4]
 *                int ix0
 *                float y[16]
 *                int iy0
 * Return Type  : void
 */
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

/*
 * Arguments    : int n
 *                float a
 *                int ix0
 *                float y[16]
 *                int iy0
 * Return Type  : void
 */
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

/*
 * File trailer for xaxpy.c
 *
 * [EOF]
 */
