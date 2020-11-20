/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: fromTorqueToAngularVels.h
 *
 * MATLAB Coder version            : 5.1
 * C/C++ source code generated on  : 19-Nov-2020 19:15:25
 */

#ifndef FROMTORQUETOANGULARVELS_H
#define FROMTORQUETOANGULARVELS_H

/* Include Files */
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>
#ifdef __cplusplus

extern "C" {

#endif

  /* Function Declarations */
  extern void fromTorqueToAngularVels(const float torques[4], float armLength,
    float kT, float kQ, float angularVels[4]);

#ifdef __cplusplus

}
#endif
#endif

/*
 * File trailer for fromTorqueToAngularVels.h
 *
 * [EOF]
 */
