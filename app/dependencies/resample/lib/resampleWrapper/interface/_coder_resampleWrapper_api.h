//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// _coder_resampleWrapper_api.h
//
// Code generation for function 'resampleWrapper'
//

#ifndef _CODER_RESAMPLEWRAPPER_API_H
#define _CODER_RESAMPLEWRAPPER_API_H

// Include files
#include "coder_array_mex.h"
#include "emlrt.h"
#include "mex.h"
#include "tmwtypes.h"
#include <algorithm>
#include <cstring>

// Variable Declarations
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

// Function Declarations
void resampleWrapper(coder::array<real_T, 1U> *data, real_T targetFs, real_T fs,
                     coder::array<real_T, 2U> *data_resampled);

void resampleWrapper_api(const mxArray *const prhs[3], const mxArray **plhs);

void resampleWrapper_atexit();

void resampleWrapper_initialize();

void resampleWrapper_terminate();

void resampleWrapper_xil_shutdown();

void resampleWrapper_xil_terminate();

#endif
// End of code generation (_coder_resampleWrapper_api.h)
