/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * fromTorqueToAngularVels.h
 *
 * Code generation for function 'fromTorqueToAngularVels'
 *
 */

#ifndef FROMTORQUETOANGULARVELS_H
#define FROMTORQUETOANGULARVELS_H

/* Include files */
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

/* End of code generation (fromTorqueToAngularVels.h) */
