/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * xrotg.c
 *
 * Code generation for function 'xrotg'
 *
 */

/* Include files */
#include "xrotg.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */
void xrotg(float *a, float *b, float *c, float *s)
{
  float absa;
  float absb;
  float ads;
  float bds;
  float roe;
  float scale;
  roe = *b;
  absa = fabsf(*a);
  absb = fabsf(*b);
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
    scale *= sqrtf(ads * ads + bds * bds);
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

/* End of code generation (xrotg.c) */
