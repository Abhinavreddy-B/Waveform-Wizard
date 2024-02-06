//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// kaiser.cpp
//
// Code generation for function 'kaiser'
//

// Include files
#include "kaiser.h"
#include "casyi.h"
#include "cmlri.h"
#include "eml_int_forloop_overflow_check.h"
#include "gammaln.h"
#include "resampleWrapper_data.h"
#include "resampleWrapper_rtwutil.h"
#include "resampleWrapper_types.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "omp.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <string>

// Function Declarations
static void f_rtErrorWithMessageID(const char *r, const char *aFcnName,
                                   int aLineNum);

static void j_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

// Function Definitions
static void f_rtErrorWithMessageID(const char *r, const char *aFcnName,
                                   int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  ((outStream << "Order, ") << r) << ", must be finite.";
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

static void j_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "Order must be greater than or equal to zero.";
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
void kaiser(double N, array<double, 1U> &w)
{
  static rtBoundsCheckInfo b_emlrtBCI{
      -1,                                                     // iFirst
      -1,                                                     // iLast
      55,                                                     // lineNo
      14,                                                     // colNo
      "",                                                     // aName
      "kaiser",                                               // fName
      "/usr/local/MATLAB/R2023b/toolbox/signal/eml/kaiser.m", // pName
      0                                                       // checkKind
  };
  static rtBoundsCheckInfo c_emlrtBCI{
      -1,                                                     // iFirst
      -1,                                                     // iLast
      55,                                                     // lineNo
      7,                                                      // colNo
      "",                                                     // aName
      "kaiser",                                               // fName
      "/usr/local/MATLAB/R2023b/toolbox/signal/eml/kaiser.m", // pName
      0                                                       // checkKind
  };
  static rtBoundsCheckInfo emlrtBCI{
      -1,                                                     // iFirst
      -1,                                                     // iLast
      51,                                                     // lineNo
      7,                                                      // colNo
      "",                                                     // aName
      "kaiser",                                               // fName
      "/usr/local/MATLAB/R2023b/toolbox/signal/eml/kaiser.m", // pName
      0                                                       // checkKind
  };
  static rtRunTimeErrorInfo k_emlrtRTEI{
      18,            // lineNo
      5,             // colNo
      "check_order", // fName
      "/usr/local/MATLAB/R2023b/toolbox/signal/eml/private/check_order.m" // pName
  };
  static rtRunTimeErrorInfo l_emlrtRTEI{
      22,            // lineNo
      23,            // colNo
      "check_order", // fName
      "/usr/local/MATLAB/R2023b/toolbox/signal/eml/private/check_order.m" // pName
  };
  creal_T tmp;
  creal_T zd;
  double ak;
  int inw;
  int nw;
  if (std::isinf(N) || std::isnan(N)) {
    f_rtErrorWithMessageID("N", k_emlrtRTEI.fName, k_emlrtRTEI.lineNo);
  }
  if (!(N >= 0.0)) {
    j_rtErrorWithMessageID(l_emlrtRTEI.fName, l_emlrtRTEI.lineNo);
  }
  if (N == std::floor(N)) {
    nw = static_cast<int>(N);
  } else {
    nw = static_cast<int>(std::round(N));
  }
  w.set_size(nw);
  if (nw <= 1) {
    w.set_size(nw);
    for (int iseven{0}; iseven < nw; iseven++) {
      w[iseven] = 1.0;
    }
  } else {
    int iseven;
    int mid;
    iseven = 1 - (nw & 1);
    mid = (nw >> 1) + 1;
    if ((mid <= nw) && (nw > 2147483646)) {
      check_forloop_overflow_error();
    }
    if (mid <= nw) {
      zd.im = 0.0;
    }
    for (int k{mid}; k <= nw; k++) {
      double AZ_tmp;
      double hz_im;
      double hz_re;
      double r;
      int b_nw;
      int ierr;
      boolean_T guard1;
      r = static_cast<double>(iseven + ((k - mid) << 1)) /
          (static_cast<double>(nw) - 1.0);
      r = (1.0 - r) * (r + 1.0);
      if (r < 0.0) {
        e_rtErrorWithMessageID("sqrt", j_emlrtRTEI.fName, j_emlrtRTEI.lineNo);
      }
      r = std::sqrt(r);
      zd.re = 5.0 * r;
      ierr = 0;
      AZ_tmp = rt_hypotd_snf(zd.re, 0.0);
      if (AZ_tmp > 1.0737418235E+9) {
        ierr = 4;
      } else if (AZ_tmp > 32767.999992370605) {
        ierr = 3;
      }
      tmp.re = 0.0;
      tmp.im = 0.0;
      guard1 = false;
      if (AZ_tmp <= 2.0) {
        b_nw = 0;
        if (AZ_tmp == 0.0) {
          tmp.re = 1.0;
          tmp.im = 0.0;
        } else if (AZ_tmp < 2.2250738585072014E-305) {
          tmp.re = 1.0;
          tmp.im = 0.0;
        } else {
          double acz;
          double ak1_re;
          double cz_re;
          double rak1;
          hz_re = 0.5 * zd.re;
          if (AZ_tmp > 4.7170688552396617E-153) {
            cz_re = hz_re * hz_re;
            acz = rt_hypotd_snf(cz_re, 0.0);
          } else {
            cz_re = 0.0;
            acz = 0.0;
          }
          ak = 1.0;
          gammaln(ak);
          ak1_re = std::log(hz_re) * 0.0 - ak;
          rak1 = ak1_re;
          if (ak1_re > -700.92179369444591) {
            double b_atol;
            double im;
            b_atol = 2.2204460492503131E-16 * acz;
            hz_re = 1.0;
            hz_im = 0.0;
            if (!(acz < 2.2204460492503131E-16)) {
              double aa;
              double s;
              ak1_re = 1.0;
              r = 0.0;
              ak = 3.0;
              s = 1.0;
              aa = 2.0;
              double re;
              double rs;
              do {
                rs = 1.0 / s;
                re = ak1_re * cz_re - r * 0.0;
                im = ak1_re * 0.0 + r * cz_re;
                ak1_re = rs * re;
                r = rs * im;
                hz_re += ak1_re;
                hz_im += r;
                s += ak;
                ak += 2.0;
                aa = aa * acz * rs;
              } while (!!(aa > b_atol));
            }
            r = std::exp(rak1);
            im = r * 0.0;
            cz_re = hz_re * r - hz_im * im;
            hz_im = hz_re * im + hz_im * r;
            tmp.re = cz_re - hz_im * 0.0;
            tmp.im = cz_re * 0.0 + hz_im;
          } else {
            b_nw = 1;
            if (acz > 0.0) {
              b_nw = -1;
            }
          }
        }
        if (b_nw < 0) {
          inw = 1;
        } else {
          inw = b_nw;
        }
        if ((1 - inw != 0) && (b_nw < 0)) {
          guard1 = true;
        }
      } else {
        guard1 = true;
      }
      if (guard1) {
        if (AZ_tmp < 21.784271729432426) {
          b_nw = cmlri(zd, tmp);
          if (b_nw < 0) {
            if (b_nw == -2) {
              inw = -2;
            } else {
              inw = -1;
            }
          } else {
            inw = 0;
          }
        } else {
          b_nw = casyi(zd, tmp);
          if (b_nw < 0) {
            if (b_nw == -2) {
              inw = -2;
            } else {
              inw = -1;
            }
          } else {
            inw = 0;
          }
        }
      }
      guard1 = false;
      if (inw < 0) {
        if (inw == -2) {
          tmp.re = rtNaN;
          tmp.im = 0.0;
        } else {
          ierr = 2;
          guard1 = true;
        }
      } else {
        guard1 = true;
      }
      if (guard1 && (ierr == 2)) {
        tmp.re = rtInf;
        tmp.im = 0.0;
      }
      if (zd.re > 0.0) {
        r = tmp.re;
        tmp.re = r;
        tmp.im = 0.0;
      }
      if (tmp.im == 0.0) {
        hz_re = tmp.re / 27.239871823604449;
        hz_im = 0.0;
      } else if (tmp.re == 0.0) {
        hz_re = 0.0;
        hz_im = tmp.im / 27.239871823604449;
      } else {
        hz_re = tmp.re / 27.239871823604449;
        hz_im = tmp.im / 27.239871823604449;
      }
      if (k > w.size(0)) {
        rtDynamicBoundsError(k, 1, w.size(0), emlrtBCI);
      }
      w[k - 1] = rt_hypotd_snf(hz_re, hz_im);
    }
    for (int k{0}; k <= mid - 2; k++) {
      iseven = nw - k;
      if ((iseven < 1) || (iseven > w.size(0))) {
        rtDynamicBoundsError(iseven, 1, w.size(0), b_emlrtBCI);
      }
      if (k + 1 > w.size(0)) {
        rtDynamicBoundsError(k + 1, 1, w.size(0), c_emlrtBCI);
      }
      w[k] = w[iseven - 1];
    }
  }
}

} // namespace coder

// End of code generation (kaiser.cpp)
