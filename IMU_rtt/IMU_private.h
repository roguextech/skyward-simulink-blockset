/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: IMU_private.h
 *
 * Code generated for Simulink model 'IMU'.
 *
 * Model version                  : 1.10
 * Simulink Coder version         : 8.8 (R2015a) 09-Feb-2015
 * TLC version                    : 8.8 (Jan 20 2015)
 * C/C++ source code generated on : Fri Mar 20 16:52:47 2015
 *
 * Target selection: realtime.tlc
 * Embedded hardware selection: Atmel->AVR
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_IMU_private_h_
#define RTW_HEADER_IMU_private_h_
#include "rtwtypes.h"
#include "multiword_types.h"

/* Private macros used by the generated code to access rtModel */
#ifndef rtmSetTFinal
# define rtmSetTFinal(rtm, val)        ((rtm)->Timing.tFinal = (val))
#endif

#ifndef rtmGetTPtr
# define rtmGetTPtr(rtm)               (&(rtm)->Timing.taskTime0)
#endif

extern void GY_88_Outputs_wrapper(real_T *temperature,
  real_T *pressure,
  real_T *altitude,
  real_T *magnitude,
  real_T *acceleration,
  real_T *angular_velocity,
  const real_T *xD);
extern void GY_88_Update_wrapper(const real_T *temperature,
  const real_T *pressure,
  const real_T *altitude,
  const real_T *magnitude,
  const real_T *acceleration,
  const real_T *angular_velocity,
  real_T *xD);

#endif                                 /* RTW_HEADER_IMU_private_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
