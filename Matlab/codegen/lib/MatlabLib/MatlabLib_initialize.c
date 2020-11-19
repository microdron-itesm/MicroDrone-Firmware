/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: MatlabLib_initialize.c
 *
 * MATLAB Coder version            : 5.1
 * C/C++ source code generated on  : 19-Nov-2020 17:37:02
 */

/* Include Files */
#include "MatlabLib_initialize.h"
#include "MatlabLib_data.h"
#include "rt_nonfinite.h"

/* Function Definitions */
/*
 * Arguments    : void
 * Return Type  : void
 */
void MatlabLib_initialize(void)
{
  rt_InitInfAndNaN();
  isInitialized_MatlabLib = true;
}

/*
 * File trailer for MatlabLib_initialize.c
 *
 * [EOF]
 */
