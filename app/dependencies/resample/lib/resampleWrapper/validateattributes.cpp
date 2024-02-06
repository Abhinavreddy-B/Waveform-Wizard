//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// validateattributes.cpp
//
// Code generation for function 'validateattributes'
//

// Include files
#include "validateattributes.h"
#include "resampleWrapper_data.h"
#include "resampleWrapper_rtwutil.h"
#include "resampleWrapper_types.h"
#include "rt_nonfinite.h"
#include <cmath>

// Function Definitions
namespace coder {
void validateattributes(const double a[4])
{
  int k;
  boolean_T exitg1;
  boolean_T p;
  p = true;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k < 4)) {
    if ((!std::isinf(a[k])) && (!std::isnan(a[k]))) {
      k++;
    } else {
      p = false;
      exitg1 = true;
    }
  }
  if (!p) {
    rtErrorWithMessageID("input number 2, f,", emlrtRTEI.fName,
                         emlrtRTEI.lineNo);
  }
}

} // namespace coder

// End of code generation (validateattributes.cpp)
