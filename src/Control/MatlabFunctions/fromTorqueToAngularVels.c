/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: fromTorqueToAngularVels.c
 *
 * MATLAB Coder version            : 5.1
 * C/C++ source code generated on  : 19-Nov-2020 19:15:25
 */

/* Include Files */
#include "fromTorqueToAngularVels.h"
#include "MatlabLib_data.h"
#include "MatlabLib_initialize.h"
#include "rt_nonfinite.h"
#include "svd.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : const float torques[4]
 *                float armLength
 *                float kT
 *                float kQ
 *                float angularVels[4]
 * Return Type  : void
 */
void fromTorqueToAngularVels(const float torques[4], float armLength, float kT,
  float kQ, float angularVels[4])
{
  float C[16];
  float U[16];
  float V[16];
  float forwardKinematics[16];
  float s[4];
  float f;
  float f1;
  float f2;
  float f3;
  float torqueConstant;
  int ar;
  int i;
  int ia;
  int j;
  int r;
  int vcol;
  boolean_T p;
  if (!isInitialized_MatlabLib) {
    MatlabLib_initialize();
  }

  torqueConstant = armLength / 1.41421354F * kT;
  forwardKinematics[0] = torqueConstant;
  forwardKinematics[4] = -torqueConstant;
  forwardKinematics[8] = -torqueConstant;
  forwardKinematics[12] = torqueConstant;
  forwardKinematics[1] = torqueConstant;
  forwardKinematics[5] = torqueConstant;
  forwardKinematics[9] = -torqueConstant;
  forwardKinematics[13] = -torqueConstant;
  forwardKinematics[2] = -kQ;
  forwardKinematics[6] = kQ;
  forwardKinematics[10] = -kQ;
  forwardKinematics[14] = kQ;
  forwardKinematics[3] = kT;
  forwardKinematics[7] = kT;
  forwardKinematics[11] = kT;
  forwardKinematics[15] = kT;
  p = true;
  for (ia = 0; ia < 16; ia++) {
    C[ia] = 0.0F;
    if ((!p) || (rtIsInfF(forwardKinematics[ia]) || rtIsNaNF
                 (forwardKinematics[ia]))) {
      p = false;
    }
  }

  if (!p) {
    for (i = 0; i < 16; i++) {
      C[i] = rtNaNF;
    }
  } else {
    svd(forwardKinematics, U, s, V);
    torqueConstant = (float)fabs(s[0]);
    if ((!rtIsInfF(torqueConstant)) && (!rtIsNaNF(torqueConstant))) {
      if (torqueConstant <= 1.17549435E-38F) {
        torqueConstant = 1.4013E-45F;
      } else {
        frexp(torqueConstant, &vcol);
        torqueConstant = (float)ldexp(1.0, vcol - 24);
      }
    } else {
      torqueConstant = rtNaNF;
    }

    torqueConstant *= 4.0F;
    r = -1;
    ia = 0;
    while ((ia < 4) && (s[ia] > torqueConstant)) {
      r++;
      ia++;
    }

    if (r + 1 > 0) {
      vcol = 1;
      for (j = 0; j <= r; j++) {
        torqueConstant = 1.0F / s[j];
        i = vcol + 3;
        for (ia = vcol; ia <= i; ia++) {
          V[ia - 1] *= torqueConstant;
        }

        vcol += 4;
      }

      memset(&C[0], 0, 16U * sizeof(float));
      ar = -1;
      i = r << 2;
      vcol = i + 1;
      for (j = 1; j <= vcol; j += 4) {
        ia = ar;
        for (r = 1; r < 5; r++) {
          ia++;
          C[r - 1] += U[j - 1] * V[ia];
        }

        ar += 4;
      }

      ar = -1;
      vcol = i + 2;
      for (j = 2; j <= vcol; j += 4) {
        ia = ar;
        for (r = 5; r < 9; r++) {
          ia++;
          C[r - 1] += U[j - 1] * V[ia];
        }

        ar += 4;
      }

      ar = -1;
      vcol = i + 3;
      for (j = 3; j <= vcol; j += 4) {
        ia = ar;
        for (r = 9; r < 13; r++) {
          ia++;
          C[r - 1] += U[j - 1] * V[ia];
        }

        ar += 4;
      }

      ar = -1;
      vcol = i + 4;
      for (j = 4; j <= vcol; j += 4) {
        ia = ar;
        for (r = 13; r < 17; r++) {
          ia++;
          C[r - 1] += U[j - 1] * V[ia];
        }

        ar += 4;
      }
    }
  }

  torqueConstant = torques[0];
  f = torques[1];
  f1 = torques[2];
  f2 = torques[3];
  for (ia = 0; ia < 4; ia++) {
    f3 = ((C[ia] * torqueConstant + C[ia + 4] * f) + C[ia + 8] * f1) + C[ia + 12]
      * f2;
    if (f3 < 0.0F) {
      f3 = 0.0F;
    }

    f3 = (float)sqrt(f3);
    angularVels[ia] = f3;
  }
}

/*
 * File trailer for fromTorqueToAngularVels.c
 *
 * [EOF]
 */
