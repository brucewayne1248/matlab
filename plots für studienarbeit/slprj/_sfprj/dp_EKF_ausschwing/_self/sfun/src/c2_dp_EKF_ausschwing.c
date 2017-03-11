/* Include files */

#include <stddef.h>
#include "blas.h"
#include "dp_EKF_ausschwing_sfun.h"
#include "c2_dp_EKF_ausschwing.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "dp_EKF_ausschwing_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static real_T _sfTime_;
static const char * c2_debug_family_names[28] = { "g", "l_1", "l_2", "m_1",
  "m_2", "m_3", "d_p1", "d_p2", "x_1", "x_2", "x_3", "x_4", "A", "C", "nargin",
  "nargout", "P", "Q", "R", "x0", "para_sys", "T_s", "u", "y", "x", "K", "x_p",
  "P_p" };

/* Function Declarations */
static void initialize_c2_dp_EKF_ausschwing(SFc2_dp_EKF_ausschwingInstanceStruct
  *chartInstance);
static void initialize_params_c2_dp_EKF_ausschwing
  (SFc2_dp_EKF_ausschwingInstanceStruct *chartInstance);
static void enable_c2_dp_EKF_ausschwing(SFc2_dp_EKF_ausschwingInstanceStruct
  *chartInstance);
static void disable_c2_dp_EKF_ausschwing(SFc2_dp_EKF_ausschwingInstanceStruct
  *chartInstance);
static void c2_update_debugger_state_c2_dp_EKF_ausschwing
  (SFc2_dp_EKF_ausschwingInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c2_dp_EKF_ausschwing
  (SFc2_dp_EKF_ausschwingInstanceStruct *chartInstance);
static void set_sim_state_c2_dp_EKF_ausschwing
  (SFc2_dp_EKF_ausschwingInstanceStruct *chartInstance, const mxArray *c2_st);
static void finalize_c2_dp_EKF_ausschwing(SFc2_dp_EKF_ausschwingInstanceStruct
  *chartInstance);
static void sf_gateway_c2_dp_EKF_ausschwing(SFc2_dp_EKF_ausschwingInstanceStruct
  *chartInstance);
static void mdl_start_c2_dp_EKF_ausschwing(SFc2_dp_EKF_ausschwingInstanceStruct *
  chartInstance);
static void c2_chartstep_c2_dp_EKF_ausschwing
  (SFc2_dp_EKF_ausschwingInstanceStruct *chartInstance);
static void initSimStructsc2_dp_EKF_ausschwing
  (SFc2_dp_EKF_ausschwingInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber, uint32_T c2_instanceNumber);
static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, void *c2_inData);
static void c2_emlrt_marshallIn(SFc2_dp_EKF_ausschwingInstanceStruct
  *chartInstance, const mxArray *c2_b_P_p, const char_T *c2_identifier, real_T
  c2_b_y[16]);
static void c2_b_emlrt_marshallIn(SFc2_dp_EKF_ausschwingInstanceStruct
  *chartInstance, const mxArray *c2_b_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_b_y[16]);
static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_c_emlrt_marshallIn(SFc2_dp_EKF_ausschwingInstanceStruct
  *chartInstance, const mxArray *c2_b_x_p, const char_T *c2_identifier, real_T
  c2_b_y[4]);
static void c2_d_emlrt_marshallIn(SFc2_dp_EKF_ausschwingInstanceStruct
  *chartInstance, const mxArray *c2_b_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_b_y[4]);
static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_c_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_e_emlrt_marshallIn(SFc2_dp_EKF_ausschwingInstanceStruct
  *chartInstance, const mxArray *c2_b_K, const char_T *c2_identifier, real_T
  c2_b_y[4]);
static void c2_f_emlrt_marshallIn(SFc2_dp_EKF_ausschwingInstanceStruct
  *chartInstance, const mxArray *c2_b_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_b_y[4]);
static void c2_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_d_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static const mxArray *c2_e_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static const mxArray *c2_f_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static real_T c2_g_emlrt_marshallIn(SFc2_dp_EKF_ausschwingInstanceStruct
  *chartInstance, const mxArray *c2_b_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_g_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_h_emlrt_marshallIn(SFc2_dp_EKF_ausschwingInstanceStruct
  *chartInstance, const mxArray *c2_b_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_b_y[16]);
static void c2_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static void c2_info_helper(const mxArray **c2_info);
static const mxArray *c2_emlrt_marshallOut(const char * c2_b_u);
static const mxArray *c2_b_emlrt_marshallOut(const uint32_T c2_b_u);
static void c2_b_info_helper(const mxArray **c2_info);
static real_T c2_mpower(SFc2_dp_EKF_ausschwingInstanceStruct *chartInstance,
  real_T c2_a);
static void c2_eml_scalar_eg(SFc2_dp_EKF_ausschwingInstanceStruct *chartInstance);
static void c2_b_eml_scalar_eg(SFc2_dp_EKF_ausschwingInstanceStruct
  *chartInstance);
static void c2_threshold(SFc2_dp_EKF_ausschwingInstanceStruct *chartInstance);
static void c2_c_eml_scalar_eg(SFc2_dp_EKF_ausschwingInstanceStruct
  *chartInstance);
static void c2_d_eml_scalar_eg(SFc2_dp_EKF_ausschwingInstanceStruct
  *chartInstance);
static real_T c2_eml_xdotu(SFc2_dp_EKF_ausschwingInstanceStruct *chartInstance,
  real_T c2_b_x[4], real_T c2_b_y[4]);
static void c2_eye(SFc2_dp_EKF_ausschwingInstanceStruct *chartInstance, real_T
                   c2_I[16]);
static const mxArray *c2_h_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static int32_T c2_i_emlrt_marshallIn(SFc2_dp_EKF_ausschwingInstanceStruct
  *chartInstance, const mxArray *c2_b_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static uint8_T c2_j_emlrt_marshallIn(SFc2_dp_EKF_ausschwingInstanceStruct
  *chartInstance, const mxArray *c2_b_is_active_c2_dp_EKF_ausschwing, const
  char_T *c2_identifier);
static uint8_T c2_k_emlrt_marshallIn(SFc2_dp_EKF_ausschwingInstanceStruct
  *chartInstance, const mxArray *c2_b_u, const emlrtMsgIdentifier *c2_parentId);
static void init_dsm_address_info(SFc2_dp_EKF_ausschwingInstanceStruct
  *chartInstance);
static void init_simulink_io_address(SFc2_dp_EKF_ausschwingInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c2_dp_EKF_ausschwing(SFc2_dp_EKF_ausschwingInstanceStruct
  *chartInstance)
{
  chartInstance->c2_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c2_x_p_not_empty = false;
  chartInstance->c2_P_p_not_empty = false;
  chartInstance->c2_is_active_c2_dp_EKF_ausschwing = 0U;
}

static void initialize_params_c2_dp_EKF_ausschwing
  (SFc2_dp_EKF_ausschwingInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void enable_c2_dp_EKF_ausschwing(SFc2_dp_EKF_ausschwingInstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c2_dp_EKF_ausschwing(SFc2_dp_EKF_ausschwingInstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c2_update_debugger_state_c2_dp_EKF_ausschwing
  (SFc2_dp_EKF_ausschwingInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *get_sim_state_c2_dp_EKF_ausschwing
  (SFc2_dp_EKF_ausschwingInstanceStruct *chartInstance)
{
  const mxArray *c2_st;
  const mxArray *c2_b_y = NULL;
  int32_T c2_i0;
  real_T c2_b_u[4];
  const mxArray *c2_c_y = NULL;
  int32_T c2_i1;
  real_T c2_c_u[4];
  const mxArray *c2_d_y = NULL;
  int32_T c2_i2;
  real_T c2_d_u[16];
  const mxArray *c2_e_y = NULL;
  int32_T c2_i3;
  real_T c2_e_u[4];
  const mxArray *c2_f_y = NULL;
  uint8_T c2_hoistedGlobal;
  uint8_T c2_f_u;
  const mxArray *c2_g_y = NULL;
  c2_st = NULL;
  c2_st = NULL;
  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_createcellmatrix(5, 1), false);
  for (c2_i0 = 0; c2_i0 < 4; c2_i0++) {
    c2_b_u[c2_i0] = (*chartInstance->c2_K)[c2_i0];
  }

  c2_c_y = NULL;
  sf_mex_assign(&c2_c_y, sf_mex_create("y", c2_b_u, 0, 0U, 1U, 0U, 1, 4), false);
  sf_mex_setcell(c2_b_y, 0, c2_c_y);
  for (c2_i1 = 0; c2_i1 < 4; c2_i1++) {
    c2_c_u[c2_i1] = (*chartInstance->c2_x)[c2_i1];
  }

  c2_d_y = NULL;
  sf_mex_assign(&c2_d_y, sf_mex_create("y", c2_c_u, 0, 0U, 1U, 0U, 1, 4), false);
  sf_mex_setcell(c2_b_y, 1, c2_d_y);
  for (c2_i2 = 0; c2_i2 < 16; c2_i2++) {
    c2_d_u[c2_i2] = chartInstance->c2_P_p[c2_i2];
  }

  c2_e_y = NULL;
  if (!chartInstance->c2_P_p_not_empty) {
    sf_mex_assign(&c2_e_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c2_e_y, sf_mex_create("y", c2_d_u, 0, 0U, 1U, 0U, 2, 4, 4),
                  false);
  }

  sf_mex_setcell(c2_b_y, 2, c2_e_y);
  for (c2_i3 = 0; c2_i3 < 4; c2_i3++) {
    c2_e_u[c2_i3] = chartInstance->c2_x_p[c2_i3];
  }

  c2_f_y = NULL;
  if (!chartInstance->c2_x_p_not_empty) {
    sf_mex_assign(&c2_f_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c2_f_y, sf_mex_create("y", c2_e_u, 0, 0U, 1U, 0U, 1, 4),
                  false);
  }

  sf_mex_setcell(c2_b_y, 3, c2_f_y);
  c2_hoistedGlobal = chartInstance->c2_is_active_c2_dp_EKF_ausschwing;
  c2_f_u = c2_hoistedGlobal;
  c2_g_y = NULL;
  sf_mex_assign(&c2_g_y, sf_mex_create("y", &c2_f_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c2_b_y, 4, c2_g_y);
  sf_mex_assign(&c2_st, c2_b_y, false);
  return c2_st;
}

static void set_sim_state_c2_dp_EKF_ausschwing
  (SFc2_dp_EKF_ausschwingInstanceStruct *chartInstance, const mxArray *c2_st)
{
  const mxArray *c2_b_u;
  real_T c2_dv0[4];
  int32_T c2_i4;
  real_T c2_dv1[4];
  int32_T c2_i5;
  real_T c2_dv2[16];
  int32_T c2_i6;
  real_T c2_dv3[4];
  int32_T c2_i7;
  chartInstance->c2_doneDoubleBufferReInit = true;
  c2_b_u = sf_mex_dup(c2_st);
  c2_e_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c2_b_u, 0)),
                        "K", c2_dv0);
  for (c2_i4 = 0; c2_i4 < 4; c2_i4++) {
    (*chartInstance->c2_K)[c2_i4] = c2_dv0[c2_i4];
  }

  c2_e_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c2_b_u, 1)),
                        "x", c2_dv1);
  for (c2_i5 = 0; c2_i5 < 4; c2_i5++) {
    (*chartInstance->c2_x)[c2_i5] = c2_dv1[c2_i5];
  }

  c2_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c2_b_u, 2)),
                      "P_p", c2_dv2);
  for (c2_i6 = 0; c2_i6 < 16; c2_i6++) {
    chartInstance->c2_P_p[c2_i6] = c2_dv2[c2_i6];
  }

  c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c2_b_u, 3)),
                        "x_p", c2_dv3);
  for (c2_i7 = 0; c2_i7 < 4; c2_i7++) {
    chartInstance->c2_x_p[c2_i7] = c2_dv3[c2_i7];
  }

  chartInstance->c2_is_active_c2_dp_EKF_ausschwing = c2_j_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c2_b_u, 4)),
     "is_active_c2_dp_EKF_ausschwing");
  sf_mex_destroy(&c2_b_u);
  c2_update_debugger_state_c2_dp_EKF_ausschwing(chartInstance);
  sf_mex_destroy(&c2_st);
}

static void finalize_c2_dp_EKF_ausschwing(SFc2_dp_EKF_ausschwingInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void sf_gateway_c2_dp_EKF_ausschwing(SFc2_dp_EKF_ausschwingInstanceStruct
  *chartInstance)
{
  int32_T c2_i8;
  int32_T c2_i9;
  int32_T c2_i10;
  int32_T c2_i11;
  int32_T c2_i12;
  int32_T c2_i13;
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 0U, chartInstance->c2_sfEvent);
  for (c2_i8 = 0; c2_i8 < 16; c2_i8++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c2_P)[c2_i8], 0U);
  }

  for (c2_i9 = 0; c2_i9 < 16; c2_i9++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c2_Q)[c2_i9], 1U);
  }

  _SFD_DATA_RANGE_CHECK(*chartInstance->c2_R, 2U);
  for (c2_i10 = 0; c2_i10 < 4; c2_i10++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c2_x0)[c2_i10], 3U);
  }

  for (c2_i11 = 0; c2_i11 < 8; c2_i11++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c2_para_sys)[c2_i11], 4U);
  }

  _SFD_DATA_RANGE_CHECK(*chartInstance->c2_T_s, 5U);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c2_u, 6U);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c2_y, 7U);
  chartInstance->c2_sfEvent = CALL_EVENT;
  c2_chartstep_c2_dp_EKF_ausschwing(chartInstance);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_dp_EKF_ausschwingMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
  for (c2_i12 = 0; c2_i12 < 4; c2_i12++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c2_x)[c2_i12], 8U);
  }

  for (c2_i13 = 0; c2_i13 < 4; c2_i13++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c2_K)[c2_i13], 9U);
  }
}

static void mdl_start_c2_dp_EKF_ausschwing(SFc2_dp_EKF_ausschwingInstanceStruct *
  chartInstance)
{
  (void)chartInstance;
}

