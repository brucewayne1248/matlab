#ifndef __c5_dp_statefeedback_h__
#define __c5_dp_statefeedback_h__

/* Include files */
#include "sf_runtime/sfc_sf.h"
#include "sf_runtime/sfc_mex.h"
#include "rtwtypes.h"
#include "multiword_types.h"

/* Type Definitions */
#ifndef typedef_SFc5_dp_statefeedbackInstanceStruct
#define typedef_SFc5_dp_statefeedbackInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c5_sfEvent;
  boolean_T c5_isStable;
  boolean_T c5_doneDoubleBufferReInit;
  uint8_T c5_is_active_c5_dp_statefeedback;
  real_T *c5_u;
  real_T *c5_phi1;
  real_T *c5_dphi1;
  real_T *c5_phi2;
  real_T *c5_dphi2;
  real_T (*c5_para_sys)[8];
  real_T *c5_ddphi1;
  real_T *c5_ddphi2;
} SFc5_dp_statefeedbackInstanceStruct;

#endif                                 /*typedef_SFc5_dp_statefeedbackInstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c5_dp_statefeedback_get_eml_resolved_functions_info
  (void);

/* Function Definitions */
extern void sf_c5_dp_statefeedback_get_check_sum(mxArray *plhs[]);
extern void c5_dp_statefeedback_method_dispatcher(SimStruct *S, int_T method,
  void *data);

#endif
