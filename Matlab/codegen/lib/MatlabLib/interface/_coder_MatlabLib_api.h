/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_MatlabLib_api.h
 *
 * MATLAB Coder version            : 5.1
 * C/C++ source code generated on  : 19-Nov-2020 17:37:02
 */

#ifndef _CODER_MATLABLIB_API_H
#define _CODER_MATLABLIB_API_H

/* Include Files */
#include "emlrt.h"
#include "tmwtypes.h"
#include <string.h>

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

#ifdef __cplusplus

extern "C" {

#endif

  /* Function Declarations */
  void MatlabLib_atexit(void);
  void MatlabLib_initialize(void);
  void MatlabLib_terminate(void);
  void MatlabLib_xil_shutdown(void);
  void MatlabLib_xil_terminate(void);
  void ProcessIMU(real32_T data[4], real32_T zero[4], real32_T out[4]);
  void ProcessIMU_api(const mxArray * const prhs[2], const mxArray *plhs[1]);
  void fromTorqueToAngularVels(real32_T torques[4], real32_T armLength, real32_T
    kT, real32_T kQ, real32_T angularVels[4]);
  void fromTorqueToAngularVels_api(const mxArray * const prhs[4], const mxArray *
    plhs[1]);

#ifdef __cplusplus

}
#endif
#endif

/*
 * File trailer for _coder_MatlabLib_api.h
 *
 * [EOF]
 */