static void c2_chartstep_c2_dp_EKF_ausschwing
  (SFc2_dp_EKF_ausschwingInstanceStruct *chartInstance)
{
  real_T c2_hoistedGlobal;
  real_T c2_b_hoistedGlobal;
  real_T c2_c_hoistedGlobal;
  real_T c2_d_hoistedGlobal;
  int32_T c2_i14;
  real_T c2_b_P[16];
  int32_T c2_i15;
  real_T c2_b_Q[16];
  real_T c2_b_R;
  int32_T c2_i16;
  real_T c2_b_x0[4];
  int32_T c2_i17;
  real_T c2_b_para_sys[8];
  real_T c2_b_T_s;
  real_T c2_b_u;
  real_T c2_b_y;
  uint32_T c2_debug_family_var_map[28];
  real_T c2_g;
  real_T c2_l_1;
  real_T c2_l_2;
  real_T c2_m_1;
  real_T c2_m_2;
  real_T c2_m_3;
  real_T c2_d_p1;
  real_T c2_d_p2;
  real_T c2_x_1;
  real_T c2_x_2;
  real_T c2_x_3;
  real_T c2_x_4;
  real_T c2_A[16];
  real_T c2_C[4];
  real_T c2_nargin = 8.0;
  real_T c2_nargout = 2.0;
  real_T c2_b_x[4];
  real_T c2_b_K[4];
  int32_T c2_i18;
  int32_T c2_i19;
  int32_T c2_i20;
  int32_T c2_i21;
  real_T c2_c_x;
  real_T c2_d_x;
  real_T c2_e_x;
  real_T c2_f_x;
  real_T c2_g_x;
  real_T c2_h_x;
  real_T c2_i_x;
  real_T c2_j_x;
  real_T c2_k_x;
  real_T c2_l_x;
  real_T c2_m_x;
  real_T c2_n_x;
  real_T c2_o_x;
  real_T c2_p_x;
  real_T c2_q_x;
  real_T c2_r_x;
  real_T c2_s_x;
  real_T c2_t_x;
  real_T c2_u_x;
  real_T c2_v_x;
  real_T c2_w_x;
  real_T c2_x_x;
  real_T c2_y_x;
  real_T c2_ab_x;
  real_T c2_b_A;
  real_T c2_B;
  real_T c2_bb_x;
  real_T c2_c_y;
  real_T c2_cb_x;
  real_T c2_d_y;
  real_T c2_db_x;
  real_T c2_e_y;
  real_T c2_f_y;
  real_T c2_eb_x;
  real_T c2_fb_x;
  real_T c2_gb_x;
  real_T c2_hb_x;
  real_T c2_ib_x;
  real_T c2_jb_x;
  real_T c2_kb_x;
  real_T c2_lb_x;
  real_T c2_mb_x;
  real_T c2_nb_x;
  real_T c2_ob_x;
  real_T c2_pb_x;
  real_T c2_qb_x;
  real_T c2_rb_x;
  real_T c2_sb_x;
  real_T c2_tb_x;
  real_T c2_ub_x;
  real_T c2_vb_x;
  real_T c2_wb_x;
  real_T c2_xb_x;
  real_T c2_yb_x;
  real_T c2_ac_x;
  real_T c2_bc_x;
  real_T c2_cc_x;
  real_T c2_dc_x;
  real_T c2_ec_x;
  real_T c2_fc_x;
  real_T c2_gc_x;
  real_T c2_hc_x;
  real_T c2_ic_x;
  real_T c2_jc_x;
  real_T c2_kc_x;
  real_T c2_lc_x;
  real_T c2_mc_x;
  real_T c2_nc_x;
  real_T c2_oc_x;
  real_T c2_c_A;
  real_T c2_b_B;
  real_T c2_pc_x;
  real_T c2_g_y;
  real_T c2_qc_x;
  real_T c2_h_y;
  real_T c2_rc_x;
  real_T c2_i_y;
  real_T c2_j_y;
  real_T c2_sc_x;
  real_T c2_tc_x;
  real_T c2_uc_x;
  real_T c2_vc_x;
  real_T c2_wc_x;
  real_T c2_xc_x;
  real_T c2_yc_x;
  real_T c2_ad_x;
  real_T c2_bd_x;
  real_T c2_cd_x;
  real_T c2_dd_x;
  real_T c2_ed_x;
  real_T c2_fd_x;
  real_T c2_gd_x;
  real_T c2_hd_x;
  real_T c2_id_x;
  real_T c2_jd_x;
  real_T c2_kd_x;
  real_T c2_ld_x;
  real_T c2_md_x;
  real_T c2_nd_x;
  real_T c2_od_x;
  real_T c2_pd_x;
  real_T c2_qd_x;
  real_T c2_rd_x;
  real_T c2_sd_x;
  real_T c2_d_A;
  real_T c2_c_B;
  real_T c2_td_x;
  real_T c2_k_y;
  real_T c2_ud_x;
  real_T c2_l_y;
  real_T c2_vd_x;
  real_T c2_m_y;
  real_T c2_n_y;
  real_T c2_wd_x;
  real_T c2_xd_x;
  real_T c2_yd_x;
  real_T c2_ae_x;
  real_T c2_be_x;
  real_T c2_ce_x;
  real_T c2_de_x;
  real_T c2_ee_x;
  real_T c2_fe_x;
  real_T c2_ge_x;
  real_T c2_he_x;
  real_T c2_ie_x;
  real_T c2_je_x;
  real_T c2_ke_x;
  real_T c2_le_x;
  real_T c2_me_x;
  real_T c2_ne_x;
  real_T c2_oe_x;
  real_T c2_pe_x;
  real_T c2_qe_x;
  real_T c2_re_x;
  real_T c2_se_x;
  real_T c2_te_x;
  real_T c2_ue_x;
  real_T c2_ve_x;
  real_T c2_we_x;
  real_T c2_xe_x;
  real_T c2_ye_x;
  real_T c2_e_A;
  real_T c2_d_B;
  real_T c2_af_x;
  real_T c2_o_y;
  real_T c2_bf_x;
  real_T c2_p_y;
  real_T c2_cf_x;
  real_T c2_q_y;
  real_T c2_r_y;
  real_T c2_df_x;
  real_T c2_ef_x;
  real_T c2_ff_x;
  real_T c2_gf_x;
  real_T c2_hf_x;
  real_T c2_if_x;
  real_T c2_f_A;
  real_T c2_e_B;
  real_T c2_jf_x;
  real_T c2_s_y;
  real_T c2_kf_x;
  real_T c2_t_y;
  real_T c2_lf_x;
  real_T c2_u_y;
  real_T c2_v_y;
  real_T c2_mf_x;
  real_T c2_nf_x;
  real_T c2_of_x;
  real_T c2_pf_x;
  real_T c2_qf_x;
  real_T c2_rf_x;
  real_T c2_sf_x;
  real_T c2_tf_x;
  real_T c2_uf_x;
  real_T c2_vf_x;
  real_T c2_wf_x;
  real_T c2_xf_x;
  real_T c2_yf_x;
  real_T c2_ag_x;
  real_T c2_bg_x;
  real_T c2_cg_x;
  real_T c2_dg_x;
  real_T c2_eg_x;
  real_T c2_fg_x;
  real_T c2_gg_x;
  real_T c2_g_A;
  real_T c2_f_B;
  real_T c2_hg_x;
  real_T c2_w_y;
  real_T c2_ig_x;
  real_T c2_x_y;
  real_T c2_jg_x;
  real_T c2_y_y;
  real_T c2_ab_y;
  real_T c2_kg_x;
  real_T c2_lg_x;
  real_T c2_mg_x;
  real_T c2_ng_x;
  real_T c2_og_x;
  real_T c2_pg_x;
  real_T c2_qg_x;
  real_T c2_rg_x;
  real_T c2_sg_x;
  real_T c2_tg_x;
  real_T c2_ug_x;
  real_T c2_vg_x;
  real_T c2_wg_x;
  real_T c2_xg_x;
  real_T c2_yg_x;
  real_T c2_ah_x;
  real_T c2_bh_x;
  real_T c2_ch_x;
  real_T c2_dh_x;
  real_T c2_eh_x;
  real_T c2_fh_x;
  real_T c2_gh_x;
  real_T c2_hh_x;
  real_T c2_ih_x;
  real_T c2_jh_x;
  real_T c2_kh_x;
  real_T c2_lh_x;
  real_T c2_mh_x;
  real_T c2_h_A;
  real_T c2_g_B;
  real_T c2_nh_x;
  real_T c2_bb_y;
  real_T c2_oh_x;
  real_T c2_cb_y;
  real_T c2_ph_x;
  real_T c2_db_y;
  real_T c2_eb_y;
  real_T c2_qh_x;
  real_T c2_rh_x;
  real_T c2_sh_x;
  real_T c2_th_x;
  real_T c2_uh_x;
  real_T c2_vh_x;
  real_T c2_i_A;
  real_T c2_h_B;
  real_T c2_wh_x;
  real_T c2_fb_y;
  real_T c2_xh_x;
  real_T c2_gb_y;
  real_T c2_yh_x;
  real_T c2_hb_y;
  real_T c2_ib_y;
  real_T c2_ai_x;
  real_T c2_bi_x;
  real_T c2_ci_x;
  real_T c2_di_x;
  real_T c2_ei_x;
  real_T c2_fi_x;
  real_T c2_gi_x;
  real_T c2_hi_x;
  real_T c2_ii_x;
  real_T c2_ji_x;
  real_T c2_ki_x;
  real_T c2_li_x;
  real_T c2_mi_x;
  real_T c2_ni_x;
  real_T c2_oi_x;
  real_T c2_pi_x;
  real_T c2_qi_x;
  real_T c2_ri_x;
  real_T c2_si_x;
  real_T c2_ti_x;
  real_T c2_ui_x;
  real_T c2_vi_x;
  real_T c2_wi_x;
  real_T c2_xi_x;
  real_T c2_j_A;
  real_T c2_i_B;
  real_T c2_yi_x;
  real_T c2_jb_y;
  real_T c2_aj_x;
  real_T c2_kb_y;
  real_T c2_bj_x;
  real_T c2_lb_y;
  real_T c2_mb_y;
  real_T c2_cj_x;
  real_T c2_dj_x;
  real_T c2_ej_x;
  real_T c2_fj_x;
  real_T c2_gj_x;
  real_T c2_hj_x;
  real_T c2_ij_x;
  real_T c2_jj_x;
  real_T c2_kj_x;
  real_T c2_lj_x;
  real_T c2_mj_x;
  real_T c2_nj_x;
  real_T c2_oj_x;
  real_T c2_pj_x;
  real_T c2_qj_x;
  real_T c2_rj_x;
  real_T c2_sj_x;
  real_T c2_tj_x;
  real_T c2_uj_x;
  real_T c2_vj_x;
  real_T c2_wj_x;
  real_T c2_xj_x;
  real_T c2_yj_x;
  real_T c2_ak_x;
  real_T c2_bk_x;
  real_T c2_ck_x;
  real_T c2_dk_x;
  real_T c2_ek_x;
  real_T c2_fk_x;
  real_T c2_gk_x;
  real_T c2_hk_x;
  real_T c2_ik_x;
  real_T c2_jk_x;
  real_T c2_kk_x;
  real_T c2_lk_x;
  real_T c2_mk_x;
  real_T c2_nk_x;
  real_T c2_ok_x;
  real_T c2_k_A;
  real_T c2_j_B;
  real_T c2_pk_x;
  real_T c2_nb_y;
  real_T c2_qk_x;
  real_T c2_ob_y;
  real_T c2_rk_x;
  real_T c2_pb_y;
  real_T c2_qb_y;
  real_T c2_sk_x;
  real_T c2_tk_x;
  real_T c2_uk_x;
  real_T c2_vk_x;
  real_T c2_wk_x;
  real_T c2_xk_x;
  real_T c2_yk_x;
  real_T c2_al_x;
  real_T c2_l_A;
  real_T c2_k_B;
  real_T c2_bl_x;
  real_T c2_rb_y;
  real_T c2_cl_x;
  real_T c2_sb_y;
  real_T c2_dl_x;
  real_T c2_tb_y;
  real_T c2_ub_y;
  real_T c2_el_x;
  real_T c2_fl_x;
  real_T c2_gl_x;
  real_T c2_hl_x;
  real_T c2_il_x;
  real_T c2_jl_x;
  real_T c2_kl_x;
  real_T c2_ll_x;
  real_T c2_ml_x;
  real_T c2_nl_x;
  real_T c2_ol_x;
  real_T c2_pl_x;
  real_T c2_ql_x;
  real_T c2_rl_x;
  real_T c2_sl_x;
  real_T c2_tl_x;
  real_T c2_ul_x;
  real_T c2_vl_x;
  real_T c2_wl_x;
  real_T c2_xl_x;
  real_T c2_yl_x;
  real_T c2_am_x;
  real_T c2_bm_x;
  real_T c2_cm_x;
  real_T c2_dm_x;
  real_T c2_em_x;
  real_T c2_fm_x;
  real_T c2_gm_x;
  real_T c2_hm_x;
  real_T c2_im_x;
  real_T c2_jm_x;
  real_T c2_km_x;
  real_T c2_lm_x;
  real_T c2_mm_x;
  real_T c2_nm_x;
  real_T c2_om_x;
  real_T c2_pm_x;
  real_T c2_qm_x;
  real_T c2_m_A;
  real_T c2_l_B;
  real_T c2_rm_x;
  real_T c2_vb_y;
  real_T c2_sm_x;
  real_T c2_wb_y;
  real_T c2_tm_x;
  real_T c2_xb_y;
  real_T c2_yb_y;
  real_T c2_um_x;
  real_T c2_vm_x;
  real_T c2_wm_x;
  real_T c2_xm_x;
  real_T c2_ym_x;
  real_T c2_an_x;
  real_T c2_bn_x;
  real_T c2_cn_x;
  real_T c2_dn_x;
  real_T c2_en_x;
  real_T c2_fn_x;
  real_T c2_gn_x;
  real_T c2_hn_x;
  real_T c2_in_x;
  real_T c2_jn_x;
  real_T c2_kn_x;
  real_T c2_ln_x;
  real_T c2_mn_x;
  real_T c2_nn_x;
  real_T c2_on_x;
  real_T c2_pn_x;
  real_T c2_qn_x;
  real_T c2_rn_x;
  real_T c2_sn_x;
  real_T c2_tn_x;
  real_T c2_un_x;
  real_T c2_vn_x;
  real_T c2_wn_x;
  real_T c2_xn_x;
  real_T c2_yn_x;
  real_T c2_ao_x;
  real_T c2_bo_x;
  real_T c2_co_x;
  real_T c2_do_x;
  real_T c2_eo_x;
  real_T c2_fo_x;
  real_T c2_n_A;
  real_T c2_m_B;
  real_T c2_go_x;
  real_T c2_ac_y;
  real_T c2_ho_x;
  real_T c2_bc_y;
  real_T c2_io_x;
  real_T c2_cc_y;
  real_T c2_dc_y;
  real_T c2_jo_x;
  real_T c2_ko_x;
  real_T c2_lo_x;
  real_T c2_mo_x;
  real_T c2_no_x;
  real_T c2_oo_x;
  real_T c2_o_A;
  real_T c2_n_B;
  real_T c2_po_x;
  real_T c2_ec_y;
  real_T c2_qo_x;
  real_T c2_fc_y;
  real_T c2_ro_x;
  real_T c2_gc_y;
  real_T c2_hc_y;
  int32_T c2_i22;
  static real_T c2_a[4] = { 1.0, 0.0, 0.0, 0.0 };

  int32_T c2_i23;
  real_T c2_e_hoistedGlobal[16];
  int32_T c2_i24;
  real_T c2_b_a[16];
  int32_T c2_i25;
  int32_T c2_i26;
  int32_T c2_i27;
  real_T c2_ic_y[16];
  int32_T c2_i28;
  int32_T c2_i29;
  int32_T c2_i30;
  int32_T c2_i31;
  int32_T c2_i32;
  int32_T c2_i33;
  real_T c2_b[16];
  int32_T c2_i34;
  int32_T c2_i35;
  int32_T c2_i36;
  int32_T c2_i37;
  int32_T c2_i38;
  int32_T c2_i39;
  int32_T c2_i40;
  int32_T c2_i41;
  real_T c2_jc_y[4];
  int32_T c2_i42;
  int32_T c2_i43;
  static real_T c2_b_b[4] = { 1.0, 0.0, 0.0, 0.0 };

  int32_T c2_i44;
  int32_T c2_i45;
  int32_T c2_i46;
  real_T c2_kc_y[4];
  int32_T c2_i47;
  int32_T c2_i48;
  real_T c2_lc_y[4];
  int32_T c2_i49;
  real_T c2_c_b[4];
  real_T c2_mc_y;
  real_T c2_o_B;
  real_T c2_nc_y;
  real_T c2_oc_y;
  real_T c2_pc_y;
  int32_T c2_i50;
  int32_T c2_i51;
  int32_T c2_i52;
  real_T c2_c_a[4];
  int32_T c2_i53;
  real_T c2_qc_y[4];
  real_T c2_rc_y;
  int32_T c2_i54;
  real_T c2_d_b;
  int32_T c2_i55;
  int32_T c2_i56;
  int32_T c2_i57;
  int32_T c2_i58;
  int32_T c2_i59;
  int32_T c2_i60;
  int32_T c2_i61;
  int32_T c2_i62;
  int32_T c2_i63;
  int32_T c2_i64;
  int32_T c2_i65;
  int32_T c2_i66;
  int32_T c2_i67;
  int32_T c2_i68;
  int32_T c2_i69;
  int32_T c2_i70;
  int32_T c2_i71;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 0U, chartInstance->c2_sfEvent);
  c2_hoistedGlobal = *chartInstance->c2_R;
  c2_b_hoistedGlobal = *chartInstance->c2_T_s;
  c2_c_hoistedGlobal = *chartInstance->c2_u;
  c2_d_hoistedGlobal = *chartInstance->c2_y;
  for (c2_i14 = 0; c2_i14 < 16; c2_i14++) {
    c2_b_P[c2_i14] = (*chartInstance->c2_P)[c2_i14];
  }

  for (c2_i15 = 0; c2_i15 < 16; c2_i15++) {
    c2_b_Q[c2_i15] = (*chartInstance->c2_Q)[c2_i15];
  }

  c2_b_R = c2_hoistedGlobal;
  for (c2_i16 = 0; c2_i16 < 4; c2_i16++) {
    c2_b_x0[c2_i16] = (*chartInstance->c2_x0)[c2_i16];
  }

  for (c2_i17 = 0; c2_i17 < 8; c2_i17++) {
    c2_b_para_sys[c2_i17] = (*chartInstance->c2_para_sys)[c2_i17];
  }

  c2_b_T_s = c2_b_hoistedGlobal;
  c2_b_u = c2_c_hoistedGlobal;
  c2_b_y = c2_d_hoistedGlobal;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 28U, 28U, c2_debug_family_names,
    c2_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_g, 0U, c2_d_sf_marshallOut,
    c2_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_l_1, 1U, c2_d_sf_marshallOut,
    c2_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_l_2, 2U, c2_d_sf_marshallOut,
    c2_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_m_1, 3U, c2_d_sf_marshallOut,
    c2_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_m_2, 4U, c2_d_sf_marshallOut,
    c2_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_m_3, 5U, c2_d_sf_marshallOut,
    c2_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_d_p1, 6U, c2_d_sf_marshallOut,
    c2_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_d_p2, 7U, c2_d_sf_marshallOut,
    c2_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_x_1, 8U, c2_d_sf_marshallOut,
    c2_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_x_2, 9U, c2_d_sf_marshallOut,
    c2_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_x_3, 10U, c2_d_sf_marshallOut,
    c2_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_x_4, 11U, c2_d_sf_marshallOut,
    c2_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_A, 12U, c2_f_sf_marshallOut,
    c2_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_C, 13U, c2_g_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargin, 14U, c2_d_sf_marshallOut,
    c2_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargout, 15U, c2_d_sf_marshallOut,
    c2_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_b_P, 16U, c2_f_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_b_Q, 17U, c2_f_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_b_R, 18U, c2_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_b_x0, 19U, c2_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_b_para_sys, 20U, c2_e_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_b_T_s, 21U, c2_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_b_u, 22U, c2_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_b_y, 23U, c2_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_b_x, 24U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_b_K, 25U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(chartInstance->c2_x_p, 26U,
    c2_b_sf_marshallOut, c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(chartInstance->c2_P_p, 27U,
    c2_sf_marshallOut, c2_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 9);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 12);
  c2_g = c2_b_para_sys[0];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 13);
  c2_l_1 = c2_b_para_sys[1];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 14);
  c2_l_2 = c2_b_para_sys[2];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 15);
  c2_m_1 = c2_b_para_sys[3];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 16);
  c2_m_2 = c2_b_para_sys[4];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 17);
  c2_m_3 = c2_b_para_sys[5];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 18);
  c2_d_p1 = c2_b_para_sys[6];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 19);
  c2_d_p2 = c2_b_para_sys[7];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 21);
  if (CV_EML_IF(0, 1, 0, !chartInstance->c2_x_p_not_empty)) {
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 22);
    for (c2_i18 = 0; c2_i18 < 4; c2_i18++) {
      chartInstance->c2_x_p[c2_i18] = c2_b_x0[c2_i18];
    }

    chartInstance->c2_x_p_not_empty = true;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 24);
    for (c2_i19 = 0; c2_i19 < 16; c2_i19++) {
      chartInstance->c2_P_p[c2_i19] = c2_b_P[c2_i19];
    }

    chartInstance->c2_P_p_not_empty = true;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 25);
    for (c2_i20 = 0; c2_i20 < 4; c2_i20++) {
      c2_b_x[c2_i20] = chartInstance->c2_x_p[c2_i20];
    }

    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 26);
    for (c2_i21 = 0; c2_i21 < 4; c2_i21++) {
      c2_b_K[c2_i21] = 0.0;
    }
  } else {
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 30);
    c2_x_1 = chartInstance->c2_x_p[0];
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 31);
    c2_x_2 = chartInstance->c2_x_p[1];
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 32);
    c2_x_3 = chartInstance->c2_x_p[2];
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 33);
    c2_x_4 = chartInstance->c2_x_p[3];
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 35);
    c2_c_x = c2_x_1 - c2_x_3;
    c2_d_x = c2_c_x;
    c2_d_x = muDoubleScalarCos(c2_d_x);
    c2_e_x = c2_x_3;
    c2_f_x = c2_e_x;
    c2_f_x = muDoubleScalarCos(c2_f_x);
    c2_g_x = c2_x_3;
    c2_h_x = c2_g_x;
    c2_h_x = muDoubleScalarSin(c2_h_x);
    c2_i_x = c2_x_1 - c2_x_3;
    c2_j_x = c2_i_x;
    c2_j_x = muDoubleScalarSin(c2_j_x);
    c2_k_x = c2_x_1;
    c2_l_x = c2_k_x;
    c2_l_x = muDoubleScalarCos(c2_l_x);
    c2_m_x = c2_x_1;
    c2_n_x = c2_m_x;
    c2_n_x = muDoubleScalarCos(c2_n_x);
    c2_o_x = c2_x_1;
    c2_p_x = c2_o_x;
    c2_p_x = muDoubleScalarCos(c2_p_x);
    c2_q_x = c2_x_1;
    c2_r_x = c2_q_x;
    c2_r_x = muDoubleScalarSin(c2_r_x);
    c2_s_x = c2_x_1;
    c2_t_x = c2_s_x;
    c2_t_x = muDoubleScalarSin(c2_t_x);
    c2_u_x = c2_x_1;
    c2_v_x = c2_u_x;
    c2_v_x = muDoubleScalarSin(c2_v_x);
    c2_w_x = c2_x_1 - c2_x_3;
    c2_x_x = c2_w_x;
    c2_x_x = muDoubleScalarSin(c2_x_x);
    c2_y_x = c2_x_1 - c2_x_3;
    c2_ab_x = c2_y_x;
    c2_ab_x = muDoubleScalarCos(c2_ab_x);
    c2_b_A = c2_b_T_s * ((((((((((12.0 * c2_d_p2 * c2_l_2 * c2_x_4 - 12.0 *
      c2_d_p1 * c2_l_2 * c2_x_2) - 12.0 * c2_d_p2 * c2_l_2 * c2_x_2) - c2_d_x *
                                ((((18.0 * c2_d_p2 * c2_l_1 * c2_x_2 - 18.0 *
      c2_d_p2 * c2_l_1 * c2_x_4) + 9.0 * c2_l_1 * c2_l_2 * c2_m_2 * c2_b_u *
      c2_f_x) + 9.0 * c2_g * c2_l_1 * c2_l_2 * c2_m_2 * c2_h_x) + 9.0 *
      c2_mpower(chartInstance, c2_l_1) * c2_l_2 * c2_m_2 * c2_mpower
      (chartInstance, c2_x_2) * c2_j_x)) + 6.0 * c2_l_1 * c2_l_2 * c2_m_1 *
      c2_b_u * c2_l_x) + 12.0 * c2_l_1 * c2_l_2 * c2_m_2 * c2_b_u * c2_n_x) +
      12.0 * c2_l_1 * c2_l_2 * c2_m_3 * c2_b_u * c2_p_x) + 6.0 * c2_g * c2_l_1 *
      c2_l_2 * c2_m_1 * c2_r_x) + 12.0 * c2_g * c2_l_1 * c2_l_2 * c2_m_2 *
      c2_t_x) + 12.0 * c2_g * c2_l_1 * c2_l_2 * c2_m_3 * c2_v_x) - 6.0 * c2_l_1 *
                         c2_mpower(chartInstance, c2_l_2) * c2_m_2 * c2_mpower
                         (chartInstance, c2_x_4) * c2_x_x);
    c2_B = c2_mpower(chartInstance, c2_l_1) * c2_l_2 * (((4.0 * c2_m_1 + 12.0 *
      c2_m_2) + 12.0 * c2_m_3) - 9.0 * c2_m_2 * c2_mpower(chartInstance, c2_ab_x));
    c2_bb_x = c2_b_A;
    c2_c_y = c2_B;
    c2_cb_x = c2_bb_x;
    c2_d_y = c2_c_y;
    c2_db_x = c2_cb_x;
    c2_e_y = c2_d_y;
    c2_f_y = c2_db_x / c2_e_y;
    c2_eb_x = c2_x_1 - c2_x_3;
    c2_fb_x = c2_eb_x;
    c2_fb_x = muDoubleScalarSin(c2_fb_x);
    c2_gb_x = c2_x_1 - c2_x_3;
    c2_hb_x = c2_gb_x;
    c2_hb_x = muDoubleScalarCos(c2_hb_x);
    c2_ib_x = c2_x_1 - c2_x_3;
    c2_jb_x = c2_ib_x;
    c2_jb_x = muDoubleScalarCos(c2_jb_x);
    c2_kb_x = c2_x_1 - c2_x_3;
    c2_lb_x = c2_kb_x;
    c2_lb_x = muDoubleScalarCos(c2_lb_x);
    c2_mb_x = c2_x_3;
    c2_nb_x = c2_mb_x;
    c2_nb_x = muDoubleScalarCos(c2_nb_x);
    c2_ob_x = c2_x_3;
    c2_pb_x = c2_ob_x;
    c2_pb_x = muDoubleScalarSin(c2_pb_x);
    c2_qb_x = 2.0 * c2_x_1 - 2.0 * c2_x_3;
    c2_rb_x = c2_qb_x;
    c2_rb_x = muDoubleScalarSin(c2_rb_x);
    c2_sb_x = 2.0 * c2_x_1 - c2_x_3;
    c2_tb_x = c2_sb_x;
    c2_tb_x = muDoubleScalarCos(c2_tb_x);
    c2_ub_x = 2.0 * c2_x_1 - c2_x_3;
    c2_vb_x = c2_ub_x;
    c2_vb_x = muDoubleScalarSin(c2_vb_x);
    c2_wb_x = c2_x_3;
    c2_xb_x = c2_wb_x;
    c2_xb_x = muDoubleScalarCos(c2_xb_x);
    c2_yb_x = c2_x_3;
    c2_ac_x = c2_yb_x;
    c2_ac_x = muDoubleScalarCos(c2_ac_x);
    c2_bc_x = c2_x_3;
    c2_cc_x = c2_bc_x;
    c2_cc_x = muDoubleScalarSin(c2_cc_x);
    c2_dc_x = c2_x_3;
    c2_ec_x = c2_dc_x;
    c2_ec_x = muDoubleScalarSin(c2_ec_x);
    c2_fc_x = 2.0 * c2_x_1 - c2_x_3;
    c2_gc_x = c2_fc_x;
    c2_gc_x = muDoubleScalarCos(c2_gc_x);
    c2_hc_x = 2.0 * c2_x_1 - c2_x_3;
    c2_ic_x = c2_hc_x;
    c2_ic_x = muDoubleScalarCos(c2_ic_x);
    c2_jc_x = 2.0 * c2_x_1 - c2_x_3;
    c2_kc_x = c2_jc_x;
    c2_kc_x = muDoubleScalarSin(c2_kc_x);
    c2_lc_x = 2.0 * c2_x_1 - c2_x_3;
    c2_mc_x = c2_lc_x;
    c2_mc_x = muDoubleScalarSin(c2_mc_x);
    c2_nc_x = 2.0 * c2_x_1 - 2.0 * c2_x_3;
    c2_oc_x = c2_nc_x;
    c2_oc_x = muDoubleScalarCos(c2_oc_x);
    c2_c_A = c2_b_T_s * ((((((((((((((((((((((c2_fb_x * ((36.0 * c2_mpower
      (chartInstance, c2_l_1) * c2_l_2 * c2_mpower(chartInstance, c2_m_2) *
      c2_mpower(chartInstance, c2_x_2) + 12.0 * c2_mpower(chartInstance, c2_l_1)
      * c2_l_2 * c2_m_1 * c2_m_2 * c2_mpower(chartInstance, c2_x_2)) + 36.0 *
      c2_mpower(chartInstance, c2_l_1) * c2_l_2 * c2_m_2 * c2_m_3 * c2_mpower
      (chartInstance, c2_x_2)) + 24.0 * c2_d_p2 * c2_l_1 * c2_m_1 * c2_x_2) +
      72.0 * c2_d_p2 * c2_l_1 * c2_m_2 * c2_x_2) - 24.0 * c2_d_p2 * c2_l_1 *
      c2_m_1 * c2_x_4) + 72.0 * c2_d_p2 * c2_l_1 * c2_m_3 * c2_x_2) - 72.0 *
      c2_d_p2 * c2_l_1 * c2_m_2 * c2_x_4) - 72.0 * c2_d_p2 * c2_l_1 * c2_m_3 *
      c2_x_4) + 36.0 * c2_d_p1 * c2_l_2 * c2_m_2 * c2_x_2 * c2_hb_x) + 36.0 *
      c2_d_p2 * c2_l_2 * c2_m_2 * c2_x_2 * c2_jb_x) - 36.0 * c2_d_p2 * c2_l_2 *
      c2_m_2 * c2_x_4 * c2_lb_x) + 18.0 * c2_l_1 * c2_l_2 * c2_mpower
      (chartInstance, c2_m_2) * c2_b_u * c2_nb_x) + 18.0 * c2_g * c2_l_1 *
      c2_l_2 * c2_mpower(chartInstance, c2_m_2) * c2_pb_x) + 9.0 * c2_l_1 *
      c2_mpower(chartInstance, c2_l_2) * c2_mpower(chartInstance, c2_m_2) *
      c2_mpower(chartInstance, c2_x_4) * c2_rb_x) - 18.0 * c2_l_1 * c2_l_2 *
      c2_mpower(chartInstance, c2_m_2) * c2_b_u * c2_tb_x) - 18.0 * c2_g *
      c2_l_1 * c2_l_2 * c2_mpower(chartInstance, c2_m_2) * c2_vb_x) + 3.0 *
      c2_l_1 * c2_l_2 * c2_m_1 * c2_m_2 * c2_b_u * c2_xb_x) + 18.0 * c2_l_1 *
      c2_l_2 * c2_m_2 * c2_m_3 * c2_b_u * c2_ac_x) + 3.0 * c2_g * c2_l_1 *
      c2_l_2 * c2_m_1 * c2_m_2 * c2_cc_x) + 18.0 * c2_g * c2_l_1 * c2_l_2 *
      c2_m_2 * c2_m_3 * c2_ec_x) - 9.0 * c2_l_1 * c2_l_2 * c2_m_1 * c2_m_2 *
      c2_b_u * c2_gc_x) - 18.0 * c2_l_1 * c2_l_2 * c2_m_2 * c2_m_3 * c2_b_u *
      c2_ic_x) - 9.0 * c2_g * c2_l_1 * c2_l_2 * c2_m_1 * c2_m_2 * c2_kc_x) -
                         18.0 * c2_g * c2_l_1 * c2_l_2 * c2_m_2 * c2_m_3 *
                         c2_mc_x);
    c2_b_B = c2_l_1 * c2_mpower(chartInstance, c2_l_2) * c2_m_2 * (((8.0 *
      c2_m_1 + 15.0 * c2_m_2) + 24.0 * c2_m_3) - 9.0 * c2_m_2 * c2_oc_x);
    c2_pc_x = c2_c_A;
    c2_g_y = c2_b_B;
    c2_qc_x = c2_pc_x;
    c2_h_y = c2_g_y;
    c2_rc_x = c2_qc_x;
    c2_i_y = c2_h_y;
    c2_j_y = c2_rc_x / c2_i_y;
    c2_b_x[0] = c2_x_1 + c2_b_T_s * c2_x_2;
    c2_b_x[1] = c2_x_2 + c2_f_y;
    c2_b_x[2] = c2_x_3 + c2_b_T_s * c2_x_4;
    c2_b_x[3] = c2_x_4 + c2_j_y;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 38);
    c2_sc_x = c2_x_1;
    c2_tc_x = c2_sc_x;
    c2_tc_x = muDoubleScalarSin(c2_tc_x);
    c2_uc_x = c2_x_1 - c2_x_3;
    c2_vc_x = c2_uc_x;
    c2_vc_x = muDoubleScalarSin(c2_vc_x);
    c2_wc_x = c2_x_3;
    c2_xc_x = c2_wc_x;
    c2_xc_x = muDoubleScalarCos(c2_xc_x);
    c2_yc_x = c2_x_3;
    c2_ad_x = c2_yc_x;
    c2_ad_x = muDoubleScalarSin(c2_ad_x);
    c2_bd_x = c2_x_1 - c2_x_3;
    c2_cd_x = c2_bd_x;
    c2_cd_x = muDoubleScalarSin(c2_cd_x);
    c2_dd_x = c2_x_1;
    c2_ed_x = c2_dd_x;
    c2_ed_x = muDoubleScalarSin(c2_ed_x);
    c2_fd_x = c2_x_1;
    c2_gd_x = c2_fd_x;
    c2_gd_x = muDoubleScalarSin(c2_gd_x);
    c2_hd_x = c2_x_1 - c2_x_3;
    c2_id_x = c2_hd_x;
    c2_id_x = muDoubleScalarCos(c2_id_x);
    c2_jd_x = c2_x_1;
    c2_kd_x = c2_jd_x;
    c2_kd_x = muDoubleScalarCos(c2_kd_x);
    c2_ld_x = c2_x_1;
    c2_md_x = c2_ld_x;
    c2_md_x = muDoubleScalarCos(c2_md_x);
    c2_nd_x = c2_x_1;
    c2_od_x = c2_nd_x;
    c2_od_x = muDoubleScalarCos(c2_od_x);
    c2_pd_x = c2_x_1 - c2_x_3;
    c2_qd_x = c2_pd_x;
    c2_qd_x = muDoubleScalarCos(c2_qd_x);
    c2_rd_x = c2_x_1 - c2_x_3;
    c2_sd_x = c2_rd_x;
    c2_sd_x = muDoubleScalarCos(c2_sd_x);
    c2_d_A = -(c2_b_T_s * ((((((((6.0 * c2_l_1 * c2_l_2 * c2_m_1 * c2_b_u *
      c2_tc_x - c2_vc_x * ((((18.0 * c2_d_p2 * c2_l_1 * c2_x_2 - 18.0 * c2_d_p2 *
      c2_l_1 * c2_x_4) + 9.0 * c2_l_1 * c2_l_2 * c2_m_2 * c2_b_u * c2_xc_x) +
      9.0 * c2_g * c2_l_1 * c2_l_2 * c2_m_2 * c2_ad_x) + 9.0 * c2_mpower
      (chartInstance, c2_l_1) * c2_l_2 * c2_m_2 * c2_mpower(chartInstance,
      c2_x_2) * c2_cd_x)) + 12.0 * c2_l_1 * c2_l_2 * c2_m_2 * c2_b_u * c2_ed_x)
      + 12.0 * c2_l_1 * c2_l_2 * c2_m_3 * c2_b_u * c2_gd_x) + 9.0 * c2_mpower
      (chartInstance, c2_l_1) * c2_l_2 * c2_m_2 * c2_mpower(chartInstance,
      c2_x_2) * c2_mpower(chartInstance, c2_id_x)) - 6.0 * c2_g * c2_l_1 *
      c2_l_2 * c2_m_1 * c2_kd_x) - 12.0 * c2_g * c2_l_1 * c2_l_2 * c2_m_2 *
      c2_md_x) - 12.0 * c2_g * c2_l_1 * c2_l_2 * c2_m_3 * c2_od_x) + 6.0 *
                c2_l_1 * c2_mpower(chartInstance, c2_l_2) * c2_m_2 * c2_mpower
                (chartInstance, c2_x_4) * c2_qd_x));
    c2_c_B = c2_mpower(chartInstance, c2_l_1) * c2_l_2 * (((4.0 * c2_m_1 + 12.0 *
      c2_m_2) + 12.0 * c2_m_3) - 9.0 * c2_m_2 * c2_mpower(chartInstance, c2_sd_x));
    c2_td_x = c2_d_A;
    c2_k_y = c2_c_B;
    c2_ud_x = c2_td_x;
    c2_l_y = c2_k_y;
    c2_vd_x = c2_ud_x;
    c2_m_y = c2_l_y;
    c2_n_y = c2_vd_x / c2_m_y;
    c2_wd_x = c2_x_1 - c2_x_3;
    c2_xd_x = c2_wd_x;
    c2_xd_x = muDoubleScalarCos(c2_xd_x);
    c2_yd_x = c2_x_1 - c2_x_3;
    c2_ae_x = c2_yd_x;
    c2_ae_x = muDoubleScalarSin(c2_ae_x);
    c2_be_x = c2_x_1 - c2_x_3;
    c2_ce_x = c2_be_x;
    c2_ce_x = muDoubleScalarCos(c2_ce_x);
    c2_de_x = c2_x_3;
    c2_ee_x = c2_de_x;
    c2_ee_x = muDoubleScalarCos(c2_ee_x);
    c2_fe_x = c2_x_3;
    c2_ge_x = c2_fe_x;
    c2_ge_x = muDoubleScalarSin(c2_ge_x);
    c2_he_x = c2_x_1 - c2_x_3;
    c2_ie_x = c2_he_x;
    c2_ie_x = muDoubleScalarSin(c2_ie_x);
    c2_je_x = c2_x_1;
    c2_ke_x = c2_je_x;
    c2_ke_x = muDoubleScalarCos(c2_ke_x);
    c2_le_x = c2_x_1;
    c2_me_x = c2_le_x;
    c2_me_x = muDoubleScalarCos(c2_me_x);
    c2_ne_x = c2_x_1;
    c2_oe_x = c2_ne_x;
    c2_oe_x = muDoubleScalarCos(c2_oe_x);
    c2_pe_x = c2_x_1;
    c2_qe_x = c2_pe_x;
    c2_qe_x = muDoubleScalarSin(c2_qe_x);
    c2_re_x = c2_x_1;
    c2_se_x = c2_re_x;
    c2_se_x = muDoubleScalarSin(c2_se_x);
    c2_te_x = c2_x_1;
    c2_ue_x = c2_te_x;
    c2_ue_x = muDoubleScalarSin(c2_ue_x);
    c2_ve_x = c2_x_1 - c2_x_3;
    c2_we_x = c2_ve_x;
    c2_we_x = muDoubleScalarSin(c2_we_x);
    c2_xe_x = c2_x_1 - c2_x_3;
    c2_ye_x = c2_xe_x;
    c2_ye_x = muDoubleScalarCos(c2_ye_x);
    c2_e_A = 18.0 * c2_b_T_s * c2_m_2 * c2_xd_x * c2_ae_x * ((((((((((12.0 *
      c2_d_p2 * c2_l_2 * c2_x_4 - 12.0 * c2_d_p1 * c2_l_2 * c2_x_2) - 12.0 *
      c2_d_p2 * c2_l_2 * c2_x_2) - c2_ce_x * ((((18.0 * c2_d_p2 * c2_l_1 *
      c2_x_2 - 18.0 * c2_d_p2 * c2_l_1 * c2_x_4) + 9.0 * c2_l_1 * c2_l_2 *
      c2_m_2 * c2_b_u * c2_ee_x) + 9.0 * c2_g * c2_l_1 * c2_l_2 * c2_m_2 *
      c2_ge_x) + 9.0 * c2_mpower(chartInstance, c2_l_1) * c2_l_2 * c2_m_2 *
      c2_mpower(chartInstance, c2_x_2) * c2_ie_x)) + 6.0 * c2_l_1 * c2_l_2 *
      c2_m_1 * c2_b_u * c2_ke_x) + 12.0 * c2_l_1 * c2_l_2 * c2_m_2 * c2_b_u *
      c2_me_x) + 12.0 * c2_l_1 * c2_l_2 * c2_m_3 * c2_b_u * c2_oe_x) + 6.0 *
      c2_g * c2_l_1 * c2_l_2 * c2_m_1 * c2_qe_x) + 12.0 * c2_g * c2_l_1 * c2_l_2
      * c2_m_2 * c2_se_x) + 12.0 * c2_g * c2_l_1 * c2_l_2 * c2_m_3 * c2_ue_x) -
      6.0 * c2_l_1 * c2_mpower(chartInstance, c2_l_2) * c2_m_2 * c2_mpower
      (chartInstance, c2_x_4) * c2_we_x);
    c2_d_B = c2_mpower(chartInstance, c2_l_1) * c2_l_2 * c2_mpower(chartInstance,
      ((4.0 * c2_m_1 + 12.0 * c2_m_2) + 12.0 * c2_m_3) - 9.0 * c2_m_2 *
      c2_mpower(chartInstance, c2_ye_x));
    c2_af_x = c2_e_A;
    c2_o_y = c2_d_B;
    c2_bf_x = c2_af_x;
    c2_p_y = c2_o_y;
    c2_cf_x = c2_bf_x;
    c2_q_y = c2_p_y;
    c2_r_y = c2_cf_x / c2_q_y;
    c2_df_x = c2_x_1 - c2_x_3;
    c2_ef_x = c2_df_x;
    c2_ef_x = muDoubleScalarCos(c2_ef_x);
    c2_ff_x = c2_x_1 - c2_x_3;
    c2_gf_x = c2_ff_x;
    c2_gf_x = muDoubleScalarSin(c2_gf_x);
    c2_hf_x = c2_x_1 - c2_x_3;
    c2_if_x = c2_hf_x;
    c2_if_x = muDoubleScalarCos(c2_if_x);
    c2_f_A = c2_b_T_s * ((12.0 * c2_d_p1 * c2_l_2 + 12.0 * c2_d_p2 * c2_l_2) +
                         c2_ef_x * (18.0 * c2_d_p2 * c2_l_1 + 18.0 * c2_mpower
      (chartInstance, c2_l_1) * c2_l_2 * c2_m_2 * c2_x_2 * c2_gf_x));
    c2_e_B = c2_mpower(chartInstance, c2_l_1) * c2_l_2 * (((4.0 * c2_m_1 + 12.0 *
      c2_m_2) + 12.0 * c2_m_3) - 9.0 * c2_m_2 * c2_mpower(chartInstance, c2_if_x));
    c2_jf_x = c2_f_A;
    c2_s_y = c2_e_B;
    c2_kf_x = c2_jf_x;
    c2_t_y = c2_s_y;
    c2_lf_x = c2_kf_x;
    c2_u_y = c2_t_y;
    c2_v_y = c2_lf_x / c2_u_y;
    c2_mf_x = c2_x_1 - c2_x_3;
    c2_nf_x = c2_mf_x;
    c2_nf_x = muDoubleScalarCos(c2_nf_x);
    c2_of_x = c2_x_3;
    c2_pf_x = c2_of_x;
    c2_pf_x = muDoubleScalarSin(c2_pf_x);
    c2_qf_x = c2_x_3;
    c2_rf_x = c2_qf_x;
    c2_rf_x = muDoubleScalarCos(c2_rf_x);
    c2_sf_x = c2_x_1 - c2_x_3;
    c2_tf_x = c2_sf_x;
    c2_tf_x = muDoubleScalarCos(c2_tf_x);
    c2_uf_x = c2_x_1 - c2_x_3;
    c2_vf_x = c2_uf_x;
    c2_vf_x = muDoubleScalarSin(c2_vf_x);
    c2_wf_x = c2_x_3;
    c2_xf_x = c2_wf_x;
    c2_xf_x = muDoubleScalarCos(c2_xf_x);
    c2_yf_x = c2_x_3;
    c2_ag_x = c2_yf_x;
    c2_ag_x = muDoubleScalarSin(c2_ag_x);
    c2_bg_x = c2_x_1 - c2_x_3;
    c2_cg_x = c2_bg_x;
    c2_cg_x = muDoubleScalarSin(c2_cg_x);
    c2_dg_x = c2_x_1 - c2_x_3;
    c2_eg_x = c2_dg_x;
    c2_eg_x = muDoubleScalarCos(c2_eg_x);
    c2_fg_x = c2_x_1 - c2_x_3;
    c2_gg_x = c2_fg_x;
    c2_gg_x = muDoubleScalarCos(c2_gg_x);
    c2_g_A = c2_b_T_s * ((c2_nf_x * ((9.0 * c2_l_1 * c2_l_2 * c2_m_2 * c2_b_u *
      c2_pf_x - 9.0 * c2_g * c2_l_1 * c2_l_2 * c2_m_2 * c2_rf_x) + 9.0 *
      c2_mpower(chartInstance, c2_l_1) * c2_l_2 * c2_m_2 * c2_mpower
      (chartInstance, c2_x_2) * c2_tf_x) - c2_vf_x * ((((18.0 * c2_d_p2 * c2_l_1
      * c2_x_2 - 18.0 * c2_d_p2 * c2_l_1 * c2_x_4) + 9.0 * c2_l_1 * c2_l_2 *
      c2_m_2 * c2_b_u * c2_xf_x) + 9.0 * c2_g * c2_l_1 * c2_l_2 * c2_m_2 *
      c2_ag_x) + 9.0 * c2_mpower(chartInstance, c2_l_1) * c2_l_2 * c2_m_2 *
      c2_mpower(chartInstance, c2_x_2) * c2_cg_x)) + 6.0 * c2_l_1 * c2_mpower
                         (chartInstance, c2_l_2) * c2_m_2 * c2_mpower
                         (chartInstance, c2_x_4) * c2_eg_x);
    c2_f_B = c2_mpower(chartInstance, c2_l_1) * c2_l_2 * (((4.0 * c2_m_1 + 12.0 *
      c2_m_2) + 12.0 * c2_m_3) - 9.0 * c2_m_2 * c2_mpower(chartInstance, c2_gg_x));
    c2_hg_x = c2_g_A;
    c2_w_y = c2_f_B;
    c2_ig_x = c2_hg_x;
    c2_x_y = c2_w_y;
    c2_jg_x = c2_ig_x;
    c2_y_y = c2_x_y;
    c2_ab_y = c2_jg_x / c2_y_y;
    c2_kg_x = c2_x_1 - c2_x_3;
    c2_lg_x = c2_kg_x;
    c2_lg_x = muDoubleScalarCos(c2_lg_x);
    c2_mg_x = c2_x_1 - c2_x_3;
    c2_ng_x = c2_mg_x;
    c2_ng_x = muDoubleScalarSin(c2_ng_x);
    c2_og_x = c2_x_1 - c2_x_3;
    c2_pg_x = c2_og_x;
    c2_pg_x = muDoubleScalarCos(c2_pg_x);
    c2_qg_x = c2_x_3;
    c2_rg_x = c2_qg_x;
    c2_rg_x = muDoubleScalarCos(c2_rg_x);
    c2_sg_x = c2_x_3;
    c2_tg_x = c2_sg_x;
    c2_tg_x = muDoubleScalarSin(c2_tg_x);
    c2_ug_x = c2_x_1 - c2_x_3;
    c2_vg_x = c2_ug_x;
    c2_vg_x = muDoubleScalarSin(c2_vg_x);
    c2_wg_x = c2_x_1;
    c2_xg_x = c2_wg_x;
    c2_xg_x = muDoubleScalarCos(c2_xg_x);
    c2_yg_x = c2_x_1;
    c2_ah_x = c2_yg_x;
    c2_ah_x = muDoubleScalarCos(c2_ah_x);
    c2_bh_x = c2_x_1;
    c2_ch_x = c2_bh_x;
    c2_ch_x = muDoubleScalarCos(c2_ch_x);
    c2_dh_x = c2_x_1;
    c2_eh_x = c2_dh_x;
    c2_eh_x = muDoubleScalarSin(c2_eh_x);
    c2_fh_x = c2_x_1;
    c2_gh_x = c2_fh_x;
    c2_gh_x = muDoubleScalarSin(c2_gh_x);
    c2_hh_x = c2_x_1;
    c2_ih_x = c2_hh_x;
    c2_ih_x = muDoubleScalarSin(c2_ih_x);
    c2_jh_x = c2_x_1 - c2_x_3;
    c2_kh_x = c2_jh_x;
    c2_kh_x = muDoubleScalarSin(c2_kh_x);
    c2_lh_x = c2_x_1 - c2_x_3;
    c2_mh_x = c2_lh_x;
    c2_mh_x = muDoubleScalarCos(c2_mh_x);
    c2_h_A = 18.0 * c2_b_T_s * c2_m_2 * c2_lg_x * c2_ng_x * ((((((((((12.0 *
      c2_d_p2 * c2_l_2 * c2_x_4 - 12.0 * c2_d_p1 * c2_l_2 * c2_x_2) - 12.0 *
      c2_d_p2 * c2_l_2 * c2_x_2) - c2_pg_x * ((((18.0 * c2_d_p2 * c2_l_1 *
      c2_x_2 - 18.0 * c2_d_p2 * c2_l_1 * c2_x_4) + 9.0 * c2_l_1 * c2_l_2 *
      c2_m_2 * c2_b_u * c2_rg_x) + 9.0 * c2_g * c2_l_1 * c2_l_2 * c2_m_2 *
      c2_tg_x) + 9.0 * c2_mpower(chartInstance, c2_l_1) * c2_l_2 * c2_m_2 *
      c2_mpower(chartInstance, c2_x_2) * c2_vg_x)) + 6.0 * c2_l_1 * c2_l_2 *
      c2_m_1 * c2_b_u * c2_xg_x) + 12.0 * c2_l_1 * c2_l_2 * c2_m_2 * c2_b_u *
      c2_ah_x) + 12.0 * c2_l_1 * c2_l_2 * c2_m_3 * c2_b_u * c2_ch_x) + 6.0 *
      c2_g * c2_l_1 * c2_l_2 * c2_m_1 * c2_eh_x) + 12.0 * c2_g * c2_l_1 * c2_l_2
      * c2_m_2 * c2_gh_x) + 12.0 * c2_g * c2_l_1 * c2_l_2 * c2_m_3 * c2_ih_x) -
      6.0 * c2_l_1 * c2_mpower(chartInstance, c2_l_2) * c2_m_2 * c2_mpower
      (chartInstance, c2_x_4) * c2_kh_x);
    c2_g_B = c2_mpower(chartInstance, c2_l_1) * c2_l_2 * c2_mpower(chartInstance,
      ((4.0 * c2_m_1 + 12.0 * c2_m_2) + 12.0 * c2_m_3) - 9.0 * c2_m_2 *
      c2_mpower(chartInstance, c2_mh_x));
    c2_nh_x = c2_h_A;
    c2_bb_y = c2_g_B;
    c2_oh_x = c2_nh_x;
    c2_cb_y = c2_bb_y;
    c2_ph_x = c2_oh_x;
    c2_db_y = c2_cb_y;
    c2_eb_y = c2_ph_x / c2_db_y;
    c2_qh_x = c2_x_1 - c2_x_3;
    c2_rh_x = c2_qh_x;
    c2_rh_x = muDoubleScalarCos(c2_rh_x);
    c2_sh_x = c2_x_1 - c2_x_3;
    c2_th_x = c2_sh_x;
    c2_th_x = muDoubleScalarSin(c2_th_x);
    c2_uh_x = c2_x_1 - c2_x_3;
    c2_vh_x = c2_uh_x;
    c2_vh_x = muDoubleScalarCos(c2_vh_x);
    c2_i_A = c2_b_T_s * ((12.0 * c2_d_p2 * c2_l_2 + 18.0 * c2_d_p2 * c2_l_1 *
                          c2_rh_x) - 12.0 * c2_l_1 * c2_mpower(chartInstance,
      c2_l_2) * c2_m_2 * c2_x_4 * c2_th_x);
    c2_h_B = c2_mpower(chartInstance, c2_l_1) * c2_l_2 * (((4.0 * c2_m_1 + 12.0 *
      c2_m_2) + 12.0 * c2_m_3) - 9.0 * c2_m_2 * c2_mpower(chartInstance, c2_vh_x));
    c2_wh_x = c2_i_A;
    c2_fb_y = c2_h_B;
    c2_xh_x = c2_wh_x;
    c2_gb_y = c2_fb_y;
    c2_yh_x = c2_xh_x;
    c2_hb_y = c2_gb_y;
    c2_ib_y = c2_yh_x / c2_hb_y;
    c2_ai_x = c2_x_1 - c2_x_3;
    c2_bi_x = c2_ai_x;
    c2_bi_x = muDoubleScalarCos(c2_bi_x);
    c2_ci_x = c2_x_1 - c2_x_3;
    c2_di_x = c2_ci_x;
    c2_di_x = muDoubleScalarSin(c2_di_x);
    c2_ei_x = c2_x_1 - c2_x_3;
    c2_fi_x = c2_ei_x;
    c2_fi_x = muDoubleScalarSin(c2_fi_x);
    c2_gi_x = c2_x_1 - c2_x_3;
    c2_hi_x = c2_gi_x;
    c2_hi_x = muDoubleScalarSin(c2_hi_x);
    c2_ii_x = 2.0 * c2_x_1 - 2.0 * c2_x_3;
    c2_ji_x = c2_ii_x;
    c2_ji_x = muDoubleScalarCos(c2_ji_x);
    c2_ki_x = 2.0 * c2_x_1 - c2_x_3;
    c2_li_x = c2_ki_x;
    c2_li_x = muDoubleScalarCos(c2_li_x);
    c2_mi_x = 2.0 * c2_x_1 - c2_x_3;
    c2_ni_x = c2_mi_x;
    c2_ni_x = muDoubleScalarSin(c2_ni_x);
    c2_oi_x = 2.0 * c2_x_1 - c2_x_3;
    c2_pi_x = c2_oi_x;
    c2_pi_x = muDoubleScalarSin(c2_pi_x);
    c2_qi_x = 2.0 * c2_x_1 - c2_x_3;
    c2_ri_x = c2_qi_x;
    c2_ri_x = muDoubleScalarSin(c2_ri_x);
    c2_si_x = 2.0 * c2_x_1 - c2_x_3;
    c2_ti_x = c2_si_x;
    c2_ti_x = muDoubleScalarCos(c2_ti_x);
    c2_ui_x = 2.0 * c2_x_1 - c2_x_3;
    c2_vi_x = c2_ui_x;
    c2_vi_x = muDoubleScalarCos(c2_vi_x);
    c2_wi_x = 2.0 * c2_x_1 - 2.0 * c2_x_3;
    c2_xi_x = c2_wi_x;
    c2_xi_x = muDoubleScalarCos(c2_xi_x);
    c2_j_A = c2_b_T_s * ((((((((((c2_bi_x * ((36.0 * c2_mpower(chartInstance,
      c2_l_1) * c2_l_2 * c2_mpower(chartInstance, c2_m_2) * c2_mpower
      (chartInstance, c2_x_2) + 12.0 * c2_mpower(chartInstance, c2_l_1) * c2_l_2
      * c2_m_1 * c2_m_2 * c2_mpower(chartInstance, c2_x_2)) + 36.0 * c2_mpower
      (chartInstance, c2_l_1) * c2_l_2 * c2_m_2 * c2_m_3 * c2_mpower
      (chartInstance, c2_x_2)) - 36.0 * c2_d_p1 * c2_l_2 * c2_m_2 * c2_x_2 *
      c2_di_x) - 36.0 * c2_d_p2 * c2_l_2 * c2_m_2 * c2_x_2 * c2_fi_x) + 36.0 *
      c2_d_p2 * c2_l_2 * c2_m_2 * c2_x_4 * c2_hi_x) + 18.0 * c2_l_1 * c2_mpower
      (chartInstance, c2_l_2) * c2_mpower(chartInstance, c2_m_2) * c2_mpower
      (chartInstance, c2_x_4) * c2_ji_x) - 36.0 * c2_g * c2_l_1 * c2_l_2 *
      c2_mpower(chartInstance, c2_m_2) * c2_li_x) + 36.0 * c2_l_1 * c2_l_2 *
      c2_mpower(chartInstance, c2_m_2) * c2_b_u * c2_ni_x) + 18.0 * c2_l_1 *
      c2_l_2 * c2_m_1 * c2_m_2 * c2_b_u * c2_pi_x) + 36.0 * c2_l_1 * c2_l_2 *
      c2_m_2 * c2_m_3 * c2_b_u * c2_ri_x) - 18.0 * c2_g * c2_l_1 * c2_l_2 *
                          c2_m_1 * c2_m_2 * c2_ti_x) - 36.0 * c2_g * c2_l_1 *
                         c2_l_2 * c2_m_2 * c2_m_3 * c2_vi_x);
    c2_i_B = c2_l_1 * c2_mpower(chartInstance, c2_l_2) * c2_m_2 * (((8.0 *
      c2_m_1 + 15.0 * c2_m_2) + 24.0 * c2_m_3) - 9.0 * c2_m_2 * c2_xi_x);
    c2_yi_x = c2_j_A;
    c2_jb_y = c2_i_B;
    c2_aj_x = c2_yi_x;
    c2_kb_y = c2_jb_y;
    c2_bj_x = c2_aj_x;
    c2_lb_y = c2_kb_y;
    c2_mb_y = c2_bj_x / c2_lb_y;
    c2_cj_x = 2.0 * c2_x_1 - 2.0 * c2_x_3;
    c2_dj_x = c2_cj_x;
    c2_dj_x = muDoubleScalarSin(c2_dj_x);
    c2_ej_x = c2_x_1 - c2_x_3;
    c2_fj_x = c2_ej_x;
    c2_fj_x = muDoubleScalarSin(c2_fj_x);
    c2_gj_x = c2_x_1 - c2_x_3;
    c2_hj_x = c2_gj_x;
    c2_hj_x = muDoubleScalarCos(c2_hj_x);
    c2_ij_x = c2_x_1 - c2_x_3;
    c2_jj_x = c2_ij_x;
    c2_jj_x = muDoubleScalarCos(c2_jj_x);
    c2_kj_x = c2_x_1 - c2_x_3;
    c2_lj_x = c2_kj_x;
    c2_lj_x = muDoubleScalarCos(c2_lj_x);
    c2_mj_x = c2_x_3;
    c2_nj_x = c2_mj_x;
    c2_nj_x = muDoubleScalarCos(c2_nj_x);
    c2_oj_x = c2_x_3;
    c2_pj_x = c2_oj_x;
    c2_pj_x = muDoubleScalarSin(c2_pj_x);
    c2_qj_x = 2.0 * c2_x_1 - 2.0 * c2_x_3;
    c2_rj_x = c2_qj_x;
    c2_rj_x = muDoubleScalarSin(c2_rj_x);
    c2_sj_x = 2.0 * c2_x_1 - c2_x_3;
    c2_tj_x = c2_sj_x;
    c2_tj_x = muDoubleScalarCos(c2_tj_x);
    c2_uj_x = 2.0 * c2_x_1 - c2_x_3;
    c2_vj_x = c2_uj_x;
    c2_vj_x = muDoubleScalarSin(c2_vj_x);
    c2_wj_x = c2_x_3;
    c2_xj_x = c2_wj_x;
    c2_xj_x = muDoubleScalarCos(c2_xj_x);
    c2_yj_x = c2_x_3;
    c2_ak_x = c2_yj_x;
    c2_ak_x = muDoubleScalarCos(c2_ak_x);
    c2_bk_x = c2_x_3;
    c2_ck_x = c2_bk_x;
    c2_ck_x = muDoubleScalarSin(c2_ck_x);
    c2_dk_x = c2_x_3;
    c2_ek_x = c2_dk_x;
    c2_ek_x = muDoubleScalarSin(c2_ek_x);
    c2_fk_x = 2.0 * c2_x_1 - c2_x_3;
    c2_gk_x = c2_fk_x;
    c2_gk_x = muDoubleScalarCos(c2_gk_x);
    c2_hk_x = 2.0 * c2_x_1 - c2_x_3;
    c2_ik_x = c2_hk_x;
    c2_ik_x = muDoubleScalarCos(c2_ik_x);
    c2_jk_x = 2.0 * c2_x_1 - c2_x_3;
    c2_kk_x = c2_jk_x;
    c2_kk_x = muDoubleScalarSin(c2_kk_x);
    c2_lk_x = 2.0 * c2_x_1 - c2_x_3;
    c2_mk_x = c2_lk_x;
    c2_mk_x = muDoubleScalarSin(c2_mk_x);
    c2_nk_x = 2.0 * c2_x_1 - 2.0 * c2_x_3;
    c2_ok_x = c2_nk_x;
    c2_ok_x = muDoubleScalarCos(c2_ok_x);
    c2_k_A = 18.0 * c2_b_T_s * c2_dj_x * ((((((((((((((((((((((c2_fj_x * ((36.0 *
      c2_mpower(chartInstance, c2_l_1) * c2_l_2 * c2_mpower(chartInstance,
      c2_m_2) * c2_mpower(chartInstance, c2_x_2) + 12.0 * c2_mpower
      (chartInstance, c2_l_1) * c2_l_2 * c2_m_1 * c2_m_2 * c2_mpower
      (chartInstance, c2_x_2)) + 36.0 * c2_mpower(chartInstance, c2_l_1) *
      c2_l_2 * c2_m_2 * c2_m_3 * c2_mpower(chartInstance, c2_x_2)) + 24.0 *
      c2_d_p2 * c2_l_1 * c2_m_1 * c2_x_2) + 72.0 * c2_d_p2 * c2_l_1 * c2_m_2 *
      c2_x_2) - 24.0 * c2_d_p2 * c2_l_1 * c2_m_1 * c2_x_4) + 72.0 * c2_d_p2 *
      c2_l_1 * c2_m_3 * c2_x_2) - 72.0 * c2_d_p2 * c2_l_1 * c2_m_2 * c2_x_4) -
      72.0 * c2_d_p2 * c2_l_1 * c2_m_3 * c2_x_4) + 36.0 * c2_d_p1 * c2_l_2 *
      c2_m_2 * c2_x_2 * c2_hj_x) + 36.0 * c2_d_p2 * c2_l_2 * c2_m_2 * c2_x_2 *
      c2_jj_x) - 36.0 * c2_d_p2 * c2_l_2 * c2_m_2 * c2_x_4 * c2_lj_x) + 18.0 *
      c2_l_1 * c2_l_2 * c2_mpower(chartInstance, c2_m_2) * c2_b_u * c2_nj_x) +
      18.0 * c2_g * c2_l_1 * c2_l_2 * c2_mpower(chartInstance, c2_m_2) * c2_pj_x)
      + 9.0 * c2_l_1 * c2_mpower(chartInstance, c2_l_2) * c2_mpower
      (chartInstance, c2_m_2) * c2_mpower(chartInstance, c2_x_4) * c2_rj_x) -
      18.0 * c2_l_1 * c2_l_2 * c2_mpower(chartInstance, c2_m_2) * c2_b_u *
      c2_tj_x) - 18.0 * c2_g * c2_l_1 * c2_l_2 * c2_mpower(chartInstance, c2_m_2)
      * c2_vj_x) + 3.0 * c2_l_1 * c2_l_2 * c2_m_1 * c2_m_2 * c2_b_u * c2_xj_x) +
      18.0 * c2_l_1 * c2_l_2 * c2_m_2 * c2_m_3 * c2_b_u * c2_ak_x) + 3.0 * c2_g *
      c2_l_1 * c2_l_2 * c2_m_1 * c2_m_2 * c2_ck_x) + 18.0 * c2_g * c2_l_1 *
      c2_l_2 * c2_m_2 * c2_m_3 * c2_ek_x) - 9.0 * c2_l_1 * c2_l_2 * c2_m_1 *
      c2_m_2 * c2_b_u * c2_gk_x) - 18.0 * c2_l_1 * c2_l_2 * c2_m_2 * c2_m_3 *
      c2_b_u * c2_ik_x) - 9.0 * c2_g * c2_l_1 * c2_l_2 * c2_m_1 * c2_m_2 *
      c2_kk_x) - 18.0 * c2_g * c2_l_1 * c2_l_2 * c2_m_2 * c2_m_3 * c2_mk_x);
    c2_j_B = c2_l_1 * c2_mpower(chartInstance, c2_l_2) * c2_mpower(chartInstance,
      ((8.0 * c2_m_1 + 15.0 * c2_m_2) + 24.0 * c2_m_3) - 9.0 * c2_m_2 * c2_ok_x);
    c2_pk_x = c2_k_A;
    c2_nb_y = c2_j_B;
    c2_qk_x = c2_pk_x;
    c2_ob_y = c2_nb_y;
    c2_rk_x = c2_qk_x;
    c2_pb_y = c2_ob_y;
    c2_qb_y = c2_rk_x / c2_pb_y;
    c2_sk_x = c2_x_1 - c2_x_3;
    c2_tk_x = c2_sk_x;
    c2_tk_x = muDoubleScalarSin(c2_tk_x);
    c2_uk_x = c2_x_1 - c2_x_3;
    c2_vk_x = c2_uk_x;
    c2_vk_x = muDoubleScalarCos(c2_vk_x);
    c2_wk_x = c2_x_1 - c2_x_3;
    c2_xk_x = c2_wk_x;
    c2_xk_x = muDoubleScalarCos(c2_xk_x);
    c2_yk_x = 2.0 * c2_x_1 - 2.0 * c2_x_3;
    c2_al_x = c2_yk_x;
    c2_al_x = muDoubleScalarCos(c2_al_x);
    c2_l_A = c2_b_T_s * (((((c2_tk_x * ((72.0 * c2_mpower(chartInstance, c2_l_1)
      * c2_l_2 * c2_mpower(chartInstance, c2_m_2) * c2_x_2 + 24.0 * c2_mpower
      (chartInstance, c2_l_1) * c2_l_2 * c2_m_1 * c2_m_2 * c2_x_2) + 72.0 *
      c2_mpower(chartInstance, c2_l_1) * c2_l_2 * c2_m_2 * c2_m_3 * c2_x_2) +
      24.0 * c2_d_p2 * c2_l_1 * c2_m_1) + 72.0 * c2_d_p2 * c2_l_1 * c2_m_2) +
      72.0 * c2_d_p2 * c2_l_1 * c2_m_3) + 36.0 * c2_d_p1 * c2_l_2 * c2_m_2 *
                          c2_vk_x) + 36.0 * c2_d_p2 * c2_l_2 * c2_m_2 * c2_xk_x);
    c2_k_B = c2_l_1 * c2_mpower(chartInstance, c2_l_2) * c2_m_2 * (((8.0 *
      c2_m_1 + 15.0 * c2_m_2) + 24.0 * c2_m_3) - 9.0 * c2_m_2 * c2_al_x);
    c2_bl_x = c2_l_A;
    c2_rb_y = c2_k_B;
    c2_cl_x = c2_bl_x;
    c2_sb_y = c2_rb_y;
    c2_dl_x = c2_cl_x;
    c2_tb_y = c2_sb_y;
    c2_ub_y = c2_dl_x / c2_tb_y;
    c2_el_x = 2.0 * c2_x_1 - 2.0 * c2_x_3;
    c2_fl_x = c2_el_x;
    c2_fl_x = muDoubleScalarSin(c2_fl_x);
    c2_gl_x = c2_x_1 - c2_x_3;
    c2_hl_x = c2_gl_x;
    c2_hl_x = muDoubleScalarSin(c2_hl_x);
    c2_il_x = c2_x_1 - c2_x_3;
    c2_jl_x = c2_il_x;
    c2_jl_x = muDoubleScalarCos(c2_jl_x);
    c2_kl_x = c2_x_1 - c2_x_3;
    c2_ll_x = c2_kl_x;
    c2_ll_x = muDoubleScalarCos(c2_ll_x);
    c2_ml_x = c2_x_1 - c2_x_3;
    c2_nl_x = c2_ml_x;
    c2_nl_x = muDoubleScalarCos(c2_nl_x);
    c2_ol_x = c2_x_3;
    c2_pl_x = c2_ol_x;
    c2_pl_x = muDoubleScalarCos(c2_pl_x);
    c2_ql_x = c2_x_3;
    c2_rl_x = c2_ql_x;
    c2_rl_x = muDoubleScalarSin(c2_rl_x);
    c2_sl_x = 2.0 * c2_x_1 - 2.0 * c2_x_3;
    c2_tl_x = c2_sl_x;
    c2_tl_x = muDoubleScalarSin(c2_tl_x);
    c2_ul_x = 2.0 * c2_x_1 - c2_x_3;
    c2_vl_x = c2_ul_x;
    c2_vl_x = muDoubleScalarCos(c2_vl_x);
    c2_wl_x = 2.0 * c2_x_1 - c2_x_3;
    c2_xl_x = c2_wl_x;
    c2_xl_x = muDoubleScalarSin(c2_xl_x);
    c2_yl_x = c2_x_3;
    c2_am_x = c2_yl_x;
    c2_am_x = muDoubleScalarCos(c2_am_x);
    c2_bm_x = c2_x_3;
    c2_cm_x = c2_bm_x;
    c2_cm_x = muDoubleScalarCos(c2_cm_x);
    c2_dm_x = c2_x_3;
    c2_em_x = c2_dm_x;
    c2_em_x = muDoubleScalarSin(c2_em_x);
    c2_fm_x = c2_x_3;
    c2_gm_x = c2_fm_x;
    c2_gm_x = muDoubleScalarSin(c2_gm_x);
    c2_hm_x = 2.0 * c2_x_1 - c2_x_3;
    c2_im_x = c2_hm_x;
    c2_im_x = muDoubleScalarCos(c2_im_x);
    c2_jm_x = 2.0 * c2_x_1 - c2_x_3;
    c2_km_x = c2_jm_x;
    c2_km_x = muDoubleScalarCos(c2_km_x);
    c2_lm_x = 2.0 * c2_x_1 - c2_x_3;
    c2_mm_x = c2_lm_x;
    c2_mm_x = muDoubleScalarSin(c2_mm_x);
    c2_nm_x = 2.0 * c2_x_1 - c2_x_3;
    c2_om_x = c2_nm_x;
    c2_om_x = muDoubleScalarSin(c2_om_x);
    c2_pm_x = 2.0 * c2_x_1 - 2.0 * c2_x_3;
    c2_qm_x = c2_pm_x;
    c2_qm_x = muDoubleScalarCos(c2_qm_x);
    c2_m_A = 18.0 * c2_b_T_s * c2_fl_x * ((((((((((((((((((((((c2_hl_x * ((36.0 *
      c2_mpower(chartInstance, c2_l_1) * c2_l_2 * c2_mpower(chartInstance,
      c2_m_2) * c2_mpower(chartInstance, c2_x_2) + 12.0 * c2_mpower
      (chartInstance, c2_l_1) * c2_l_2 * c2_m_1 * c2_m_2 * c2_mpower
      (chartInstance, c2_x_2)) + 36.0 * c2_mpower(chartInstance, c2_l_1) *
      c2_l_2 * c2_m_2 * c2_m_3 * c2_mpower(chartInstance, c2_x_2)) + 24.0 *
      c2_d_p2 * c2_l_1 * c2_m_1 * c2_x_2) + 72.0 * c2_d_p2 * c2_l_1 * c2_m_2 *
      c2_x_2) - 24.0 * c2_d_p2 * c2_l_1 * c2_m_1 * c2_x_4) + 72.0 * c2_d_p2 *
      c2_l_1 * c2_m_3 * c2_x_2) - 72.0 * c2_d_p2 * c2_l_1 * c2_m_2 * c2_x_4) -
      72.0 * c2_d_p2 * c2_l_1 * c2_m_3 * c2_x_4) + 36.0 * c2_d_p1 * c2_l_2 *
      c2_m_2 * c2_x_2 * c2_jl_x) + 36.0 * c2_d_p2 * c2_l_2 * c2_m_2 * c2_x_2 *
      c2_ll_x) - 36.0 * c2_d_p2 * c2_l_2 * c2_m_2 * c2_x_4 * c2_nl_x) + 18.0 *
      c2_l_1 * c2_l_2 * c2_mpower(chartInstance, c2_m_2) * c2_b_u * c2_pl_x) +
      18.0 * c2_g * c2_l_1 * c2_l_2 * c2_mpower(chartInstance, c2_m_2) * c2_rl_x)
      + 9.0 * c2_l_1 * c2_mpower(chartInstance, c2_l_2) * c2_mpower
      (chartInstance, c2_m_2) * c2_mpower(chartInstance, c2_x_4) * c2_tl_x) -
      18.0 * c2_l_1 * c2_l_2 * c2_mpower(chartInstance, c2_m_2) * c2_b_u *
      c2_vl_x) - 18.0 * c2_g * c2_l_1 * c2_l_2 * c2_mpower(chartInstance, c2_m_2)
      * c2_xl_x) + 3.0 * c2_l_1 * c2_l_2 * c2_m_1 * c2_m_2 * c2_b_u * c2_am_x) +
      18.0 * c2_l_1 * c2_l_2 * c2_m_2 * c2_m_3 * c2_b_u * c2_cm_x) + 3.0 * c2_g *
      c2_l_1 * c2_l_2 * c2_m_1 * c2_m_2 * c2_em_x) + 18.0 * c2_g * c2_l_1 *
      c2_l_2 * c2_m_2 * c2_m_3 * c2_gm_x) - 9.0 * c2_l_1 * c2_l_2 * c2_m_1 *
      c2_m_2 * c2_b_u * c2_im_x) - 18.0 * c2_l_1 * c2_l_2 * c2_m_2 * c2_m_3 *
      c2_b_u * c2_km_x) - 9.0 * c2_g * c2_l_1 * c2_l_2 * c2_m_1 * c2_m_2 *
      c2_mm_x) - 18.0 * c2_g * c2_l_1 * c2_l_2 * c2_m_2 * c2_m_3 * c2_om_x);
    c2_l_B = c2_l_1 * c2_mpower(chartInstance, c2_l_2) * c2_mpower(chartInstance,
      ((8.0 * c2_m_1 + 15.0 * c2_m_2) + 24.0 * c2_m_3) - 9.0 * c2_m_2 * c2_qm_x);
    c2_rm_x = c2_m_A;
    c2_vb_y = c2_l_B;
    c2_sm_x = c2_rm_x;
    c2_wb_y = c2_vb_y;
    c2_tm_x = c2_sm_x;
    c2_xb_y = c2_wb_y;
    c2_yb_y = c2_tm_x / c2_xb_y;
    c2_um_x = c2_x_1 - c2_x_3;
    c2_vm_x = c2_um_x;
    c2_vm_x = muDoubleScalarCos(c2_vm_x);
    c2_wm_x = c2_x_1 - c2_x_3;
    c2_xm_x = c2_wm_x;
    c2_xm_x = muDoubleScalarSin(c2_xm_x);
    c2_ym_x = c2_x_1 - c2_x_3;
    c2_an_x = c2_ym_x;
    c2_an_x = muDoubleScalarSin(c2_an_x);
    c2_bn_x = c2_x_1 - c2_x_3;
    c2_cn_x = c2_bn_x;
    c2_cn_x = muDoubleScalarSin(c2_cn_x);
    c2_dn_x = c2_x_3;
    c2_en_x = c2_dn_x;
    c2_en_x = muDoubleScalarCos(c2_en_x);
    c2_fn_x = c2_x_3;
    c2_gn_x = c2_fn_x;
    c2_gn_x = muDoubleScalarSin(c2_gn_x);
    c2_hn_x = 2.0 * c2_x_1 - 2.0 * c2_x_3;
    c2_in_x = c2_hn_x;
    c2_in_x = muDoubleScalarCos(c2_in_x);
    c2_jn_x = 2.0 * c2_x_1 - c2_x_3;
    c2_kn_x = c2_jn_x;
    c2_kn_x = muDoubleScalarCos(c2_kn_x);
    c2_ln_x = 2.0 * c2_x_1 - c2_x_3;
    c2_mn_x = c2_ln_x;
    c2_mn_x = muDoubleScalarSin(c2_mn_x);
    c2_nn_x = 2.0 * c2_x_1 - c2_x_3;
    c2_on_x = c2_nn_x;
    c2_on_x = muDoubleScalarSin(c2_on_x);
    c2_pn_x = 2.0 * c2_x_1 - c2_x_3;
    c2_qn_x = c2_pn_x;
    c2_qn_x = muDoubleScalarSin(c2_qn_x);
    c2_rn_x = c2_x_3;
    c2_sn_x = c2_rn_x;
    c2_sn_x = muDoubleScalarCos(c2_sn_x);
    c2_tn_x = c2_x_3;
    c2_un_x = c2_tn_x;
    c2_un_x = muDoubleScalarCos(c2_un_x);
    c2_vn_x = c2_x_3;
    c2_wn_x = c2_vn_x;
    c2_wn_x = muDoubleScalarSin(c2_wn_x);
    c2_xn_x = c2_x_3;
    c2_yn_x = c2_xn_x;
    c2_yn_x = muDoubleScalarSin(c2_yn_x);
    c2_ao_x = 2.0 * c2_x_1 - c2_x_3;
    c2_bo_x = c2_ao_x;
    c2_bo_x = muDoubleScalarCos(c2_bo_x);
    c2_co_x = 2.0 * c2_x_1 - c2_x_3;
    c2_do_x = c2_co_x;
    c2_do_x = muDoubleScalarCos(c2_do_x);
    c2_eo_x = 2.0 * c2_x_1 - 2.0 * c2_x_3;
    c2_fo_x = c2_eo_x;
    c2_fo_x = muDoubleScalarCos(c2_fo_x);
    c2_n_A = c2_b_T_s * ((((((((((((((((c2_vm_x * ((36.0 * c2_mpower
      (chartInstance, c2_l_1) * c2_l_2 * c2_mpower(chartInstance, c2_m_2) *
      c2_mpower(chartInstance, c2_x_2) + 12.0 * c2_mpower(chartInstance, c2_l_1)
      * c2_l_2 * c2_m_1 * c2_m_2 * c2_mpower(chartInstance, c2_x_2)) + 36.0 *
      c2_mpower(chartInstance, c2_l_1) * c2_l_2 * c2_m_2 * c2_m_3 * c2_mpower
      (chartInstance, c2_x_2)) - 36.0 * c2_d_p1 * c2_l_2 * c2_m_2 * c2_x_2 *
      c2_xm_x) - 36.0 * c2_d_p2 * c2_l_2 * c2_m_2 * c2_x_2 * c2_an_x) + 36.0 *
      c2_d_p2 * c2_l_2 * c2_m_2 * c2_x_4 * c2_cn_x) - 18.0 * c2_g * c2_l_1 *
      c2_l_2 * c2_mpower(chartInstance, c2_m_2) * c2_en_x) + 18.0 * c2_l_1 *
      c2_l_2 * c2_mpower(chartInstance, c2_m_2) * c2_b_u * c2_gn_x) + 18.0 *
      c2_l_1 * c2_mpower(chartInstance, c2_l_2) * c2_mpower(chartInstance,
      c2_m_2) * c2_mpower(chartInstance, c2_x_4) * c2_in_x) - 18.0 * c2_g *
      c2_l_1 * c2_l_2 * c2_mpower(chartInstance, c2_m_2) * c2_kn_x) + 18.0 *
      c2_l_1 * c2_l_2 * c2_mpower(chartInstance, c2_m_2) * c2_b_u * c2_mn_x) +
      9.0 * c2_l_1 * c2_l_2 * c2_m_1 * c2_m_2 * c2_b_u * c2_on_x) + 18.0 *
      c2_l_1 * c2_l_2 * c2_m_2 * c2_m_3 * c2_b_u * c2_qn_x) - 3.0 * c2_g *
      c2_l_1 * c2_l_2 * c2_m_1 * c2_m_2 * c2_sn_x) - 18.0 * c2_g * c2_l_1 *
      c2_l_2 * c2_m_2 * c2_m_3 * c2_un_x) + 3.0 * c2_l_1 * c2_l_2 * c2_m_1 *
      c2_m_2 * c2_b_u * c2_wn_x) + 18.0 * c2_l_1 * c2_l_2 * c2_m_2 * c2_m_3 *
      c2_b_u * c2_yn_x) - 9.0 * c2_g * c2_l_1 * c2_l_2 * c2_m_1 * c2_m_2 *
                          c2_bo_x) - 18.0 * c2_g * c2_l_1 * c2_l_2 * c2_m_2 *
                         c2_m_3 * c2_do_x);
    c2_m_B = c2_l_1 * c2_mpower(chartInstance, c2_l_2) * c2_m_2 * (((8.0 *
      c2_m_1 + 15.0 * c2_m_2) + 24.0 * c2_m_3) - 9.0 * c2_m_2 * c2_fo_x);
    c2_go_x = c2_n_A;
    c2_ac_y = c2_m_B;
    c2_ho_x = c2_go_x;
    c2_bc_y = c2_ac_y;
    c2_io_x = c2_ho_x;
    c2_cc_y = c2_bc_y;
    c2_dc_y = c2_io_x / c2_cc_y;
    c2_jo_x = c2_x_1 - c2_x_3;
    c2_ko_x = c2_jo_x;
    c2_ko_x = muDoubleScalarCos(c2_ko_x);
    c2_lo_x = 2.0 * c2_x_1 - 2.0 * c2_x_3;
    c2_mo_x = c2_lo_x;
    c2_mo_x = muDoubleScalarSin(c2_mo_x);
    c2_no_x = 2.0 * c2_x_1 - 2.0 * c2_x_3;
    c2_oo_x = c2_no_x;
    c2_oo_x = muDoubleScalarCos(c2_oo_x);
    c2_o_A = c2_b_T_s * ((((24.0 * c2_d_p2 * c2_l_1 * c2_m_1 + 72.0 * c2_d_p2 *
      c2_l_1 * c2_m_2) + 72.0 * c2_d_p2 * c2_l_1 * c2_m_3) + 36.0 * c2_d_p2 *
                          c2_l_2 * c2_m_2 * c2_ko_x) - 18.0 * c2_l_1 * c2_mpower
                         (chartInstance, c2_l_2) * c2_mpower(chartInstance,
      c2_m_2) * c2_x_4 * c2_mo_x);
    c2_n_B = c2_l_1 * c2_mpower(chartInstance, c2_l_2) * c2_m_2 * (((8.0 *
      c2_m_1 + 15.0 * c2_m_2) + 24.0 * c2_m_3) - 9.0 * c2_m_2 * c2_oo_x);
    c2_po_x = c2_o_A;
    c2_ec_y = c2_n_B;
    c2_qo_x = c2_po_x;
    c2_fc_y = c2_ec_y;
    c2_ro_x = c2_qo_x;
    c2_gc_y = c2_fc_y;
    c2_hc_y = c2_ro_x / c2_gc_y;
    c2_A[0] = 1.0;
    c2_A[4] = c2_b_T_s;
    c2_A[8] = 0.0;
    c2_A[12] = 0.0;
    c2_A[1] = c2_n_y - c2_r_y;
    c2_A[5] = 1.0 - c2_v_y;
    c2_A[9] = c2_ab_y + c2_eb_y;
    c2_A[13] = c2_ib_y;
    c2_A[2] = 0.0;
    c2_A[6] = 0.0;
    c2_A[10] = 1.0;
    c2_A[14] = c2_b_T_s;
    c2_A[3] = c2_mb_y - c2_qb_y;
    c2_A[7] = c2_ub_y;
    c2_A[11] = c2_yb_y - c2_dc_y;
    c2_A[15] = 1.0 - c2_hc_y;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 39);
    for (c2_i22 = 0; c2_i22 < 4; c2_i22++) {
      c2_C[c2_i22] = c2_a[c2_i22];
    }

    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 42);
    for (c2_i23 = 0; c2_i23 < 16; c2_i23++) {
      c2_e_hoistedGlobal[c2_i23] = chartInstance->c2_P_p[c2_i23];
    }

    for (c2_i24 = 0; c2_i24 < 16; c2_i24++) {
      c2_b_a[c2_i24] = c2_A[c2_i24];
    }

    c2_b_eml_scalar_eg(chartInstance);
    c2_b_eml_scalar_eg(chartInstance);
    c2_threshold(chartInstance);
    for (c2_i25 = 0; c2_i25 < 4; c2_i25++) {
      c2_i26 = 0;
      for (c2_i27 = 0; c2_i27 < 4; c2_i27++) {
        c2_ic_y[c2_i26 + c2_i25] = 0.0;
        c2_i28 = 0;
        for (c2_i29 = 0; c2_i29 < 4; c2_i29++) {
          c2_ic_y[c2_i26 + c2_i25] += c2_b_a[c2_i28 + c2_i25] *
            c2_e_hoistedGlobal[c2_i29 + c2_i26];
          c2_i28 += 4;
        }

        c2_i26 += 4;
      }
    }

    c2_i30 = 0;
    for (c2_i31 = 0; c2_i31 < 4; c2_i31++) {
      c2_i32 = 0;
      for (c2_i33 = 0; c2_i33 < 4; c2_i33++) {
        c2_b[c2_i33 + c2_i30] = c2_A[c2_i32 + c2_i31];
        c2_i32 += 4;
      }

      c2_i30 += 4;
    }

    c2_b_eml_scalar_eg(chartInstance);
    c2_b_eml_scalar_eg(chartInstance);
    c2_threshold(chartInstance);
    for (c2_i34 = 0; c2_i34 < 4; c2_i34++) {
      c2_i35 = 0;
      for (c2_i36 = 0; c2_i36 < 4; c2_i36++) {
        c2_e_hoistedGlobal[c2_i35 + c2_i34] = 0.0;
        c2_i37 = 0;
        for (c2_i38 = 0; c2_i38 < 4; c2_i38++) {
          c2_e_hoistedGlobal[c2_i35 + c2_i34] += c2_ic_y[c2_i37 + c2_i34] *
            c2_b[c2_i38 + c2_i35];
          c2_i37 += 4;
        }

        c2_i35 += 4;
      }
    }

    for (c2_i39 = 0; c2_i39 < 16; c2_i39++) {
      c2_b_P[c2_i39] = c2_e_hoistedGlobal[c2_i39] + c2_b_Q[c2_i39];
    }

    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 43);
    for (c2_i40 = 0; c2_i40 < 16; c2_i40++) {
      c2_b_a[c2_i40] = c2_b_P[c2_i40];
    }

    c2_c_eml_scalar_eg(chartInstance);
    c2_c_eml_scalar_eg(chartInstance);
    c2_threshold(chartInstance);
    for (c2_i41 = 0; c2_i41 < 4; c2_i41++) {
      c2_jc_y[c2_i41] = 0.0;
      c2_i42 = 0;
      for (c2_i43 = 0; c2_i43 < 4; c2_i43++) {
        c2_jc_y[c2_i41] += c2_b_a[c2_i42 + c2_i41] * c2_b_b[c2_i43];
        c2_i42 += 4;
      }
    }

    for (c2_i44 = 0; c2_i44 < 16; c2_i44++) {
      c2_b[c2_i44] = c2_b_P[c2_i44];
    }

    c2_d_eml_scalar_eg(chartInstance);
    c2_d_eml_scalar_eg(chartInstance);
    c2_threshold(chartInstance);
    c2_i45 = 0;
    for (c2_i46 = 0; c2_i46 < 4; c2_i46++) {
      c2_kc_y[c2_i46] = 0.0;
      for (c2_i47 = 0; c2_i47 < 4; c2_i47++) {
        c2_kc_y[c2_i46] += c2_a[c2_i47] * c2_b[c2_i47 + c2_i45];
      }

      c2_i45 += 4;
    }

    for (c2_i48 = 0; c2_i48 < 4; c2_i48++) {
      c2_lc_y[c2_i48] = c2_kc_y[c2_i48];
    }

    for (c2_i49 = 0; c2_i49 < 4; c2_i49++) {
      c2_c_b[c2_i49] = c2_b_b[c2_i49];
    }

    c2_mc_y = c2_eml_xdotu(chartInstance, c2_lc_y, c2_c_b);
    c2_o_B = c2_mc_y + c2_b_R;
    c2_nc_y = c2_o_B;
    c2_oc_y = c2_nc_y;
    c2_pc_y = c2_oc_y;
    for (c2_i50 = 0; c2_i50 < 4; c2_i50++) {
      c2_b_K[c2_i50] = c2_jc_y[c2_i50] / c2_pc_y;
    }

    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 44);
    for (c2_i51 = 0; c2_i51 < 4; c2_i51++) {
      c2_jc_y[c2_i51] = c2_b_x[c2_i51];
    }

    for (c2_i52 = 0; c2_i52 < 4; c2_i52++) {
      c2_c_a[c2_i52] = c2_a[c2_i52];
    }

    for (c2_i53 = 0; c2_i53 < 4; c2_i53++) {
      c2_qc_y[c2_i53] = c2_jc_y[c2_i53];
    }

    c2_rc_y = c2_eml_xdotu(chartInstance, c2_c_a, c2_qc_y);
    for (c2_i54 = 0; c2_i54 < 4; c2_i54++) {
      c2_jc_y[c2_i54] = c2_b_K[c2_i54];
    }

    c2_d_b = c2_b_y - c2_rc_y;
    for (c2_i55 = 0; c2_i55 < 4; c2_i55++) {
      c2_jc_y[c2_i55] *= c2_d_b;
    }

    for (c2_i56 = 0; c2_i56 < 4; c2_i56++) {
      c2_b_x[c2_i56] += c2_jc_y[c2_i56];
    }

    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 45);
    for (c2_i57 = 0; c2_i57 < 4; c2_i57++) {
      c2_jc_y[c2_i57] = c2_b_K[c2_i57];
    }

    for (c2_i58 = 0; c2_i58 < 4; c2_i58++) {
      c2_i59 = 0;
      for (c2_i60 = 0; c2_i60 < 4; c2_i60++) {
        c2_ic_y[c2_i59 + c2_i58] = c2_jc_y[c2_i58] * c2_a[c2_i60];
        c2_i59 += 4;
      }
    }

    c2_eye(chartInstance, c2_b_a);
    for (c2_i61 = 0; c2_i61 < 16; c2_i61++) {
      c2_b_a[c2_i61] -= c2_ic_y[c2_i61];
    }

    for (c2_i62 = 0; c2_i62 < 16; c2_i62++) {
      c2_b[c2_i62] = c2_b_P[c2_i62];
    }

    c2_b_eml_scalar_eg(chartInstance);
    c2_b_eml_scalar_eg(chartInstance);
    c2_threshold(chartInstance);
    for (c2_i63 = 0; c2_i63 < 4; c2_i63++) {
      c2_i64 = 0;
      for (c2_i65 = 0; c2_i65 < 4; c2_i65++) {
        c2_ic_y[c2_i64 + c2_i63] = 0.0;
        c2_i66 = 0;
        for (c2_i67 = 0; c2_i67 < 4; c2_i67++) {
          c2_ic_y[c2_i64 + c2_i63] += c2_b_a[c2_i66 + c2_i63] * c2_b[c2_i67 +
            c2_i64];
          c2_i66 += 4;
        }

        c2_i64 += 4;
      }
    }

    for (c2_i68 = 0; c2_i68 < 16; c2_i68++) {
      chartInstance->c2_P_p[c2_i68] = c2_ic_y[c2_i68];
    }

    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 47);
    for (c2_i69 = 0; c2_i69 < 4; c2_i69++) {
      chartInstance->c2_x_p[c2_i69] = c2_b_x[c2_i69];
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, -47);
  _SFD_SYMBOL_SCOPE_POP();
  for (c2_i70 = 0; c2_i70 < 4; c2_i70++) {
    (*chartInstance->c2_x)[c2_i70] = c2_b_x[c2_i70];
  }

  for (c2_i71 = 0; c2_i71 < 4; c2_i71++) {
    (*chartInstance->c2_K)[c2_i71] = c2_b_K[c2_i71];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c2_sfEvent);
}

