/*
 * dp_UKF.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "dp_UKF".
 *
 * Model version              : 1.28
 * Simulink Coder version : 8.9 (R2015b) 13-Aug-2015
 * C source code generated on : Thu Nov 24 14:24:46 2016
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_dp_UKF_h_
#define RTW_HEADER_dp_UKF_h_
#include <math.h>
#include <string.h>
#include <float.h>
#include <stddef.h>
#ifndef dp_UKF_COMMON_INCLUDES_
# define dp_UKF_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "rt_logging.h"
#endif                                 /* dp_UKF_COMMON_INCLUDES_ */

#include "dp_UKF_types.h"

/* Shared type includes */
#include "multiword_types.h"
#include "rt_nonfinite.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetBlkStateChangeFlag
# define rtmGetBlkStateChangeFlag(rtm) ((rtm)->ModelData.blkStateChange)
#endif

#ifndef rtmSetBlkStateChangeFlag
# define rtmSetBlkStateChangeFlag(rtm, val) ((rtm)->ModelData.blkStateChange = (val))
#endif

#ifndef rtmGetContStateDisabled
# define rtmGetContStateDisabled(rtm)  ((rtm)->ModelData.contStateDisabled)
#endif

#ifndef rtmSetContStateDisabled
# define rtmSetContStateDisabled(rtm, val) ((rtm)->ModelData.contStateDisabled = (val))
#endif

#ifndef rtmGetContStates
# define rtmGetContStates(rtm)         ((rtm)->ModelData.contStates)
#endif

#ifndef rtmSetContStates
# define rtmSetContStates(rtm, val)    ((rtm)->ModelData.contStates = (val))
#endif

#ifndef rtmGetDerivCacheNeedsReset
# define rtmGetDerivCacheNeedsReset(rtm) ((rtm)->ModelData.derivCacheNeedsReset)
#endif

#ifndef rtmSetDerivCacheNeedsReset
# define rtmSetDerivCacheNeedsReset(rtm, val) ((rtm)->ModelData.derivCacheNeedsReset = (val))
#endif

#ifndef rtmGetFinalTime
# define rtmGetFinalTime(rtm)          ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetIntgData
# define rtmGetIntgData(rtm)           ((rtm)->ModelData.intgData)
#endif

#ifndef rtmSetIntgData
# define rtmSetIntgData(rtm, val)      ((rtm)->ModelData.intgData = (val))
#endif

#ifndef rtmGetOdeF
# define rtmGetOdeF(rtm)               ((rtm)->ModelData.odeF)
#endif

#ifndef rtmSetOdeF
# define rtmSetOdeF(rtm, val)          ((rtm)->ModelData.odeF = (val))
#endif

#ifndef rtmGetOdeY
# define rtmGetOdeY(rtm)               ((rtm)->ModelData.odeY)
#endif

#ifndef rtmSetOdeY
# define rtmSetOdeY(rtm, val)          ((rtm)->ModelData.odeY = (val))
#endif

#ifndef rtmGetPeriodicContStateIndices
# define rtmGetPeriodicContStateIndices(rtm) ((rtm)->ModelData.periodicContStateIndices)
#endif

#ifndef rtmSetPeriodicContStateIndices
# define rtmSetPeriodicContStateIndices(rtm, val) ((rtm)->ModelData.periodicContStateIndices = (val))
#endif

#ifndef rtmGetPeriodicContStateRanges
# define rtmGetPeriodicContStateRanges(rtm) ((rtm)->ModelData.periodicContStateRanges)
#endif

#ifndef rtmSetPeriodicContStateRanges
# define rtmSetPeriodicContStateRanges(rtm, val) ((rtm)->ModelData.periodicContStateRanges = (val))
#endif

#ifndef rtmGetRTWLogInfo
# define rtmGetRTWLogInfo(rtm)         ((rtm)->rtwLogInfo)
#endif

#ifndef rtmGetZCCacheNeedsReset
# define rtmGetZCCacheNeedsReset(rtm)  ((rtm)->ModelData.zCCacheNeedsReset)
#endif

#ifndef rtmSetZCCacheNeedsReset
# define rtmSetZCCacheNeedsReset(rtm, val) ((rtm)->ModelData.zCCacheNeedsReset = (val))
#endif

