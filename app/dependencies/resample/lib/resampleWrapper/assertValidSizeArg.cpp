//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// assertValidSizeArg.cpp
//
// Code generation for function 'assertValidSizeArg'
//

// Include files
#include "assertValidSizeArg.h"
#include "resampleWrapper_types.h"
#include "rt_nonfinite.h"
#include "omp.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <string>

// Function Declarations
static void d_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void q_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

// Function Definitions
static void d_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "Maximum variable size allowed by the program is exceeded.";
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

static void q_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  ((((outStream << "Size vector must be a row vector with finite integer "
                   "elements in the range: ")
     << MIN_int32_T)
    << " to ")
   << MAX_int32_T)
      << ".";
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
namespace internal {
void assertValidSizeArg(const double varargin_1[2])
{
  static rtRunTimeErrorInfo k_emlrtRTEI{
      49,                   // lineNo
      19,                   // colNo
      "assertValidSizeArg", // fName
      "/usr/local/MATLAB/R2023b/toolbox/eml/eml/+coder/+internal/"
      "assertValidSizeArg.m" // pName
  };
  static rtRunTimeErrorInfo l_emlrtRTEI{
      64,                   // lineNo
      15,                   // colNo
      "assertValidSizeArg", // fName
      "/usr/local/MATLAB/R2023b/toolbox/eml/eml/+coder/+internal/"
      "assertValidSizeArg.m" // pName
  };
  double d;
  int exitg2;
  int k;
  k = 0;
  do {
    exitg2 = 0;
    if (k < 2) {
      if ((varargin_1[k] != varargin_1[k]) || std::isinf(varargin_1[k])) {
        q_rtErrorWithMessageID(k_emlrtRTEI.fName, k_emlrtRTEI.lineNo);
      } else {
        k++;
      }
    } else {
      k = 0;
      exitg2 = 2;
    }
  } while (exitg2 == 0);
  if (exitg2 != 1) {
    boolean_T exitg1;
    exitg1 = false;
    while ((!exitg1) && (k < 2)) {
      if ((varargin_1[k] < -2.147483648E+9) ||
          (varargin_1[k] > 2.147483647E+9)) {
        q_rtErrorWithMessageID(k_emlrtRTEI.fName, k_emlrtRTEI.lineNo);
      } else {
        k++;
      }
    }
  }
  if (varargin_1[0] <= 0.0) {
    d = 0.0;
  } else {
    d = varargin_1[0];
  }
  if (varargin_1[1] <= 0.0) {
    d = 0.0;
  } else {
    d *= varargin_1[1];
  }
  if (!(d <= 2.147483647E+9)) {
    d_rtErrorWithMessageID(l_emlrtRTEI.fName, l_emlrtRTEI.lineNo);
  }
}

} // namespace internal
} // namespace coder

// End of code generation (assertValidSizeArg.cpp)