static void initSimStructsc2_dp_EKF_ausschwing
  (SFc2_dp_EKF_ausschwingInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber, uint32_T c2_instanceNumber)
{
  (void)c2_machineNumber;
  (void)c2_chartNumber;
  (void)c2_instanceNumber;
}

static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, void *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i72;
  int32_T c2_i73;
  int32_T c2_i74;
  real_T c2_b_inData[16];
  int32_T c2_i75;
  int32_T c2_i76;
  int32_T c2_i77;
  real_T c2_b_u[16];
  const mxArray *c2_b_y = NULL;
  SFc2_dp_EKF_ausschwingInstanceStruct *chartInstance;
  chartInstance = (SFc2_dp_EKF_ausschwingInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_i72 = 0;
  for (c2_i73 = 0; c2_i73 < 4; c2_i73++) {
    for (c2_i74 = 0; c2_i74 < 4; c2_i74++) {
      c2_b_inData[c2_i74 + c2_i72] = (*(real_T (*)[16])c2_inData)[c2_i74 +
        c2_i72];
    }

    c2_i72 += 4;
  }

  c2_i75 = 0;
  for (c2_i76 = 0; c2_i76 < 4; c2_i76++) {
    for (c2_i77 = 0; c2_i77 < 4; c2_i77++) {
      c2_b_u[c2_i77 + c2_i75] = c2_b_inData[c2_i77 + c2_i75];
    }

    c2_i75 += 4;
  }

  c2_b_y = NULL;
  if (!chartInstance->c2_P_p_not_empty) {
    sf_mex_assign(&c2_b_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_b_u, 0, 0U, 1U, 0U, 2, 4, 4),
                  false);
  }

  sf_mex_assign(&c2_mxArrayOutData, c2_b_y, false);
  return c2_mxArrayOutData;
}