#ifndef rtmGetdX
# define rtmGetdX(rtm)                 ((rtm)->ModelData.derivs)
#endif

#ifndef rtmSetdX
# define rtmSetdX(rtm, val)            ((rtm)->ModelData.derivs = (val))
#endif

#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
# define rtmGetStopRequested(rtm)      ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
# define rtmSetStopRequested(rtm, val) ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
# define rtmGetStopRequestedPtr(rtm)   (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
# define rtmGetT(rtm)                  (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTFinal
# define rtmGetTFinal(rtm)             ((rtm)->Timing.tFinal)
#endif

/* Block signals (auto storage) */
typedef struct {
  real_T IntegratorSecondOrder_o2;     /* '<Root>/Integrator, Second-Order' */
  real_T Sum1;                         /* '<Root>/Sum1' */
  real_T phi1;                         /* '<Root>/Gain1' */
  real_T IntegratorSecondOrder2_o1;    /* '<Root>/Integrator, Second-Order2' */
  real_T IntegratorSecondOrder2_o2;    /* '<Root>/Integrator, Second-Order2' */
  real_T IntegratorSecondOrder1_o1;    /* '<Root>/Integrator, Second-Order1' */
  real_T IntegratorSecondOrder1_o2;    /* '<Root>/Integrator, Second-Order1' */
  real_T Gain9;                        /* '<Root>/Gain9' */
  real_T Sum;                          /* '<Root>/Sum' */
  real_T phi2;                         /* '<Root>/Gain5' */
  real_T Saturation;                   /* '<Root>/Saturation' */
  real_T ddphi1;                       /* '<Root>/Bewegungsgleichungen' */
  real_T ddphi2;                       /* '<Root>/Bewegungsgleichungen' */
} B_dp_UKF_T;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real_T x_p[4];                       /* '<S4>/UKF_code' */
  real_T P_p[16];                      /* '<S4>/UKF_code' */
  real_T x0_sig[36];                   /* '<S4>/UKF_code' */
  real_T x_sig[36];                    /* '<S4>/UKF_code' */
  real_T W_m[9];                       /* '<S4>/UKF_code' */
  real_T W_c[9];                       /* '<S4>/UKF_code' */
  struct {
    void *LoggedData[4];
  } Scope_PWORK;                       /* '<Root>/Scope' */

  struct {
    void *LoggedData;
  } Scope1_PWORK;                      /* '<Root>/Scope1' */

  struct {
    void *LoggedData;
  } Scope10_PWORK;                     /* '<Root>/Scope10' */

  struct {
    void *LoggedData;
  } Scope2_PWORK;                      /* '<Root>/Scope2' */

  struct {
    void *LoggedData;
  } Scope3_PWORK;                      /* '<Root>/Scope3' */

  struct {
    void *LoggedData;
  } Scope4_PWORK;                      /* '<Root>/Scope4' */

  struct {
    void *LoggedData;
  } Scope5_PWORK;                      /* '<Root>/Scope5' */

  struct {
    void *LoggedData;
  } Scope6_PWORK;                      /* '<Root>/Scope6' */

  struct {
    void *LoggedData;
  } Scope7_PWORK;                      /* '<Root>/Scope7' */

  struct {
    void *LoggedData;
  } Scope8_PWORK;                      /* '<Root>/Scope8' */

  struct {
    void *LoggedData;
  } Scope9_PWORK;                      /* '<Root>/Scope9' */

  int_T IntegratorSecondOrder_MODE;    /* '<Root>/Integrator, Second-Order' */
  int_T IntegratorSecondOrder2_MODE;   /* '<Root>/Integrator, Second-Order2' */
  int_T IntegratorSecondOrder1_MODE;   /* '<Root>/Integrator, Second-Order1' */
  boolean_T IntegratorSecondOrder_DWORK1;/* '<Root>/Integrator, Second-Order' */
  boolean_T IntegratorSecondOrder2_DWORK1;/* '<Root>/Integrator, Second-Order2' */
  boolean_T IntegratorSecondOrder1_DWORK1;/* '<Root>/Integrator, Second-Order1' */
  boolean_T x_p_not_empty;             /* '<S4>/UKF_code' */
  boolean_T P_p_not_empty;             /* '<S4>/UKF_code' */
  boolean_T x0_sig_not_empty;          /* '<S4>/UKF_code' */
  boolean_T x_sig_not_empty;           /* '<S4>/UKF_code' */
  boolean_T W_m_not_empty;             /* '<S4>/UKF_code' */
  boolean_T W_c_not_empty;             /* '<S4>/UKF_code' */
} DW_dp_UKF_T;

