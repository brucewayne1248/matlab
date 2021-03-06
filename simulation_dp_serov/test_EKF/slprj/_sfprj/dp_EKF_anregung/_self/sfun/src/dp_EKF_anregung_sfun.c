/* Include files */

#include "dp_EKF_anregung_sfun.h"
#include "dp_EKF_anregung_sfun_debug_macros.h"
#include "c2_dp_EKF_anregung.h"
#include "c5_dp_EKF_anregung.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */
uint32_T _dp_EKF_anregungMachineNumber_;

/* Function Declarations */

/* Function Definitions */
void dp_EKF_anregung_initializer(void)
{
}

void dp_EKF_anregung_terminator(void)
{
}

/* SFunction Glue Code */
unsigned int sf_dp_EKF_anregung_method_dispatcher(SimStruct *simstructPtr,
  unsigned int chartFileNumber, const char* specsCksum, int_T method, void *data)
{
  if (chartFileNumber==2) {
    c2_dp_EKF_anregung_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==5) {
    c5_dp_EKF_anregung_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  return 0;
}

extern void sf_dp_EKF_anregung_uses_exported_functions(int nlhs, mxArray * plhs[],
  int nrhs, const mxArray * prhs[])
{
  plhs[0] = mxCreateLogicalScalar(0);
}

unsigned int sf_dp_EKF_anregung_process_check_sum_call( int nlhs, mxArray *
  plhs[], int nrhs, const mxArray * prhs[] )
{

#ifdef MATLAB_MEX_FILE

  char commandName[20];
  if (nrhs<1 || !mxIsChar(prhs[0]) )
    return 0;

  /* Possible call to get the checksum */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"sf_get_check_sum"))
    return 0;
  plhs[0] = mxCreateDoubleMatrix( 1,4,mxREAL);
  if (nrhs>1 && mxIsChar(prhs[1])) {
    mxGetString(prhs[1], commandName,sizeof(commandName)/sizeof(char));
    commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
    if (!strcmp(commandName,"machine")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3219810790U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(2021301449U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3296613852U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(4257421027U);
    } else if (!strcmp(commandName,"exportedFcn")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(0U);
    } else if (!strcmp(commandName,"makefile")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3880004845U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(3288112240U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3777513381U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3497619517U);
    } else if (nrhs==3 && !strcmp(commandName,"chart")) {
      unsigned int chartFileNumber;
      chartFileNumber = (unsigned int)mxGetScalar(prhs[2]);
      switch (chartFileNumber) {
       case 2:
        {
          extern void sf_c2_dp_EKF_anregung_get_check_sum(mxArray *plhs[]);
          sf_c2_dp_EKF_anregung_get_check_sum(plhs);
          break;
        }

       case 5:
        {
          extern void sf_c5_dp_EKF_anregung_get_check_sum(mxArray *plhs[]);
          sf_c5_dp_EKF_anregung_get_check_sum(plhs);
          break;
        }

       default:
        ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(0.0);
        ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(0.0);
        ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(0.0);
        ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(0.0);
      }
    } else if (!strcmp(commandName,"target")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3061339410U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1991824845U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3599338742U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(2357874978U);
    } else {
      return 0;
    }
  } else {
    ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(807383827U);
    ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1964722310U);
    ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(1762266005U);
    ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(2737985656U);
  }

  return 1;

#else

  return 0;

#endif

}

