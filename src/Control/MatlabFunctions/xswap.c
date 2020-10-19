/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * xswap.c
 *
 * Code generation for function 'xswap'
 *
 */

/* Include files */
#include "xswap.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void xswap(float x[16], int ix0, int iy0)
{
  float temp;
  temp = x[ix0 - 1];
  x[ix0 - 1] = x[iy0 - 1];
  x[iy0 - 1] = temp;
  temp = x[ix0];
  x[ix0] = x[iy0];
  x[iy0] = temp;
  temp = x[ix0 + 1];
  x[ix0 + 1] = x[iy0 + 1];
  x[iy0 + 1] = temp;
  temp = x[ix0 + 2];
  x[ix0 + 2] = x[iy0 + 2];
  x[iy0 + 2] = temp;
}

/* End of code generation (xswap.c) */