/* Continuous states (auto storage) */
typedef struct {
  real_T IntegratorSecondOrder_CSTATE[2];/* '<Root>/Integrator, Second-Order' */
  real_T IntegratorSecondOrder2_CSTATE[2];/* '<Root>/Integrator, Second-Order2' */
  real_T IntegratorSecondOrder1_CSTATE[2];/* '<Root>/Integrator, Second-Order1' */
} X_dp_UKF_T;

/* State derivatives (auto storage) */
typedef struct {
  real_T IntegratorSecondOrder_CSTATE[2];/* '<Root>/Integrator, Second-Order' */
  real_T IntegratorSecondOrder2_CSTATE[2];/* '<Root>/Integrator, Second-Order2' */
  real_T IntegratorSecondOrder1_CSTATE[2];/* '<Root>/Integrator, Second-Order1' */
} XDot_dp_UKF_T;

/* State disabled  */
typedef struct {
  boolean_T IntegratorSecondOrder_CSTATE[2];/* '<Root>/Integrator, Second-Order' */
  boolean_T IntegratorSecondOrder2_CSTATE[2];/* '<Root>/Integrator, Second-Order2' */
  boolean_T IntegratorSecondOrder1_CSTATE[2];/* '<Root>/Integrator, Second-Order1' */
} XDis_dp_UKF_T;

#ifndef ODE3_INTG
#define ODE3_INTG

/* ODE3 Integration Data */
typedef struct {
  real_T *y;                           /* output */
  real_T *f[3];                        /* derivatives */
} ODE3_IntgData;

#endif

