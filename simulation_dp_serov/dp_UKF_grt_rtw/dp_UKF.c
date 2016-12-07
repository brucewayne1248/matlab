/*
 * dp_UKF.c
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

/* Block signals (auto storage) */
B_dp_UKF_T dp_UKF_B;

/* Continuous states */
X_dp_UKF_T dp_UKF_X;

/* Block states (auto storage) */
DW_dp_UKF_T dp_UKF_DW;

/* Real-time model */
RT_MODEL_dp_UKF_T dp_UKF_M_;
RT_MODEL_dp_UKF_T *const dp_UKF_M = &dp_UKF_M_;

/*
 * This function updates continuous states using the ODE3 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  /* Solver Matrices */
  static const real_T rt_ODE3_A[3] = {
    1.0/2.0, 3.0/4.0, 1.0
  };

  static const real_T rt_ODE3_B[3][3] = {
    { 1.0/2.0, 0.0, 0.0 },

    { 0.0, 3.0/4.0, 0.0 },

    { 2.0/9.0, 1.0/3.0, 4.0/9.0 }
  };

  time_T t = rtsiGetT(si);
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE3_IntgData *id = (ODE3_IntgData *)rtsiGetSolverData(si);
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T hB[3];
  int_T i;
  int_T nXc = 6;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  dp_UKF_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  dp_UKF_step();
  dp_UKF_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  dp_UKF_step();
  dp_UKF_derivatives();

  /* tnew = t + hA(3);
     ynew = y + f*hB(:,3); */
  for (i = 0; i <= 2; i++) {
    hB[i] = h * rt_ODE3_B[2][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2]);
  }

  rtsiSetT(si, tnew);
  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model step function */
