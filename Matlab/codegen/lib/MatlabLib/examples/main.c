/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: main.c
 *
 * MATLAB Coder version            : 5.1
 * C/C++ source code generated on  : 19-Nov-2020 19:15:25
 */

/*************************************************************************/
/* This automatically generated example C main file shows how to call    */
/* entry-point functions that MATLAB Coder generated. You must customize */
/* this file for your application. Do not modify this file directly.     */
/* Instead, make a copy of this file, modify it, and integrate it into   */
/* your development environment.                                         */
/*                                                                       */
/* This file initializes entry-point function arguments to a default     */
/* size and value before calling the entry-point functions. It does      */
/* not store or use any values returned from the entry-point functions.  */
/* If necessary, it does pre-allocate memory for returned values.        */
/* You can use this file as a starting point for a main function that    */
/* you can deploy in your application.                                   */
/*                                                                       */
/* After you copy the file, and before you deploy it, you must make the  */
/* following changes:                                                    */
/* * For variable-size function arguments, change the example sizes to   */
/* the sizes that your application requires.                             */
/* * Change the example values of function arguments to the values that  */
/* your application requires.                                            */
/* * If the entry-point functions return values, store these values or   */
/* otherwise use them as required by your application.                   */
/*                                                                       */
/*************************************************************************/

/* Include Files */
#include "main.h"
#include "MatlabLib_terminate.h"
#include "ProcessIMU.h"
#include "fromTorqueToAngularVels.h"
#include "rt_nonfinite.h"

/* Function Declarations */
static void argInit_4x1_real32_T(float result[4]);
static float argInit_real32_T(void);
static void main_ProcessIMU(void);
static void main_fromTorqueToAngularVels(void);

/* Function Definitions */
/*
 * Arguments    : float result[4]
 * Return Type  : void
 */
static void argInit_4x1_real32_T(float result[4])
{
  int idx0;

  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < 4; idx0++) {
    /* Set the value of the array element.
       Change this value to the value that the application requires. */
    result[idx0] = argInit_real32_T();
  }
}

/*
 * Arguments    : void
 * Return Type  : float
 */
static float argInit_real32_T(void)
{
  return 0.0F;
}

/*
 * Arguments    : void
 * Return Type  : void
 */
static void main_ProcessIMU(void)
{
  float data_tmp[4];
  float out[4];

  /* Initialize function 'ProcessIMU' input arguments. */
  /* Initialize function input argument 'data'. */
  argInit_4x1_real32_T(data_tmp);

  /* Initialize function input argument 'zero'. */
  /* Call the entry-point 'ProcessIMU'. */
  ProcessIMU(data_tmp, data_tmp, out);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
static void main_fromTorqueToAngularVels(void)
{
  float angularVels[4];
  float fv[4];
  float armLength_tmp;

  /* Initialize function 'fromTorqueToAngularVels' input arguments. */
  /* Initialize function input argument 'torques'. */
  armLength_tmp = argInit_real32_T();

  /* Call the entry-point 'fromTorqueToAngularVels'. */
  argInit_4x1_real32_T(fv);
  fromTorqueToAngularVels(fv, armLength_tmp, armLength_tmp, armLength_tmp,
    angularVels);
}

/*
 * Arguments    : int argc
 *                const char * const argv[]
 * Return Type  : int
 */
int main(int argc, const char * const argv[])
{
  (void)argc;
  (void)argv;

  /* The initialize function is being called automatically from your entry-point function. So, a call to initialize is not included here. */
  /* Invoke the entry-point functions.
     You can call entry-point functions multiple times. */
  main_fromTorqueToAngularVels();
  main_ProcessIMU();

  /* Terminate the application.
     You do not need to do this more than one time. */
  MatlabLib_terminate();
  return 0;
}

/*
 * File trailer for main.c
 *
 * [EOF]
 */
