//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// eml_int_forloop_overflow_check.cpp
//
// Code generation for function 'eml_int_forloop_overflow_check'
//

// Include files
#include "eml_int_forloop_overflow_check.h"
#include "resampleWrapper_types.h"
#include "rt_nonfinite.h"
#include "omp.h"
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <string>

// Function Declarations
static void g_rtErrorWithMessageID(const char *r, const char *aFcnName,
                                   int aLineNum);

// Function Definitions
static void g_rtErrorWithMessageID(const char *r, const char *aFcnName,
                                   int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  ((outStream << "The loop variable of class ") << r)
      << " might overflow on the last iteration of the for loop. This could "
         "lead to an infinite loop.";
  outStream << "\n";
  ((((outStream << "Error in ") << aFcnName) << " (line ") << aLineNum) << ")";
  if (omp_in_parallel()) {
    errMsg = outStream.str();
    std::fprintf(stderr, "%s", errMsg.c_str());
    std::abort();
  } else {
    throw std::runtime_error(outStream.str());
  }
}

namespace coder {
void check_forloop_overflow_error()
{
  static rtRunTimeErrorInfo k_emlrtRTEI{
      87,                             // lineNo
      33,                             // colNo
      "check_forloop_overflow_error", // fName
      "/usr/local/MATLAB/R2023b/toolbox/eml/lib/matlab/eml/"
      "eml_int_forloop_overflow_check.m" // pName
  };
  g_rtErrorWithMessageID("int32", k_emlrtRTEI.fName, k_emlrtRTEI.lineNo);
}

} // namespace coder

// End of code generation (eml_int_forloop_overflow_check.cpp)