static void c2_emlrt_marshallIn(SFc2_dp_EKF_ausschwingInstanceStruct
  *chartInstance, const mxArray *c2_b_P_p, const char_T *c2_identifier, real_T
  c2_b_y[16])
{
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_P_p), &c2_thisId, c2_b_y);
  sf_mex_destroy(&c2_b_P_p);
}

static void c2_b_emlrt_marshallIn(SFc2_dp_EKF_ausschwingInstanceStruct
  *chartInstance, const mxArray *c2_b_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_b_y[16])
{
  real_T c2_dv4[16];
  int32_T c2_i78;
  if (mxIsEmpty(c2_b_u)) {
    chartInstance->c2_P_p_not_empty = false;
  } else {
    chartInstance->c2_P_p_not_empty = true;
    sf_mex_import(c2_parentId, sf_mex_dup(c2_b_u), c2_dv4, 1, 0, 0U, 1, 0U, 2, 4,
                  4);
    for (c2_i78 = 0; c2_i78 < 16; c2_i78++) {
      c2_b_y[c2_i78] = c2_dv4[c2_i78];
    }
  }

  sf_mex_destroy(&c2_b_u);
}

static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_P_p;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_b_y[16];
  int32_T c2_i79;
  int32_T c2_i80;
  int32_T c2_i81;
  SFc2_dp_EKF_ausschwingInstanceStruct *chartInstance;
  chartInstance = (SFc2_dp_EKF_ausschwingInstanceStruct *)chartInstanceVoid;
  c2_b_P_p = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_P_p), &c2_thisId, c2_b_y);
  sf_mex_destroy(&c2_b_P_p);
  c2_i79 = 0;
  for (c2_i80 = 0; c2_i80 < 4; c2_i80++) {
    for (c2_i81 = 0; c2_i81 < 4; c2_i81++) {
      (*(real_T (*)[16])c2_outData)[c2_i81 + c2_i79] = c2_b_y[c2_i81 + c2_i79];
    }

    c2_i79 += 4;
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i82;
  real_T c2_b_inData[4];
  int32_T c2_i83;
  real_T c2_b_u[4];
  const mxArray *c2_b_y = NULL;
  SFc2_dp_EKF_ausschwingInstanceStruct *chartInstance;
  chartInstance = (SFc2_dp_EKF_ausschwingInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  for (c2_i82 = 0; c2_i82 < 4; c2_i82++) {
    c2_b_inData[c2_i82] = (*(real_T (*)[4])c2_inData)[c2_i82];
  }

  for (c2_i83 = 0; c2_i83 < 4; c2_i83++) {
    c2_b_u[c2_i83] = c2_b_inData[c2_i83];
  }

  c2_b_y = NULL;
  if (!chartInstance->c2_x_p_not_empty) {
    sf_mex_assign(&c2_b_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_b_u, 0, 0U, 1U, 0U, 1, 4),
                  false);
  }

  sf_mex_assign(&c2_mxArrayOutData, c2_b_y, false);
  return c2_mxArrayOutData;
}

