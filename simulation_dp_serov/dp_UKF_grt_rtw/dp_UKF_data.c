/*
 * dp_UKF_data.c
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

#include "dp_UKF.h"
#include "dp_UKF_private.h"

/* Block parameters (auto storage) */
P_dp_UKF_T dp_UKF_P = {
  /*  Variable: K6_lqr
   * Referenced by: '<Root>/Gain'
   */
  { 22.360679774993635, 25.662201248620917, 373.60796218765529,
    -1.5599620733812358, -508.08055031378643, -38.589206035505192 },

  /*  Variable: Pk_0
   * Referenced by: '<S4>/P'
   */
  { 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0,
    1.0 },

  /*  Variable: Qk
   * Referenced by: '<S4>/Q'
   */
  { 0.001, 0.0, 0.0, 0.0, 0.0, 0.001, 0.0, 0.0, 0.0, 0.0, 1.0000000000000002E-6,
    0.0, 0.0, 0.0, 0.0, 1.0000000000000002E-6 },
  0.1,                                 /* Variable: Rk
                                        * Referenced by: '<S4>/R'
                                        */
  0.001,                               /* Variable: T_s
                                        * Referenced by: '<S4>/T'
                                        */
  0.001,                               /* Variable: alpha
                                        * Referenced by: '<S4>/alpha'
                                        */
  2.0,                                 /* Variable: beta
                                        * Referenced by: '<S4>/beta'
                                        */
  0.0,                                 /* Variable: dphi1_0
                                        * Referenced by: '<Root>/Integrator, Second-Order'
                                        */
  0.0,                                 /* Variable: dphi2_0
                                        * Referenced by: '<Root>/Integrator, Second-Order1'
                                        */
  0.0,                                 /* Variable: dx_0
                                        * Referenced by: '<Root>/Integrator, Second-Order2'
                                        */
  0.0,                                 /* Variable: kappa
                                        * Referenced by: '<S4>/kappa'
                                        */
  0.052500000000000005,                /* Variable: phi1_0
                                        * Referenced by: '<Root>/Integrator, Second-Order'
                                        */
  0.0,                                 /* Variable: phi2_0
                                        * Referenced by: '<Root>/Integrator, Second-Order1'
                                        */

  /*  Variable: x0
   * Referenced by: '<S4>/x0'
   */
  { 0.052500000000000005, 0.0, 0.0, 0.0 },
  0.0,                                 /* Variable: x_0
                                        * Referenced by: '<Root>/Integrator, Second-Order2'
                                        */
  3.0,                                 /* Expression: 3
                                        * Referenced by: '<Root>/Step'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<Root>/Step'
                                        */
  0.0175,                              /* Expression: 1*0.0175
                                        * Referenced by: '<Root>/Step'
                                        */
  57.295779513082323,                  /* Expression: 180/pi
                                        * Referenced by: '<Root>/Gain1'
                                        */

  /*  Expression: [g l_1 l_2 m_1 m_2 m_3 d_p1 d_p2]
   * Referenced by: '<S4>/para_sys'
   */
  { 9.81, 0.194, 0.1855, 0.0313, 0.0313, 0.0308, 0.001, 0.001 },
  0.2,                                 /* Expression: 0.2
                                        * Referenced by: '<Root>/Integrator, Second-Order2'
                                        */
  -0.2,                                /* Expression: -0.2
                                        * Referenced by: '<Root>/Integrator, Second-Order2'
                                        */
  5.0,                                 /* Expression: 5
                                        * Referenced by: '<Root>/Integrator, Second-Order2'
                                        */
  -5.0,                                /* Expression: -5
                                        * Referenced by: '<Root>/Integrator, Second-Order2'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<Root>/Gain9'
                                        */
  57.295779513082323,                  /* Expression: 180/pi
                                        * Referenced by: '<Root>/Gain2'
                                        */
  57.295779513082323,                  /* Expression: 180/pi
                                        * Referenced by: '<Root>/Gain5'
                                        */
  57.295779513082323,                  /* Expression: 180/pi
                                        * Referenced by: '<Root>/Gain6'
                                        */
  20.0,                                /* Expression: 20
                                        * Referenced by: '<Root>/Saturation'
                                        */
  -20.0,                               /* Expression: -20
                                        * Referenced by: '<Root>/Saturation'
                                        */

  /*  Expression: [g l_1 l_2 m_1 m_2 m_3 d_p1 d_p2]
   * Referenced by: '<Root>/para_sys'
   */
  { 9.81, 0.194, 0.1855, 0.0313, 0.0313, 0.0308, 0.001, 0.001 }
};