void dp_UKF_step(void)
{
  /* local block i/o variables */
  real_T rtb_x[4];
  real_T rtb_phi2_est;
  real_T rtb_phi1_est;
  if (rtmIsMajorTimeStep(dp_UKF_M)) {
    /* set solver stop time */
    if (!(dp_UKF_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&dp_UKF_M->solverInfo,
                            ((dp_UKF_M->Timing.clockTickH0 + 1) *
        dp_UKF_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&dp_UKF_M->solverInfo, ((dp_UKF_M->Timing.clockTick0
        + 1) * dp_UKF_M->Timing.stepSize0 + dp_UKF_M->Timing.clockTickH0 *
        dp_UKF_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(dp_UKF_M)) {
    dp_UKF_M->Timing.t[0] = rtsiGetT(&dp_UKF_M->solverInfo);
  }

  {
    real_T g;
    real_T l_2;
    real_T m_1;
    real_T m_2;
    real_T m_3;
    real_T d_p1;
    real_T d_p2;
    real_T lambda_ukf;
    real_T P_an[16];
    real_T y_sig[9];
    int32_T jmax;
    real_T A[16];
    int32_T jj;
    real_T ajj;
    int32_T colj;
    int32_T b_j;
    int32_T ix;
    int32_T iy;
    int32_T k;
    int32_T b_ix;
    real_T c;
    int32_T e;
    int32_T ia;
    boolean_T exitg1;
    real_T rtb_IntegratorSecondOrder_o1;
    real_T tmp[6];
    real_T tmp_0[4];

    /* SecondOrderIntegrator: '<Root>/Integrator, Second-Order' */
    dp_UKF_B.IntegratorSecondOrder_o2 = dp_UKF_X.IntegratorSecondOrder_CSTATE[1];

    /* Step: '<Root>/Step' */
    if (dp_UKF_M->Timing.t[0] < dp_UKF_P.Step_Time) {
      g = dp_UKF_P.Step_Y0;
    } else {
      g = dp_UKF_P.Step_YFinal;
    }

    /* End of Step: '<Root>/Step' */

    /* Sum: '<Root>/Sum1' incorporates:
     *  SecondOrderIntegrator: '<Root>/Integrator, Second-Order'
     */
    dp_UKF_B.Sum1 = g + dp_UKF_X.IntegratorSecondOrder_CSTATE[0];

    /* Gain: '<Root>/Gain1' */
    dp_UKF_B.phi1 = dp_UKF_P.Gain1_Gain * dp_UKF_B.Sum1;

    /* SecondOrderIntegrator: '<Root>/Integrator, Second-Order2' */
    if (rtmIsMajorTimeStep(dp_UKF_M)) {
      switch (dp_UKF_DW.IntegratorSecondOrder2_MODE) {
       case 0:
        if (dp_UKF_X.IntegratorSecondOrder2_CSTATE[0] <=
            dp_UKF_P.IntegratorSecondOrder2_LowerLim) {
          dp_UKF_X.IntegratorSecondOrder2_CSTATE[0] =
            dp_UKF_P.IntegratorSecondOrder2_LowerLim;
          if (dp_UKF_X.IntegratorSecondOrder2_CSTATE[1] > 0.0) {
            dp_UKF_DW.IntegratorSecondOrder2_MODE = 0;
          } else {
            dp_UKF_X.IntegratorSecondOrder2_CSTATE[1] = 0.0;
            dp_UKF_DW.IntegratorSecondOrder2_MODE = 1;
          }

          rtsiSetSolverNeedsReset(&dp_UKF_M->solverInfo, true);
        }

        if (dp_UKF_X.IntegratorSecondOrder2_CSTATE[0] >=
            dp_UKF_P.IntegratorSecondOrder2_UpperLim) {
          dp_UKF_X.IntegratorSecondOrder2_CSTATE[0] =
            dp_UKF_P.IntegratorSecondOrder2_UpperLim;
          if (dp_UKF_X.IntegratorSecondOrder2_CSTATE[1] < 0.0) {
            dp_UKF_DW.IntegratorSecondOrder2_MODE = 0;
          } else {
            dp_UKF_X.IntegratorSecondOrder2_CSTATE[1] = 0.0;
            dp_UKF_DW.IntegratorSecondOrder2_MODE = 2;
          }

          rtsiSetSolverNeedsReset(&dp_UKF_M->solverInfo, true);
        }

        if (dp_UKF_X.IntegratorSecondOrder2_CSTATE[1] <=
            dp_UKF_P.IntegratorSecondOrder2_LowerL_k) {
          dp_UKF_X.IntegratorSecondOrder2_CSTATE[1] =
            dp_UKF_P.IntegratorSecondOrder2_LowerL_k;
          dp_UKF_DW.IntegratorSecondOrder2_MODE = 3;
          rtsiSetSolverNeedsReset(&dp_UKF_M->solverInfo, true);
        }

        if (dp_UKF_X.IntegratorSecondOrder2_CSTATE[1] >=
            dp_UKF_P.IntegratorSecondOrder2_UpperL_e) {
          dp_UKF_X.IntegratorSecondOrder2_CSTATE[1] =
            dp_UKF_P.IntegratorSecondOrder2_UpperL_e;
          dp_UKF_DW.IntegratorSecondOrder2_MODE = 4;
          rtsiSetSolverNeedsReset(&dp_UKF_M->solverInfo, true);
        }
        break;

       case 1:
        if (dp_UKF_X.IntegratorSecondOrder2_CSTATE[0] >
            dp_UKF_P.IntegratorSecondOrder2_LowerLim) {
          if (dp_UKF_X.IntegratorSecondOrder2_CSTATE[0] >=
              dp_UKF_P.IntegratorSecondOrder2_UpperLim) {
            dp_UKF_DW.IntegratorSecondOrder2_MODE = 2;
            dp_UKF_X.IntegratorSecondOrder2_CSTATE[0] =
              dp_UKF_P.IntegratorSecondOrder2_UpperLim;
          } else {
            dp_UKF_DW.IntegratorSecondOrder2_MODE = 0;
          }
        } else {
          dp_UKF_X.IntegratorSecondOrder2_CSTATE[0] =
            dp_UKF_P.IntegratorSecondOrder2_LowerLim;
          dp_UKF_X.IntegratorSecondOrder2_CSTATE[1] = 0.0;
        }
        break;

       case 2:
        if (dp_UKF_X.IntegratorSecondOrder2_CSTATE[0] <
            dp_UKF_P.IntegratorSecondOrder2_UpperLim) {
          if (dp_UKF_X.IntegratorSecondOrder2_CSTATE[0] <=
              dp_UKF_P.IntegratorSecondOrder2_LowerLim) {
            dp_UKF_DW.IntegratorSecondOrder2_MODE = 1;
            dp_UKF_X.IntegratorSecondOrder2_CSTATE[0] =
              dp_UKF_P.IntegratorSecondOrder2_LowerLim;
          } else {
            dp_UKF_DW.IntegratorSecondOrder2_MODE = 0;
          }
        } else {
          dp_UKF_X.IntegratorSecondOrder2_CSTATE[0] =
            dp_UKF_P.IntegratorSecondOrder2_UpperLim;
          dp_UKF_X.IntegratorSecondOrder2_CSTATE[1] = 0.0;
        }
        break;

       case 3:
        if (dp_UKF_X.IntegratorSecondOrder2_CSTATE[1] >
            dp_UKF_P.IntegratorSecondOrder2_LowerL_k) {
          if (dp_UKF_X.IntegratorSecondOrder2_CSTATE[1] >=
              dp_UKF_P.IntegratorSecondOrder2_UpperL_e) {
            dp_UKF_DW.IntegratorSecondOrder2_MODE = 4;
            dp_UKF_X.IntegratorSecondOrder2_CSTATE[1] =
              dp_UKF_P.IntegratorSecondOrder2_UpperL_e;
          } else {
            dp_UKF_DW.IntegratorSecondOrder2_MODE = 0;
          }
        } else {
          dp_UKF_X.IntegratorSecondOrder2_CSTATE[1] =
            dp_UKF_P.IntegratorSecondOrder2_LowerL_k;
        }

        if (dp_UKF_X.IntegratorSecondOrder2_CSTATE[0] <=
            dp_UKF_P.IntegratorSecondOrder2_LowerLim) {
          dp_UKF_X.IntegratorSecondOrder2_CSTATE[0] =
            dp_UKF_P.IntegratorSecondOrder2_LowerLim;
          dp_UKF_X.IntegratorSecondOrder2_CSTATE[1] = 0.0;
          dp_UKF_DW.IntegratorSecondOrder2_MODE = 1;
          rtsiSetSolverNeedsReset(&dp_UKF_M->solverInfo, true);
        }
        break;

       case 4:
        if (dp_UKF_X.IntegratorSecondOrder2_CSTATE[1] <
            dp_UKF_P.IntegratorSecondOrder2_UpperL_e) {
          if (dp_UKF_X.IntegratorSecondOrder2_CSTATE[1] <=
              dp_UKF_P.IntegratorSecondOrder2_LowerL_k) {
            dp_UKF_DW.IntegratorSecondOrder2_MODE = 3;
            dp_UKF_X.IntegratorSecondOrder2_CSTATE[1] =
              dp_UKF_P.IntegratorSecondOrder2_LowerL_k;
          } else {
            dp_UKF_DW.IntegratorSecondOrder2_MODE = 0;
          }
        } else {
          dp_UKF_X.IntegratorSecondOrder2_CSTATE[1] =
            dp_UKF_P.IntegratorSecondOrder2_UpperL_e;
        }

        if (dp_UKF_X.IntegratorSecondOrder2_CSTATE[0] >=
            dp_UKF_P.IntegratorSecondOrder2_UpperLim) {
          dp_UKF_X.IntegratorSecondOrder2_CSTATE[0] =
            dp_UKF_P.IntegratorSecondOrder2_UpperLim;
          dp_UKF_X.IntegratorSecondOrder2_CSTATE[1] = 0.0;
          dp_UKF_DW.IntegratorSecondOrder2_MODE = 2;
          rtsiSetSolverNeedsReset(&dp_UKF_M->solverInfo, true);
        }
        break;
      }
    }

    if (dp_UKF_X.IntegratorSecondOrder2_CSTATE[0] <
        dp_UKF_P.IntegratorSecondOrder2_LowerLim) {
      dp_UKF_B.IntegratorSecondOrder2_o1 =
        dp_UKF_P.IntegratorSecondOrder2_LowerLim;
    } else if (dp_UKF_X.IntegratorSecondOrder2_CSTATE[0] >
               dp_UKF_P.IntegratorSecondOrder2_UpperLim) {
      dp_UKF_B.IntegratorSecondOrder2_o1 =
        dp_UKF_P.IntegratorSecondOrder2_UpperLim;
    } else {
      dp_UKF_B.IntegratorSecondOrder2_o1 =
        dp_UKF_X.IntegratorSecondOrder2_CSTATE[0];
    }

    if (dp_UKF_X.IntegratorSecondOrder2_CSTATE[1] <
        dp_UKF_P.IntegratorSecondOrder2_LowerL_k) {
      dp_UKF_B.IntegratorSecondOrder2_o2 =
        dp_UKF_P.IntegratorSecondOrder2_LowerL_k;
    } else if (dp_UKF_X.IntegratorSecondOrder2_CSTATE[1] >
               dp_UKF_P.IntegratorSecondOrder2_UpperL_e) {
      dp_UKF_B.IntegratorSecondOrder2_o2 =
        dp_UKF_P.IntegratorSecondOrder2_UpperL_e;
    } else {
      dp_UKF_B.IntegratorSecondOrder2_o2 =
        dp_UKF_X.IntegratorSecondOrder2_CSTATE[1];
    }

    /* End of SecondOrderIntegrator: '<Root>/Integrator, Second-Order2' */

    /* SecondOrderIntegrator: '<Root>/Integrator, Second-Order1' */
    dp_UKF_B.IntegratorSecondOrder1_o1 = dp_UKF_X.IntegratorSecondOrder1_CSTATE
      [0];
    dp_UKF_B.IntegratorSecondOrder1_o2 = dp_UKF_X.IntegratorSecondOrder1_CSTATE
      [1];
    if (rtmIsMajorTimeStep(dp_UKF_M)) {
      /* ZeroOrderHold: '<Root>/Zero-Order Hold' */
      tmp[0] = dp_UKF_B.IntegratorSecondOrder2_o1;
      tmp[1] = dp_UKF_B.IntegratorSecondOrder2_o2;
      tmp[2] = dp_UKF_B.Sum1;
      tmp[3] = dp_UKF_B.IntegratorSecondOrder_o2;
      tmp[4] = dp_UKF_B.IntegratorSecondOrder1_o1;
      tmp[5] = dp_UKF_B.IntegratorSecondOrder1_o2;

      /* Gain: '<Root>/Gain' */
      g = 0.0;
      for (colj = 0; colj < 6; colj++) {
        g += -dp_UKF_P.K6_lqr[colj] * tmp[colj];
      }

      rtb_phi1_est = g;

      /* End of Gain: '<Root>/Gain' */

      /* Gain: '<Root>/Gain9' */
      dp_UKF_B.Gain9 = dp_UKF_P.Gain9_Gain * rtb_phi1_est;
    }

    /* Sum: '<Root>/Sum' */
    dp_UKF_B.Sum = dp_UKF_B.Sum1;

    /* Gain: '<Root>/Gain5' */
    dp_UKF_B.phi2 = dp_UKF_P.Gain5_Gain * dp_UKF_B.IntegratorSecondOrder1_o1;
    if (rtmIsMajorTimeStep(dp_UKF_M)) {
      /* MATLAB Function: '<S4>/UKF_code' incorporates:
       *  Constant: '<S4>/P'
       *  Constant: '<S4>/Q'
       *  Constant: '<S4>/R'
       *  Constant: '<S4>/T'
       *  Constant: '<S4>/alpha'
       *  Constant: '<S4>/beta'
       *  Constant: '<S4>/kappa'
       *  Constant: '<S4>/para_sys'
       *  Constant: '<S4>/x0'
       *  ZeroOrderHold: '<Root>/Zero-Order Hold1'
       */
      /* MATLAB Function 'UKF/UKF_code': '<S5>:1' */
      /*  Unscented Kalman Filter (UKF) fuer nichtlineare Systeme */
      /*  Das UKF praediziert den Zustand eines nichtliniearen Systems durch */
      /*  Mittelung sog. Sigma Punkte. Dazu werden 2n+1 Sigmapunkte (moegliche */
      /*  Zustaende des Systems) mittels Kovarianzmatrix P berechnet und fuer jeden */
      /*  Sigmapunkt mithilfe der Zustandsgleichung ein neuer Zustand praediziert. */
      /*  Diese werden gewichtet gemittelt und mit deren Hilfe die neuen */
      /*  Kovarianzmatrizen, die Rueckfuehrmatrix K und die Zustaende ermittelt. */
      /*  Weitere Infos unter */
      /*  http://www.agnld.uni-potsdam.de/~shw/TSA/Tools/UKF/node4.html */
      /*  http://cslu.cse.ogi.edu/nsel/ukf/node6.html */
      /*  */
      /*  Tipp: kappa meist zu 0 waehlen, alpha sehr klein bspw. 0.001, beta bei */
      /*  Gaussverteilung = 2 */
      /*  -alpha bestimmt die Streuung der Sigma-Punkte um den Mittelwert */
      /*  -beta wird benutzt, um Wissen ueber die Verteilung aufzunehmen */
      /*  -kappa ist ein sekundaerer skalierender Parameter, der gewoehnlich  */
      /*  gleich 0 oder 3-n gesetzt wird */
      /*  */
      /*  Vorlage von Matthias Dagen, September 2009, veraendert durch David */
      /*  Klinkenbuss */
      /*  Parameter */
      /* '<S5>:1:27' */
      g = dp_UKF_P.para_sys_Value[0];

      /* '<S5>:1:28' */
      rtb_IntegratorSecondOrder_o1 = dp_UKF_P.para_sys_Value[1];

      /* '<S5>:1:29' */
      l_2 = dp_UKF_P.para_sys_Value[2];

      /* '<S5>:1:30' */
      m_1 = dp_UKF_P.para_sys_Value[3];

      /* '<S5>:1:31' */
      m_2 = dp_UKF_P.para_sys_Value[4];

      /* '<S5>:1:32' */
      m_3 = dp_UKF_P.para_sys_Value[5];

      /* '<S5>:1:33' */
      d_p1 = dp_UKF_P.para_sys_Value[6];

      /* '<S5>:1:34' */
      d_p2 = dp_UKF_P.para_sys_Value[7];

      /* '<S5>:1:36' */
      /*  Laenge von f(x) */
      /*  Anzahl der zurueckgefuehrten Variablen */
      if ((!dp_UKF_DW.x_p_not_empty) || (!dp_UKF_DW.P_p_not_empty) ||
          (!dp_UKF_DW.x0_sig_not_empty) || (!dp_UKF_DW.x_sig_not_empty) ||
          (!dp_UKF_DW.W_m_not_empty) || (!dp_UKF_DW.W_c_not_empty)) {
        /* '<S5>:1:39' */
        /* '<S5>:1:40' */
        dp_UKF_DW.x_p[0] = dp_UKF_P.x0[0];
        dp_UKF_DW.x_p[1] = dp_UKF_P.x0[1];
        dp_UKF_DW.x_p[2] = dp_UKF_P.x0[2];
        dp_UKF_DW.x_p[3] = dp_UKF_P.x0[3];
        dp_UKF_DW.x_p_not_empty = true;

        /* '<S5>:1:41' */
        memcpy(&dp_UKF_DW.P_p[0], &dp_UKF_P.Pk_0[0], sizeof(real_T) << 4U);
        dp_UKF_DW.P_p_not_empty = true;

        /* '<S5>:1:42' */
        dp_UKF_DW.x0_sig_not_empty = true;

        /* '<S5>:1:43' */
        for (jmax = 0; jmax < 36; jmax++) {
          dp_UKF_DW.x0_sig[jmax] = 0.0;
          dp_UKF_DW.x_sig[jmax] = 0.0;
        }

        dp_UKF_DW.x_sig_not_empty = true;

        /* '<S5>:1:44' */
        dp_UKF_DW.W_m_not_empty = true;

        /* '<S5>:1:45' */
        for (jmax = 0; jmax < 9; jmax++) {
          dp_UKF_DW.W_m[jmax] = 0.0;
          dp_UKF_DW.W_c[jmax] = 0.0;
        }

        dp_UKF_DW.W_c_not_empty = true;

        /* '<S5>:1:46' */
        rtb_x[0] = dp_UKF_DW.x_p[0];
        rtb_x[1] = dp_UKF_DW.x_p[1];
        rtb_x[2] = dp_UKF_DW.x_p[2];
        rtb_x[3] = dp_UKF_DW.x_p[3];
      } else {
        /* % Parameter-Initialization */
        /* '<S5>:1:50' */
        lambda_ukf = dp_UKF_P.alpha * dp_UKF_P.alpha * (4.0 + dp_UKF_P.kappa) -
          4.0;

        /* % Weight calculation */
        /* '<S5>:1:53' */
        dp_UKF_DW.W_m[0] = lambda_ukf / (4.0 + lambda_ukf);

        /* '<S5>:1:54' */
        dp_UKF_DW.W_c[0] = ((lambda_ukf / (4.0 + lambda_ukf) + 1.0) -
                            dp_UKF_P.alpha * dp_UKF_P.alpha) + dp_UKF_P.beta;

        /* '<S5>:1:55' */
        for (jmax = 0; jmax < 8; jmax++) {
          /* '<S5>:1:55' */
          /* '<S5>:1:56' */
          dp_UKF_DW.W_m[jmax + 1] = 1.0 / ((4.0 + lambda_ukf) * 2.0);

          /* '<S5>:1:57' */
          dp_UKF_DW.W_c[jmax + 1] = 1.0 / ((4.0 + lambda_ukf) * 2.0);

          /* '<S5>:1:55' */
        }

        /* % 2n+1 Sigma Points calculation */
        /* '<S5>:1:62' */
        lambda_ukf = sqrt(4.0 + lambda_ukf);
        memcpy(&A[0], &dp_UKF_DW.P_p[0], sizeof(real_T) << 4U);
        jmax = 0;
        colj = 0;
        b_j = 1;
        exitg1 = false;
        while ((!exitg1) && (b_j < 5)) {
          jj = (colj + b_j) - 1;
          ajj = 0.0;
          if (!(b_j - 1 < 1)) {
            ix = colj;
            iy = colj;
            for (k = 1; k < b_j; k++) {
              ajj += A[ix] * A[iy];
              ix++;
              iy++;
            }
          }

          ajj = A[jj] - ajj;
          if (ajj > 0.0) {
            ajj = sqrt(ajj);
            A[jj] = ajj;
            if (b_j < 4) {
              if (b_j - 1 != 0) {
                ix = jj + 4;
                iy = (((3 - b_j) << 2) + colj) + 5;
                for (k = colj + 5; k <= iy; k += 4) {
                  b_ix = colj;
                  c = 0.0;
                  e = (k + b_j) - 2;
                  for (ia = k; ia <= e; ia++) {
                    c += A[ia - 1] * A[b_ix];
                    b_ix++;
                  }

                  A[ix] += -c;
                  ix += 4;
                }
              }

              ajj = 1.0 / ajj;
              ix = (((3 - b_j) << 2) + jj) + 5;
              for (jj += 4; jj + 1 <= ix; jj += 4) {
                A[jj] *= ajj;
              }

              colj += 4;
            }

            b_j++;
          } else {
            A[jj] = ajj;
            jmax = b_j;
            exitg1 = true;
          }
        }

        if (jmax == 0) {
          jmax = 4;
        } else {
          jmax--;
        }

        for (colj = 0; colj + 1 <= jmax; colj++) {
          for (b_j = colj + 1; b_j + 1 <= jmax; b_j++) {
            A[b_j + (colj << 2)] = 0.0;
          }
        }

        /*  Wurzelmatrix mittels Cholesky-Zerlegung */
        /* '<S5>:1:63' */
        for (colj = 0; colj < 4; colj++) {
          P_an[colj << 2] = lambda_ukf * A[colj];
          P_an[1 + (colj << 2)] = A[colj + 4] * lambda_ukf;
          P_an[2 + (colj << 2)] = A[colj + 8] * lambda_ukf;
          P_an[3 + (colj << 2)] = A[colj + 12] * lambda_ukf;
          dp_UKF_DW.x0_sig[colj] = dp_UKF_DW.x_p[colj];
        }

        /* '<S5>:1:64' */
        for (jmax = 0; jmax < 4; jmax++) {
          /* '<S5>:1:64' */
          /* '<S5>:1:65' */
          dp_UKF_DW.x0_sig[(jmax + 1) << 2] = P_an[jmax << 2] + dp_UKF_DW.x_p[0];
          dp_UKF_DW.x0_sig[1 + ((jmax + 1) << 2)] = P_an[(jmax << 2) + 1] +
            dp_UKF_DW.x_p[1];
          dp_UKF_DW.x0_sig[2 + ((jmax + 1) << 2)] = P_an[(jmax << 2) + 2] +
            dp_UKF_DW.x_p[2];
          dp_UKF_DW.x0_sig[3 + ((jmax + 1) << 2)] = P_an[(jmax << 2) + 3] +
            dp_UKF_DW.x_p[3];

          /* '<S5>:1:66' */
          dp_UKF_DW.x0_sig[(jmax + 5) << 2] = dp_UKF_DW.x_p[0] - P_an[jmax << 2];
          dp_UKF_DW.x0_sig[1 + ((jmax + 5) << 2)] = dp_UKF_DW.x_p[1] - P_an
            [(jmax << 2) + 1];
          dp_UKF_DW.x0_sig[2 + ((jmax + 5) << 2)] = dp_UKF_DW.x_p[2] - P_an
            [(jmax << 2) + 2];
          dp_UKF_DW.x0_sig[3 + ((jmax + 5) << 2)] = dp_UKF_DW.x_p[3] - P_an
            [(jmax << 2) + 3];

          /* '<S5>:1:64' */
        }

        /* % Unscented Kalman filter time update equations */
        /* '<S5>:1:70' */
        /* '<S5>:1:81' */
        for (jmax = 0; jmax < 9; jmax++) {
          /* '<S5>:1:70' */
          /* '<S5>:1:73' */
          /* '<S5>:1:74' */
          /* '<S5>:1:75' */
          /* '<S5>:1:76' */
          /* '<S5>:1:78' */
          lambda_ukf = cos(dp_UKF_DW.x0_sig[jmax << 2] - dp_UKF_DW.x0_sig[(jmax <<
            2) + 2]);
          dp_UKF_DW.x_sig[jmax << 2] = dp_UKF_DW.x0_sig[(jmax << 2) + 1] *
            dp_UKF_P.T_s + dp_UKF_DW.x0_sig[jmax << 2];
          dp_UKF_DW.x_sig[1 + (jmax << 2)] = ((((((((((12.0 * d_p2 * l_2 *
            dp_UKF_DW.x0_sig[(jmax << 2) + 3] - 12.0 * d_p1 * l_2 *
            dp_UKF_DW.x0_sig[(jmax << 2) + 1]) - 12.0 * d_p2 * l_2 *
            dp_UKF_DW.x0_sig[(jmax << 2) + 1]) - (((9.0 *
            rtb_IntegratorSecondOrder_o1 * l_2 * m_2 * dp_UKF_B.Gain9 * cos
            (dp_UKF_DW.x0_sig[(jmax << 2) + 2]) + (18.0 * d_p2 *
            rtb_IntegratorSecondOrder_o1 * dp_UKF_DW.x0_sig[(jmax << 2) + 1] -
            18.0 * d_p2 * rtb_IntegratorSecondOrder_o1 * dp_UKF_DW.x0_sig[(jmax <<
            2) + 3])) + 9.0 * g * rtb_IntegratorSecondOrder_o1 * l_2 * m_2 * sin
            (dp_UKF_DW.x0_sig[(jmax << 2) + 2])) + rtb_IntegratorSecondOrder_o1 *
            rtb_IntegratorSecondOrder_o1 * 9.0 * l_2 * m_2 * (dp_UKF_DW.x0_sig
            [(jmax << 2) + 1] * dp_UKF_DW.x0_sig[(jmax << 2) + 1]) * sin
            (dp_UKF_DW.x0_sig[jmax << 2] - dp_UKF_DW.x0_sig[(jmax << 2) + 2])) *
            cos(dp_UKF_DW.x0_sig[jmax << 2] - dp_UKF_DW.x0_sig[(jmax << 2) + 2]))
            + 6.0 * rtb_IntegratorSecondOrder_o1 * l_2 * m_1 * dp_UKF_B.Gain9 *
            cos(dp_UKF_DW.x0_sig[jmax << 2])) + 12.0 *
            rtb_IntegratorSecondOrder_o1 * l_2 * m_2 * dp_UKF_B.Gain9 * cos
            (dp_UKF_DW.x0_sig[jmax << 2])) + 12.0 * rtb_IntegratorSecondOrder_o1
            * l_2 * m_3 * dp_UKF_B.Gain9 * cos(dp_UKF_DW.x0_sig[jmax << 2])) +
            6.0 * g * rtb_IntegratorSecondOrder_o1 * l_2 * m_1 * sin
            (dp_UKF_DW.x0_sig[jmax << 2])) + 12.0 * g *
            rtb_IntegratorSecondOrder_o1 * l_2 * m_2 * sin(dp_UKF_DW.x0_sig[jmax
            << 2])) + 12.0 * g * rtb_IntegratorSecondOrder_o1 * l_2 * m_3 * sin
            (dp_UKF_DW.x0_sig[jmax << 2])) - 6.0 * rtb_IntegratorSecondOrder_o1 *
            (l_2 * l_2) * m_2 * (dp_UKF_DW.x0_sig[(jmax << 2) + 3] *
            dp_UKF_DW.x0_sig[(jmax << 2) + 3]) * sin(dp_UKF_DW.x0_sig[jmax << 2]
            - dp_UKF_DW.x0_sig[(jmax << 2) + 2])) * dp_UKF_P.T_s / ((((4.0 * m_1
            + 12.0 * m_2) + 12.0 * m_3) - 9.0 * m_2 * (lambda_ukf * lambda_ukf))
            * (rtb_IntegratorSecondOrder_o1 * rtb_IntegratorSecondOrder_o1 * l_2))
            + dp_UKF_DW.x0_sig[(jmax << 2) + 1];
          dp_UKF_DW.x_sig[2 + (jmax << 2)] = dp_UKF_DW.x0_sig[(jmax << 2) + 3] *
            dp_UKF_P.T_s + dp_UKF_DW.x0_sig[(jmax << 2) + 2];
          dp_UKF_DW.x_sig[3 + (jmax << 2)] =
            ((((((((((((((((((((((((rtb_IntegratorSecondOrder_o1 *
            rtb_IntegratorSecondOrder_o1 * 12.0 * l_2 * m_1 * m_2 *
            (dp_UKF_DW.x0_sig[(jmax << 2) + 1] * dp_UKF_DW.x0_sig[(jmax << 2) +
            1]) + rtb_IntegratorSecondOrder_o1 * rtb_IntegratorSecondOrder_o1 *
            36.0 * l_2 * (m_2 * m_2) * (dp_UKF_DW.x0_sig[(jmax << 2) + 1] *
            dp_UKF_DW.x0_sig[(jmax << 2) + 1])) + rtb_IntegratorSecondOrder_o1 *
            rtb_IntegratorSecondOrder_o1 * 36.0 * l_2 * m_2 * m_3 *
            (dp_UKF_DW.x0_sig[(jmax << 2) + 1] * dp_UKF_DW.x0_sig[(jmax << 2) +
            1])) * sin(dp_UKF_DW.x0_sig[jmax << 2] - dp_UKF_DW.x0_sig[(jmax << 2)
            + 2]) + 24.0 * d_p2 * rtb_IntegratorSecondOrder_o1 * m_1 *
            dp_UKF_DW.x0_sig[(jmax << 2) + 1]) + 72.0 * d_p2 *
            rtb_IntegratorSecondOrder_o1 * m_2 * dp_UKF_DW.x0_sig[(jmax << 2) +
            1]) - 24.0 * d_p2 * rtb_IntegratorSecondOrder_o1 * m_1 *
            dp_UKF_DW.x0_sig[(jmax << 2) + 3]) + 72.0 * d_p2 *
                               rtb_IntegratorSecondOrder_o1 * m_3 *
                               dp_UKF_DW.x0_sig[(jmax << 2) + 1]) - 72.0 * d_p2 *
                              rtb_IntegratorSecondOrder_o1 * m_2 *
                              dp_UKF_DW.x0_sig[(jmax << 2) + 3]) - 72.0 * d_p2 *
                             rtb_IntegratorSecondOrder_o1 * m_3 *
                             dp_UKF_DW.x0_sig[(jmax << 2) + 3]) + 36.0 * d_p1 *
                            l_2 * m_2 * dp_UKF_DW.x0_sig[(jmax << 2) + 1] * cos
                            (dp_UKF_DW.x0_sig[jmax << 2] - dp_UKF_DW.x0_sig
                             [(jmax << 2) + 2])) + 36.0 * d_p2 * l_2 * m_2 *
                           dp_UKF_DW.x0_sig[(jmax << 2) + 1] * cos
                           (dp_UKF_DW.x0_sig[jmax << 2] - dp_UKF_DW.x0_sig[(jmax
            << 2) + 2])) - 36.0 * d_p2 * l_2 * m_2 * dp_UKF_DW.x0_sig[(jmax << 2)
                          + 3] * cos(dp_UKF_DW.x0_sig[jmax << 2] -
            dp_UKF_DW.x0_sig[(jmax << 2) + 2])) + 18.0 *
                         rtb_IntegratorSecondOrder_o1 * l_2 * (m_2 * m_2) *
                         dp_UKF_B.Gain9 * cos(dp_UKF_DW.x0_sig[(jmax << 2) + 2]))
                        + 18.0 * g * rtb_IntegratorSecondOrder_o1 * l_2 * (m_2 *
            m_2) * sin(dp_UKF_DW.x0_sig[(jmax << 2) + 2])) + 9.0 *
                       rtb_IntegratorSecondOrder_o1 * (l_2 * l_2) * (m_2 * m_2) *
                       (dp_UKF_DW.x0_sig[(jmax << 2) + 3] * dp_UKF_DW.x0_sig
                        [(jmax << 2) + 3]) * sin(dp_UKF_DW.x0_sig[jmax << 2] *
            2.0 - dp_UKF_DW.x0_sig[(jmax << 2) + 2] * 2.0)) - 18.0 *
                      rtb_IntegratorSecondOrder_o1 * l_2 * (m_2 * m_2) *
                      dp_UKF_B.Gain9 * cos(dp_UKF_DW.x0_sig[jmax << 2] * 2.0 -
            dp_UKF_DW.x0_sig[(jmax << 2) + 2])) - 18.0 * g *
                     rtb_IntegratorSecondOrder_o1 * l_2 * (m_2 * m_2) * sin
                     (dp_UKF_DW.x0_sig[jmax << 2] * 2.0 - dp_UKF_DW.x0_sig[(jmax
            << 2) + 2])) + 3.0 * rtb_IntegratorSecondOrder_o1 * l_2 * m_1 * m_2 *
                    dp_UKF_B.Gain9 * cos(dp_UKF_DW.x0_sig[(jmax << 2) + 2])) +
                   18.0 * rtb_IntegratorSecondOrder_o1 * l_2 * m_2 * m_3 *
                   dp_UKF_B.Gain9 * cos(dp_UKF_DW.x0_sig[(jmax << 2) + 2])) +
                  3.0 * g * rtb_IntegratorSecondOrder_o1 * l_2 * m_1 * m_2 * sin
                  (dp_UKF_DW.x0_sig[(jmax << 2) + 2])) + 18.0 * g *
                 rtb_IntegratorSecondOrder_o1 * l_2 * m_2 * m_3 * sin
                 (dp_UKF_DW.x0_sig[(jmax << 2) + 2])) - 9.0 *
                rtb_IntegratorSecondOrder_o1 * l_2 * m_1 * m_2 * dp_UKF_B.Gain9 *
                cos(dp_UKF_DW.x0_sig[jmax << 2] * 2.0 - dp_UKF_DW.x0_sig[(jmax <<
                  2) + 2])) - 18.0 * rtb_IntegratorSecondOrder_o1 * l_2 * m_2 *
               m_3 * dp_UKF_B.Gain9 * cos(dp_UKF_DW.x0_sig[jmax << 2] * 2.0 -
                dp_UKF_DW.x0_sig[(jmax << 2) + 2])) - 9.0 * g *
              rtb_IntegratorSecondOrder_o1 * l_2 * m_1 * m_2 * sin
              (dp_UKF_DW.x0_sig[jmax << 2] * 2.0 - dp_UKF_DW.x0_sig[(jmax << 2)
               + 2])) - 18.0 * g * rtb_IntegratorSecondOrder_o1 * l_2 * m_2 *
             m_3 * sin(dp_UKF_DW.x0_sig[jmax << 2] * 2.0 - dp_UKF_DW.x0_sig
                       [(jmax << 2) + 2])) * dp_UKF_P.T_s / ((((8.0 * m_1 + 15.0
            * m_2) + 24.0 * m_3) - cos(dp_UKF_DW.x0_sig[jmax << 2] * 2.0 -
            dp_UKF_DW.x0_sig[(jmax << 2) + 2] * 2.0) * (9.0 * m_2)) * (l_2 * l_2
            * rtb_IntegratorSecondOrder_o1 * m_2)) + dp_UKF_DW.x0_sig[(jmax << 2)
            + 3];

          /* '<S5>:1:70' */
          lambda_ukf = dp_UKF_DW.x_sig[(jmax << 2) + 3] * 0.0 +
            (dp_UKF_DW.x_sig[(jmax << 2) + 2] * 0.0 + (dp_UKF_DW.x_sig[(jmax <<
               2) + 1] * 0.0 + dp_UKF_DW.x_sig[jmax << 2]));
          y_sig[jmax] = lambda_ukf;
        }

        /*  Prediction, weighted sum */
        /* '<S5>:1:83' */
        for (colj = 0; colj < 4; colj++) {
          dp_UKF_DW.x_p[colj] = 0.0;
          for (jmax = 0; jmax < 9; jmax++) {
            dp_UKF_DW.x_p[colj] += dp_UKF_DW.x_sig[(jmax << 2) + colj] *
              dp_UKF_DW.W_m[jmax];
          }
        }

        /* '<S5>:1:84' */
        g = 0.0;
        for (colj = 0; colj < 9; colj++) {
          g += y_sig[colj] * dp_UKF_DW.W_m[colj];
        }

        /* P_p calculation */
        /* '<S5>:1:86' */
        for (colj = 0; colj < 16; colj++) {
          dp_UKF_DW.P_p[colj] *= 0.0;
        }

        /* '<S5>:1:87' */
        for (jmax = 0; jmax < 9; jmax++) {
          /* '<S5>:1:87' */
          /* '<S5>:1:88' */
          tmp_0[0] = dp_UKF_DW.x_sig[jmax << 2] - dp_UKF_DW.x_p[0];
          rtb_IntegratorSecondOrder_o1 = dp_UKF_DW.x_sig[jmax << 2] -
            dp_UKF_DW.x_p[0];
          tmp_0[1] = dp_UKF_DW.x_sig[(jmax << 2) + 1] - dp_UKF_DW.x_p[1];
          l_2 = dp_UKF_DW.x_sig[(jmax << 2) + 1] - dp_UKF_DW.x_p[1];
          tmp_0[2] = dp_UKF_DW.x_sig[(jmax << 2) + 2] - dp_UKF_DW.x_p[2];
          m_1 = dp_UKF_DW.x_sig[(jmax << 2) + 2] - dp_UKF_DW.x_p[2];
          tmp_0[3] = dp_UKF_DW.x_sig[(jmax << 2) + 3] - dp_UKF_DW.x_p[3];
          m_2 = dp_UKF_DW.x_sig[(jmax << 2) + 3] - dp_UKF_DW.x_p[3];
          m_3 = dp_UKF_DW.W_c[jmax];
          for (colj = 0; colj < 4; colj++) {
            A[colj] = tmp_0[colj] * rtb_IntegratorSecondOrder_o1;
            A[colj + 4] = tmp_0[colj] * l_2;
            A[colj + 8] = tmp_0[colj] * m_1;
            A[colj + 12] = tmp_0[colj] * m_2;
          }

          for (colj = 0; colj < 4; colj++) {
            dp_UKF_DW.P_p[colj << 2] += A[colj << 2] * m_3;
            dp_UKF_DW.P_p[1 + (colj << 2)] += A[(colj << 2) + 1] * m_3;
            dp_UKF_DW.P_p[2 + (colj << 2)] += A[(colj << 2) + 2] * m_3;
            dp_UKF_DW.P_p[3 + (colj << 2)] += A[(colj << 2) + 3] * m_3;
          }

          /* '<S5>:1:87' */
        }

        /* '<S5>:1:90' */
        for (colj = 0; colj < 16; colj++) {
          dp_UKF_DW.P_p[colj] += dp_UKF_P.Qk[colj];
        }

        /* % Unscented Kalman filter measurement update equations */
        /*  Pyy calculation */
        /* '<S5>:1:94' */
        rtb_IntegratorSecondOrder_o1 = 0.0;

        /* '<S5>:1:95' */
        for (jmax = 0; jmax < 9; jmax++) {
          /* '<S5>:1:95' */
          /* '<S5>:1:96' */
          rtb_IntegratorSecondOrder_o1 += (y_sig[jmax] - g) * (y_sig[jmax] - g) *
            dp_UKF_DW.W_c[jmax];

          /* '<S5>:1:95' */
        }

        /* '<S5>:1:98' */
        rtb_IntegratorSecondOrder_o1 += dp_UKF_P.Rk;

        /*  Pxy calculation */
        /* '<S5>:1:100' */
        rtb_x[0] = 0.0;
        rtb_x[1] = 0.0;
        rtb_x[2] = 0.0;
        rtb_x[3] = 0.0;

        /* '<S5>:1:101' */
        for (jmax = 0; jmax < 9; jmax++) {
          /* '<S5>:1:101' */
          /* '<S5>:1:102' */
          l_2 = y_sig[jmax] - g;
          rtb_x[0] += (dp_UKF_DW.x_sig[jmax << 2] - dp_UKF_DW.x_p[0]) * l_2 *
            dp_UKF_DW.W_c[jmax];
          rtb_x[1] += (dp_UKF_DW.x_sig[(jmax << 2) + 1] - dp_UKF_DW.x_p[1]) *
            l_2 * dp_UKF_DW.W_c[jmax];
          rtb_x[2] += (dp_UKF_DW.x_sig[(jmax << 2) + 2] - dp_UKF_DW.x_p[2]) *
            l_2 * dp_UKF_DW.W_c[jmax];
          rtb_x[3] += (dp_UKF_DW.x_sig[(jmax << 2) + 3] - dp_UKF_DW.x_p[3]) *
            l_2 * dp_UKF_DW.W_c[jmax];

          /* '<S5>:1:101' */
        }

        /*  Kalman Gain */
        /* '<S5>:1:105' */
        rtb_x[0] /= rtb_IntegratorSecondOrder_o1;
        rtb_x[1] /= rtb_IntegratorSecondOrder_o1;
        rtb_x[2] /= rtb_IntegratorSecondOrder_o1;
        rtb_x[3] /= rtb_IntegratorSecondOrder_o1;

        /* '<S5>:1:106' */
        for (colj = 0; colj < 4; colj++) {
          dp_UKF_DW.P_p[colj] -= rtb_x[colj] * rtb_IntegratorSecondOrder_o1 *
            rtb_x[0];
          dp_UKF_DW.P_p[colj + 4] -= rtb_x[colj] * rtb_IntegratorSecondOrder_o1 *
            rtb_x[1];
          dp_UKF_DW.P_p[colj + 8] -= rtb_x[colj] * rtb_IntegratorSecondOrder_o1 *
            rtb_x[2];
          dp_UKF_DW.P_p[colj + 12] -= rtb_x[colj] * rtb_IntegratorSecondOrder_o1
            * rtb_x[3];
        }

        /* '<S5>:1:107' */
        g = dp_UKF_B.Sum - g;

        /* '<S5>:1:108' */
        rtb_x[0] = rtb_x[0] * g + dp_UKF_DW.x_p[0];
        dp_UKF_DW.x_p[0] = rtb_x[0];
        rtb_x[1] = rtb_x[1] * g + dp_UKF_DW.x_p[1];
        dp_UKF_DW.x_p[1] = rtb_x[1];
        rtb_x[2] = rtb_x[2] * g + dp_UKF_DW.x_p[2];
        dp_UKF_DW.x_p[2] = rtb_x[2];
        rtb_x[3] = rtb_x[3] * g + dp_UKF_DW.x_p[3];
        dp_UKF_DW.x_p[3] = rtb_x[3];
      }

      /* End of MATLAB Function: '<S4>/UKF_code' */

      /* Gain: '<Root>/Gain2' */
      rtb_phi1_est = dp_UKF_P.Gain2_Gain * rtb_x[0];

      /* Gain: '<Root>/Gain6' */
      rtb_phi2_est = dp_UKF_P.Gain6_Gain * rtb_x[2];

      /* Saturate: '<Root>/Saturation' */
      if (dp_UKF_B.Gain9 > dp_UKF_P.Saturation_UpperSat) {
        dp_UKF_B.Saturation = dp_UKF_P.Saturation_UpperSat;
      } else if (dp_UKF_B.Gain9 < dp_UKF_P.Saturation_LowerSat) {
        dp_UKF_B.Saturation = dp_UKF_P.Saturation_LowerSat;
      } else {
        dp_UKF_B.Saturation = dp_UKF_B.Gain9;
      }

      /* End of Saturate: '<Root>/Saturation' */
    }

    /* MATLAB Function: '<Root>/Bewegungsgleichungen' incorporates:
     *  Constant: '<Root>/para_sys'
     */
    /* MATLAB Function 'Bewegungsgleichungen': '<S2>:1' */
    /* '<S2>:1:4' */
    /* '<S2>:1:5' */
    /* '<S2>:1:6' */
    /* '<S2>:1:7' */
    /* '<S2>:1:8' */
    /* '<S2>:1:9' */
    /* '<S2>:1:10' */
    /* '<S2>:1:11' */
    /* '<S2>:1:13' */
    lambda_ukf = cos(dp_UKF_B.Sum1 - dp_UKF_B.IntegratorSecondOrder1_o1);
    dp_UKF_B.ddphi1 = ((((((((((((((dp_UKF_B.IntegratorSecondOrder_o2 *
      dp_UKF_B.IntegratorSecondOrder_o2 * 9.0 * cos(dp_UKF_B.Sum1 -
      dp_UKF_B.IntegratorSecondOrder1_o1) * sin(dp_UKF_B.Sum1 -
      dp_UKF_B.IntegratorSecondOrder1_o1) * (dp_UKF_P.para_sys_Value_g[1] *
      dp_UKF_P.para_sys_Value_g[1]) * dp_UKF_P.para_sys_Value_g[2] *
      dp_UKF_P.para_sys_Value_g[4] + 6.0 * dp_UKF_P.para_sys_Value_g[4] *
      dp_UKF_P.para_sys_Value_g[1] * (dp_UKF_P.para_sys_Value_g[2] *
      dp_UKF_P.para_sys_Value_g[2]) * sin(dp_UKF_B.Sum1 -
      dp_UKF_B.IntegratorSecondOrder1_o1) * (dp_UKF_B.IntegratorSecondOrder1_o2 *
      dp_UKF_B.IntegratorSecondOrder1_o2)) + 9.0 * dp_UKF_B.Gain9 * cos
      (dp_UKF_B.Sum1 - dp_UKF_B.IntegratorSecondOrder1_o1) * cos
      (dp_UKF_B.IntegratorSecondOrder1_o1) * dp_UKF_P.para_sys_Value_g[1] *
      dp_UKF_P.para_sys_Value_g[2] * dp_UKF_P.para_sys_Value_g[4]) + cos
      (dp_UKF_B.Sum1 - dp_UKF_B.IntegratorSecondOrder1_o1) * 9.0 * sin
      (dp_UKF_B.IntegratorSecondOrder1_o1) * dp_UKF_P.para_sys_Value_g[0] *
      dp_UKF_P.para_sys_Value_g[1] * dp_UKF_P.para_sys_Value_g[2] *
      dp_UKF_P.para_sys_Value_g[4]) - 6.0 * dp_UKF_P.para_sys_Value_g[1] * cos
      (dp_UKF_B.Sum1) * dp_UKF_B.Gain9 * dp_UKF_P.para_sys_Value_g[3] *
      dp_UKF_P.para_sys_Value_g[2]) - 12.0 * dp_UKF_P.para_sys_Value_g[1] * cos
      (dp_UKF_B.Sum1) * dp_UKF_B.Gain9 * dp_UKF_P.para_sys_Value_g[4] *
      dp_UKF_P.para_sys_Value_g[2]) - 12.0 * dp_UKF_P.para_sys_Value_g[1] * cos
      (dp_UKF_B.Sum1) * dp_UKF_B.Gain9 * dp_UKF_P.para_sys_Value_g[5] *
      dp_UKF_P.para_sys_Value_g[2]) - 6.0 * dp_UKF_P.para_sys_Value_g[1] *
      dp_UKF_P.para_sys_Value_g[0] * sin(dp_UKF_B.Sum1) *
      dp_UKF_P.para_sys_Value_g[3] * dp_UKF_P.para_sys_Value_g[2]) - 12.0 *
      dp_UKF_P.para_sys_Value_g[1] * dp_UKF_P.para_sys_Value_g[0] * sin
      (dp_UKF_B.Sum1) * dp_UKF_P.para_sys_Value_g[4] *
      dp_UKF_P.para_sys_Value_g[2]) - 12.0 * dp_UKF_P.para_sys_Value_g[1] *
      dp_UKF_P.para_sys_Value_g[0] * sin(dp_UKF_B.Sum1) *
      dp_UKF_P.para_sys_Value_g[5] * dp_UKF_P.para_sys_Value_g[2]) + 18.0 *
      dp_UKF_B.IntegratorSecondOrder_o2 * cos(dp_UKF_B.Sum1 -
      dp_UKF_B.IntegratorSecondOrder1_o1) * dp_UKF_P.para_sys_Value_g[7] *
      dp_UKF_P.para_sys_Value_g[1]) - 18.0 * dp_UKF_B.IntegratorSecondOrder1_o2 *
                          cos(dp_UKF_B.Sum1 - dp_UKF_B.IntegratorSecondOrder1_o1)
                          * dp_UKF_P.para_sys_Value_g[7] *
                          dp_UKF_P.para_sys_Value_g[1]) + 12.0 *
                         dp_UKF_B.IntegratorSecondOrder_o2 *
                         dp_UKF_P.para_sys_Value_g[6] *
                         dp_UKF_P.para_sys_Value_g[2]) + 12.0 *
                        dp_UKF_B.IntegratorSecondOrder_o2 *
                        dp_UKF_P.para_sys_Value_g[7] *
                        dp_UKF_P.para_sys_Value_g[2]) - 12.0 *
                       dp_UKF_P.para_sys_Value_g[7] *
                       dp_UKF_B.IntegratorSecondOrder1_o2 *
                       dp_UKF_P.para_sys_Value_g[2]) * (1.0 / ((((lambda_ukf *
      lambda_ukf * 9.0 * dp_UKF_P.para_sys_Value_g[4] - 4.0 *
      dp_UKF_P.para_sys_Value_g[3]) - 12.0 * dp_UKF_P.para_sys_Value_g[4]) -
      12.0 * dp_UKF_P.para_sys_Value_g[5]) * (dp_UKF_P.para_sys_Value_g[1] *
      dp_UKF_P.para_sys_Value_g[1]) * dp_UKF_P.para_sys_Value_g[2]));

    /* '<S2>:1:15' */
    lambda_ukf = cos(dp_UKF_B.Sum1 - dp_UKF_B.IntegratorSecondOrder1_o1);
    dp_UKF_B.ddphi2 = ((((((((((((((((((((((((12.0 *
      dp_UKF_B.IntegratorSecondOrder_o2 * dp_UKF_P.para_sys_Value_g[7] *
      dp_UKF_P.para_sys_Value_g[1] * dp_UKF_P.para_sys_Value_g[3] + 36.0 *
      dp_UKF_B.IntegratorSecondOrder_o2 * dp_UKF_P.para_sys_Value_g[7] *
      dp_UKF_P.para_sys_Value_g[1] * dp_UKF_P.para_sys_Value_g[4]) + 36.0 *
      dp_UKF_B.IntegratorSecondOrder_o2 * dp_UKF_P.para_sys_Value_g[7] *
      dp_UKF_P.para_sys_Value_g[1] * dp_UKF_P.para_sys_Value_g[5]) - 12.0 *
      dp_UKF_B.IntegratorSecondOrder1_o2 * dp_UKF_P.para_sys_Value_g[7] *
      dp_UKF_P.para_sys_Value_g[1] * dp_UKF_P.para_sys_Value_g[3]) - 36.0 *
      dp_UKF_B.IntegratorSecondOrder1_o2 * dp_UKF_P.para_sys_Value_g[7] *
      dp_UKF_P.para_sys_Value_g[1] * dp_UKF_P.para_sys_Value_g[4]) - 36.0 *
      dp_UKF_B.IntegratorSecondOrder1_o2 * dp_UKF_P.para_sys_Value_g[7] *
      dp_UKF_P.para_sys_Value_g[1] * dp_UKF_P.para_sys_Value_g[5]) - 9.0 * cos
      (dp_UKF_B.Sum1) * dp_UKF_B.Gain9 * cos(dp_UKF_B.Sum1 -
      dp_UKF_B.IntegratorSecondOrder1_o1) * dp_UKF_P.para_sys_Value_g[1] *
      dp_UKF_P.para_sys_Value_g[2] * dp_UKF_P.para_sys_Value_g[3] *
      dp_UKF_P.para_sys_Value_g[4]) - 18.0 * cos(dp_UKF_B.Sum1) * dp_UKF_B.Gain9
      * cos(dp_UKF_B.Sum1 - dp_UKF_B.IntegratorSecondOrder1_o1) *
      dp_UKF_P.para_sys_Value_g[1] * dp_UKF_P.para_sys_Value_g[2] *
      dp_UKF_P.para_sys_Value_g[4] * dp_UKF_P.para_sys_Value_g[5]) - cos
      (dp_UKF_B.Sum1 - dp_UKF_B.IntegratorSecondOrder1_o1) * 9.0 * sin
      (dp_UKF_B.Sum1) * dp_UKF_P.para_sys_Value_g[0] *
      dp_UKF_P.para_sys_Value_g[1] * dp_UKF_P.para_sys_Value_g[2] *
      dp_UKF_P.para_sys_Value_g[3] * dp_UKF_P.para_sys_Value_g[4]) - cos
      (dp_UKF_B.Sum1 - dp_UKF_B.IntegratorSecondOrder1_o1) * 18.0 * sin
      (dp_UKF_B.Sum1) * dp_UKF_P.para_sys_Value_g[0] *
      dp_UKF_P.para_sys_Value_g[1] * dp_UKF_P.para_sys_Value_g[2] *
      dp_UKF_P.para_sys_Value_g[4] * dp_UKF_P.para_sys_Value_g[5]) +
      dp_UKF_B.IntegratorSecondOrder1_o2 * dp_UKF_B.IntegratorSecondOrder1_o2 *
      9.0 * cos(dp_UKF_B.Sum1 - dp_UKF_B.IntegratorSecondOrder1_o1) * sin
      (dp_UKF_B.Sum1 - dp_UKF_B.IntegratorSecondOrder1_o1) *
      dp_UKF_P.para_sys_Value_g[1] * (dp_UKF_P.para_sys_Value_g[2] *
      dp_UKF_P.para_sys_Value_g[2]) * (dp_UKF_P.para_sys_Value_g[4] *
      dp_UKF_P.para_sys_Value_g[4])) + dp_UKF_B.IntegratorSecondOrder_o2 *
      dp_UKF_B.IntegratorSecondOrder_o2 * 6.0 * sin(dp_UKF_B.Sum1 -
      dp_UKF_B.IntegratorSecondOrder1_o1) * (dp_UKF_P.para_sys_Value_g[1] *
      dp_UKF_P.para_sys_Value_g[1]) * dp_UKF_P.para_sys_Value_g[2] *
      dp_UKF_P.para_sys_Value_g[3] * dp_UKF_P.para_sys_Value_g[4]) +
      dp_UKF_B.IntegratorSecondOrder_o2 * dp_UKF_B.IntegratorSecondOrder_o2 *
      18.0 * sin(dp_UKF_B.Sum1 - dp_UKF_B.IntegratorSecondOrder1_o1) *
      (dp_UKF_P.para_sys_Value_g[1] * dp_UKF_P.para_sys_Value_g[1]) *
      dp_UKF_P.para_sys_Value_g[2] * dp_UKF_P.para_sys_Value_g[4] *
      dp_UKF_P.para_sys_Value_g[5]) - 18.0 * cos(dp_UKF_B.Sum1) * dp_UKF_B.Gain9
      * cos(dp_UKF_B.Sum1 - dp_UKF_B.IntegratorSecondOrder1_o1) *
      dp_UKF_P.para_sys_Value_g[1] * dp_UKF_P.para_sys_Value_g[2] *
      (dp_UKF_P.para_sys_Value_g[4] * dp_UKF_P.para_sys_Value_g[4])) - cos
      (dp_UKF_B.Sum1 - dp_UKF_B.IntegratorSecondOrder1_o1) * 18.0 * sin
      (dp_UKF_B.Sum1) * dp_UKF_P.para_sys_Value_g[0] *
      dp_UKF_P.para_sys_Value_g[1] * dp_UKF_P.para_sys_Value_g[2] *
      (dp_UKF_P.para_sys_Value_g[4] * dp_UKF_P.para_sys_Value_g[4])) + 6.0 *
      dp_UKF_B.Gain9 * cos(dp_UKF_B.IntegratorSecondOrder1_o1) *
      dp_UKF_P.para_sys_Value_g[1] * dp_UKF_P.para_sys_Value_g[2] *
      dp_UKF_P.para_sys_Value_g[3] * dp_UKF_P.para_sys_Value_g[4]) + 18.0 *
      dp_UKF_B.Gain9 * cos(dp_UKF_B.IntegratorSecondOrder1_o1) *
      dp_UKF_P.para_sys_Value_g[1] * dp_UKF_P.para_sys_Value_g[2] *
      dp_UKF_P.para_sys_Value_g[4] * dp_UKF_P.para_sys_Value_g[5]) + 6.0 * sin
      (dp_UKF_B.IntegratorSecondOrder1_o1) * dp_UKF_P.para_sys_Value_g[0] *
      dp_UKF_P.para_sys_Value_g[1] * dp_UKF_P.para_sys_Value_g[2] *
      dp_UKF_P.para_sys_Value_g[3] * dp_UKF_P.para_sys_Value_g[4]) + 18.0 * sin
      (dp_UKF_B.IntegratorSecondOrder1_o1) * dp_UKF_P.para_sys_Value_g[0] *
      dp_UKF_P.para_sys_Value_g[1] * dp_UKF_P.para_sys_Value_g[2] *
      dp_UKF_P.para_sys_Value_g[4] * dp_UKF_P.para_sys_Value_g[5]) +
      dp_UKF_B.IntegratorSecondOrder_o2 * dp_UKF_B.IntegratorSecondOrder_o2 *
      18.0 * sin(dp_UKF_B.Sum1 - dp_UKF_B.IntegratorSecondOrder1_o1) *
      (dp_UKF_P.para_sys_Value_g[1] * dp_UKF_P.para_sys_Value_g[1]) *
      dp_UKF_P.para_sys_Value_g[2] * (dp_UKF_P.para_sys_Value_g[4] *
      dp_UKF_P.para_sys_Value_g[4])) + 18.0 * dp_UKF_B.Gain9 * cos
      (dp_UKF_B.IntegratorSecondOrder1_o1) * dp_UKF_P.para_sys_Value_g[1] *
      dp_UKF_P.para_sys_Value_g[2] * (dp_UKF_P.para_sys_Value_g[4] *
      dp_UKF_P.para_sys_Value_g[4])) + 18.0 * sin
                          (dp_UKF_B.IntegratorSecondOrder1_o1) *
                          dp_UKF_P.para_sys_Value_g[0] *
                          dp_UKF_P.para_sys_Value_g[1] *
                          dp_UKF_P.para_sys_Value_g[2] *
                          (dp_UKF_P.para_sys_Value_g[4] *
      dp_UKF_P.para_sys_Value_g[4])) + 18.0 * dp_UKF_B.IntegratorSecondOrder_o2 *
                         cos(dp_UKF_B.Sum1 - dp_UKF_B.IntegratorSecondOrder1_o1)
                         * dp_UKF_P.para_sys_Value_g[6] *
                         dp_UKF_P.para_sys_Value_g[2] *
                         dp_UKF_P.para_sys_Value_g[4]) + 18.0 *
                        dp_UKF_B.IntegratorSecondOrder_o2 * cos(dp_UKF_B.Sum1 -
      dp_UKF_B.IntegratorSecondOrder1_o1) * dp_UKF_P.para_sys_Value_g[7] *
                        dp_UKF_P.para_sys_Value_g[2] *
                        dp_UKF_P.para_sys_Value_g[4]) - 18.0 *
                       dp_UKF_B.IntegratorSecondOrder1_o2 * cos(dp_UKF_B.Sum1 -
      dp_UKF_B.IntegratorSecondOrder1_o1) * dp_UKF_P.para_sys_Value_g[7] *
                       dp_UKF_P.para_sys_Value_g[2] * dp_UKF_P.para_sys_Value_g
                       [4]) * (-1.0 / ((((lambda_ukf * lambda_ukf * 9.0 *
      dp_UKF_P.para_sys_Value_g[4] - 4.0 * dp_UKF_P.para_sys_Value_g[3]) - 12.0 *
      dp_UKF_P.para_sys_Value_g[4]) - 12.0 * dp_UKF_P.para_sys_Value_g[5]) *
      (dp_UKF_P.para_sys_Value_g[2] * dp_UKF_P.para_sys_Value_g[2] *
       dp_UKF_P.para_sys_Value_g[1]) * dp_UKF_P.para_sys_Value_g[4]));
    if (rtmIsMajorTimeStep(dp_UKF_M)) {
    }
  }

  if (rtmIsMajorTimeStep(dp_UKF_M)) {
    /* Matfile logging */
    rt_UpdateTXYLogVars(dp_UKF_M->rtwLogInfo, (dp_UKF_M->Timing.t));
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(dp_UKF_M)) {
    boolean_T resetSolver;
    int32_T uMode;

    /* Update for SecondOrderIntegrator: '<Root>/Integrator, Second-Order2' */
    resetSolver = false;
    uMode = dp_UKF_DW.IntegratorSecondOrder2_MODE;
    if ((((dp_UKF_DW.IntegratorSecondOrder2_MODE == 1) ||
          (dp_UKF_DW.IntegratorSecondOrder2_MODE == 3)) && (dp_UKF_B.Saturation >
          0.0)) || (((dp_UKF_DW.IntegratorSecondOrder2_MODE == 2) ||
                     (dp_UKF_DW.IntegratorSecondOrder2_MODE == 4)) &&
                    (dp_UKF_B.Saturation < 0.0))) {
      uMode = 0;
    }

    if (dp_UKF_DW.IntegratorSecondOrder2_MODE != uMode) {
      dp_UKF_DW.IntegratorSecondOrder2_MODE = uMode;
      resetSolver = true;
    }

    if (resetSolver) {
      rtsiSetSolverNeedsReset(&dp_UKF_M->solverInfo, true);
    }

    /* End of Update for SecondOrderIntegrator: '<Root>/Integrator, Second-Order2' */
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(dp_UKF_M)) {
    /* signal main to stop simulation */
    {                                  /* Sample time: [0.0s, 0.0s] */
      if ((rtmGetTFinal(dp_UKF_M)!=-1) &&
          !((rtmGetTFinal(dp_UKF_M)-(((dp_UKF_M->Timing.clockTick1+
               dp_UKF_M->Timing.clockTickH1* 4294967296.0)) * 0.001)) >
            (((dp_UKF_M->Timing.clockTick1+dp_UKF_M->Timing.clockTickH1*
               4294967296.0)) * 0.001) * (DBL_EPSILON))) {
        rtmSetErrorStatus(dp_UKF_M, "Simulation finished");
      }
    }

    rt_ertODEUpdateContinuousStates(&dp_UKF_M->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick0 and the high bits
     * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++dp_UKF_M->Timing.clockTick0)) {
      ++dp_UKF_M->Timing.clockTickH0;
    }

    dp_UKF_M->Timing.t[0] = rtsiGetSolverStopTime(&dp_UKF_M->solverInfo);

    {
      /* Update absolute timer for sample time: [0.001s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.001, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       * Timer of this task consists of two 32 bit unsigned integers.
       * The two integers represent the low bits Timing.clockTick1 and the high bits
       * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
       */
      dp_UKF_M->Timing.clockTick1++;
      if (!dp_UKF_M->Timing.clockTick1) {
        dp_UKF_M->Timing.clockTickH1++;
      }
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void dp_UKF_derivatives(void)
{
  XDot_dp_UKF_T *_rtXdot;
  _rtXdot = ((XDot_dp_UKF_T *) dp_UKF_M->ModelData.derivs);

  /* Derivatives for SecondOrderIntegrator: '<Root>/Integrator, Second-Order' */
  if (dp_UKF_DW.IntegratorSecondOrder_MODE == 0) {
    _rtXdot->IntegratorSecondOrder_CSTATE[0] =
      dp_UKF_X.IntegratorSecondOrder_CSTATE[1];
    _rtXdot->IntegratorSecondOrder_CSTATE[1] = dp_UKF_B.ddphi1;
  }

  /* End of Derivatives for SecondOrderIntegrator: '<Root>/Integrator, Second-Order' */

  /* Derivatives for SecondOrderIntegrator: '<Root>/Integrator, Second-Order2' */
  switch (dp_UKF_DW.IntegratorSecondOrder2_MODE) {
   case 0:
    _rtXdot->IntegratorSecondOrder2_CSTATE[0] =
      dp_UKF_X.IntegratorSecondOrder2_CSTATE[1];
    _rtXdot->IntegratorSecondOrder2_CSTATE[1] = dp_UKF_B.Saturation;
    break;

   case 3:
    _rtXdot->IntegratorSecondOrder2_CSTATE[0] =
      dp_UKF_X.IntegratorSecondOrder2_CSTATE[1];
    _rtXdot->IntegratorSecondOrder2_CSTATE[1] = 0.0;
    break;

   case 4:
    _rtXdot->IntegratorSecondOrder2_CSTATE[0] =
      dp_UKF_X.IntegratorSecondOrder2_CSTATE[1];
    _rtXdot->IntegratorSecondOrder2_CSTATE[1] = 0.0;
    break;

   case 1:
    _rtXdot->IntegratorSecondOrder2_CSTATE[0] = 0.0;
    _rtXdot->IntegratorSecondOrder2_CSTATE[1] = 0.0;
    break;

   case 2:
    _rtXdot->IntegratorSecondOrder2_CSTATE[0] = 0.0;
    _rtXdot->IntegratorSecondOrder2_CSTATE[1] = 0.0;
    break;
  }

  /* End of Derivatives for SecondOrderIntegrator: '<Root>/Integrator, Second-Order2' */

  /* Derivatives for SecondOrderIntegrator: '<Root>/Integrator, Second-Order1' */
  if (dp_UKF_DW.IntegratorSecondOrder1_MODE == 0) {
    _rtXdot->IntegratorSecondOrder1_CSTATE[0] =
      dp_UKF_X.IntegratorSecondOrder1_CSTATE[1];
    _rtXdot->IntegratorSecondOrder1_CSTATE[1] = dp_UKF_B.ddphi2;
  }

  /* End of Derivatives for SecondOrderIntegrator: '<Root>/Integrator, Second-Order1' */
}

/* Model initialize function */
void dp_UKF_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)dp_UKF_M, 0,
                sizeof(RT_MODEL_dp_UKF_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&dp_UKF_M->solverInfo, &dp_UKF_M->Timing.simTimeStep);
    rtsiSetTPtr(&dp_UKF_M->solverInfo, &rtmGetTPtr(dp_UKF_M));
    rtsiSetStepSizePtr(&dp_UKF_M->solverInfo, &dp_UKF_M->Timing.stepSize0);
    rtsiSetdXPtr(&dp_UKF_M->solverInfo, &dp_UKF_M->ModelData.derivs);
    rtsiSetContStatesPtr(&dp_UKF_M->solverInfo, (real_T **)
                         &dp_UKF_M->ModelData.contStates);
    rtsiSetNumContStatesPtr(&dp_UKF_M->solverInfo,
      &dp_UKF_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&dp_UKF_M->solverInfo,
      &dp_UKF_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&dp_UKF_M->solverInfo,
      &dp_UKF_M->ModelData.periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&dp_UKF_M->solverInfo,
      &dp_UKF_M->ModelData.periodicContStateRanges);
    rtsiSetErrorStatusPtr(&dp_UKF_M->solverInfo, (&rtmGetErrorStatus(dp_UKF_M)));
    rtsiSetRTModelPtr(&dp_UKF_M->solverInfo, dp_UKF_M);
  }

  rtsiSetSimTimeStep(&dp_UKF_M->solverInfo, MAJOR_TIME_STEP);
  dp_UKF_M->ModelData.intgData.y = dp_UKF_M->ModelData.odeY;
  dp_UKF_M->ModelData.intgData.f[0] = dp_UKF_M->ModelData.odeF[0];
  dp_UKF_M->ModelData.intgData.f[1] = dp_UKF_M->ModelData.odeF[1];
  dp_UKF_M->ModelData.intgData.f[2] = dp_UKF_M->ModelData.odeF[2];
  dp_UKF_M->ModelData.contStates = ((X_dp_UKF_T *) &dp_UKF_X);
  rtsiSetSolverData(&dp_UKF_M->solverInfo, (void *)&dp_UKF_M->ModelData.intgData);
  rtsiSetSolverName(&dp_UKF_M->solverInfo,"ode3");
  rtmSetTPtr(dp_UKF_M, &dp_UKF_M->Timing.tArray[0]);
  rtmSetTFinal(dp_UKF_M, 5.0);
  dp_UKF_M->Timing.stepSize0 = 0.001;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    rt_DataLoggingInfo.loggingInterval = NULL;
    dp_UKF_M->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(dp_UKF_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(dp_UKF_M->rtwLogInfo, (NULL));
    rtliSetLogT(dp_UKF_M->rtwLogInfo, "tout");
    rtliSetLogX(dp_UKF_M->rtwLogInfo, "");
    rtliSetLogXFinal(dp_UKF_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(dp_UKF_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(dp_UKF_M->rtwLogInfo, 4);
    rtliSetLogMaxRows(dp_UKF_M->rtwLogInfo, 1000);
    rtliSetLogDecimation(dp_UKF_M->rtwLogInfo, 1);
    rtliSetLogY(dp_UKF_M->rtwLogInfo, "");
    rtliSetLogYSignalInfo(dp_UKF_M->rtwLogInfo, (NULL));
    rtliSetLogYSignalPtrs(dp_UKF_M->rtwLogInfo, (NULL));
  }

  /* block I/O */
  (void) memset(((void *) &dp_UKF_B), 0,
                sizeof(B_dp_UKF_T));

  /* states (continuous) */
  {
    (void) memset((void *)&dp_UKF_X, 0,
                  sizeof(X_dp_UKF_T));
  }

  /* states (dwork) */
  (void) memset((void *)&dp_UKF_DW, 0,
                sizeof(DW_dp_UKF_T));

  /* Matfile logging */
  rt_StartDataLoggingWithStartTime(dp_UKF_M->rtwLogInfo, 0.0, rtmGetTFinal
    (dp_UKF_M), dp_UKF_M->Timing.stepSize0, (&rtmGetErrorStatus(dp_UKF_M)));

  /* InitializeConditions for SecondOrderIntegrator: '<Root>/Integrator, Second-Order' */
  dp_UKF_X.IntegratorSecondOrder_CSTATE[0] = dp_UKF_P.phi1_0;
  dp_UKF_X.IntegratorSecondOrder_CSTATE[1] = dp_UKF_P.dphi1_0;
  dp_UKF_DW.IntegratorSecondOrder_MODE = 0;

  /* InitializeConditions for SecondOrderIntegrator: '<Root>/Integrator, Second-Order2' */
  dp_UKF_X.IntegratorSecondOrder2_CSTATE[0] = dp_UKF_P.x_0;
  dp_UKF_X.IntegratorSecondOrder2_CSTATE[1] = dp_UKF_P.dx_0;
  dp_UKF_DW.IntegratorSecondOrder2_MODE = 0;

  /* InitializeConditions for SecondOrderIntegrator: '<Root>/Integrator, Second-Order1' */
  dp_UKF_X.IntegratorSecondOrder1_CSTATE[0] = dp_UKF_P.phi2_0;
  dp_UKF_X.IntegratorSecondOrder1_CSTATE[1] = dp_UKF_P.dphi2_0;
  dp_UKF_DW.IntegratorSecondOrder1_MODE = 0;

  /* InitializeConditions for MATLAB Function: '<S4>/UKF_code' */
  dp_UKF_DW.x_p_not_empty = false;
  dp_UKF_DW.P_p_not_empty = false;
  dp_UKF_DW.x0_sig_not_empty = false;
  dp_UKF_DW.x_sig_not_empty = false;
  dp_UKF_DW.W_m_not_empty = false;
  dp_UKF_DW.W_c_not_empty = false;
}

/* Model terminate function */
void dp_UKF_terminate(void)
{
  /* (no terminate code required) */
}
