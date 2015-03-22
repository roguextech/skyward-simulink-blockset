/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: IMU.c
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

#include "IMU.h"
#include "IMU_private.h"
#include "IMU_dt.h"

/* Block signals (auto storage) */
B_IMU_T IMU_B;

/* Block states (auto storage) */
DW_IMU_T IMU_DW;

/* Real-time model */
RT_MODEL_IMU_T IMU_M_;
RT_MODEL_IMU_T *const IMU_M = &IMU_M_;

/* Model output function */
void IMU_output(void)
{
  /* S-Function (GY_88): '<Root>/S-Function Builder' */
  GY_88_Outputs_wrapper( &IMU_B.SFunctionBuilder_o1, &IMU_B.SFunctionBuilder_o2,
                        &IMU_B.SFunctionBuilder_o3, &IMU_B.SFunctionBuilder_o4[0],
                        &IMU_B.SFunctionBuilder_o5[0],
                        &IMU_B.SFunctionBuilder_o6[0],
                        &IMU_DW.SFunctionBuilder_DSTATE);
}

/* Model update function */
void IMU_update(void)
{
  /* S-Function "GY_88_wrapper" Block: <Root>/S-Function Builder */
  GY_88_Update_wrapper( &IMU_B.SFunctionBuilder_o1, &IMU_B.SFunctionBuilder_o2,
                       &IMU_B.SFunctionBuilder_o3, &IMU_B.SFunctionBuilder_o4[0],
                       &IMU_B.SFunctionBuilder_o5[0],
                       &IMU_B.SFunctionBuilder_o6[0],
                       &IMU_DW.SFunctionBuilder_DSTATE);

  /* signal main to stop simulation */
  {                                    /* Sample time: [1.0s, 0.0s] */
    if ((rtmGetTFinal(IMU_M)!=-1) &&
        !((rtmGetTFinal(IMU_M)-IMU_M->Timing.taskTime0) >
          IMU_M->Timing.taskTime0 * (DBL_EPSILON))) {
      rtmSetErrorStatus(IMU_M, "Simulation finished");
    }

    if (rtmGetStopRequested(IMU_M)) {
      rtmSetErrorStatus(IMU_M, "Simulation finished");
    }
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   */
  IMU_M->Timing.taskTime0 =
    (++IMU_M->Timing.clockTick0) * IMU_M->Timing.stepSize0;
}

/* Model initialize function */
void IMU_initialize(void)
{
  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)IMU_M, 0,
                sizeof(RT_MODEL_IMU_T));
  rtmSetTFinal(IMU_M, 20.0);
  IMU_M->Timing.stepSize0 = 1.0;

  /* External mode info */
  IMU_M->Sizes.checksums[0] = (2488959007U);
  IMU_M->Sizes.checksums[1] = (3641729993U);
  IMU_M->Sizes.checksums[2] = (1816117536U);
  IMU_M->Sizes.checksums[3] = (3899866405U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[1];
    IMU_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(IMU_M->extModeInfo,
      &IMU_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(IMU_M->extModeInfo, IMU_M->Sizes.checksums);
    rteiSetTPtr(IMU_M->extModeInfo, rtmGetTPtr(IMU_M));
  }

  /* block I/O */
  (void) memset(((void *) &IMU_B), 0,
                sizeof(B_IMU_T));

  /* states (dwork) */
  (void) memset((void *)&IMU_DW, 0,
                sizeof(DW_IMU_T));

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    IMU_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 14;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.B = &rtBTransTable;
  }

  /* S-Function Block: <Root>/S-Function Builder */
  {
    real_T initVector[1] = { 0 };

    {
      int_T i1;
      for (i1=0; i1 < 1; i1++) {
        IMU_DW.SFunctionBuilder_DSTATE = initVector[0];
      }
    }
  }
}

/* Model terminate function */
void IMU_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