/* Parameters (auto storage) */
struct P_dp_UKF_T_ {
  real_T K6_lqr[6];                    /* Variable: K6_lqr
                                        * Referenced by: '<Root>/Gain'
                                        */
  real_T Pk_0[16];                     /* Variable: Pk_0
                                        * Referenced by: '<S4>/P'
                                        */
  real_T Qk[16];                       /* Variable: Qk
                                        * Referenced by: '<S4>/Q'
                                        */
  real_T Rk;                           /* Variable: Rk
                                        * Referenced by: '<S4>/R'
                                        */
  real_T T_s;                          /* Variable: T_s
                                        * Referenced by: '<S4>/T'
                                        */
  real_T alpha;                        /* Variable: alpha
                                        * Referenced by: '<S4>/alpha'
                                        */
  real_T beta;                         /* Variable: beta
                                        * Referenced by: '<S4>/beta'
                                        */
  real_T dphi1_0;                      /* Variable: dphi1_0
                                        * Referenced by: '<Root>/Integrator, Second-Order'
                                        */
  real_T dphi2_0;                      /* Variable: dphi2_0
                                        * Referenced by: '<Root>/Integrator, Second-Order1'
                                        */
  real_T dx_0;                         /* Variable: dx_0
                                        * Referenced by: '<Root>/Integrator, Second-Order2'
                                        */
  real_T kappa;                        /* Variable: kappa
                                        * Referenced by: '<S4>/kappa'
                                        */
  real_T phi1_0;                       /* Variable: phi1_0
                                        * Referenced by: '<Root>/Integrator, Second-Order'
                                        */
  real_T phi2_0;                       /* Variable: phi2_0
                                        * Referenced by: '<Root>/Integrator, Second-Order1'
                                        */
  real_T x0[4];                        /* Variable: x0
                                        * Referenced by: '<S4>/x0'
                                        */
  real_T x_0;                          /* Variable: x_0
                                        * Referenced by: '<Root>/Integrator, Second-Order2'
                                        */
  real_T Step_Time;                    /* Expression: 3
                                        * Referenced by: '<Root>/Step'
                                        */
  real_T Step_Y0;                      /* Expression: 0
                                        * Referenced by: '<Root>/Step'
                                        */
  real_T Step_YFinal;                  /* Expression: 1*0.0175
                                        * Referenced by: '<Root>/Step'
                                        */
  real_T Gain1_Gain;                   /* Expression: 180/pi
                                        * Referenced by: '<Root>/Gain1'
                                        */
  real_T para_sys_Value[8];            /* Expression: [g l_1 l_2 m_1 m_2 m_3 d_p1 d_p2]
                                        * Referenced by: '<S4>/para_sys'
                                        */
  real_T IntegratorSecondOrder2_UpperLim;/* Expression: 0.2
                                          * Referenced by: '<Root>/Integrator, Second-Order2'
                                          */
  real_T IntegratorSecondOrder2_LowerLim;/* Expression: -0.2
                                          * Referenced by: '<Root>/Integrator, Second-Order2'
                                          */
  real_T IntegratorSecondOrder2_UpperL_e;/* Expression: 5
                                          * Referenced by: '<Root>/Integrator, Second-Order2'
                                          */
  real_T IntegratorSecondOrder2_LowerL_k;/* Expression: -5
                                          * Referenced by: '<Root>/Integrator, Second-Order2'
                                          */
  real_T Gain9_Gain;                   /* Expression: 1
                                        * Referenced by: '<Root>/Gain9'
                                        */
  real_T Gain2_Gain;                   /* Expression: 180/pi
                                        * Referenced by: '<Root>/Gain2'
                                        */
  real_T Gain5_Gain;                   /* Expression: 180/pi
                                        * Referenced by: '<Root>/Gain5'
                                        */
  real_T Gain6_Gain;                   /* Expression: 180/pi
                                        * Referenced by: '<Root>/Gain6'
                                        */
  real_T Saturation_UpperSat;          /* Expression: 20
                                        * Referenced by: '<Root>/Saturation'
                                        */
  real_T Saturation_LowerSat;          /* Expression: -20
                                        * Referenced by: '<Root>/Saturation'
                                        */
  real_T para_sys_Value_g[8];          /* Expression: [g l_1 l_2 m_1 m_2 m_3 d_p1 d_p2]
                                        * Referenced by: '<Root>/para_sys'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_dp_UKF_T {
  const char_T *errorStatus;
  RTWLogInfo *rtwLogInfo;
  RTWSolverInfo solverInfo;

  /*
   * ModelData:
   * The following substructure contains information regarding
   * the data used in the model.
   */
  struct {
    X_dp_UKF_T *contStates;
    int_T *periodicContStateIndices;
    real_T *periodicContStateRanges;
    real_T *derivs;
    boolean_T *contStateDisabled;
    boolean_T zCCacheNeedsReset;
    boolean_T derivCacheNeedsReset;
    boolean_T blkStateChange;
    real_T odeY[6];
    real_T odeF[3][6];
    ODE3_IntgData intgData;
  } ModelData;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    int_T numContStates;
    int_T numPeriodicContStates;
    int_T numSampTimes;
  } Sizes;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
    uint32_T clockTickH0;
    time_T stepSize0;
    uint32_T clockTick1;
    uint32_T clockTickH1;
    time_T tFinal;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[2];
  } Timing;
};

/* Block parameters (auto storage) */
extern P_dp_UKF_T dp_UKF_P;

/* Block signals (auto storage) */
extern B_dp_UKF_T dp_UKF_B;

/* Continuous states (auto storage) */
extern X_dp_UKF_T dp_UKF_X;

/* Block states (auto storage) */
extern DW_dp_UKF_T dp_UKF_DW;

/* Model entry point functions */
extern void dp_UKF_initialize(void);
extern void dp_UKF_step(void);
extern void dp_UKF_terminate(void);

/* Real-time Model object */
extern RT_MODEL_dp_UKF_T *const dp_UKF_M;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'dp_UKF'
 * '<S1>'   : 'dp_UKF/Band-Limited White Noise'
 * '<S2>'   : 'dp_UKF/Bewegungsgleichungen'
 * '<S3>'   : 'dp_UKF/Discrete Derivative'
 * '<S4>'   : 'dp_UKF/UKF'
 * '<S5>'   : 'dp_UKF/UKF/UKF_code'
 */
#endif                                 /* RTW_HEADER_dp_UKF_h_ */
