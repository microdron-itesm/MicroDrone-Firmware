/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: MatlabLib_terminate.c
 *
 * MATLAB Coder version            : 5.1
 * C/C++ source code generated on  : 19-Nov-2020 17:37:02
 */

/* Include Files */
#include "MatlabLib_terminate.h"
#include "MatlabLib_data.h"
#include "rt_nonfinite.h"

/* Function Definitions */
/*
 * Arguments    : void
 * Return Type  : void
 */
void MatlabLib_terminate(void)
{
  /* (no terminate code required) */
  isInitialized_MatlabLib = false;
}

/*
 * File trailer for MatlabLib_terminate.c
 *
 * [EOF]
 */