static void c2_c_emlrt_marshallIn(SFc2_dp_EKF_ausschwingInstanceStruct
  *chartInstance, const mxArray *c2_b_x_p, const char_T *c2_identifier, real_T
  c2_b_y[4])
{
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_x_p), &c2_thisId, c2_b_y);
  sf_mex_destroy(&c2_b_x_p);
}

static void c2_d_emlrt_marshallIn(SFc2_dp_EKF_ausschwingInstanceStruct
  *chartInstance, const mxArray *c2_b_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_b_y[4])
{
  real_T c2_dv5[4];
  int32_T c2_i84;
  if (mxIsEmpty(c2_b_u)) {
    chartInstance->c2_x_p_not_empty = false;
  } else {
    chartInstance->c2_x_p_not_empty = true;
    sf_mex_import(c2_parentId, sf_mex_dup(c2_b_u), c2_dv5, 1, 0, 0U, 1, 0U, 1, 4);
    for (c2_i84 = 0; c2_i84 < 4; c2_i84++) {
      c2_b_y[c2_i84] = c2_dv5[c2_i84];
    }
  }

  sf_mex_destroy(&c2_b_u);
}

static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_x_p;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_b_y[4];
  int32_T c2_i85;
  SFc2_dp_EKF_ausschwingInstanceStruct *chartInstance;
  chartInstance = (SFc2_dp_EKF_ausschwingInstanceStruct *)chartInstanceVoid;
  c2_b_x_p = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_x_p), &c2_thisId, c2_b_y);
  sf_mex_destroy(&c2_b_x_p);
  for (c2_i85 = 0; c2_i85 < 4; c2_i85++) {
    (*(real_T (*)[4])c2_outData)[c2_i85] = c2_b_y[c2_i85];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_c_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i86;
  real_T c2_b_inData[4];
  int32_T c2_i87;
  real_T c2_b_u[4];
  const mxArray *c2_b_y = NULL;
  SFc2_dp_EKF_ausschwingInstanceStruct *chartInstance;
  chartInstance = (SFc2_dp_EKF_ausschwingInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  for (c2_i86 = 0; c2_i86 < 4; c2_i86++) {
    c2_b_inData[c2_i86] = (*(real_T (*)[4])c2_inData)[c2_i86];
  }

  for (c2_i87 = 0; c2_i87 < 4; c2_i87++) {
    c2_b_u[c2_i87] = c2_b_inData[c2_i87];
  }

  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_b_u, 0, 0U, 1U, 0U, 1, 4), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_b_y, false);
  return c2_mxArrayOutData;
}

static void c2_e_emlrt_marshallIn(SFc2_dp_EKF_ausschwingInstanceStruct
  *chartInstance, const mxArray *c2_b_K, const char_T *c2_identifier, real_T
  c2_b_y[4])
{
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_K), &c2_thisId, c2_b_y);
  sf_mex_destroy(&c2_b_K);
}

static void c2_f_emlrt_marshallIn(SFc2_dp_EKF_ausschwingInstanceStruct
  *chartInstance, const mxArray *c2_b_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_b_y[4])
{
  real_T c2_dv6[4];
  int32_T c2_i88;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_b_u), c2_dv6, 1, 0, 0U, 1, 0U, 1, 4);
  for (c2_i88 = 0; c2_i88 < 4; c2_i88++) {
    c2_b_y[c2_i88] = c2_dv6[c2_i88];
  }

  sf_mex_destroy(&c2_b_u);
}

static void c2_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_K;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_b_y[4];
  int32_T c2_i89;
  SFc2_dp_EKF_ausschwingInstanceStruct *chartInstance;
  chartInstance = (SFc2_dp_EKF_ausschwingInstanceStruct *)chartInstanceVoid;
  c2_b_K = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_K), &c2_thisId, c2_b_y);
  sf_mex_destroy(&c2_b_K);
  for (c2_i89 = 0; c2_i89 < 4; c2_i89++) {
    (*(real_T (*)[4])c2_outData)[c2_i89] = c2_b_y[c2_i89];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_d_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  real_T c2_b_u;
  const mxArray *c2_b_y = NULL;
  SFc2_dp_EKF_ausschwingInstanceStruct *chartInstance;
  chartInstance = (SFc2_dp_EKF_ausschwingInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_b_u = *(real_T *)c2_inData;
  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", &c2_b_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_b_y, false);
  return c2_mxArrayOutData;
}

static const mxArray *c2_e_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i90;
  real_T c2_b_inData[8];
  int32_T c2_i91;
  real_T c2_b_u[8];
  const mxArray *c2_b_y = NULL;
  SFc2_dp_EKF_ausschwingInstanceStruct *chartInstance;
  chartInstance = (SFc2_dp_EKF_ausschwingInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  for (c2_i90 = 0; c2_i90 < 8; c2_i90++) {
    c2_b_inData[c2_i90] = (*(real_T (*)[8])c2_inData)[c2_i90];
  }

  for (c2_i91 = 0; c2_i91 < 8; c2_i91++) {
    c2_b_u[c2_i91] = c2_b_inData[c2_i91];
  }

  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_b_u, 0, 0U, 1U, 0U, 1, 8), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_b_y, false);
  return c2_mxArrayOutData;
}

