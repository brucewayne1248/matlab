#ifndef __c2_dp_EKF_h__
#define __c2_dp_EKF_h__

/* Include files */
#include "sf_runtime/sfc_sf.h"
#include "sf_runtime/sfc_mex.h"
#include "rtwtypes.h"
#include "multiword_types.h"

/* Type Definitions */
#ifndef typedef_SFc2_dp_EKFInstanceStruct
#define typedef_SFc2_dp_EKFInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c2_sfEvent;
  boolean_T c2_isStable;
  boolean_T c2_doneDoubleBufferReInit;
  uint8_T c2_is_active_c2_dp_EKF;
  real_T c2_x_p[4];
  boolean_T c2_x_p_not_empty;
  real_T c2_P_p[16];
  boolean_T c2_P_p_not_empty;
  real_T (*c2_P)[16];
  real_T (*c2_Q)[16];
  real_T *c2_R;
  real_T (*c2_x0)[4];
  real_T (*c2_para_sys)[8];
  real_T *c2_T_s;
  real_T *c2_u;
  real_T *c2_y;
  real_T (*c2_x)[4];
  real_T (*c2_K)[4];
} SFc2_dp_EKFInstanceStruct;

#endif                                 /*typedef_SFc2_dp_EKFInstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c2_dp_EKF_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c2_dp_EKF_get_check_sum(mxArray *plhs[]);
extern void c2_dp_EKF_method_dispatcher(SimStruct *S, int_T method, void *data);

#endif
