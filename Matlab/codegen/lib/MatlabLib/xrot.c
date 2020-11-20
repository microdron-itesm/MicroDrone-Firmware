/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: xrot.c
 *
 * MATLAB Coder version            : 5.1
 * C/C++ source code generated on  : 19-Nov-2020 19:15:25
 */

/* Include Files */
#include "xrot.h"
#include "rt_nonfinite.h"

/* Function Definitions */
/*
 * Arguments    : float x[16]
 *                int ix0
 *                int iy0
 *                float c
 *                float s
 * Return Type  : void
 */
void xrot(float x[16], int ix0, int iy0, float c, float s)
{
  float temp;
  float temp_tmp;
  temp = x[iy0 - 1];
  temp_tmp = x[ix0 - 1];
  x[iy0 - 1] = c * temp - s * temp_tmp;
  x[ix0 - 1] = c * temp_tmp + s * temp;
  temp = c * x[ix0] + s * x[iy0];
  x[iy0] = c * x[iy0] - s * x[ix0];
  x[ix0] = temp;
  temp = x[iy0 + 1];
  temp_tmp = x[ix0 + 1];
  x[iy0 + 1] = c * temp - s * temp_tmp;
  x[ix0 + 1] = c * temp_tmp + s * temp;
  temp = x[iy0 + 2];
  temp_tmp = x[ix0 + 2];
  x[iy0 + 2] = c * temp - s * temp_tmp;
  x[ix0 + 2] = c * temp_tmp + s * temp;
}

/*
 * File trailer for xrot.c
 *
 * [EOF]
 */