static const mxArray *c2_f_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i92;
  int32_T c2_i93;
  int32_T c2_i94;
  real_T c2_b_inData[16];
  int32_T c2_i95;
  int32_T c2_i96;
  int32_T c2_i97;
  real_T c2_b_u[16];
  const mxArray *c2_b_y = NULL;
  SFc2_dp_EKF_ausschwingInstanceStruct *chartInstance;
  chartInstance = (SFc2_dp_EKF_ausschwingInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_i92 = 0;
  for (c2_i93 = 0; c2_i93 < 4; c2_i93++) {
    for (c2_i94 = 0; c2_i94 < 4; c2_i94++) {
      c2_b_inData[c2_i94 + c2_i92] = (*(real_T (*)[16])c2_inData)[c2_i94 +
        c2_i92];
    }

    c2_i92 += 4;
  }

  c2_i95 = 0;
  for (c2_i96 = 0; c2_i96 < 4; c2_i96++) {
    for (c2_i97 = 0; c2_i97 < 4; c2_i97++) {
      c2_b_u[c2_i97 + c2_i95] = c2_b_inData[c2_i97 + c2_i95];
    }

    c2_i95 += 4;
  }

  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_b_u, 0, 0U, 1U, 0U, 2, 4, 4),
                false);
  sf_mex_assign(&c2_mxArrayOutData, c2_b_y, false);
  return c2_mxArrayOutData;
}

static real_T c2_g_emlrt_marshallIn(SFc2_dp_EKF_ausschwingInstanceStruct
  *chartInstance, const mxArray *c2_b_u, const emlrtMsgIdentifier *c2_parentId)
{
  real_T c2_b_y;
  real_T c2_d0;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_b_u), &c2_d0, 1, 0, 0U, 0, 0U, 0);
  c2_b_y = c2_d0;
  sf_mex_destroy(&c2_b_u);
  return c2_b_y;
}

static void c2_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_nargout;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_b_y;
  SFc2_dp_EKF_ausschwingInstanceStruct *chartInstance;
  chartInstance = (SFc2_dp_EKF_ausschwingInstanceStruct *)chartInstanceVoid;
  c2_nargout = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_b_y = c2_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_nargout),
    &c2_thisId);
  sf_mex_destroy(&c2_nargout);
  *(real_T *)c2_outData = c2_b_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_g_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i98;
  real_T c2_b_inData[4];
  int32_T c2_i99;
  real_T c2_b_u[4];
  const mxArray *c2_b_y = NULL;
  SFc2_dp_EKF_ausschwingInstanceStruct *chartInstance;
  chartInstance = (SFc2_dp_EKF_ausschwingInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  for (c2_i98 = 0; c2_i98 < 4; c2_i98++) {
    c2_b_inData[c2_i98] = (*(real_T (*)[4])c2_inData)[c2_i98];
  }

  for (c2_i99 = 0; c2_i99 < 4; c2_i99++) {
    c2_b_u[c2_i99] = c2_b_inData[c2_i99];
  }

  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_b_u, 0, 0U, 1U, 0U, 2, 1, 4),
                false);
  sf_mex_assign(&c2_mxArrayOutData, c2_b_y, false);
  return c2_mxArrayOutData;
}

static void c2_h_emlrt_marshallIn(SFc2_dp_EKF_ausschwingInstanceStruct
  *chartInstance, const mxArray *c2_b_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_b_y[16])
{
  real_T c2_dv7[16];
  int32_T c2_i100;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_b_u), c2_dv7, 1, 0, 0U, 1, 0U, 2, 4,
                4);
  for (c2_i100 = 0; c2_i100 < 16; c2_i100++) {
    c2_b_y[c2_i100] = c2_dv7[c2_i100];
  }

  sf_mex_destroy(&c2_b_u);
}

static void c2_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_A;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_b_y[16];
  int32_T c2_i101;
  int32_T c2_i102;
  int32_T c2_i103;
  SFc2_dp_EKF_ausschwingInstanceStruct *chartInstance;
  chartInstance = (SFc2_dp_EKF_ausschwingInstanceStruct *)chartInstanceVoid;
  c2_A = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_A), &c2_thisId, c2_b_y);
  sf_mex_destroy(&c2_A);
  c2_i101 = 0;
  for (c2_i102 = 0; c2_i102 < 4; c2_i102++) {
    for (c2_i103 = 0; c2_i103 < 4; c2_i103++) {
      (*(real_T (*)[16])c2_outData)[c2_i103 + c2_i101] = c2_b_y[c2_i103 +
        c2_i101];
    }

    c2_i101 += 4;
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

const mxArray *sf_c2_dp_EKF_ausschwing_get_eml_resolved_functions_info(void)
{
  const mxArray *c2_nameCaptureInfo = NULL;
  c2_nameCaptureInfo = NULL;
  sf_mex_assign(&c2_nameCaptureInfo, sf_mex_createstruct("structure", 2, 78, 1),
                false);
  c2_info_helper(&c2_nameCaptureInfo);
  c2_b_info_helper(&c2_nameCaptureInfo);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c2_nameCaptureInfo);
  return c2_nameCaptureInfo;
}

