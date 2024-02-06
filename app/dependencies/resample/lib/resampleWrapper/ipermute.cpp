//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// ipermute.cpp
//
// Code generation for function 'ipermute'
//

// Include files
#include "ipermute.h"
#include "eml_int_forloop_overflow_check.h"
#include "resampleWrapper_data.h"
#include "resampleWrapper_rtwutil.h"
#include "resampleWrapper_types.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

// Function Definitions
namespace coder {
void ipermute(const array<double, 1U> &b, array<double, 1U> &a)
{
  int k;
  int plast;
  boolean_T b_b;
  b_b = true;
  if (b.size(0) != 0) {
    boolean_T exitg1;
    plast = 0;
    k = 0;
    exitg1 = false;
    while ((!exitg1) && (k < 2)) {
      int i;
      if (k + 1 <= 1) {
        i = b.size(0);
      } else {
        i = 1;
      }
      if (i != 1) {
        if (plast > k + 1) {
          b_b = false;
          exitg1 = true;
        } else {
          plast = k + 1;
          k++;
        }
      } else {
        k++;
      }
    }
  }
  if (b_b) {
    plast = b.size(0);
    if (b.size(0) < 1) {
      plast = 1;
    }
    k = b.size(0);
    if (k >= plast) {
      plast = k;
    }
    if (b.size(0) > plast) {
      rtErrorWithMessageID(f_emlrtRTEI.fName, f_emlrtRTEI.lineNo);
    }
    a.set_size(b.size(0));
    plast = b.size(0);
    for (k = 0; k < plast; k++) {
      a[k] = b[k];
    }
  } else {
    plast = b.size(0);
    if (b.size(0) < 1) {
      plast = 1;
    }
    k = b.size(0);
    if (k >= plast) {
      plast = k;
    }
    if (b.size(0) > plast) {
      rtErrorWithMessageID(f_emlrtRTEI.fName, f_emlrtRTEI.lineNo);
    }
    a.set_size(b.size(0));
    plast = b.size(0);
    if (b.size(0) > 2147483646) {
      check_forloop_overflow_error();
    }
    for (k = 0; k < plast; k++) {
      a[k] = b[k];
    }
  }
}

} // namespace coder

// End of code generation (ipermute.cpp)
