/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * xaxpy.h
 *
 * Code generation for function 'xaxpy'
 *
 */

#ifndef XAXPY_H
#define XAXPY_H

/* Include files */
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>
#ifdef __cplusplus

extern "C" {

#endif

  /* Function Declarations */
  void b_xaxpy(int n, float a, const float x[16], int ix0, float y[4], int iy0);
  void c_xaxpy(int n, float a, const float x[4], int ix0, float y[16], int iy0);
  void xaxpy(int n, float a, int ix0, float y[16], int iy0);

#ifdef __cplusplus

}
#endif
#endif

/* End of code generation (xaxpy.h) */
