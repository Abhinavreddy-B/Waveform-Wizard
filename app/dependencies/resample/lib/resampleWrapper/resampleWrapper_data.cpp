//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// resampleWrapper_data.cpp
//
// Code generation for function 'resampleWrapper_data'
//

// Include files
#include "resampleWrapper_data.h"
#include "resampleWrapper_types.h"
#include "rt_nonfinite.h"

// Variable Definitions
omp_nest_lock_t resampleWrapper_nestLockGlobal;

rtRunTimeErrorInfo emlrtRTEI{
    14,               // lineNo
    37,               // colNo
    "validatefinite", // fName
    "/usr/local/MATLAB/R2023b/toolbox/eml/eml/+coder/+internal/+valattr/"
    "validatefinite.m" // pName
};

rtRunTimeErrorInfo b_emlrtRTEI{
    14,                 // lineNo
    37,                 // colNo
    "validatepositive", // fName
    "/usr/local/MATLAB/R2023b/toolbox/eml/eml/+coder/+internal/+valattr/"
    "validatepositive.m" // pName
};

rtRunTimeErrorInfo c_emlrtRTEI{
    13,                // lineNo
    37,                // colNo
    "validateinteger", // fName
    "/usr/local/MATLAB/R2023b/toolbox/eml/eml/+coder/+internal/+valattr/"
    "validateinteger.m" // pName
};

rtRunTimeErrorInfo d_emlrtRTEI{
    13,                 // lineNo
    37,                 // colNo
    "validatenonempty", // fName
    "/usr/local/MATLAB/R2023b/toolbox/eml/eml/+coder/+internal/+valattr/"
    "validatenonempty.m" // pName
};

rtRunTimeErrorInfo f_emlrtRTEI{
    74,                  // lineNo
    13,                  // colNo
    "reshapeSizeChecks", // fName
    "/usr/local/MATLAB/R2023b/toolbox/eml/eml/+coder/+internal/"
    "reshapeSizeChecks.m" // pName
};

rtRunTimeErrorInfo j_emlrtRTEI{
    13,                                                            // lineNo
    9,                                                             // colNo
    "sqrt",                                                        // fName
    "/usr/local/MATLAB/R2023b/toolbox/eml/lib/matlab/elfun/sqrt.m" // pName
};

boolean_T isInitialized_resampleWrapper{false};

// End of code generation (resampleWrapper_data.cpp)
