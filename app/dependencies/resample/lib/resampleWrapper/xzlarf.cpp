//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// xzlarf.cpp
//
// Code generation for function 'xzlarf'
//

// Include files
#include "xzlarf.h"
#include "eml_int_forloop_overflow_check.h"
#include "resampleWrapper_types.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "omp.h"
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <string>

// Function Declarations
static void o_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

// Function Definitions
static void o_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "Vector expression with zero stride is not supported.";
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
namespace reflapack {
void xzlarf(int m, int n, int iv0, double tau, array<double, 2U> &C, int ic0,
            int ldc, array<double, 1U> &work)
{
  static rtRunTimeErrorInfo k_emlrtRTEI{
      18,                               // lineNo
      27,                               // colNo
      "eml_int_forloop_overflow_check", // fName
      "/usr/local/MATLAB/R2023b/toolbox/eml/lib/matlab/eml/"
      "eml_int_forloop_overflow_check.m" // pName
  };
  int colbottom;
  int i;
  int lastc;
  int lastv;
  if (tau != 0.0) {
    boolean_T exitg2;
    lastv = m - 1;
    i = iv0 + m;
    while ((lastv + 1 > 0) && (C[i - 2] == 0.0)) {
      lastv--;
      i--;
    }
    lastc = n;
    exitg2 = false;
    while ((!exitg2) && (lastc > 0)) {
      int exitg1;
      i = ic0 + (lastc - 1) * ldc;
      colbottom = i + lastv;
      if ((i <= colbottom) && (colbottom > 2147483646)) {
        check_forloop_overflow_error();
      }
      do {
        exitg1 = 0;
        if (i <= colbottom) {
          if (C[i - 1] != 0.0) {
            exitg1 = 1;
          } else {
            i++;
          }
        } else {
          lastc--;
          exitg1 = 2;
        }
      } while (exitg1 == 0);
      if (exitg1 == 1) {
        exitg2 = true;
      }
    }
  } else {
    lastv = -1;
    lastc = 0;
  }
  if (lastv + 1 > 0) {
    double c;
    int b;
    if (lastc != 0) {
      boolean_T overflow;
      if (lastc > 2147483646) {
        check_forloop_overflow_error();
      }
      for (colbottom = 0; colbottom < lastc; colbottom++) {
        work[colbottom] = 0.0;
      }
      colbottom = 0;
      b = ic0 + ldc * (lastc - 1);
      if ((ldc == 0) || (ic0 > b)) {
        overflow = false;
      } else {
        overflow = (b > MAX_int32_T - ldc);
      }
      if (ldc == 0) {
        o_rtErrorWithMessageID(k_emlrtRTEI.fName, k_emlrtRTEI.lineNo);
      }
      if (overflow) {
        check_forloop_overflow_error();
      }
      for (int iac{ic0}; ldc < 0 ? iac >= b : iac <= b; iac += ldc) {
        c = 0.0;
        i = iac + lastv;
        if ((iac <= i) && (i > 2147483646)) {
          check_forloop_overflow_error();
        }
        for (int ia{iac}; ia <= i; ia++) {
          c += C[ia - 1] * C[((iv0 + ia) - iac) - 1];
        }
        work[colbottom] = work[colbottom] + c;
        colbottom++;
      }
    }
    if (!(-tau == 0.0)) {
      i = ic0;
      for (colbottom = 0; colbottom < lastc; colbottom++) {
        c = work[colbottom];
        if (c != 0.0) {
          c *= -tau;
          b = lastv + i;
          if ((i <= b) && (b > 2147483646)) {
            check_forloop_overflow_error();
          }
          for (int iac{i}; iac <= b; iac++) {
            C[iac - 1] = C[iac - 1] + C[((iv0 + iac) - i) - 1] * c;
          }
        }
        i += ldc;
      }
    }
  }
}

} // namespace reflapack
} // namespace internal
} // namespace coder

// End of code generation (xzlarf.cpp)
