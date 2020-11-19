/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: svd.c
 *
 * MATLAB Coder version            : 5.1
 * C/C++ source code generated on  : 19-Nov-2020 17:37:02
 */

/* Include Files */
#include "svd.h"
#include "rt_nonfinite.h"
#include "xaxpy.h"
#include "xdotc.h"
#include "xnrm2.h"
#include "xrot.h"
#include "xrotg.h"
#include "xswap.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */
/*
 * Arguments    : const float A[16]
 *                float U[16]
 *                float s[4]
 *                float V[16]
 * Return Type  : void
 */
void svd(const float A[16], float U[16], float s[4], float V[16])
{
  float Vf[16];
  float b_A[16];
  float b_s[4];
  float e[4];
  float work[4];
  float b;
  float nrm;
  float r;
  float scale;
  float sm;
  float snorm;
  float sqds;
  int exitg1;
  int iter;
  int k;
  int m;
  int q;
  int qjj;
  int qp1;
  int qp1jj;
  int qq;
  boolean_T apply_transform;
  boolean_T exitg2;
  b_s[0] = 0.0F;
  e[0] = 0.0F;
  work[0] = 0.0F;
  b_s[1] = 0.0F;
  e[1] = 0.0F;
  work[1] = 0.0F;
  b_s[2] = 0.0F;
  e[2] = 0.0F;
  work[2] = 0.0F;
  b_s[3] = 0.0F;
  e[3] = 0.0F;
  work[3] = 0.0F;
  for (qp1jj = 0; qp1jj < 16; qp1jj++) {
    b_A[qp1jj] = A[qp1jj];
    U[qp1jj] = 0.0F;
    Vf[qp1jj] = 0.0F;
  }

  for (q = 0; q < 3; q++) {
    qp1 = q + 2;
    iter = q << 2;
    qq = (q + iter) + 1;
    apply_transform = false;
    nrm = xnrm2(4 - q, b_A, qq);
    if (nrm > 0.0F) {
      apply_transform = true;
      if (b_A[qq - 1] < 0.0F) {
        r = -nrm;
        b_s[q] = -nrm;
      } else {
        r = nrm;
        b_s[q] = nrm;
      }

      if ((float)fabs(r) >= 9.86076132E-32F) {
        nrm = 1.0F / r;
        qp1jj = (qq - q) + 3;
        for (k = qq; k <= qp1jj; k++) {
          b_A[k - 1] *= nrm;
        }
      } else {
        qp1jj = (qq - q) + 3;
        for (k = qq; k <= qp1jj; k++) {
          b_A[k - 1] /= b_s[q];
        }
      }

      b_A[qq - 1]++;
      b_s[q] = -b_s[q];
    } else {
      b_s[q] = 0.0F;
    }

    for (k = qp1; k < 5; k++) {
      qjj = q + ((k - 1) << 2);
      if (apply_transform) {
        xaxpy(4 - q, -(xdotc(4 - q, b_A, qq, b_A, qjj + 1) / b_A[q + (q << 2)]),
              qq, b_A, qjj + 1);
      }

      e[k - 1] = b_A[qjj];
    }

    for (k = q + 1; k < 5; k++) {
      qp1jj = (k + iter) - 1;
      U[qp1jj] = b_A[qp1jj];
    }

    if (q + 1 <= 2) {
      nrm = b_xnrm2(3 - q, e, q + 2);
      if (nrm == 0.0F) {
        e[q] = 0.0F;
      } else {
        if (e[q + 1] < 0.0F) {
          e[q] = -nrm;
        } else {
          e[q] = nrm;
        }

        nrm = e[q];
        if ((float)fabs(e[q]) >= 9.86076132E-32F) {
          nrm = 1.0F / e[q];
          for (k = qp1; k < 5; k++) {
            e[k - 1] *= nrm;
          }
        } else {
          for (k = qp1; k < 5; k++) {
            e[k - 1] /= nrm;
          }
        }

        e[q + 1]++;
        e[q] = -e[q];
        for (k = qp1; k < 5; k++) {
          work[k - 1] = 0.0F;
        }

        for (k = qp1; k < 5; k++) {
          b_xaxpy(3 - q, e[k - 1], b_A, (q + ((k - 1) << 2)) + 2, work, q + 2);
        }

        for (k = qp1; k < 5; k++) {
          c_xaxpy(3 - q, -e[k - 1] / e[q + 1], work, q + 2, b_A, (q + ((k - 1) <<
                    2)) + 2);
        }
      }

      for (k = qp1; k < 5; k++) {
        Vf[(k + iter) - 1] = e[k - 1];
      }
    }
  }

  m = 2;
  b_s[3] = b_A[15];
  e[2] = b_A[14];
  e[3] = 0.0F;
  U[12] = 0.0F;
  U[13] = 0.0F;
  U[14] = 0.0F;
  U[15] = 1.0F;
  for (q = 2; q >= 0; q--) {
    qp1 = q + 2;
    iter = q << 2;
    qq = q + iter;
    if (b_s[q] != 0.0F) {
      for (k = qp1; k < 5; k++) {
        qjj = (q + ((k - 1) << 2)) + 1;
        xaxpy(4 - q, -(xdotc(4 - q, U, qq + 1, U, qjj) / U[qq]), qq + 1, U, qjj);
      }

      for (k = q + 1; k < 5; k++) {
        qp1jj = (k + iter) - 1;
        U[qp1jj] = -U[qp1jj];
      }

      U[qq]++;
      for (k = 0; k < q; k++) {
        U[k + iter] = 0.0F;
      }
    } else {
      U[iter] = 0.0F;
      U[iter + 1] = 0.0F;
      U[iter + 2] = 0.0F;
      U[iter + 3] = 0.0F;
      U[qq] = 1.0F;
    }
  }

  for (q = 3; q >= 0; q--) {
    if ((q + 1 <= 2) && (e[q] != 0.0F)) {
      qp1 = q + 2;
      qjj = (q + (q << 2)) + 2;
      for (k = qp1; k < 5; k++) {
        qp1jj = (q + ((k - 1) << 2)) + 2;
        xaxpy(3 - q, -(xdotc(3 - q, Vf, qjj, Vf, qp1jj) / Vf[qjj - 1]), qjj, Vf,
              qp1jj);
      }
    }

    qjj = q << 2;
    Vf[qjj] = 0.0F;
    Vf[qjj + 1] = 0.0F;
    Vf[qjj + 2] = 0.0F;
    Vf[qjj + 3] = 0.0F;
    Vf[q + (q << 2)] = 1.0F;
  }

  iter = 0;
  snorm = 0.0F;
  if (b_s[0] != 0.0F) {
    nrm = (float)fabs(b_s[0]);
    r = b_s[0] / nrm;
    b_s[0] = nrm;
    e[0] /= r;
    for (k = 1; k < 5; k++) {
      U[k - 1] *= r;
    }
  }

  if (e[0] != 0.0F) {
    nrm = (float)fabs(e[0]);
    r = nrm / e[0];
    e[0] = nrm;
    b_s[1] *= r;
    for (k = 5; k < 9; k++) {
      Vf[k - 1] *= r;
    }
  }

  if ((b_s[0] > e[0]) || rtIsNaNF(e[0])) {
    nrm = b_s[0];
  } else {
    nrm = e[0];
  }

  if (!rtIsNaNF(nrm)) {
    snorm = nrm;
  }

  if (b_s[1] != 0.0F) {
    nrm = (float)fabs(b_s[1]);
    r = b_s[1] / nrm;
    b_s[1] = nrm;
    e[1] /= r;
    for (k = 5; k < 9; k++) {
      U[k - 1] *= r;
    }
  }

  if (e[1] != 0.0F) {
    nrm = (float)fabs(e[1]);
    r = nrm / e[1];
    e[1] = nrm;
    b_s[2] *= r;
    for (k = 9; k < 13; k++) {
      Vf[k - 1] *= r;
    }
  }

  if ((b_s[1] > e[1]) || rtIsNaNF(e[1])) {
    nrm = b_s[1];
  } else {
    nrm = e[1];
  }

  if ((!(snorm > nrm)) && (!rtIsNaNF(nrm))) {
    snorm = nrm;
  }

  if (b_s[2] != 0.0F) {
    nrm = (float)fabs(b_s[2]);
    r = b_s[2] / nrm;
    b_s[2] = nrm;
    e[2] = b_A[14] / r;
    for (k = 9; k < 13; k++) {
      U[k - 1] *= r;
    }
  }

  if (e[2] != 0.0F) {
    nrm = (float)fabs(e[2]);
    r = nrm / e[2];
    e[2] = nrm;
    b_s[3] = b_A[15] * r;
    for (k = 13; k < 17; k++) {
      Vf[k - 1] *= r;
    }
  }

  if ((b_s[2] > e[2]) || rtIsNaNF(e[2])) {
    nrm = b_s[2];
  } else {
    nrm = e[2];
  }

  if ((!(snorm > nrm)) && (!rtIsNaNF(nrm))) {
    snorm = nrm;
  }

  if (b_s[3] != 0.0F) {
    nrm = (float)fabs(b_s[3]);
    r = b_s[3] / nrm;
    b_s[3] = nrm;
    for (k = 13; k < 17; k++) {
      U[k - 1] *= r;
    }
  }

  if (b_s[3] > 0.0F) {
    nrm = b_s[3];
  } else {
    nrm = 0.0F;
  }

  if ((!(snorm > nrm)) && (!rtIsNaNF(nrm))) {
    snorm = nrm;
  }

  while ((m + 2 > 0) && (iter < 75)) {
    k = m;
    do {
      exitg1 = 0;
      q = k + 1;
      if (k + 1 == 0) {
        exitg1 = 1;
      } else {
        nrm = (float)fabs(e[k]);
        if ((nrm <= 1.1920929E-7F * ((float)fabs(b_s[k]) + (float)fabs(b_s[k + 1])))
            || (nrm <= 9.86076132E-32F) || ((iter > 20) && (nrm <= 1.1920929E-7F
              * snorm))) {
          e[k] = 0.0F;
          exitg1 = 1;
        } else {
          k--;
        }
      }
    } while (exitg1 == 0);

    if (k + 1 == m + 1) {
      qjj = 4;
    } else {
      qp1jj = m + 2;
      qjj = m + 2;
      exitg2 = false;
      while ((!exitg2) && (qjj >= k + 1)) {
        qp1jj = qjj;
        if (qjj == k + 1) {
          exitg2 = true;
        } else {
          nrm = 0.0F;
          if (qjj < m + 2) {
            nrm = (float)fabs(e[qjj - 1]);
          }

          if (qjj > k + 2) {
            nrm += (float)fabs(e[qjj - 2]);
          }

          r = (float)fabs(b_s[qjj - 1]);
          if ((r <= 1.1920929E-7F * nrm) || (r <= 9.86076132E-32F)) {
            b_s[qjj - 1] = 0.0F;
            exitg2 = true;
          } else {
            qjj--;
          }
        }
      }

      if (qp1jj == k + 1) {
        qjj = 3;
      } else if (qp1jj == m + 2) {
        qjj = 1;
      } else {
        qjj = 2;
        q = qp1jj;
      }
    }

    switch (qjj) {
     case 1:
      r = e[m];
      e[m] = 0.0F;
      qp1jj = m + 1;
      for (k = qp1jj; k >= q + 1; k--) {
        xrotg(&b_s[k - 1], &r, &sm, &sqds);
        if (k > q + 1) {
          b = e[k - 2];
          r = -sqds * b;
          e[k - 2] = b * sm;
        }

        xrot(Vf, ((k - 1) << 2) + 1, ((m + 1) << 2) + 1, sm, sqds);
      }
      break;

     case 2:
      r = e[q - 1];
      e[q - 1] = 0.0F;
      for (k = q + 1; k <= m + 2; k++) {
        xrotg(&b_s[k - 1], &r, &sm, &sqds);
        b = e[k - 1];
        r = -sqds * b;
        e[k - 1] = b * sm;
        xrot(U, ((k - 1) << 2) + 1, ((q - 1) << 2) + 1, sm, sqds);
      }
      break;

     case 3:
      qjj = m + 1;
      r = b_s[m + 1];
      scale = (float)fabs(r);
      nrm = (float)fabs(b_s[m]);
      if ((!(scale > nrm)) && (!rtIsNaNF(nrm))) {
        scale = nrm;
      }

      nrm = (float)fabs(e[m]);
      if ((!(scale > nrm)) && (!rtIsNaNF(nrm))) {
        scale = nrm;
      }

      nrm = (float)fabs(b_s[q]);
      if ((!(scale > nrm)) && (!rtIsNaNF(nrm))) {
        scale = nrm;
      }

      nrm = (float)fabs(e[q]);
      if ((!(scale > nrm)) && (!rtIsNaNF(nrm))) {
        scale = nrm;
      }

      sm = r / scale;
      nrm = b_s[m] / scale;
      r = e[m] / scale;
      sqds = b_s[q] / scale;
      b = ((nrm + sm) * (nrm - sm) + r * r) / 2.0F;
      nrm = sm * r;
      nrm *= nrm;
      if ((b != 0.0F) || (nrm != 0.0F)) {
        r = (float)sqrt(b * b + nrm);
        if (b < 0.0F) {
          r = -r;
        }

        r = nrm / (b + r);
      } else {
        r = 0.0F;
      }

      r += (sqds + sm) * (sqds - sm);
      nrm = sqds * (e[q] / scale);
      for (k = q + 1; k <= qjj; k++) {
        xrotg(&r, &nrm, &sm, &sqds);
        if (k > q + 1) {
          e[k - 2] = r;
        }

        nrm = e[k - 1];
        b = b_s[k - 1];
        e[k - 1] = sm * nrm - sqds * b;
        r = sqds * b_s[k];
        b_s[k] *= sm;
        xrot(Vf, ((k - 1) << 2) + 1, (k << 2) + 1, sm, sqds);
        b_s[k - 1] = sm * b + sqds * nrm;
        xrotg(&b_s[k - 1], &r, &sm, &sqds);
        r = sm * e[k - 1] + sqds * b_s[k];
        b_s[k] = -sqds * e[k - 1] + sm * b_s[k];
        nrm = sqds * e[k];
        e[k] *= sm;
        xrot(U, ((k - 1) << 2) + 1, (k << 2) + 1, sm, sqds);
      }

      e[m] = r;
      iter++;
      break;

     default:
      if (b_s[q] < 0.0F) {
        b_s[q] = -b_s[q];
        qjj = q << 2;
        qp1jj = qjj + 4;
        for (k = qjj + 1; k <= qp1jj; k++) {
          Vf[k - 1] = -Vf[k - 1];
        }
      }

      qp1 = q + 1;
      while ((q + 1 < 4) && (b_s[q] < b_s[qp1])) {
        nrm = b_s[q];
        b_s[q] = b_s[qp1];
        b_s[qp1] = nrm;
        xswap(Vf, (q << 2) + 1, ((q + 1) << 2) + 1);
        xswap(U, (q << 2) + 1, ((q + 1) << 2) + 1);
        q = qp1;
        qp1++;
      }

      iter = 0;
      m--;
      break;
    }
  }

  for (k = 0; k < 4; k++) {
    s[k] = b_s[k];
    qjj = k << 2;
    V[qjj] = Vf[qjj];
    V[qjj + 1] = Vf[qjj + 1];
    V[qjj + 2] = Vf[qjj + 2];
    V[qjj + 3] = Vf[qjj + 3];
  }
}

/*
 * File trailer for svd.c
 *
 * [EOF]
 */