static void c2_info_helper(const mxArray **c2_info)
{
  const mxArray *c2_rhs0 = NULL;
  const mxArray *c2_lhs0 = NULL;
  const mxArray *c2_rhs1 = NULL;
  const mxArray *c2_lhs1 = NULL;
  const mxArray *c2_rhs2 = NULL;
  const mxArray *c2_lhs2 = NULL;
  const mxArray *c2_rhs3 = NULL;
  const mxArray *c2_lhs3 = NULL;
  const mxArray *c2_rhs4 = NULL;
  const mxArray *c2_lhs4 = NULL;
  const mxArray *c2_rhs5 = NULL;
  const mxArray *c2_lhs5 = NULL;
  const mxArray *c2_rhs6 = NULL;
  const mxArray *c2_lhs6 = NULL;
  const mxArray *c2_rhs7 = NULL;
  const mxArray *c2_lhs7 = NULL;
  const mxArray *c2_rhs8 = NULL;
  const mxArray *c2_lhs8 = NULL;
  const mxArray *c2_rhs9 = NULL;
  const mxArray *c2_lhs9 = NULL;
  const mxArray *c2_rhs10 = NULL;
  const mxArray *c2_lhs10 = NULL;
  const mxArray *c2_rhs11 = NULL;
  const mxArray *c2_lhs11 = NULL;
  const mxArray *c2_rhs12 = NULL;
  const mxArray *c2_lhs12 = NULL;
  const mxArray *c2_rhs13 = NULL;
  const mxArray *c2_lhs13 = NULL;
  const mxArray *c2_rhs14 = NULL;
  const mxArray *c2_lhs14 = NULL;
  const mxArray *c2_rhs15 = NULL;
  const mxArray *c2_lhs15 = NULL;
  const mxArray *c2_rhs16 = NULL;
  const mxArray *c2_lhs16 = NULL;
  const mxArray *c2_rhs17 = NULL;
  const mxArray *c2_lhs17 = NULL;
  const mxArray *c2_rhs18 = NULL;
  const mxArray *c2_lhs18 = NULL;
  const mxArray *c2_rhs19 = NULL;
  const mxArray *c2_lhs19 = NULL;
  const mxArray *c2_rhs20 = NULL;
  const mxArray *c2_lhs20 = NULL;
  const mxArray *c2_rhs21 = NULL;
  const mxArray *c2_lhs21 = NULL;
  const mxArray *c2_rhs22 = NULL;
  const mxArray *c2_lhs22 = NULL;
  const mxArray *c2_rhs23 = NULL;
  const mxArray *c2_lhs23 = NULL;
  const mxArray *c2_rhs24 = NULL;
  const mxArray *c2_lhs24 = NULL;
  const mxArray *c2_rhs25 = NULL;
  const mxArray *c2_lhs25 = NULL;
  const mxArray *c2_rhs26 = NULL;
  const mxArray *c2_lhs26 = NULL;
  const mxArray *c2_rhs27 = NULL;
  const mxArray *c2_lhs27 = NULL;
  const mxArray *c2_rhs28 = NULL;
  const mxArray *c2_lhs28 = NULL;
  const mxArray *c2_rhs29 = NULL;
  const mxArray *c2_lhs29 = NULL;
  const mxArray *c2_rhs30 = NULL;
  const mxArray *c2_lhs30 = NULL;
  const mxArray *c2_rhs31 = NULL;
  const mxArray *c2_lhs31 = NULL;
  const mxArray *c2_rhs32 = NULL;
  const mxArray *c2_lhs32 = NULL;
  const mxArray *c2_rhs33 = NULL;
  const mxArray *c2_lhs33 = NULL;
  const mxArray *c2_rhs34 = NULL;
  const mxArray *c2_lhs34 = NULL;
  const mxArray *c2_rhs35 = NULL;
  const mxArray *c2_lhs35 = NULL;
  const mxArray *c2_rhs36 = NULL;
  const mxArray *c2_lhs36 = NULL;
  const mxArray *c2_rhs37 = NULL;
  const mxArray *c2_lhs37 = NULL;
  const mxArray *c2_rhs38 = NULL;
  const mxArray *c2_lhs38 = NULL;
  const mxArray *c2_rhs39 = NULL;
  const mxArray *c2_lhs39 = NULL;
  const mxArray *c2_rhs40 = NULL;
  const mxArray *c2_lhs40 = NULL;
  const mxArray *c2_rhs41 = NULL;
  const mxArray *c2_lhs41 = NULL;
  const mxArray *c2_rhs42 = NULL;
  const mxArray *c2_lhs42 = NULL;
  const mxArray *c2_rhs43 = NULL;
  const mxArray *c2_lhs43 = NULL;
  const mxArray *c2_rhs44 = NULL;
  const mxArray *c2_lhs44 = NULL;
  const mxArray *c2_rhs45 = NULL;
  const mxArray *c2_lhs45 = NULL;
  const mxArray *c2_rhs46 = NULL;
  const mxArray *c2_lhs46 = NULL;
  const mxArray *c2_rhs47 = NULL;
  const mxArray *c2_lhs47 = NULL;
  const mxArray *c2_rhs48 = NULL;
  const mxArray *c2_lhs48 = NULL;
  const mxArray *c2_rhs49 = NULL;
  const mxArray *c2_lhs49 = NULL;
  const mxArray *c2_rhs50 = NULL;
  const mxArray *c2_lhs50 = NULL;
  const mxArray *c2_rhs51 = NULL;
  const mxArray *c2_lhs51 = NULL;
  const mxArray *c2_rhs52 = NULL;
  const mxArray *c2_lhs52 = NULL;
  const mxArray *c2_rhs53 = NULL;
  const mxArray *c2_lhs53 = NULL;
  const mxArray *c2_rhs54 = NULL;
  const mxArray *c2_lhs54 = NULL;
  const mxArray *c2_rhs55 = NULL;
  const mxArray *c2_lhs55 = NULL;
  const mxArray *c2_rhs56 = NULL;
  const mxArray *c2_lhs56 = NULL;
  const mxArray *c2_rhs57 = NULL;
  const mxArray *c2_lhs57 = NULL;
  const mxArray *c2_rhs58 = NULL;
  const mxArray *c2_lhs58 = NULL;
  const mxArray *c2_rhs59 = NULL;
  const mxArray *c2_lhs59 = NULL;
  const mxArray *c2_rhs60 = NULL;
  const mxArray *c2_lhs60 = NULL;
  const mxArray *c2_rhs61 = NULL;
  const mxArray *c2_lhs61 = NULL;
  const mxArray *c2_rhs62 = NULL;
  const mxArray *c2_lhs62 = NULL;
  const mxArray *c2_rhs63 = NULL;
  const mxArray *c2_lhs63 = NULL;
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "context", "context", 0);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("cos"), "name", "name", 0);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 0);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m"), "resolved",
                  "resolved", 0);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1395328496U), "fileTimeLo",
                  "fileTimeLo", 0);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 0);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 0);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 0);
  sf_mex_assign(&c2_rhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs0), "rhs", "rhs", 0);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs0), "lhs", "lhs", 0);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m"), "context",
                  "context", 1);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalar_cos"), "name",
                  "name", 1);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 1);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_cos.m"),
                  "resolved", "resolved", 1);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286818722U), "fileTimeLo",
                  "fileTimeLo", 1);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 1);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 1);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 1);
  sf_mex_assign(&c2_rhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs1), "rhs", "rhs", 1);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs1), "lhs", "lhs", 1);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "context", "context", 2);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("sin"), "name", "name", 2);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 2);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m"), "resolved",
                  "resolved", 2);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1395328504U), "fileTimeLo",
                  "fileTimeLo", 2);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 2);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 2);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 2);
  sf_mex_assign(&c2_rhs2, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs2, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs2), "rhs", "rhs", 2);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs2), "lhs", "lhs", 2);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m"), "context",
                  "context", 3);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalar_sin"), "name",
                  "name", 3);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 3);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_sin.m"),
                  "resolved", "resolved", 3);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286818736U), "fileTimeLo",
                  "fileTimeLo", 3);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 3);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 3);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 3);
  sf_mex_assign(&c2_rhs3, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs3, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs3), "rhs", "rhs", 3);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs3), "lhs", "lhs", 3);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "context", "context", 4);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("mpower"), "name", "name", 4);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 4);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m"), "resolved",
                  "resolved", 4);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363713878U), "fileTimeLo",
                  "fileTimeLo", 4);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 4);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 4);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 4);
  sf_mex_assign(&c2_rhs4, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs4, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs4), "rhs", "rhs", 4);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs4), "lhs", "lhs", 4);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m"), "context",
                  "context", 5);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 5);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 5);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 5);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1395931856U), "fileTimeLo",
                  "fileTimeLo", 5);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 5);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 5);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 5);
  sf_mex_assign(&c2_rhs5, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs5, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs5), "rhs", "rhs", 5);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs5), "lhs", "lhs", 5);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m"), "context",
                  "context", 6);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("ismatrix"), "name", "name", 6);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 6);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/ismatrix.m"), "resolved",
                  "resolved", 6);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1331304858U), "fileTimeLo",
                  "fileTimeLo", 6);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 6);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 6);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 6);
  sf_mex_assign(&c2_rhs6, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs6, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs6), "rhs", "rhs", 6);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs6), "lhs", "lhs", 6);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m"), "context",
                  "context", 7);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("power"), "name", "name", 7);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 7);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m"), "resolved",
                  "resolved", 7);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1395328506U), "fileTimeLo",
                  "fileTimeLo", 7);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 7);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 7);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 7);
  sf_mex_assign(&c2_rhs7, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs7, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs7), "rhs", "rhs", 7);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs7), "lhs", "lhs", 7);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m"), "context",
                  "context", 8);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 8);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 8);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 8);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1395931856U), "fileTimeLo",
                  "fileTimeLo", 8);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 8);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 8);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 8);
  sf_mex_assign(&c2_rhs8, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs8, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs8), "rhs", "rhs", 8);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs8), "lhs", "lhs", 8);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower"), "context",
                  "context", 9);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 9);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 9);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 9);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 9);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 9);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 9);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 9);
  sf_mex_assign(&c2_rhs9, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs9, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs9), "rhs", "rhs", 9);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs9), "lhs", "lhs", 9);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "context",
                  "context", 10);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.scalarEg"),
                  "name", "name", 10);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 10);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalarEg.p"),
                  "resolved", "resolved", 10);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1410807770U), "fileTimeLo",
                  "fileTimeLo", 10);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 10);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 10);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 10);
  sf_mex_assign(&c2_rhs10, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs10, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs10), "rhs", "rhs",
                  10);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs10), "lhs", "lhs",
                  10);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower"), "context",
                  "context", 11);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalexp_alloc"), "name",
                  "name", 11);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 11);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m"),
                  "resolved", "resolved", 11);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 11);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 11);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 11);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 11);
  sf_mex_assign(&c2_rhs11, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs11, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs11), "rhs", "rhs",
                  11);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs11), "lhs", "lhs",
                  11);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m"),
                  "context", "context", 12);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.scalexpAlloc"),
                  "name", "name", 12);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 12);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalexpAlloc.p"),
                  "resolved", "resolved", 12);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1410807770U), "fileTimeLo",
                  "fileTimeLo", 12);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 12);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 12);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 12);
  sf_mex_assign(&c2_rhs12, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs12, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs12), "rhs", "rhs",
                  12);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs12), "lhs", "lhs",
                  12);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower"), "context",
                  "context", 13);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("floor"), "name", "name", 13);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 13);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m"), "resolved",
                  "resolved", 13);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363713854U), "fileTimeLo",
                  "fileTimeLo", 13);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 13);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 13);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 13);
  sf_mex_assign(&c2_rhs13, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs13, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs13), "rhs", "rhs",
                  13);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs13), "lhs", "lhs",
                  13);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m"), "context",
                  "context", 14);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 14);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 14);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 14);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1395931856U), "fileTimeLo",
                  "fileTimeLo", 14);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 14);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 14);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 14);
  sf_mex_assign(&c2_rhs14, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs14, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs14), "rhs", "rhs",
                  14);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs14), "lhs", "lhs",
                  14);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m"), "context",
                  "context", 15);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalar_floor"), "name",
                  "name", 15);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 15);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_floor.m"),
                  "resolved", "resolved", 15);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286818726U), "fileTimeLo",
                  "fileTimeLo", 15);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 15);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 15);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 15);
  sf_mex_assign(&c2_rhs15, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs15, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs15), "rhs", "rhs",
                  15);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs15), "lhs", "lhs",
                  15);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!scalar_float_power"),
                  "context", "context", 16);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 16);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 16);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 16);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 16);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 16);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 16);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 16);
  sf_mex_assign(&c2_rhs16, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs16, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs16), "rhs", "rhs",
                  16);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs16), "lhs", "lhs",
                  16);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "context", "context", 17);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("mrdivide"), "name", "name", 17);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 17);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p"), "resolved",
                  "resolved", 17);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1410807648U), "fileTimeLo",
                  "fileTimeLo", 17);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 17);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1370009886U), "mFileTimeLo",
                  "mFileTimeLo", 17);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 17);
  sf_mex_assign(&c2_rhs17, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs17, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs17), "rhs", "rhs",
                  17);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs17), "lhs", "lhs",
                  17);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p"), "context",
                  "context", 18);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.assert"),
                  "name", "name", 18);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 18);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/assert.m"),
                  "resolved", "resolved", 18);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389717774U), "fileTimeLo",
                  "fileTimeLo", 18);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 18);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 18);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 18);
  sf_mex_assign(&c2_rhs18, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs18, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs18), "rhs", "rhs",
                  18);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs18), "lhs", "lhs",
                  18);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p"), "context",
                  "context", 19);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("rdivide"), "name", "name", 19);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 19);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "resolved",
                  "resolved", 19);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363713880U), "fileTimeLo",
                  "fileTimeLo", 19);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 19);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 19);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 19);
  sf_mex_assign(&c2_rhs19, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs19, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs19), "rhs", "rhs",
                  19);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs19), "lhs", "lhs",
                  19);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "context",
                  "context", 20);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 20);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 20);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 20);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1395931856U), "fileTimeLo",
                  "fileTimeLo", 20);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 20);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 20);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 20);
  sf_mex_assign(&c2_rhs20, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs20, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs20), "rhs", "rhs",
                  20);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs20), "lhs", "lhs",
                  20);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "context",
                  "context", 21);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalexp_compatible"),
                  "name", "name", 21);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 21);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m"),
                  "resolved", "resolved", 21);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286818796U), "fileTimeLo",
                  "fileTimeLo", 21);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 21);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 21);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 21);
  sf_mex_assign(&c2_rhs21, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs21, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs21), "rhs", "rhs",
                  21);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs21), "lhs", "lhs",
                  21);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "context",
                  "context", 22);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_div"), "name", "name", 22);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 22);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m"), "resolved",
                  "resolved", 22);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1386423952U), "fileTimeLo",
                  "fileTimeLo", 22);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 22);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 22);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 22);
  sf_mex_assign(&c2_rhs22, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs22, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs22), "rhs", "rhs",
                  22);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs22), "lhs", "lhs",
                  22);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m"), "context",
                  "context", 23);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.div"), "name",
                  "name", 23);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 23);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/div.p"), "resolved",
                  "resolved", 23);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1410807770U), "fileTimeLo",
                  "fileTimeLo", 23);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 23);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 23);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 23);
  sf_mex_assign(&c2_rhs23, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs23, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs23), "rhs", "rhs",
                  23);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs23), "lhs", "lhs",
                  23);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "context", "context", 24);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_mtimes_helper"), "name",
                  "name", 24);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 24);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m"),
                  "resolved", "resolved", 24);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1383877294U), "fileTimeLo",
                  "fileTimeLo", 24);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 24);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 24);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 24);
  sf_mex_assign(&c2_rhs24, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs24, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs24), "rhs", "rhs",
                  24);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs24), "lhs", "lhs",
                  24);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m!common_checks"),
                  "context", "context", 25);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 25);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 25);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 25);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1395931856U), "fileTimeLo",
                  "fileTimeLo", 25);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 25);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 25);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 25);
  sf_mex_assign(&c2_rhs25, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs25, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs25), "rhs", "rhs",
                  25);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs25), "lhs", "lhs",
                  25);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m"),
                  "context", "context", 26);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 26);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 26);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 26);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1323170578U), "fileTimeLo",
                  "fileTimeLo", 26);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 26);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 26);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 26);
  sf_mex_assign(&c2_rhs26, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs26, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs26), "rhs", "rhs",
                  26);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs26), "lhs", "lhs",
                  26);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m"),
                  "context", "context", 27);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 27);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 27);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 27);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 27);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 27);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 27);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 27);
  sf_mex_assign(&c2_rhs27, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs27, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs27), "rhs", "rhs",
                  27);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs27), "lhs", "lhs",
                  27);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m"),
                  "context", "context", 28);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_xgemm"), "name", "name",
                  28);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 28);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m"),
                  "resolved", "resolved", 28);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375980690U), "fileTimeLo",
                  "fileTimeLo", 28);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 28);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 28);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 28);
  sf_mex_assign(&c2_rhs28, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs28, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs28), "rhs", "rhs",
                  28);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs28), "lhs", "lhs",
                  28);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m"), "context",
                  "context", 29);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.blas.inline"),
                  "name", "name", 29);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 29);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/inline.p"),
                  "resolved", "resolved", 29);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1410807772U), "fileTimeLo",
                  "fileTimeLo", 29);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 29);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 29);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 29);
  sf_mex_assign(&c2_rhs29, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs29, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs29), "rhs", "rhs",
                  29);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs29), "lhs", "lhs",
                  29);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m"), "context",
                  "context", 30);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.blas.xgemm"),
                  "name", "name", 30);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 30);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p"),
                  "resolved", "resolved", 30);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1410807770U), "fileTimeLo",
                  "fileTimeLo", 30);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 30);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 30);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 30);
  sf_mex_assign(&c2_rhs30, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs30, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs30), "rhs", "rhs",
                  30);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs30), "lhs", "lhs",
                  30);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p"),
                  "context", "context", 31);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "coder.internal.blas.use_refblas"), "name", "name", 31);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 31);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/use_refblas.p"),
                  "resolved", "resolved", 31);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1410807770U), "fileTimeLo",
                  "fileTimeLo", 31);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 31);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 31);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 31);
  sf_mex_assign(&c2_rhs31, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs31, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs31), "rhs", "rhs",
                  31);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs31), "lhs", "lhs",
                  31);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p!below_threshold"),
                  "context", "context", 32);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.blas.threshold"),
                  "name", "name", 32);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 32);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/threshold.p"),
                  "resolved", "resolved", 32);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1410807772U), "fileTimeLo",
                  "fileTimeLo", 32);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 32);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 32);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 32);
  sf_mex_assign(&c2_rhs32, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs32, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs32), "rhs", "rhs",
                  32);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs32), "lhs", "lhs",
                  32);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/threshold.p"),
                  "context", "context", 33);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_switch_helper"), "name",
                  "name", 33);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 33);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_switch_helper.m"),
                  "resolved", "resolved", 33);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1393330858U), "fileTimeLo",
                  "fileTimeLo", 33);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 33);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 33);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 33);
  sf_mex_assign(&c2_rhs33, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs33, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs33), "rhs", "rhs",
                  33);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs33), "lhs", "lhs",
                  33);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p"),
                  "context", "context", 34);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.scalarEg"),
                  "name", "name", 34);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 34);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalarEg.p"),
                  "resolved", "resolved", 34);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1410807770U), "fileTimeLo",
                  "fileTimeLo", 34);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 34);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 34);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 34);
  sf_mex_assign(&c2_rhs34, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs34, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs34), "rhs", "rhs",
                  34);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs34), "lhs", "lhs",
                  34);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p"),
                  "context", "context", 35);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.refblas.xgemm"),
                  "name", "name", 35);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 35);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xgemm.p"),
                  "resolved", "resolved", 35);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1410807772U), "fileTimeLo",
                  "fileTimeLo", 35);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 35);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 35);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 35);
  sf_mex_assign(&c2_rhs35, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs35, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs35), "rhs", "rhs",
                  35);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs35), "lhs", "lhs",
                  35);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m"),
                  "context", "context", 36);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "coder.internal.blas.use_refblas"), "name", "name", 36);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 36);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/use_refblas.p"),
                  "resolved", "resolved", 36);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1410807770U), "fileTimeLo",
                  "fileTimeLo", 36);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 36);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 36);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 36);
  sf_mex_assign(&c2_rhs36, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs36, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs36), "rhs", "rhs",
                  36);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs36), "lhs", "lhs",
                  36);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m"),
                  "context", "context", 37);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_xdotu"), "name", "name",
                  37);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 37);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xdotu.m"),
                  "resolved", "resolved", 37);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375980690U), "fileTimeLo",
                  "fileTimeLo", 37);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 37);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 37);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 37);
  sf_mex_assign(&c2_rhs37, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs37, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs37), "rhs", "rhs",
                  37);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs37), "lhs", "lhs",
                  37);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xdotu.m"), "context",
                  "context", 38);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.blas.inline"),
                  "name", "name", 38);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 38);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/inline.p"),
                  "resolved", "resolved", 38);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1410807772U), "fileTimeLo",
                  "fileTimeLo", 38);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 38);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 38);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 38);
  sf_mex_assign(&c2_rhs38, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs38, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs38), "rhs", "rhs",
                  38);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs38), "lhs", "lhs",
                  38);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xdotu.m"), "context",
                  "context", 39);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.blas.xdotu"),
                  "name", "name", 39);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 39);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xdotu.p"),
                  "resolved", "resolved", 39);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1410807770U), "fileTimeLo",
                  "fileTimeLo", 39);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 39);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 39);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 39);
  sf_mex_assign(&c2_rhs39, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs39, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs39), "rhs", "rhs",
                  39);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs39), "lhs", "lhs",
                  39);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xdotu.p"),
                  "context", "context", 40);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.blas.xdot"),
                  "name", "name", 40);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 40);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xdot.p"),
                  "resolved", "resolved", 40);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1410807772U), "fileTimeLo",
                  "fileTimeLo", 40);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 40);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 40);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 40);
  sf_mex_assign(&c2_rhs40, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs40, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs40), "rhs", "rhs",
                  40);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs40), "lhs", "lhs",
                  40);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xdot.p"),
                  "context", "context", 41);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "coder.internal.blas.use_refblas"), "name", "name", 41);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 41);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/use_refblas.p"),
                  "resolved", "resolved", 41);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1410807770U), "fileTimeLo",
                  "fileTimeLo", 41);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 41);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 41);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 41);
  sf_mex_assign(&c2_rhs41, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs41, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs41), "rhs", "rhs",
                  41);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs41), "lhs", "lhs",
                  41);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xdot.p!below_threshold"),
                  "context", "context", 42);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.blas.threshold"),
                  "name", "name", 42);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 42);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/threshold.p"),
                  "resolved", "resolved", 42);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1410807772U), "fileTimeLo",
                  "fileTimeLo", 42);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 42);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 42);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 42);
  sf_mex_assign(&c2_rhs42, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs42, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs42), "rhs", "rhs",
                  42);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs42), "lhs", "lhs",
                  42);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xdot.p"),
                  "context", "context", 43);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.refblas.xdot"),
                  "name", "name", 43);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 43);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xdot.p"),
                  "resolved", "resolved", 43);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1410807772U), "fileTimeLo",
                  "fileTimeLo", 43);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 43);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 43);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 43);
  sf_mex_assign(&c2_rhs43, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs43, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs43), "rhs", "rhs",
                  43);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs43), "lhs", "lhs",
                  43);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xdot.p"),
                  "context", "context", 44);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.refblas.xdotx"),
                  "name", "name", 44);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 44);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xdotx.p"),
                  "resolved", "resolved", 44);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1410807772U), "fileTimeLo",
                  "fileTimeLo", 44);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 44);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 44);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 44);
  sf_mex_assign(&c2_rhs44, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs44, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs44), "rhs", "rhs",
                  44);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs44), "lhs", "lhs",
                  44);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xdotx.p"),
                  "context", "context", 45);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.scalarEg"),
                  "name", "name", 45);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 45);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalarEg.p"),
                  "resolved", "resolved", 45);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1410807770U), "fileTimeLo",
                  "fileTimeLo", 45);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 45);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 45);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 45);
  sf_mex_assign(&c2_rhs45, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs45, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs45), "rhs", "rhs",
                  45);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs45), "lhs", "lhs",
                  45);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xdotx.p"),
                  "context", "context", 46);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexMinus"),
                  "name", "name", 46);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 46);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexMinus.m"),
                  "resolved", "resolved", 46);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1372583160U), "fileTimeLo",
                  "fileTimeLo", 46);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 46);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 46);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 46);
  sf_mex_assign(&c2_rhs46, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs46, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs46), "rhs", "rhs",
                  46);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs46), "lhs", "lhs",
                  46);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xdotx.p"),
                  "context", "context", 47);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexTimes"),
                  "name", "name", 47);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 47);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexTimes.m"),
                  "resolved", "resolved", 47);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1372583160U), "fileTimeLo",
                  "fileTimeLo", 47);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 47);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 47);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 47);
  sf_mex_assign(&c2_rhs47, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs47, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs47), "rhs", "rhs",
                  47);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs47), "lhs", "lhs",
                  47);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xdotx.p"),
                  "context", "context", 48);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexPlus"),
                  "name", "name", 48);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 48);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexPlus.m"),
                  "resolved", "resolved", 48);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1372583160U), "fileTimeLo",
                  "fileTimeLo", 48);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 48);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 48);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 48);
  sf_mex_assign(&c2_rhs48, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs48, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs48), "rhs", "rhs",
                  48);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs48), "lhs", "lhs",
                  48);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xdotx.p"),
                  "context", "context", 49);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "eml_int_forloop_overflow_check"), "name", "name", 49);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 49);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m"),
                  "resolved", "resolved", 49);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1397257422U), "fileTimeLo",
                  "fileTimeLo", 49);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 49);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 49);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 49);
  sf_mex_assign(&c2_rhs49, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs49, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs49), "rhs", "rhs",
                  49);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs49), "lhs", "lhs",
                  49);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m!eml_int_forloop_overflow_check_helper"),
                  "context", "context", 50);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("isfi"), "name", "name", 50);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 50);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m"), "resolved",
                  "resolved", 50);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346510358U), "fileTimeLo",
                  "fileTimeLo", 50);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 50);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 50);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 50);
  sf_mex_assign(&c2_rhs50, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs50, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs50), "rhs", "rhs",
                  50);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs50), "lhs", "lhs",
                  50);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m"), "context",
                  "context", 51);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("isnumerictype"), "name",
                  "name", 51);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 51);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isnumerictype.m"), "resolved",
                  "resolved", 51);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1398875598U), "fileTimeLo",
                  "fileTimeLo", 51);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 51);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 51);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 51);
  sf_mex_assign(&c2_rhs51, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs51, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs51), "rhs", "rhs",
                  51);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs51), "lhs", "lhs",
                  51);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m!eml_int_forloop_overflow_check_helper"),
                  "context", "context", 52);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("intmax"), "name", "name", 52);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 52);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m"), "resolved",
                  "resolved", 52);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1362261882U), "fileTimeLo",
                  "fileTimeLo", 52);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 52);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 52);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 52);
  sf_mex_assign(&c2_rhs52, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs52, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs52), "rhs", "rhs",
                  52);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs52), "lhs", "lhs",
                  52);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m"), "context",
                  "context", 53);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_switch_helper"), "name",
                  "name", 53);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 53);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_switch_helper.m"),
                  "resolved", "resolved", 53);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1393330858U), "fileTimeLo",
                  "fileTimeLo", 53);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 53);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 53);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 53);
  sf_mex_assign(&c2_rhs53, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs53, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs53), "rhs", "rhs",
                  53);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs53), "lhs", "lhs",
                  53);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m!eml_int_forloop_overflow_check_helper"),
                  "context", "context", 54);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("intmin"), "name", "name", 54);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 54);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmin.m"), "resolved",
                  "resolved", 54);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1362261882U), "fileTimeLo",
                  "fileTimeLo", 54);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 54);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 54);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 54);
  sf_mex_assign(&c2_rhs54, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs54, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs54), "rhs", "rhs",
                  54);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs54), "lhs", "lhs",
                  54);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmin.m"), "context",
                  "context", 55);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_switch_helper"), "name",
                  "name", 55);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 55);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_switch_helper.m"),
                  "resolved", "resolved", 55);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1393330858U), "fileTimeLo",
                  "fileTimeLo", 55);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 55);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 55);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 55);
  sf_mex_assign(&c2_rhs55, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs55, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs55), "rhs", "rhs",
                  55);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs55), "lhs", "lhs",
                  55);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "context", "context", 56);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eye"), "name", "name", 56);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 56);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eye.m"), "resolved",
                  "resolved", 56);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1406813148U), "fileTimeLo",
                  "fileTimeLo", 56);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 56);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 56);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 56);
  sf_mex_assign(&c2_rhs56, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs56, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs56), "rhs", "rhs",
                  56);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs56), "lhs", "lhs",
                  56);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eye.m"), "context",
                  "context", 57);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_assert_valid_size_arg"),
                  "name", "name", 57);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 57);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m"),
                  "resolved", "resolved", 57);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1368183030U), "fileTimeLo",
                  "fileTimeLo", 57);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 57);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 57);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 57);
  sf_mex_assign(&c2_rhs57, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs57, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs57), "rhs", "rhs",
                  57);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs57), "lhs", "lhs",
                  57);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m"),
                  "context", "context", 58);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 58);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 58);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 58);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1395931856U), "fileTimeLo",
                  "fileTimeLo", 58);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 58);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 58);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 58);
  sf_mex_assign(&c2_rhs58, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs58, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs58), "rhs", "rhs",
                  58);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs58), "lhs", "lhs",
                  58);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m!isintegral"),
                  "context", "context", 59);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("isinf"), "name", "name", 59);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 59);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isinf.m"), "resolved",
                  "resolved", 59);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363713856U), "fileTimeLo",
                  "fileTimeLo", 59);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 59);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 59);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 59);
  sf_mex_assign(&c2_rhs59, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs59, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs59), "rhs", "rhs",
                  59);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs59), "lhs", "lhs",
                  59);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isinf.m"), "context",
                  "context", 60);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 60);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 60);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 60);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1395931856U), "fileTimeLo",
                  "fileTimeLo", 60);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 60);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 60);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 60);
  sf_mex_assign(&c2_rhs60, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs60, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs60), "rhs", "rhs",
                  60);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs60), "lhs", "lhs",
                  60);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m!isinbounds"),
                  "context", "context", 61);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_is_integer_class"), "name",
                  "name", 61);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 61);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_is_integer_class.m"),
                  "resolved", "resolved", 61);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286818782U), "fileTimeLo",
                  "fileTimeLo", 61);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 61);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 61);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 61);
  sf_mex_assign(&c2_rhs61, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs61, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs61), "rhs", "rhs",
                  61);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs61), "lhs", "lhs",
                  61);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m!isinbounds"),
                  "context", "context", 62);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("intmax"), "name", "name", 62);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 62);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m"), "resolved",
                  "resolved", 62);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1362261882U), "fileTimeLo",
                  "fileTimeLo", 62);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 62);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 62);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 62);
  sf_mex_assign(&c2_rhs62, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs62, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs62), "rhs", "rhs",
                  62);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs62), "lhs", "lhs",
                  62);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m!isinbounds"),
                  "context", "context", 63);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("intmin"), "name", "name", 63);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 63);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmin.m"), "resolved",
                  "resolved", 63);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1362261882U), "fileTimeLo",
                  "fileTimeLo", 63);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 63);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 63);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 63);
  sf_mex_assign(&c2_rhs63, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs63, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs63), "rhs", "rhs",
                  63);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs63), "lhs", "lhs",
                  63);
  sf_mex_destroy(&c2_rhs0);
  sf_mex_destroy(&c2_lhs0);
  sf_mex_destroy(&c2_rhs1);
  sf_mex_destroy(&c2_lhs1);
  sf_mex_destroy(&c2_rhs2);
  sf_mex_destroy(&c2_lhs2);
  sf_mex_destroy(&c2_rhs3);
  sf_mex_destroy(&c2_lhs3);
  sf_mex_destroy(&c2_rhs4);
  sf_mex_destroy(&c2_lhs4);
  sf_mex_destroy(&c2_rhs5);
  sf_mex_destroy(&c2_lhs5);
  sf_mex_destroy(&c2_rhs6);
  sf_mex_destroy(&c2_lhs6);
  sf_mex_destroy(&c2_rhs7);
  sf_mex_destroy(&c2_lhs7);
  sf_mex_destroy(&c2_rhs8);
  sf_mex_destroy(&c2_lhs8);
  sf_mex_destroy(&c2_rhs9);
  sf_mex_destroy(&c2_lhs9);
  sf_mex_destroy(&c2_rhs10);
  sf_mex_destroy(&c2_lhs10);
  sf_mex_destroy(&c2_rhs11);
  sf_mex_destroy(&c2_lhs11);
  sf_mex_destroy(&c2_rhs12);
  sf_mex_destroy(&c2_lhs12);
  sf_mex_destroy(&c2_rhs13);
  sf_mex_destroy(&c2_lhs13);
  sf_mex_destroy(&c2_rhs14);
  sf_mex_destroy(&c2_lhs14);
  sf_mex_destroy(&c2_rhs15);
  sf_mex_destroy(&c2_lhs15);
  sf_mex_destroy(&c2_rhs16);
  sf_mex_destroy(&c2_lhs16);
  sf_mex_destroy(&c2_rhs17);
  sf_mex_destroy(&c2_lhs17);
  sf_mex_destroy(&c2_rhs18);
  sf_mex_destroy(&c2_lhs18);
  sf_mex_destroy(&c2_rhs19);
  sf_mex_destroy(&c2_lhs19);
  sf_mex_destroy(&c2_rhs20);
  sf_mex_destroy(&c2_lhs20);
  sf_mex_destroy(&c2_rhs21);
  sf_mex_destroy(&c2_lhs21);
  sf_mex_destroy(&c2_rhs22);
  sf_mex_destroy(&c2_lhs22);
  sf_mex_destroy(&c2_rhs23);
  sf_mex_destroy(&c2_lhs23);
  sf_mex_destroy(&c2_rhs24);
  sf_mex_destroy(&c2_lhs24);
  sf_mex_destroy(&c2_rhs25);
  sf_mex_destroy(&c2_lhs25);
  sf_mex_destroy(&c2_rhs26);
  sf_mex_destroy(&c2_lhs26);
  sf_mex_destroy(&c2_rhs27);
  sf_mex_destroy(&c2_lhs27);
  sf_mex_destroy(&c2_rhs28);
  sf_mex_destroy(&c2_lhs28);
  sf_mex_destroy(&c2_rhs29);
  sf_mex_destroy(&c2_lhs29);
  sf_mex_destroy(&c2_rhs30);
  sf_mex_destroy(&c2_lhs30);
  sf_mex_destroy(&c2_rhs31);
  sf_mex_destroy(&c2_lhs31);
  sf_mex_destroy(&c2_rhs32);
  sf_mex_destroy(&c2_lhs32);
  sf_mex_destroy(&c2_rhs33);
  sf_mex_destroy(&c2_lhs33);
  sf_mex_destroy(&c2_rhs34);
  sf_mex_destroy(&c2_lhs34);
  sf_mex_destroy(&c2_rhs35);
  sf_mex_destroy(&c2_lhs35);
  sf_mex_destroy(&c2_rhs36);
  sf_mex_destroy(&c2_lhs36);
  sf_mex_destroy(&c2_rhs37);
  sf_mex_destroy(&c2_lhs37);
  sf_mex_destroy(&c2_rhs38);
  sf_mex_destroy(&c2_lhs38);
  sf_mex_destroy(&c2_rhs39);
  sf_mex_destroy(&c2_lhs39);
  sf_mex_destroy(&c2_rhs40);
  sf_mex_destroy(&c2_lhs40);
  sf_mex_destroy(&c2_rhs41);
  sf_mex_destroy(&c2_lhs41);
  sf_mex_destroy(&c2_rhs42);
  sf_mex_destroy(&c2_lhs42);
  sf_mex_destroy(&c2_rhs43);
  sf_mex_destroy(&c2_lhs43);
  sf_mex_destroy(&c2_rhs44);
  sf_mex_destroy(&c2_lhs44);
  sf_mex_destroy(&c2_rhs45);
  sf_mex_destroy(&c2_lhs45);
  sf_mex_destroy(&c2_rhs46);
  sf_mex_destroy(&c2_lhs46);
  sf_mex_destroy(&c2_rhs47);
  sf_mex_destroy(&c2_lhs47);
  sf_mex_destroy(&c2_rhs48);
  sf_mex_destroy(&c2_lhs48);
  sf_mex_destroy(&c2_rhs49);
  sf_mex_destroy(&c2_lhs49);
  sf_mex_destroy(&c2_rhs50);
  sf_mex_destroy(&c2_lhs50);
  sf_mex_destroy(&c2_rhs51);
  sf_mex_destroy(&c2_lhs51);
  sf_mex_destroy(&c2_rhs52);
  sf_mex_destroy(&c2_lhs52);
  sf_mex_destroy(&c2_rhs53);
  sf_mex_destroy(&c2_lhs53);
  sf_mex_destroy(&c2_rhs54);
  sf_mex_destroy(&c2_lhs54);
  sf_mex_destroy(&c2_rhs55);
  sf_mex_destroy(&c2_lhs55);
  sf_mex_destroy(&c2_rhs56);
  sf_mex_destroy(&c2_lhs56);
  sf_mex_destroy(&c2_rhs57);
  sf_mex_destroy(&c2_lhs57);
  sf_mex_destroy(&c2_rhs58);
  sf_mex_destroy(&c2_lhs58);
  sf_mex_destroy(&c2_rhs59);
  sf_mex_destroy(&c2_lhs59);
  sf_mex_destroy(&c2_rhs60);
  sf_mex_destroy(&c2_lhs60);
  sf_mex_destroy(&c2_rhs61);
  sf_mex_destroy(&c2_lhs61);
  sf_mex_destroy(&c2_rhs62);
  sf_mex_destroy(&c2_lhs62);
  sf_mex_destroy(&c2_rhs63);
  sf_mex_destroy(&c2_lhs63);
}

static const mxArray *c2_emlrt_marshallOut(const char * c2_b_u)
{
  const mxArray *c2_b_y = NULL;
  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_b_u, 15, 0U, 0U, 0U, 2, 1, strlen
                 (c2_b_u)), false);
  return c2_b_y;
}

static const mxArray *c2_b_emlrt_marshallOut(const uint32_T c2_b_u)
{
  const mxArray *c2_b_y = NULL;
  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", &c2_b_u, 7, 0U, 0U, 0U, 0), false);
  return c2_b_y;
}

