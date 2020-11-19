/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: ProcessIMU.c
 *
 * MATLAB Coder version            : 5.1
 * C/C++ source code generated on  : 19-Nov-2020 17:37:02
 */

/* Include Files */
#include "ProcessIMU.h"
#include "MatlabLib_data.h"
#include "MatlabLib_initialize.h"
#include "rt_nonfinite.h"

/* Function Definitions */
/*
 * Arguments    : const float data[4]
 *                const float zero[4]
 *                float out[4]
 * Return Type  : void
 */
void ProcessIMU(const float data[4], const float zero[4], float out[4])
{
  float fcnOutput_idx_0;
  float fcnOutput_idx_1;
  float fcnOutput_idx_2;
  float qnrm;
  if (!isInitialized_MatlabLib) {
    MatlabLib_initialize();
  }

  qnrm = ((zero[0] * zero[0] + zero[1] * zero[1]) + zero[2] * zero[2]) + zero[3]
    * zero[3];
  fcnOutput_idx_0 = zero[0] / qnrm;
  fcnOutput_idx_1 = -zero[1] / qnrm;
  fcnOutput_idx_2 = -zero[2] / qnrm;
  qnrm = -zero[3] / qnrm;
  out[0] = ((data[0] * fcnOutput_idx_0 - data[1] * fcnOutput_idx_1) - data[2] *
            fcnOutput_idx_2) - data[3] * qnrm;
  out[1] = (data[0] * fcnOutput_idx_1 + fcnOutput_idx_0 * data[1]) + (data[2] *
    qnrm - data[3] * fcnOutput_idx_2);
  out[2] = (data[0] * fcnOutput_idx_2 + fcnOutput_idx_0 * data[2]) + (data[3] *
    fcnOutput_idx_1 - data[1] * qnrm);
  out[3] = (data[0] * qnrm + fcnOutput_idx_0 * data[3]) + (data[1] *
    fcnOutput_idx_2 - data[2] * fcnOutput_idx_1);
}

/*
 * File trailer for ProcessIMU.c
 *
 * [EOF]
 */