unsigned int sf_dp_EKF_anregung_autoinheritance_info( int nlhs, mxArray * plhs[],
  int nrhs, const mxArray * prhs[] )
{

#ifdef MATLAB_MEX_FILE

  char commandName[32];
  char aiChksum[64];
  if (nrhs<3 || !mxIsChar(prhs[0]) )
    return 0;

  /* Possible call to get the autoinheritance_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_autoinheritance_info"))
    return 0;
  mxGetString(prhs[2], aiChksum,sizeof(aiChksum)/sizeof(char));
  aiChksum[(sizeof(aiChksum)/sizeof(char)-1)] = '\0';

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 2:
      {
        if (strcmp(aiChksum, "yuLrGIjzgzfyC3vVYEDcVD") == 0) {
          extern mxArray *sf_c2_dp_EKF_anregung_get_autoinheritance_info(void);
          plhs[0] = sf_c2_dp_EKF_anregung_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 5:
      {
        if (strcmp(aiChksum, "dOnsCV1Zzh5YP8XkdYbO0E") == 0) {
          extern mxArray *sf_c5_dp_EKF_anregung_get_autoinheritance_info(void);
          plhs[0] = sf_c5_dp_EKF_anregung_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;

#else

  return 0;

#endif

}

unsigned int sf_dp_EKF_anregung_get_eml_resolved_functions_info( int nlhs,
  mxArray * plhs[], int nrhs, const mxArray * prhs[] )
{

#ifdef MATLAB_MEX_FILE

  char commandName[64];
  if (nrhs<2 || !mxIsChar(prhs[0]))
    return 0;

  /* Possible call to get the get_eml_resolved_functions_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_eml_resolved_functions_info"))
    return 0;

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 2:
      {
        extern const mxArray
          *sf_c2_dp_EKF_anregung_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c2_dp_EKF_anregung_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 5:
      {
        extern const mxArray
          *sf_c5_dp_EKF_anregung_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c5_dp_EKF_anregung_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;

#else

  return 0;

#endif

}

unsigned int sf_dp_EKF_anregung_third_party_uses_info( int nlhs, mxArray * plhs[],
  int nrhs, const mxArray * prhs[] )
{
  char commandName[64];
  char tpChksum[64];
  if (nrhs<3 || !mxIsChar(prhs[0]))
    return 0;

  /* Possible call to get the third_party_uses_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  mxGetString(prhs[2], tpChksum,sizeof(tpChksum)/sizeof(char));
  tpChksum[(sizeof(tpChksum)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_third_party_uses_info"))
    return 0;

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 2:
      {
        if (strcmp(tpChksum, "r7jJJtP1ZMiIltgDpDkBqF") == 0) {
          extern mxArray *sf_c2_dp_EKF_anregung_third_party_uses_info(void);
          plhs[0] = sf_c2_dp_EKF_anregung_third_party_uses_info();
          break;
        }
      }

     case 5:
      {
        if (strcmp(tpChksum, "V4VkpbFSSMGnONPJxfSBU") == 0) {
          extern mxArray *sf_c5_dp_EKF_anregung_third_party_uses_info(void);
          plhs[0] = sf_c5_dp_EKF_anregung_third_party_uses_info();
          break;
        }
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;
}

unsigned int sf_dp_EKF_anregung_jit_fallback_info( int nlhs, mxArray * plhs[],
  int nrhs, const mxArray * prhs[] )
{
  char commandName[64];
  char tpChksum[64];
  if (nrhs<3 || !mxIsChar(prhs[0]))
    return 0;

  /* Possible call to get the jit_fallback_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  mxGetString(prhs[2], tpChksum,sizeof(tpChksum)/sizeof(char));
  tpChksum[(sizeof(tpChksum)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_jit_fallback_info"))
    return 0;

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 2:
      {
        if (strcmp(tpChksum, "r7jJJtP1ZMiIltgDpDkBqF") == 0) {
          extern mxArray *sf_c2_dp_EKF_anregung_jit_fallback_info(void);
          plhs[0] = sf_c2_dp_EKF_anregung_jit_fallback_info();
          break;
        }
      }

     case 5:
      {
        if (strcmp(tpChksum, "V4VkpbFSSMGnONPJxfSBU") == 0) {
          extern mxArray *sf_c5_dp_EKF_anregung_jit_fallback_info(void);
          plhs[0] = sf_c5_dp_EKF_anregung_jit_fallback_info();
          break;
        }
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;
}

unsigned int sf_dp_EKF_anregung_updateBuildInfo_args_info( int nlhs, mxArray *
  plhs[], int nrhs, const mxArray * prhs[] )
{
  char commandName[64];
  char tpChksum[64];
  if (nrhs<3 || !mxIsChar(prhs[0]))
    return 0;

  /* Possible call to get the updateBuildInfo_args_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  mxGetString(prhs[2], tpChksum,sizeof(tpChksum)/sizeof(char));
  tpChksum[(sizeof(tpChksum)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_updateBuildInfo_args_info"))
    return 0;

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 2:
      {
        if (strcmp(tpChksum, "r7jJJtP1ZMiIltgDpDkBqF") == 0) {
          extern mxArray *sf_c2_dp_EKF_anregung_updateBuildInfo_args_info(void);
          plhs[0] = sf_c2_dp_EKF_anregung_updateBuildInfo_args_info();
          break;
        }
      }

     case 5:
      {
        if (strcmp(tpChksum, "V4VkpbFSSMGnONPJxfSBU") == 0) {
          extern mxArray *sf_c5_dp_EKF_anregung_updateBuildInfo_args_info(void);
          plhs[0] = sf_c5_dp_EKF_anregung_updateBuildInfo_args_info();
          break;
        }
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;
}

void sf_dp_EKF_anregung_get_post_codegen_info( int nlhs, mxArray * plhs[], int
  nrhs, const mxArray * prhs[] )
{
  unsigned int chartFileNumber = (unsigned int) mxGetScalar(prhs[0]);
  char tpChksum[64];
  mxGetString(prhs[1], tpChksum,sizeof(tpChksum)/sizeof(char));
  tpChksum[(sizeof(tpChksum)/sizeof(char)-1)] = '\0';
  switch (chartFileNumber) {
   case 2:
    {
      if (strcmp(tpChksum, "r7jJJtP1ZMiIltgDpDkBqF") == 0) {
        extern mxArray *sf_c2_dp_EKF_anregung_get_post_codegen_info(void);
        plhs[0] = sf_c2_dp_EKF_anregung_get_post_codegen_info();
        return;
      }
    }
    break;

   case 5:
    {
      if (strcmp(tpChksum, "V4VkpbFSSMGnONPJxfSBU") == 0) {
        extern mxArray *sf_c5_dp_EKF_anregung_get_post_codegen_info(void);
        plhs[0] = sf_c5_dp_EKF_anregung_get_post_codegen_info();
        return;
      }
    }
    break;

   default:
    break;
  }

  plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
}

void dp_EKF_anregung_debug_initialize(struct SfDebugInstanceStruct*
  debugInstance)
{
  _dp_EKF_anregungMachineNumber_ = sf_debug_initialize_machine(debugInstance,
    "dp_EKF_anregung","sfun",0,2,0,0,0);
  sf_debug_set_machine_event_thresholds(debugInstance,
    _dp_EKF_anregungMachineNumber_,0,0);
  sf_debug_set_machine_data_thresholds(debugInstance,
    _dp_EKF_anregungMachineNumber_,0);
}

void dp_EKF_anregung_register_exported_symbols(SimStruct* S)
{
}

static mxArray* sRtwOptimizationInfoStruct= NULL;
mxArray* load_dp_EKF_anregung_optimization_info(void)
{
  if (sRtwOptimizationInfoStruct==NULL) {
    sRtwOptimizationInfoStruct = sf_load_rtw_optimization_info("dp_EKF_anregung",
      "dp_EKF_anregung");
    mexMakeArrayPersistent(sRtwOptimizationInfoStruct);
  }

  return(sRtwOptimizationInfoStruct);
}

void unload_dp_EKF_anregung_optimization_info(void)
{
  if (sRtwOptimizationInfoStruct!=NULL) {
    mxDestroyArray(sRtwOptimizationInfoStruct);
    sRtwOptimizationInfoStruct = NULL;
  }
}
