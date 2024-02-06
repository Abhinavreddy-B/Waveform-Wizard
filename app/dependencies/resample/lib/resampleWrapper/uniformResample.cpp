//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// uniformResample.cpp
//
// Code generation for function 'uniformResample'
//

// Include files
#include "uniformResample.h"
#include "assertValidSizeArg.h"
#include "firls.h"
#include "indexShapeCheck.h"
#include "ipermute.h"
#include "kaiser.h"
#include "resampleWrapper_data.h"
#include "resampleWrapper_rtwutil.h"
#include "resampleWrapper_types.h"
#include "rt_nonfinite.h"
#include "uniformParserNBetaAndDesignFilter.h"
#include "upfirdnCoreImpl.h"
#include "coder_array.h"
#include "omp.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <string>

// Variable Definitions
static rtRunTimeErrorInfo g_emlrtRTEI{
    79,                  // lineNo
    23,                  // colNo
    "reshapeSizeChecks", // fName
    "/usr/local/MATLAB/R2023b/toolbox/eml/eml/+coder/+internal/"
    "reshapeSizeChecks.m" // pName
};

static rtRunTimeErrorInfo h_emlrtRTEI{
    81,                  // lineNo
    23,                  // colNo
    "reshapeSizeChecks", // fName
    "/usr/local/MATLAB/R2023b/toolbox/eml/eml/+coder/+internal/"
    "reshapeSizeChecks.m" // pName
};

// Function Declarations
static void b_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void c_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

namespace coder {
namespace b_signal {
namespace internal {
namespace resample {
static void resampleCore(const array<double, 1U> &x, double Lx,
                         const double xSize[2], double xNumel,
                         const array<double, 2U> &h, double delay, double p,
                         double q, double Dim, const double xtrueSize[2],
                         boolean_T xtrueIsRow, double xtrueNumel,
                         array<double, 2U> &y);

}
} // namespace internal
} // namespace b_signal
} // namespace coder
static void rtErrorWithMessageID(const char *r, const char *r1,
                                 const char *aFcnName, int aLineNum);

// Function Definitions
static void b_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "Size vector elements should be nonnegative.";
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