static void c2_b_info_helper(const mxArray **c2_info)
{
  const mxArray *c2_rhs64 = NULL;
  const mxArray *c2_lhs64 = NULL;
  const mxArray *c2_rhs65 = NULL;
  const mxArray *c2_lhs65 = NULL;
  const mxArray *c2_rhs66 = NULL;
  const mxArray *c2_lhs66 = NULL;
  const mxArray *c2_rhs67 = NULL;
  const mxArray *c2_lhs67 = NULL;
  const mxArray *c2_rhs68 = NULL;
  const mxArray *c2_lhs68 = NULL;
  const mxArray *c2_rhs69 = NULL;
  const mxArray *c2_lhs69 = NULL;
  const mxArray *c2_rhs70 = NULL;
  const mxArray *c2_lhs70 = NULL;
  const mxArray *c2_rhs71 = NULL;
  const mxArray *c2_lhs71 = NULL;
  const mxArray *c2_rhs72 = NULL;
  const mxArray *c2_lhs72 = NULL;
  const mxArray *c2_rhs73 = NULL;
  const mxArray *c2_lhs73 = NULL;
  const mxArray *c2_rhs74 = NULL;
  const mxArray *c2_lhs74 = NULL;
  const mxArray *c2_rhs75 = NULL;
  const mxArray *c2_lhs75 = NULL;
  const mxArray *c2_rhs76 = NULL;
  const mxArray *c2_lhs76 = NULL;
  const mxArray *c2_rhs77 = NULL;
  const mxArray *c2_lhs77 = NULL;
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m!isinbounds"),
                  "context", "context", 64);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexIntRelop"),
                  "name", "name", 64);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 64);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexIntRelop.m"),
                  "resolved", "resolved", 64);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1326728322U), "fileTimeLo",
                  "fileTimeLo", 64);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 64);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 64);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 64);
  sf_mex_assign(&c2_rhs64, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs64, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs64), "rhs", "rhs",
                  64);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs64), "lhs", "lhs",
                  64);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexIntRelop.m!apply_float_relop"),
                  "context", "context", 65);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_switch_helper"), "name",
                  "name", 65);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 65);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_switch_helper.m"),
                  "resolved", "resolved", 65);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1393330858U), "fileTimeLo",
                  "fileTimeLo", 65);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 65);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 65);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 65);
  sf_mex_assign(&c2_rhs65, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs65, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs65), "rhs", "rhs",
                  65);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs65), "lhs", "lhs",
                  65);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexIntRelop.m!float_class_contains_indexIntClass"),
                  "context", "context", 66);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_float_model"), "name",
                  "name", 66);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 66);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_float_model.m"),
                  "resolved", "resolved", 66);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1326727996U), "fileTimeLo",
                  "fileTimeLo", 66);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 66);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 66);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 66);
  sf_mex_assign(&c2_rhs66, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs66, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs66), "rhs", "rhs",
                  66);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs66), "lhs", "lhs",
                  66);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexIntRelop.m!is_signed_indexIntClass"),
                  "context", "context", 67);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("intmin"), "name", "name", 67);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 67);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmin.m"), "resolved",
                  "resolved", 67);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1362261882U), "fileTimeLo",
                  "fileTimeLo", 67);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 67);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 67);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 67);
  sf_mex_assign(&c2_rhs67, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs67, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs67), "rhs", "rhs",
                  67);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs67), "lhs", "lhs",
                  67);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m"),
                  "context", "context", 68);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 68);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 68);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 68);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1323170578U), "fileTimeLo",
                  "fileTimeLo", 68);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 68);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 68);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 68);
  sf_mex_assign(&c2_rhs68, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs68, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs68), "rhs", "rhs",
                  68);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs68), "lhs", "lhs",
                  68);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m"),
                  "context", "context", 69);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("intmax"), "name", "name", 69);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 69);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m"), "resolved",
                  "resolved", 69);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1362261882U), "fileTimeLo",
                  "fileTimeLo", 69);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 69);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 69);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 69);
  sf_mex_assign(&c2_rhs69, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs69, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs69), "rhs", "rhs",
                  69);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs69), "lhs", "lhs",
                  69);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eye.m"), "context",
                  "context", 70);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("min"), "name", "name", 70);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 70);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m"), "resolved",
                  "resolved", 70);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1311255318U), "fileTimeLo",
                  "fileTimeLo", 70);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 70);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 70);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 70);
  sf_mex_assign(&c2_rhs70, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs70, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs70), "rhs", "rhs",
                  70);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs70), "lhs", "lhs",
                  70);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m"), "context",
                  "context", 71);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_min_or_max"), "name",
                  "name", 71);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 71);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m"),
                  "resolved", "resolved", 71);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1378295984U), "fileTimeLo",
                  "fileTimeLo", 71);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 71);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 71);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 71);
  sf_mex_assign(&c2_rhs71, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs71, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs71), "rhs", "rhs",
                  71);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs71), "lhs", "lhs",
                  71);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum"),
                  "context", "context", 72);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 72);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 72);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 72);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 72);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 72);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 72);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 72);
  sf_mex_assign(&c2_rhs72, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs72, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs72), "rhs", "rhs",
                  72);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs72), "lhs", "lhs",
                  72);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum"),
                  "context", "context", 73);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalexp_alloc"), "name",
                  "name", 73);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 73);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m"),
                  "resolved", "resolved", 73);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 73);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 73);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 73);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 73);
  sf_mex_assign(&c2_rhs73, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs73, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs73), "rhs", "rhs",
                  73);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs73), "lhs", "lhs",
                  73);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum"),
                  "context", "context", 74);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 74);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 74);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 74);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1323170578U), "fileTimeLo",
                  "fileTimeLo", 74);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 74);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 74);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 74);
  sf_mex_assign(&c2_rhs74, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs74, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs74), "rhs", "rhs",
                  74);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs74), "lhs", "lhs",
                  74);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_scalar_bin_extremum"),
                  "context", "context", 75);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 75);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 75);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 75);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 75);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 75);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 75);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 75);
  sf_mex_assign(&c2_rhs75, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs75, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs75), "rhs", "rhs",
                  75);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs75), "lhs", "lhs",
                  75);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_scalar_bin_extremum"),
                  "context", "context", 76);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 76);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 76);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 76);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1395931856U), "fileTimeLo",
                  "fileTimeLo", 76);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 76);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 76);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 76);
  sf_mex_assign(&c2_rhs76, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs76, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs76), "rhs", "rhs",
                  76);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs76), "lhs", "lhs",
                  76);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eye.m"), "context",
                  "context", 77);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "eml_int_forloop_overflow_check"), "name", "name", 77);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 77);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m"),
                  "resolved", "resolved", 77);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1397257422U), "fileTimeLo",
                  "fileTimeLo", 77);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 77);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 77);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 77);
  sf_mex_assign(&c2_rhs77, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs77, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs77), "rhs", "rhs",
                  77);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs77), "lhs", "lhs",
                  77);
  sf_mex_destroy(&c2_rhs64);
  sf_mex_destroy(&c2_lhs64);
  sf_mex_destroy(&c2_rhs65);
  sf_mex_destroy(&c2_lhs65);
  sf_mex_destroy(&c2_rhs66);
  sf_mex_destroy(&c2_lhs66);
  sf_mex_destroy(&c2_rhs67);
  sf_mex_destroy(&c2_lhs67);
  sf_mex_destroy(&c2_rhs68);
  sf_mex_destroy(&c2_lhs68);
  sf_mex_destroy(&c2_rhs69);
  sf_mex_destroy(&c2_lhs69);
  sf_mex_destroy(&c2_rhs70);
  sf_mex_destroy(&c2_lhs70);
  sf_mex_destroy(&c2_rhs71);
  sf_mex_destroy(&c2_lhs71);
  sf_mex_destroy(&c2_rhs72);
  sf_mex_destroy(&c2_lhs72);
  sf_mex_destroy(&c2_rhs73);
  sf_mex_destroy(&c2_lhs73);
  sf_mex_destroy(&c2_rhs74);
  sf_mex_destroy(&c2_lhs74);
  sf_mex_destroy(&c2_rhs75);
  sf_mex_destroy(&c2_lhs75);
  sf_mex_destroy(&c2_rhs76);
  sf_mex_destroy(&c2_lhs76);
  sf_mex_destroy(&c2_rhs77);
  sf_mex_destroy(&c2_lhs77);
}

static real_T c2_mpower(SFc2_dp_EKF_ausschwingInstanceStruct *chartInstance,
  real_T c2_a)
{
  real_T c2_b_a;
  real_T c2_c_a;
  real_T c2_ak;
  real_T c2_d_a;
  c2_b_a = c2_a;
  c2_c_a = c2_b_a;
  c2_eml_scalar_eg(chartInstance);
  c2_ak = c2_c_a;
  c2_d_a = c2_ak;
  c2_eml_scalar_eg(chartInstance);
  return c2_d_a * c2_d_a;
}

static void c2_eml_scalar_eg(SFc2_dp_EKF_ausschwingInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c2_b_eml_scalar_eg(SFc2_dp_EKF_ausschwingInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void c2_threshold(SFc2_dp_EKF_ausschwingInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c2_c_eml_scalar_eg(SFc2_dp_EKF_ausschwingInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void c2_d_eml_scalar_eg(SFc2_dp_EKF_ausschwingInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static real_T c2_eml_xdotu(SFc2_dp_EKF_ausschwingInstanceStruct *chartInstance,
  real_T c2_b_x[4], real_T c2_b_y[4])
{
  real_T c2_d;
  int32_T c2_k;
  int32_T c2_b_k;
  (void)chartInstance;
  c2_d = 0.0;
  for (c2_k = 1; c2_k < 5; c2_k++) {
    c2_b_k = c2_k;
    c2_d += c2_b_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
      "", (real_T)c2_b_k), 1, 4, 1, 0) - 1] * c2_b_y[_SFD_EML_ARRAY_BOUNDS_CHECK
      ("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_b_k), 1, 4, 1, 0) - 1];
  }

  return c2_d;
}

static void c2_eye(SFc2_dp_EKF_ausschwingInstanceStruct *chartInstance, real_T
                   c2_I[16])
{
  int32_T c2_i104;
  int32_T c2_k;
  int32_T c2_b_k;
  (void)chartInstance;
  for (c2_i104 = 0; c2_i104 < 16; c2_i104++) {
    c2_I[c2_i104] = 0.0;
  }

  for (c2_k = 1; c2_k < 5; c2_k++) {
    c2_b_k = c2_k;
    c2_I[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c2_b_k), 1, 4, 1, 0) + ((_SFD_EML_ARRAY_BOUNDS_CHECK("",
             (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_b_k), 1, 4, 2, 0) - 1) <<
           2)) - 1] = 1.0;
  }
}

static const mxArray *c2_h_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_b_u;
  const mxArray *c2_b_y = NULL;
  SFc2_dp_EKF_ausschwingInstanceStruct *chartInstance;
  chartInstance = (SFc2_dp_EKF_ausschwingInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_b_u = *(int32_T *)c2_inData;
  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", &c2_b_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_b_y, false);
  return c2_mxArrayOutData;
}

static int32_T c2_i_emlrt_marshallIn(SFc2_dp_EKF_ausschwingInstanceStruct
  *chartInstance, const mxArray *c2_b_u, const emlrtMsgIdentifier *c2_parentId)
{
  int32_T c2_b_y;
  int32_T c2_i105;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_b_u), &c2_i105, 1, 6, 0U, 0, 0U, 0);
  c2_b_y = c2_i105;
  sf_mex_destroy(&c2_b_u);
  return c2_b_y;
}

static void c2_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_sfEvent;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  int32_T c2_b_y;
  SFc2_dp_EKF_ausschwingInstanceStruct *chartInstance;
  chartInstance = (SFc2_dp_EKF_ausschwingInstanceStruct *)chartInstanceVoid;
  c2_b_sfEvent = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_b_y = c2_i_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_sfEvent),
    &c2_thisId);
  sf_mex_destroy(&c2_b_sfEvent);
  *(int32_T *)c2_outData = c2_b_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static uint8_T c2_j_emlrt_marshallIn(SFc2_dp_EKF_ausschwingInstanceStruct
  *chartInstance, const mxArray *c2_b_is_active_c2_dp_EKF_ausschwing, const
  char_T *c2_identifier)
{
  uint8_T c2_b_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_b_y = c2_k_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c2_b_is_active_c2_dp_EKF_ausschwing), &c2_thisId);
  sf_mex_destroy(&c2_b_is_active_c2_dp_EKF_ausschwing);
  return c2_b_y;
}

static uint8_T c2_k_emlrt_marshallIn(SFc2_dp_EKF_ausschwingInstanceStruct
  *chartInstance, const mxArray *c2_b_u, const emlrtMsgIdentifier *c2_parentId)
{
  uint8_T c2_b_y;
  uint8_T c2_u0;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_b_u), &c2_u0, 1, 3, 0U, 0, 0U, 0);
  c2_b_y = c2_u0;
  sf_mex_destroy(&c2_b_u);
  return c2_b_y;
}

static void init_dsm_address_info(SFc2_dp_EKF_ausschwingInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void init_simulink_io_address(SFc2_dp_EKF_ausschwingInstanceStruct
  *chartInstance)
{
  chartInstance->c2_P = (real_T (*)[16])ssGetInputPortSignal_wrapper
    (chartInstance->S, 0);
  chartInstance->c2_Q = (real_T (*)[16])ssGetInputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c2_R = (real_T *)ssGetInputPortSignal_wrapper(chartInstance->S,
    2);
  chartInstance->c2_x0 = (real_T (*)[4])ssGetInputPortSignal_wrapper
    (chartInstance->S, 3);
  chartInstance->c2_para_sys = (real_T (*)[8])ssGetInputPortSignal_wrapper
    (chartInstance->S, 4);
  chartInstance->c2_T_s = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 5);
  chartInstance->c2_u = (real_T *)ssGetInputPortSignal_wrapper(chartInstance->S,
    6);
  chartInstance->c2_y = (real_T *)ssGetInputPortSignal_wrapper(chartInstance->S,
    7);
  chartInstance->c2_x = (real_T (*)[4])ssGetOutputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c2_K = (real_T (*)[4])ssGetOutputPortSignal_wrapper
    (chartInstance->S, 2);
}

/* SFunction Glue Code */
#ifdef utFree
#undef utFree
#endif

#ifdef utMalloc
#undef utMalloc
#endif

#ifdef __cplusplus

extern "C" void *utMalloc(size_t size);
extern "C" void utFree(void*);

#else

extern void *utMalloc(size_t size);
extern void utFree(void*);

#endif

void sf_c2_dp_EKF_ausschwing_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(2570295491U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(3626346814U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(274504686U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(2343303305U);
}

mxArray* sf_c2_dp_EKF_ausschwing_get_post_codegen_info(void);
mxArray *sf_c2_dp_EKF_ausschwing_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals", "postCodegenInfo" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1, 1, sizeof
    (autoinheritanceFields)/sizeof(autoinheritanceFields[0]),
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("0wcWb3XjIzfvsUdBr2wZQH");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,8,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(4);
      pr[1] = (double)(4);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(4);
      pr[1] = (double)(4);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(4);
      pr[1] = (double)(1);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(8);
      pr[1] = (double)(1);
      mxSetField(mxData,4,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,4,"type",mxType);
    }

    mxSetField(mxData,4,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,5,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,5,"type",mxType);
    }

    mxSetField(mxData,5,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,6,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,6,"type",mxType);
    }

    mxSetField(mxData,6,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,7,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,7,"type",mxType);
    }

    mxSetField(mxData,7,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,2,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(4);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(4);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  {
    mxArray* mxPostCodegenInfo = sf_c2_dp_EKF_ausschwing_get_post_codegen_info();
    mxSetField(mxAutoinheritanceInfo,0,"postCodegenInfo",mxPostCodegenInfo);
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c2_dp_EKF_ausschwing_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c2_dp_EKF_ausschwing_jit_fallback_info(void)
{
  const char *infoFields[] = { "fallbackType", "fallbackReason",
    "incompatibleSymbol", };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 3, infoFields);
  mxArray *fallbackReason = mxCreateString("feature_off");
  mxArray *incompatibleSymbol = mxCreateString("");
  mxArray *fallbackType = mxCreateString("early");
  mxSetField(mxInfo, 0, infoFields[0], fallbackType);
  mxSetField(mxInfo, 0, infoFields[1], fallbackReason);
  mxSetField(mxInfo, 0, infoFields[2], incompatibleSymbol);
  return mxInfo;
}

mxArray *sf_c2_dp_EKF_ausschwing_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

mxArray* sf_c2_dp_EKF_ausschwing_get_post_codegen_info(void)
{
  const char* fieldNames[] = { "exportedFunctionsUsedByThisChart",
    "exportedFunctionsChecksum" };

  mwSize dims[2] = { 1, 1 };

  mxArray* mxPostCodegenInfo = mxCreateStructArray(2, dims, sizeof(fieldNames)/
    sizeof(fieldNames[0]), fieldNames);

  {
    mxArray* mxExportedFunctionsChecksum = mxCreateString("");
    mwSize exp_dims[2] = { 0, 1 };

    mxArray* mxExportedFunctionsUsedByThisChart = mxCreateCellArray(2, exp_dims);
    mxSetField(mxPostCodegenInfo, 0, "exportedFunctionsUsedByThisChart",
               mxExportedFunctionsUsedByThisChart);
    mxSetField(mxPostCodegenInfo, 0, "exportedFunctionsChecksum",
               mxExportedFunctionsChecksum);
  }

  return mxPostCodegenInfo;
}

static const mxArray *sf_get_sim_state_info_c2_dp_EKF_ausschwing(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x5'type','srcId','name','auxInfo'{{M[1],M[13],T\"K\",},{M[1],M[12],T\"x\",},{M[4],M[0],T\"P_p\",S'l','i','p'{{M1x2[439 442],M[0],}}},{M[4],M[0],T\"x_p\",S'l','i','p'{{M1x2[435 438],M[0],}}},{M[8],M[0],T\"is_active_c2_dp_EKF_ausschwing\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 5, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c2_dp_EKF_ausschwing_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc2_dp_EKF_ausschwingInstanceStruct *chartInstance;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    chartInstance = (SFc2_dp_EKF_ausschwingInstanceStruct *)
      chartInfo->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _dp_EKF_ausschwingMachineNumber_,
           2,
           1,
           1,
           0,
           10,
           0,
           0,
           0,
           0,
           0,
           &(chartInstance->chartNumber),
           &(chartInstance->instanceNumber),
           (void *)S);

        /* Each instance must initialize its own list of scripts */
        init_script_number_translation(_dp_EKF_ausschwingMachineNumber_,
          chartInstance->chartNumber,chartInstance->instanceNumber);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_dp_EKF_ausschwingMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _dp_EKF_ausschwingMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"P");
          _SFD_SET_DATA_PROPS(1,1,1,0,"Q");
          _SFD_SET_DATA_PROPS(2,1,1,0,"R");
          _SFD_SET_DATA_PROPS(3,1,1,0,"x0");
          _SFD_SET_DATA_PROPS(4,1,1,0,"para_sys");
          _SFD_SET_DATA_PROPS(5,1,1,0,"T_s");
          _SFD_SET_DATA_PROPS(6,1,1,0,"u");
          _SFD_SET_DATA_PROPS(7,1,1,0,"y");
          _SFD_SET_DATA_PROPS(8,2,0,1,"x");
          _SFD_SET_DATA_PROPS(9,2,0,1,"K");
          _SFD_STATE_INFO(0,0,2);
          _SFD_CH_SUBSTATE_COUNT(0);
          _SFD_CH_SUBSTATE_DECOMP(0);
        }

        _SFD_CV_INIT_CHART(0,0,0,0);

        {
          _SFD_CV_INIT_STATE(0,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);

        /* Initialization of MATLAB Function Model Coverage */
        _SFD_CV_INIT_EML(0,1,1,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,8332);
        _SFD_CV_INIT_EML_IF(0,1,0,609,624,717,8332);

        {
          unsigned int dimVector[2];
          dimVector[0]= 4;
          dimVector[1]= 4;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_f_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 4;
          dimVector[1]= 4;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_f_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_d_sf_marshallOut,(MexInFcnForType)NULL);

        {
          unsigned int dimVector[1];
          dimVector[0]= 4;
          _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_c_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 8;
          _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_e_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_d_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(6,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_d_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(7,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_d_sf_marshallOut,(MexInFcnForType)NULL);

        {
          unsigned int dimVector[1];
          dimVector[0]= 4;
          _SFD_SET_DATA_COMPILED_PROPS(8,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_c_sf_marshallOut,(MexInFcnForType)
            c2_c_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 4;
          _SFD_SET_DATA_COMPILED_PROPS(9,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_c_sf_marshallOut,(MexInFcnForType)
            c2_c_sf_marshallIn);
        }

        _SFD_SET_DATA_VALUE_PTR(0U, *chartInstance->c2_P);
        _SFD_SET_DATA_VALUE_PTR(1U, *chartInstance->c2_Q);
        _SFD_SET_DATA_VALUE_PTR(2U, chartInstance->c2_R);
        _SFD_SET_DATA_VALUE_PTR(3U, *chartInstance->c2_x0);
        _SFD_SET_DATA_VALUE_PTR(4U, *chartInstance->c2_para_sys);
        _SFD_SET_DATA_VALUE_PTR(5U, chartInstance->c2_T_s);
        _SFD_SET_DATA_VALUE_PTR(6U, chartInstance->c2_u);
        _SFD_SET_DATA_VALUE_PTR(7U, chartInstance->c2_y);
        _SFD_SET_DATA_VALUE_PTR(8U, *chartInstance->c2_x);
        _SFD_SET_DATA_VALUE_PTR(9U, *chartInstance->c2_K);
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _dp_EKF_ausschwingMachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "Xobrp6PzrX3xzLN2JiqdmE";
}

static void sf_opaque_initialize_c2_dp_EKF_ausschwing(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc2_dp_EKF_ausschwingInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c2_dp_EKF_ausschwing((SFc2_dp_EKF_ausschwingInstanceStruct*)
    chartInstanceVar);
  initialize_c2_dp_EKF_ausschwing((SFc2_dp_EKF_ausschwingInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c2_dp_EKF_ausschwing(void *chartInstanceVar)
{
  enable_c2_dp_EKF_ausschwing((SFc2_dp_EKF_ausschwingInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_disable_c2_dp_EKF_ausschwing(void *chartInstanceVar)
{
  disable_c2_dp_EKF_ausschwing((SFc2_dp_EKF_ausschwingInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c2_dp_EKF_ausschwing(void *chartInstanceVar)
{
  sf_gateway_c2_dp_EKF_ausschwing((SFc2_dp_EKF_ausschwingInstanceStruct*)
    chartInstanceVar);
}

static const mxArray* sf_opaque_get_sim_state_c2_dp_EKF_ausschwing(SimStruct* S)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  return get_sim_state_c2_dp_EKF_ausschwing
    ((SFc2_dp_EKF_ausschwingInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
}

static void sf_opaque_set_sim_state_c2_dp_EKF_ausschwing(SimStruct* S, const
  mxArray *st)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  set_sim_state_c2_dp_EKF_ausschwing((SFc2_dp_EKF_ausschwingInstanceStruct*)
    chartInfo->chartInstance, st);
}

static void sf_opaque_terminate_c2_dp_EKF_ausschwing(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc2_dp_EKF_ausschwingInstanceStruct*) chartInstanceVar)->S;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_dp_EKF_ausschwing_optimization_info();
    }

    finalize_c2_dp_EKF_ausschwing((SFc2_dp_EKF_ausschwingInstanceStruct*)
      chartInstanceVar);
    utFree(chartInstanceVar);
    if (crtInfo != NULL) {
      utFree(crtInfo);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc2_dp_EKF_ausschwing((SFc2_dp_EKF_ausschwingInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c2_dp_EKF_ausschwing(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    initialize_params_c2_dp_EKF_ausschwing((SFc2_dp_EKF_ausschwingInstanceStruct*)
      (chartInfo->chartInstance));
  }
}

static void mdlSetWorkWidths_c2_dp_EKF_ausschwing(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_dp_EKF_ausschwing_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,2);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(sf_get_instance_specialization(),
                infoStruct,2,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,2,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(sf_get_instance_specialization(),infoStruct,2);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 4, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 5, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 6, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 7, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,2,8);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,2,2);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=2; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 8; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,2);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(316580123U));
  ssSetChecksum1(S,(4185527205U));
  ssSetChecksum2(S,(2119350851U));
  ssSetChecksum3(S,(2436669803U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c2_dp_EKF_ausschwing(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c2_dp_EKF_ausschwing(SimStruct *S)
{
  SFc2_dp_EKF_ausschwingInstanceStruct *chartInstance;
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)utMalloc(sizeof
    (ChartRunTimeInfo));
  chartInstance = (SFc2_dp_EKF_ausschwingInstanceStruct *)utMalloc(sizeof
    (SFc2_dp_EKF_ausschwingInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc2_dp_EKF_ausschwingInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c2_dp_EKF_ausschwing;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c2_dp_EKF_ausschwing;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c2_dp_EKF_ausschwing;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c2_dp_EKF_ausschwing;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c2_dp_EKF_ausschwing;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c2_dp_EKF_ausschwing;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c2_dp_EKF_ausschwing;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c2_dp_EKF_ausschwing;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c2_dp_EKF_ausschwing;
  chartInstance->chartInfo.mdlStart = mdlStart_c2_dp_EKF_ausschwing;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c2_dp_EKF_ausschwing;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->chartInfo.callAtomicSubchartUserFcn = NULL;
  chartInstance->chartInfo.callAtomicSubchartAutoFcn = NULL;
  chartInstance->chartInfo.debugInstance = sfGlobalDebugInstanceStruct;
  chartInstance->S = S;
  crtInfo->checksum = SF_RUNTIME_INFO_CHECKSUM;
  crtInfo->instanceInfo = (&(chartInstance->chartInfo));
  crtInfo->isJITEnabled = false;
  crtInfo->compiledInfo = NULL;
  ssSetUserData(S,(void *)(crtInfo));  /* register the chart instance with simstruct */
  init_dsm_address_info(chartInstance);
  init_simulink_io_address(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  sf_opaque_init_subchart_simstructs(chartInstance->chartInfo.chartInstance);
  chart_debug_initialization(S,1);
}

void c2_dp_EKF_ausschwing_method_dispatcher(SimStruct *S, int_T method, void
  *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c2_dp_EKF_ausschwing(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c2_dp_EKF_ausschwing(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c2_dp_EKF_ausschwing(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c2_dp_EKF_ausschwing_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
