//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// resampleWrapper.cpp
//
// Code generation for function 'resampleWrapper'
//

// Include files
#include "resampleWrapper.h"
#include "resampleWrapper_data.h"
#include "resampleWrapper_initialize.h"
#include "resampleWrapper_rtwutil.h"
#include "resampleWrapper_types.h"
#include "rt_nonfinite.h"
#include "uniformResample.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
void resampleWrapper(const coder::array<double, 1U> &data, double targetFs,
                     double fs, coder::array<double, 2U> &data_resampled)
{
  static rtBoundsCheckInfo emlrtBCI{
      -1,          // iFirst
      -1,          // iLast
      40,          // lineNo
      22,          // colNo
      "",          // aName
      "dimParser", // fName
      "/usr/local/MATLAB/R2023b/toolbox/signal/signal/+signal/+internal/"
      "+resample/sharedParser.m", // pName
      0                           // checkKind
  };
  coder::array<double, 2U> hout;
  double b_data[2];
  double c_data[2];
  double n;
  double tau;
  double x;
  double xin;
  unsigned int sx[2];
  int exponent;
  int idx;
  boolean_T b;
  boolean_T b1;
  if (!isInitialized_resampleWrapper) {
    resampleWrapper_initialize();
  }
  sx[0] = static_cast<unsigned int>(data.size(0));
  sx[1] = 1U;
  idx = 1;
  if (data.size(0) != 1) {
    int ii;
    signed char ii_data[2];
    boolean_T exitg1;
    idx = 0;
    ii = 0;
    exitg1 = false;
    while ((!exitg1) && (ii < 2)) {
      if (static_cast<int>(sx[ii]) > 1) {
        idx++;
        ii_data[idx - 1] = static_cast<signed char>(ii + 1);
        if (idx >= 2) {
          exitg1 = true;
        } else {
          ii++;
        }
      } else {
        ii++;
      }
    }
    if (idx < 1) {
      idx = 0;
    }
    if (idx < 1) {
      rtDynamicBoundsError(1, 1, idx, emlrtBCI);
    }
    idx = ii_data[0];
  }
  if (data.size(0) == 0) {
    d_rtErrorWithMessageID("input number 1, X,", d_emlrtRTEI.fName,
                           d_emlrtRTEI.lineNo);
  }
  if (std::isinf(targetFs) || std::isnan(targetFs) ||
      (!(std::floor(targetFs) == targetFs))) {
    c_rtErrorWithMessageID("input number 2, P,", c_emlrtRTEI.fName,
                           c_emlrtRTEI.lineNo);
  }
  if (targetFs <= 0.0) {
    b_rtErrorWithMessageID("input number 2, P,", b_emlrtRTEI.fName,
                           b_emlrtRTEI.lineNo);
  }
  if (std::isinf(fs) || std::isnan(fs) || (!(std::floor(fs) == fs))) {
    c_rtErrorWithMessageID("input number 3, Q,", c_emlrtRTEI.fName,
                           c_emlrtRTEI.lineNo);
  }
  if (fs <= 0.0) {
    b_rtErrorWithMessageID("input number 3, Q,", b_emlrtRTEI.fName,
                           b_emlrtRTEI.lineNo);
  }
  x = targetFs / fs;
  xin = x;
  b = std::isnan(x);
  b1 = (std::isinf(x) || b);
  if (b1) {
    tau = rtNaN;
  } else if (x < 4.4501477170144028E-308) {
    tau = 4.94065645841247E-324;
  } else {
    std::frexp(x, &exponent);
    tau = std::ldexp(1.0, exponent - 53);
  }
  tau = std::fmax(1.0E-12, tau);
  if (b1) {
    n = !b;
    tau = 0.0;
  } else {
    double d;
    double dlast;
    double nlast;
    n = 1.0;
    d = 0.0;
    nlast = 0.0;
    dlast = 1.0;
    double rndx;
    int exitg2;
    do {
      exitg2 = 0;
      rndx = std::round(x);
      if (!std::isinf(x)) {
        double tmp;
        x -= rndx;
        tmp = nlast;
        nlast = n;
        n = n * rndx + tmp;
        tmp = dlast;
        dlast = d;
        d = d * rndx + tmp;
      } else {
        nlast = n;
        dlast = d;
        n = x;
        d = 0.0;
      }
      if ((x == 0.0) || (std::abs(n / d - xin) <= tau)) {
        exitg2 = 1;
      } else {
        x = 1.0 / x;
      }
    } while (exitg2 == 0);
    if (std::isnan(d)) {
      x = rtNaN;
    } else if (d < 0.0) {
      x = -1.0;
    } else {
      x = (d > 0.0);
    }
    n /= x;
    tau = std::abs(d);
  }
  b_data[0] = data.size(0);
  b_data[1] = 1.0;
  c_data[0] = data.size(0);
  c_data[1] = 1.0;
  coder::b_signal::internal::resample::resampleByDesignedFilter(
      data, static_cast<double>(data.size(0)), b_data,
      static_cast<double>(data.size(0)), n, tau, static_cast<double>(idx),
      c_data, static_cast<double>(data.size(0)), data.size(0) == 1,
      data_resampled, hout);
}

// End of code generation (resampleWrapper.cpp)