static void c_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "To RESHAPE the number of elements must not change.";
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
namespace b_signal {
namespace internal {
namespace resample {
static void resampleCore(const array<double, 1U> &x, double Lx,
                         const double xSize[2], double xNumel,
                         const array<double, 2U> &h, double delay, double p,
                         double q, double Dim, const double xtrueSize[2],
                         boolean_T xtrueIsRow, double xtrueNumel,
                         array<double, 2U> &y)
{
  static rtBoundsCheckInfo b_emlrtBCI{
      -1,             // iFirst
      -1,             // iLast
      183,            // lineNo
      19,             // colNo
      "",             // aName
      "resampleCore", // fName
      "/usr/local/MATLAB/R2023b/toolbox/signal/signal/+signal/+internal/"
      "+resample/uniformResample.m", // pName
      0                              // checkKind
  };
  static rtBoundsCheckInfo emlrtBCI{
      -1,             // iFirst
      -1,             // iLast
      190,            // lineNo
      19,             // colNo
      "",             // aName
      "resampleCore", // fName
      "/usr/local/MATLAB/R2023b/toolbox/signal/signal/+signal/+internal/"
      "+resample/uniformResample.m", // pName
      0                              // checkKind
  };
  static rtDoubleCheckInfo b_emlrtDCI{
      190,            // lineNo
      19,             // colNo
      "resampleCore", // fName
      "/usr/local/MATLAB/R2023b/toolbox/signal/signal/+signal/+internal/"
      "+resample/uniformResample.m", // pName
      1                              // checkKind
  };
  static rtDoubleCheckInfo c_emlrtDCI{
      173,            // lineNo
      26,             // colNo
      "resampleCore", // fName
      "/usr/local/MATLAB/R2023b/toolbox/signal/signal/+signal/+internal/"
      "+resample/uniformResample.m", // pName
      4                              // checkKind
  };
  static rtDoubleCheckInfo d_emlrtDCI{
      173,            // lineNo
      26,             // colNo
      "resampleCore", // fName
      "/usr/local/MATLAB/R2023b/toolbox/signal/signal/+signal/+internal/"
      "+resample/uniformResample.m", // pName
      1                              // checkKind
  };
  static rtDoubleCheckInfo emlrtDCI{
      183,            // lineNo
      19,             // colNo
      "resampleCore", // fName
      "/usr/local/MATLAB/R2023b/toolbox/signal/signal/+signal/+internal/"
      "+resample/uniformResample.m", // pName
      1                              // checkKind
  };
  static rtRunTimeErrorInfo k_emlrtRTEI{
      35,                                                     // lineNo
      80,                                                     // colNo
      "upfirdn",                                              // fName
      "/usr/local/MATLAB/R2023b/toolbox/signal/eml/upfirdn.m" // pName
  };
  array<double, 2U> indV;
  array<double, 2U> yVec;
  array<double, 1U> b_h;
  array<double, 1U> b_y;
  array<double, 1U> yV;
  double sy[2];
  double syTrue[2];
  double Ly;
  int k;
  int maxdimlen;
  boolean_T b_p;
  boolean_T exitg1;
  Ly = std::ceil(Lx * p / q);
  sy[0] = xSize[0];
  sy[1] = xSize[1];
  syTrue[0] = xtrueSize[0];
  syTrue[1] = xtrueSize[1];
  if (xtrueIsRow) {
    sy[1] = Ly;
    syTrue[1] = Ly;
  } else {
    sy[0] = Ly;
    syTrue[0] = Ly;
  }
  if (!(syTrue[0] >= 0.0)) {
    rtNonNegativeError(syTrue[0], c_emlrtDCI);
  }
  if (syTrue[0] != static_cast<int>(std::floor(syTrue[0]))) {
    rtIntegerError(syTrue[0], d_emlrtDCI);
  }
  if (!(syTrue[1] >= 0.0)) {
    rtNonNegativeError(syTrue[1], c_emlrtDCI);
  }
  if (syTrue[1] != static_cast<int>(std::floor(syTrue[1]))) {
    rtIntegerError(syTrue[1], d_emlrtDCI);
  }
  if (std::isinf(p) || std::isnan(p)) {
    rtErrorWithMessageID("input number 3, P,", emlrtRTEI.fName,
                         emlrtRTEI.lineNo);
  }
  if (p <= 0.0) {
    b_rtErrorWithMessageID("input number 3, P,", b_emlrtRTEI.fName,
                           b_emlrtRTEI.lineNo);
  }
  if (!(std::floor(p) == p)) {
    c_rtErrorWithMessageID("input number 3, P,", c_emlrtRTEI.fName,
                           c_emlrtRTEI.lineNo);
  }
  if (std::isinf(q) || std::isnan(q)) {
    rtErrorWithMessageID("input number 4, Q,", emlrtRTEI.fName,
                         emlrtRTEI.lineNo);
  }
  if (q <= 0.0) {
    b_rtErrorWithMessageID("input number 4, Q,", b_emlrtRTEI.fName,
                           b_emlrtRTEI.lineNo);
  }
  if (!(std::floor(q) == q)) {
    c_rtErrorWithMessageID("input number 4, Q,", c_emlrtRTEI.fName,
                           c_emlrtRTEI.lineNo);
  }
  if (p * q > 2.147483647E+9) {
    rtErrorWithMessageID("Q", "P", k_emlrtRTEI.fName, k_emlrtRTEI.lineNo);
  }
  if (x.size(0) == 0) {
    d_rtErrorWithMessageID("input number 1, X,", d_emlrtRTEI.fName,
                           d_emlrtRTEI.lineNo);
  }
  if (h.size(1) == 0) {
    d_rtErrorWithMessageID("input number 2, H,", d_emlrtRTEI.fName,
                           d_emlrtRTEI.lineNo);
  }
  b_p = true;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k <= h.size(1) - 1)) {
    if ((!std::isinf(h[k])) && (!std::isnan(h[k]))) {
      k++;
    } else {
      b_p = false;
      exitg1 = true;
    }
  }
  if (!b_p) {
    rtErrorWithMessageID("input number 2, H,", emlrtRTEI.fName,
                         emlrtRTEI.lineNo);
  }
  k = h.size(1);
  b_h = h.reshape(k);
  upfirdn::upfirdnCoreImpl(x, b_h, static_cast<double>(x.size(0)),
                           static_cast<double>(h.size(1)), p, q, b_y);
  if (x.size(0) == 1) {
    yVec.set_size(1, b_y.size(0));
    maxdimlen = b_y.size(0);
    for (int i{0}; i < maxdimlen; i++) {
      yVec[yVec.size(0) * i] = b_y[i];
    }
  } else {
    yVec.set_size(b_y.size(0), 1);
    maxdimlen = b_y.size(0);
    for (int i{0}; i < maxdimlen; i++) {
      yVec[i] = b_y[i];
    }
  }
  if (std::isnan(Ly)) {
    indV.set_size(1, 1);
    indV[0] = rtNaN;
  } else if (Ly < 1.0) {
    indV.set_size(indV.size(0), 0);
  } else {
    indV.set_size(1, static_cast<int>(Ly - 1.0) + 1);
    maxdimlen = static_cast<int>(Ly - 1.0);
    for (int i{0}; i <= maxdimlen; i++) {
      indV[i] = static_cast<double>(i) + 1.0;
    }
  }
  indV.set_size(1, indV.size(1));
  maxdimlen = indV.size(1) - 1;
  for (int i{0}; i <= maxdimlen; i++) {
    indV[i] = delay + indV[i];
  }
  if (x.size(0) != 1) {
    b_y.set_size(indV.size(1));
    maxdimlen = indV.size(1);
    for (int i{0}; i < maxdimlen; i++) {
      b_y[i] = indV[i];
    }
    int iv[2];
    iv[0] = (*(int(*)[2])yVec.size())[0];
    iv[1] = (*(int(*)[2])yVec.size())[1];
    ::coder::internal::indexShapeCheck(iv, b_y.size(0));
    k = yVec.size(0) * yVec.size(1);
    yV.set_size(b_y.size(0));
    maxdimlen = b_y.size(0);
    for (int i{0}; i < maxdimlen; i++) {
      int i1;
      if (b_y[i] != static_cast<int>(std::floor(b_y[i]))) {
        rtIntegerError(b_y[i], emlrtDCI);
      }
      i1 = static_cast<int>(b_y[i]);
      if ((i1 < 1) || (i1 > k)) {
        rtDynamicBoundsError(i1, 1, k, b_emlrtBCI);
      }
      yV[i] = yVec[i1 - 1];
    }
    if (xtrueNumel == xtrueSize[static_cast<int>(Dim) - 1]) {
      ::coder::internal::assertValidSizeArg(syTrue);
      maxdimlen = b_y.size(0);
      if (b_y.size(0) < 1) {
        maxdimlen = 1;
      }
      k = b_y.size(0);
      if (k >= maxdimlen) {
        maxdimlen = k;
      }
      if (static_cast<int>(syTrue[0]) > maxdimlen) {
        rtErrorWithMessageID(f_emlrtRTEI.fName, f_emlrtRTEI.lineNo);
      }
      if (static_cast<int>(syTrue[1]) > maxdimlen) {
        rtErrorWithMessageID(f_emlrtRTEI.fName, f_emlrtRTEI.lineNo);
      }
      b_p = (static_cast<int>(syTrue[0]) >= 0);
      if ((!b_p) || (static_cast<int>(syTrue[1]) < 0)) {
        b_p = false;
      }
      if (!b_p) {
        b_rtErrorWithMessageID(g_emlrtRTEI.fName, g_emlrtRTEI.lineNo);
      }
      maxdimlen = static_cast<int>(syTrue[0]) * static_cast<int>(syTrue[1]);
      if (maxdimlen != b_y.size(0)) {
        c_rtErrorWithMessageID(h_emlrtRTEI.fName, h_emlrtRTEI.lineNo);
      }
      y.set_size(static_cast<int>(syTrue[0]), static_cast<int>(syTrue[1]));
      for (int i{0}; i < maxdimlen; i++) {
        y[i] = yV[i];
      }
    } else {
      y.set_size(b_y.size(0), 1);
      maxdimlen = b_y.size(0);
      for (int i{0}; i < maxdimlen; i++) {
        y[i] = yV[i];
      }
    }
  } else {
    int iv[2];
    int iv1[2];
    iv[0] = (*(int(*)[2])yVec.size())[0];
    iv[1] = (*(int(*)[2])yVec.size())[1];
    iv1[0] = (*(int(*)[2])indV.size())[0];
    iv1[1] = (*(int(*)[2])indV.size())[1];
    ::coder::internal::indexShapeCheck(iv, iv1);
    k = yVec.size(0) * yVec.size(1);
    maxdimlen = indV.size(1);
    for (int i{0}; i < maxdimlen; i++) {
      int i1;
      if (indV[i] != static_cast<int>(std::floor(indV[i]))) {
        rtIntegerError(indV[i], b_emlrtDCI);
      }
      i1 = static_cast<int>(indV[i]);
      if ((i1 < 1) || (i1 > k)) {
        rtDynamicBoundsError(i1, 1, k, emlrtBCI);
      }
    }
    b_y.set_size(indV.size(1));
    maxdimlen = indV.size(1);
    for (int i{0}; i < maxdimlen; i++) {
      b_y[i] = yVec[static_cast<int>(indV[i]) - 1];
    }
    if (xNumel == xtrueNumel) {
      ::coder::internal::assertValidSizeArg(syTrue);
      maxdimlen = indV.size(1);
      if (indV.size(1) < 1) {
        maxdimlen = 1;
      }
      k = indV.size(1);
      if (k >= maxdimlen) {
        maxdimlen = k;
      }
      if (static_cast<int>(syTrue[0]) > maxdimlen) {
        rtErrorWithMessageID(f_emlrtRTEI.fName, f_emlrtRTEI.lineNo);
      }
      if (static_cast<int>(syTrue[1]) > maxdimlen) {
        rtErrorWithMessageID(f_emlrtRTEI.fName, f_emlrtRTEI.lineNo);
      }
      b_p = (static_cast<int>(syTrue[0]) >= 0);
      if ((!b_p) || (static_cast<int>(syTrue[1]) < 0)) {
        b_p = false;
      }
      if (!b_p) {
        b_rtErrorWithMessageID(g_emlrtRTEI.fName, g_emlrtRTEI.lineNo);
      }
      maxdimlen = static_cast<int>(syTrue[0]) * static_cast<int>(syTrue[1]);
      if (maxdimlen != indV.size(1)) {
        c_rtErrorWithMessageID(h_emlrtRTEI.fName, h_emlrtRTEI.lineNo);
      }
      y.set_size(static_cast<int>(syTrue[0]), static_cast<int>(syTrue[1]));
      for (int i{0}; i < maxdimlen; i++) {
        y[i] = b_y[i];
      }
    } else {
      ::coder::internal::assertValidSizeArg(sy);
      maxdimlen = indV.size(1);
      if (indV.size(1) < 1) {
        maxdimlen = 1;
      }
      k = indV.size(1);
      if (k >= maxdimlen) {
        maxdimlen = k;
      }
      if (static_cast<int>(sy[0]) > maxdimlen) {
        rtErrorWithMessageID(f_emlrtRTEI.fName, f_emlrtRTEI.lineNo);
      }
      if (static_cast<int>(sy[1]) > maxdimlen) {
        rtErrorWithMessageID(f_emlrtRTEI.fName, f_emlrtRTEI.lineNo);
      }
      b_p = (static_cast<int>(sy[0]) >= 0);
      if ((!b_p) || (static_cast<int>(sy[1]) < 0)) {
        b_p = false;
      }
      if (!b_p) {
        b_rtErrorWithMessageID(g_emlrtRTEI.fName, g_emlrtRTEI.lineNo);
      }
      maxdimlen = static_cast<int>(sy[0]) * static_cast<int>(sy[1]);
      if (maxdimlen != indV.size(1)) {
        c_rtErrorWithMessageID(h_emlrtRTEI.fName, h_emlrtRTEI.lineNo);
      }
      y.set_size(static_cast<int>(sy[0]), static_cast<int>(sy[1]));
      for (int i{0}; i < maxdimlen; i++) {
        y[i] = b_y[i];
      }
    }
  }
}

} // namespace resample
} // namespace internal
} // namespace b_signal
} // namespace coder
static void rtErrorWithMessageID(const char *r, const char *r1,
                                 const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  ((((outStream << "The product of the downsample factor ") << r)
    << " and the upsample factor ")
   << r1)
      << " must be less than 2^31.";
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
namespace b_signal {
namespace internal {
namespace resample {
void resampleByDesignedFilter(const array<double, 1U> &xIn, double Lx,
                              const double xSize[2], double xNumel, double p,
                              double q, double Dim, const double xtrueSize[2],
                              double xtrueNumel, boolean_T xtrueIsRow,
                              array<double, 2U> &y, array<double, 2U> &hout)
{
  static rtBoundsCheckInfo b_emlrtBCI{
      -1,                          // iFirst
      -1,                          // iLast
      34,                          // lineNo
      21,                          // colNo
      "",                          // aName
      "findDelayAndZeroPadFilter", // fName
      "/usr/local/MATLAB/R2023b/toolbox/signal/signal/+signal/+internal/"
      "+resample/findDelayAndZeroPadFilter.m", // pName
      0                                        // checkKind
  };
  static rtBoundsCheckInfo emlrtBCI{
      -1,                          // iFirst
      -1,                          // iLast
      34,                          // lineNo
      8,                           // colNo
      "",                          // aName
      "findDelayAndZeroPadFilter", // fName
      "/usr/local/MATLAB/R2023b/toolbox/signal/signal/+signal/+internal/"
      "+resample/findDelayAndZeroPadFilter.m", // pName
      0                                        // checkKind
  };
  static rtDoubleCheckInfo b_emlrtDCI{
      20,                          // lineNo
      13,                          // colNo
      "findDelayAndZeroPadFilter", // fName
      "/usr/local/MATLAB/R2023b/toolbox/signal/signal/+signal/+internal/"
      "+resample/findDelayAndZeroPadFilter.m", // pName
      1                                        // checkKind
  };
  static rtDoubleCheckInfo c_emlrtDCI{
      31,                          // lineNo
      8,                           // colNo
      "findDelayAndZeroPadFilter", // fName
      "/usr/local/MATLAB/R2023b/toolbox/signal/signal/+signal/+internal/"
      "+resample/findDelayAndZeroPadFilter.m", // pName
      1                                        // checkKind
  };
  static rtDoubleCheckInfo d_emlrtDCI{
      31,                          // lineNo
      16,                          // colNo
      "findDelayAndZeroPadFilter", // fName
      "/usr/local/MATLAB/R2023b/toolbox/signal/signal/+signal/+internal/"
      "+resample/findDelayAndZeroPadFilter.m", // pName
      1                                        // checkKind
  };
  static rtDoubleCheckInfo emlrtDCI{
      20,                          // lineNo
      13,                          // colNo
      "findDelayAndZeroPadFilter", // fName
      "/usr/local/MATLAB/R2023b/toolbox/signal/signal/+signal/+internal/"
      "+resample/findDelayAndZeroPadFilter.m", // pName
      4                                        // checkKind
  };
  static rtEqualityCheckInfo emlrtECI{
      2,                                   // nDims
      44,                                  // lineNo
      10,                                  // colNo
      "uniformParserNBetaAndDesignFilter", // fName
      "/usr/local/MATLAB/R2023b/toolbox/signal/signal/+signal/+internal/"
      "+resample/uniformParserNBetaAndDesignFilter.m" // pName
  };
  array<double, 2U> h;
  array<double, 2U> h1;
  array<double, 1U> a;
  array<double, 1U> b_xIn;
  if ((p == 1.0) && (q == 1.0)) {
    if (xNumel == xtrueNumel) {
      int firstBlockLength;
      int xblockoffset;
      ipermute(xIn, a);
      ::coder::internal::assertValidSizeArg(xtrueSize);
      xblockoffset = a.size(0);
      if (a.size(0) < 1) {
        xblockoffset = 1;
      }
      firstBlockLength = a.size(0);
      if (firstBlockLength >= xblockoffset) {
        xblockoffset = firstBlockLength;
      }
      if (static_cast<int>(xtrueSize[0]) > xblockoffset) {
        rtErrorWithMessageID(f_emlrtRTEI.fName, f_emlrtRTEI.lineNo);
      }
      if (static_cast<int>(xtrueSize[0]) < 0) {
        b_rtErrorWithMessageID(g_emlrtRTEI.fName, g_emlrtRTEI.lineNo);
      }
      if (static_cast<int>(xtrueSize[0]) != a.size(0)) {
        c_rtErrorWithMessageID(h_emlrtRTEI.fName, h_emlrtRTEI.lineNo);
      }
      xblockoffset = static_cast<int>(xtrueSize[0]);
      y.set_size(static_cast<int>(xtrueSize[0]), 1);
      for (firstBlockLength = 0; firstBlockLength < xblockoffset;
           firstBlockLength++) {
        y[firstBlockLength] = a[firstBlockLength];
      }
    } else {
      int firstBlockLength;
      int xblockoffset;
      ::coder::internal::assertValidSizeArg(xSize);
      xblockoffset = xIn.size(0);
      if (xIn.size(0) < 1) {
        xblockoffset = 1;
      }
      firstBlockLength = xIn.size(0);
      if (firstBlockLength >= xblockoffset) {
        xblockoffset = firstBlockLength;
      }
      if (static_cast<int>(xSize[0]) > xblockoffset) {
        rtErrorWithMessageID(f_emlrtRTEI.fName, f_emlrtRTEI.lineNo);
      }
      if (static_cast<int>(xSize[0]) < 0) {
        b_rtErrorWithMessageID(g_emlrtRTEI.fName, g_emlrtRTEI.lineNo);
      }
      if (static_cast<int>(xSize[0]) != xIn.size(0)) {
        c_rtErrorWithMessageID(h_emlrtRTEI.fName, h_emlrtRTEI.lineNo);
      }
      xblockoffset = static_cast<int>(xSize[0]);
      b_xIn = xIn.reshape(xblockoffset);
      ipermute(b_xIn, a);
      y.set_size(a.size(0), 1);
      xblockoffset = a.size(0);
      for (firstBlockLength = 0; firstBlockLength < xblockoffset;
           firstBlockLength++) {
        y[firstBlockLength] = a[firstBlockLength];
      }
    }
    hout.set_size(1, 1);
    hout[0] = 1.0;
  } else {
    double dv[4];
    double fc;
    double nZeroBegin;
    double pqmax;
    int firstBlockLength;
    int nblocks;
    int xblockoffset;
    pqmax = std::fmax(p, q);
    fc = 0.5 / pqmax;
    nZeroBegin = 20.0 * pqmax + 1.0;
    dv[0] = 0.0;
    dv[1] = 2.0 * fc;
    dv[2] = 2.0 * fc;
    dv[3] = 1.0;
    eFirls(nZeroBegin - 1.0, dv, h, a);
    kaiser(nZeroBegin, a);
    if ((a.size(0) != h.size(1)) && ((h.size(1) != 1) && (a.size(0) != 1))) {
      emlrtDimSizeImpxCheckR2021b(h.size(1), a.size(0), emlrtECI);
    }
    if (a.size(0) == h.size(1)) {
      h1.set_size(1, h.size(1));
      xblockoffset = h.size(1);
      for (firstBlockLength = 0; firstBlockLength < xblockoffset;
           firstBlockLength++) {
        h1[firstBlockLength] = h[firstBlockLength] * a[firstBlockLength];
      }
    } else {
      binary_expand_op(h1, h, a);
    }
    if (h1.size(1) == 0) {
      pqmax = 0.0;
    } else {
      int lastBlockLength;
      if (h1.size(1) <= 1024) {
        firstBlockLength = h1.size(1);
        lastBlockLength = 0;
        nblocks = 1;
      } else {
        firstBlockLength = 1024;
        nblocks = static_cast<int>(static_cast<unsigned int>(h1.size(1)) >> 10);
        lastBlockLength = h1.size(1) - (nblocks << 10);
        if (lastBlockLength > 0) {
          nblocks++;
        } else {
          lastBlockLength = 1024;
        }
      }
      pqmax = h1[0];
      for (int k{2}; k <= firstBlockLength; k++) {
        pqmax += h1[k - 1];
      }
      for (int ib{2}; ib <= nblocks; ib++) {
        xblockoffset = (ib - 1) << 10;
        fc = h1[xblockoffset];
        if (ib == nblocks) {
          firstBlockLength = lastBlockLength;
        } else {
          firstBlockLength = 1024;
        }
        for (int k{2}; k <= firstBlockLength; k++) {
          fc += h1[(xblockoffset + k) - 1];
        }
        pqmax += fc;
      }
    }
    h1.set_size(1, h1.size(1));
    xblockoffset = h1.size(1) - 1;
    for (firstBlockLength = 0; firstBlockLength <= xblockoffset;
         firstBlockLength++) {
      h1[firstBlockLength] = p * h1[firstBlockLength] / pqmax;
    }
    fc = (nZeroBegin - 1.0) / 2.0;
    pqmax = fc;
    if (q == 0.0) {
      if (fc == 0.0) {
        pqmax = 0.0;
      }
    } else if (std::isnan(fc) || std::isnan(q) || std::isinf(fc)) {
      pqmax = rtNaN;
    } else if (fc == 0.0) {
      pqmax = 0.0 / q;
    } else if (std::isinf(q)) {
      if (fc < 0.0) {
        pqmax = q;
      }
    } else {
      pqmax = std::fmod(fc, q);
      if (pqmax == 0.0) {
        pqmax = q * 0.0;
      } else if (fc < 0.0) {
        pqmax += q;
      }
    }
    nZeroBegin = std::floor(q - pqmax);
    if (!(nZeroBegin >= 0.0)) {
      rtNonNegativeError(nZeroBegin, emlrtDCI);
    }
    if (nZeroBegin != static_cast<int>(nZeroBegin)) {
      rtIntegerError(nZeroBegin, b_emlrtDCI);
    }
    h.set_size(1, h1.size(1) + static_cast<int>(nZeroBegin));
    xblockoffset = static_cast<int>(nZeroBegin);
    for (firstBlockLength = 0; firstBlockLength < xblockoffset;
         firstBlockLength++) {
      h[firstBlockLength] = 0.0;
    }
    xblockoffset = h1.size(1);
    for (firstBlockLength = 0; firstBlockLength < xblockoffset;
         firstBlockLength++) {
      h[firstBlockLength + static_cast<int>(nZeroBegin)] = h1[firstBlockLength];
    }
    fc = std::floor(std::ceil(fc + nZeroBegin) / q);
    for (pqmax = 0.0;
         std::ceil((((Lx - 1.0) * p + static_cast<double>(h.size(1))) + pqmax) /
                   q) -
             fc <
         std::ceil(Lx * p / q);
         pqmax++) {
    }
    firstBlockLength = h.size(1);
    if (pqmax != static_cast<int>(pqmax)) {
      rtIntegerError(pqmax, c_emlrtDCI);
    }
    xblockoffset = static_cast<int>(pqmax);
    h.set_size(h.size(0), h.size(1) + static_cast<int>(pqmax));
    if (pqmax != static_cast<int>(pqmax)) {
      rtIntegerError(pqmax, d_emlrtDCI);
    }
    for (nblocks = 0; nblocks < xblockoffset; nblocks++) {
      h[firstBlockLength + nblocks] = 0.0;
    }
    pqmax = static_cast<double>(h.size(1)) - pqmax;
    if (nZeroBegin + 1.0 > pqmax) {
      firstBlockLength = 0;
      nblocks = 0;
    } else {
      if ((static_cast<int>(nZeroBegin + 1.0) < 1) ||
          (static_cast<int>(nZeroBegin + 1.0) > h.size(1))) {
        rtDynamicBoundsError(static_cast<int>(nZeroBegin + 1.0), 1, h.size(1),
                             emlrtBCI);
      }
      firstBlockLength = static_cast<int>(nZeroBegin + 1.0) - 1;
      nblocks = static_cast<int>(pqmax);
      if (nblocks > h.size(1)) {
        rtDynamicBoundsError(static_cast<int>(pqmax), 1, h.size(1), b_emlrtBCI);
      }
    }
    xblockoffset = nblocks - firstBlockLength;
    hout.set_size(1, xblockoffset);
    for (nblocks = 0; nblocks < xblockoffset; nblocks++) {
      hout[nblocks] = h[firstBlockLength + nblocks];
    }
    resampleCore(xIn, Lx, xSize, xNumel, h, fc, p, q, Dim, xtrueSize,
                 xtrueIsRow, xtrueNumel, y);
  }
}

} // namespace resample
} // namespace internal
} // namespace b_signal
} // namespace coder

// End of code generation (uniformResample.cpp)
