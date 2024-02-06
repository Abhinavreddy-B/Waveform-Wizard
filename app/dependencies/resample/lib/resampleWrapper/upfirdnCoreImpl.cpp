//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// upfirdnCoreImpl.cpp
//
// Code generation for function 'upfirdnCoreImpl'
//

// Include files
#include "upfirdnCoreImpl.h"
#include "eml_int_forloop_overflow_check.h"
#include "resampleWrapper_rtwutil.h"
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
static void rtDivisionByZeroError(const rtRunTimeErrorInfo &aInfo);

// Function Definitions
static void rtDivisionByZeroError(const rtRunTimeErrorInfo &aInfo)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "Division by zero detected.\nEarly termination due to division "
               "by zero.";
  outStream << "\n";
  ((((outStream << "Error in ") << aInfo.fName) << " (line ") << aInfo.lineNo)
      << ")";
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
namespace upfirdn {
void upfirdnCoreImpl(const array<double, 1U> &xCol,
                     const array<double, 1U> &hCl, double LxD, double LhD,
                     double pD, double qD, array<double, 1U> &y)
{
  static rtBoundsCheckInfo b_emlrtBCI{
      -1,                // iFirst
      -1,                // iLast
      83,                // lineNo
      15,                // colNo
      "",                // aName
      "upfirdnCoreImpl", // fName
      "/usr/local/MATLAB/R2023b/toolbox/signal/signal/+signal/+internal/"
      "+upfirdn/upfirdnCoreImpl.m", // pName
      0                             // checkKind
  };
  static rtBoundsCheckInfo c_emlrtBCI{
      -1,                // iFirst
      -1,                // iLast
      91,                // lineNo
      26,                // colNo
      "",                // aName
      "upfirdnCoreImpl", // fName
      "/usr/local/MATLAB/R2023b/toolbox/signal/signal/+signal/+internal/"
      "+upfirdn/upfirdnCoreImpl.m", // pName
      0                             // checkKind
  };
  static rtBoundsCheckInfo d_emlrtBCI{
      -1,                // iFirst
      -1,                // iLast
      92,                // lineNo
      38,                // colNo
      "",                // aName
      "upfirdnCoreImpl", // fName
      "/usr/local/MATLAB/R2023b/toolbox/signal/signal/+signal/+internal/"
      "+upfirdn/upfirdnCoreImpl.m", // pName
      0                             // checkKind
  };
  static rtBoundsCheckInfo e_emlrtBCI{
      -1,                // iFirst
      -1,                // iLast
      108,               // lineNo
      26,                // colNo
      "",                // aName
      "upfirdnCoreImpl", // fName
      "/usr/local/MATLAB/R2023b/toolbox/signal/signal/+signal/+internal/"
      "+upfirdn/upfirdnCoreImpl.m", // pName
      0                             // checkKind
  };
  static rtBoundsCheckInfo emlrtBCI{
      -1,                // iFirst
      -1,                // iLast
      82,                // lineNo
      14,                // colNo
      "",                // aName
      "upfirdnCoreImpl", // fName
      "/usr/local/MATLAB/R2023b/toolbox/signal/signal/+signal/+internal/"
      "+upfirdn/upfirdnCoreImpl.m", // pName
      0                             // checkKind
  };
  static rtBoundsCheckInfo f_emlrtBCI{
      -1,                // iFirst
      -1,                // iLast
      108,               // lineNo
      46,                // colNo
      "",                // aName
      "upfirdnCoreImpl", // fName
      "/usr/local/MATLAB/R2023b/toolbox/signal/signal/+signal/+internal/"
      "+upfirdn/upfirdnCoreImpl.m", // pName
      0                             // checkKind
  };
  static rtBoundsCheckInfo g_emlrtBCI{
      -1,                // iFirst
      -1,                // iLast
      110,               // lineNo
      7,                 // colNo
      "",                // aName
      "upfirdnCoreImpl", // fName
      "/usr/local/MATLAB/R2023b/toolbox/signal/signal/+signal/+internal/"
      "+upfirdn/upfirdnCoreImpl.m", // pName
      0                             // checkKind
  };
  static rtDoubleCheckInfo b_emlrtDCI{
      74,                // lineNo
      38,                // colNo
      "upfirdnCoreImpl", // fName
      "/usr/local/MATLAB/R2023b/toolbox/signal/signal/+signal/+internal/"
      "+upfirdn/upfirdnCoreImpl.m", // pName
      4                             // checkKind
  };
  static rtDoubleCheckInfo emlrtDCI{
      61,                // lineNo
      1,                 // colNo
      "upfirdnCoreImpl", // fName
      "/usr/local/MATLAB/R2023b/toolbox/signal/signal/+signal/+internal/"
      "+upfirdn/upfirdnCoreImpl.m", // pName
      4                             // checkKind
  };
  static rtRunTimeErrorInfo
      k_emlrtRTEI{
          102,      // lineNo
          9,        // colNo
          "intmod", // fName
          "/usr/local/MATLAB/R2023b/toolbox/eml/eml/+coder/+internal/+scalar/"
          "mod.m" // pName
      };
  static rtRunTimeErrorInfo
      l_emlrtRTEI{
          19,            // lineNo
          9,             // colNo
          "indexDivide", // fName
          "/usr/local/MATLAB/R2023b/toolbox/eml/eml/+coder/+internal/"
          "indexDivide.m" // pName
      };
  array<int, 2U> hStartList;
  array<int, 2U> inpMultList;
  double yout;
  int Lh;
  int Lx;
  int Lxup;
  int Ly;
  int countInner1;
  int hClStart;
  int i;
  int ihstart;
  int ixend;
  int m;
  int mm;
  int p;
  int p_tmp_tmp_tmp;
  int r;
  int xd_tmp;
  int xdzxm;
  int xm;
  Lx = static_cast<int>(LxD);
  Lh = static_cast<int>(LhD);
  p_tmp_tmp_tmp = static_cast<int>(pD);
  p = static_cast<int>(pD);
  Lxup = static_cast<int>(pD) * (static_cast<int>(LxD) - 1) +
         static_cast<int>(LhD);
  m = Lxup;
  if (Lxup > 0) {
    m = 1;
  } else if (Lxup < 0) {
    m = -1;
  }
  if (m != 0) {
    if (static_cast<int>(qD) == 0) {
      m = Lxup;
    } else {
      m = Lxup - div_s32(Lxup, static_cast<int>(qD)) * static_cast<int>(qD);
    }
  } else {
    if (static_cast<int>(qD) == 0) {
      r = Lxup;
    } else {
      r = Lxup - div_s32(Lxup, static_cast<int>(qD)) * static_cast<int>(qD);
    }
    m = r - static_cast<int>(qD);
  }
  if (m != 0) {
    Ly = div_s32(Lxup, static_cast<int>(qD)) + 1;
  } else {
    Ly = div_s32(Lxup, static_cast<int>(qD));
  }
  if (Ly < 0) {
    rtNonNegativeError(static_cast<double>(Ly), emlrtDCI);
  }
  y.set_size(Ly);
  for (m = 0; m < Ly; m++) {
    y[m] = 0.0;
  }
  xd_tmp = div_s32(static_cast<int>(qD), static_cast<int>(pD));
  if (static_cast<int>(pD) == 0) {
    xm = static_cast<int>(qD);
  } else {
    xm = static_cast<int>(qD) - xd_tmp * static_cast<int>(pD);
  }
  xdzxm = xd_tmp * static_cast<int>(pD) + xm;
  hStartList.set_size(1, hStartList.size(1));
  if (static_cast<int>(pD) < 0) {
    rtNonNegativeError(static_cast<double>(static_cast<int>(pD)), b_emlrtDCI);
  }
  hStartList.set_size(hStartList.size(0), p_tmp_tmp_tmp);
  inpMultList.set_size(1, p_tmp_tmp_tmp);
  if (static_cast<int>(pD) > 2147483646) {
    check_forloop_overflow_error();
  }
  for (int ii{0}; ii < p_tmp_tmp_tmp; ii++) {
    if (static_cast<int>(pD) == 0) {
      m = ii;
    } else {
      if (static_cast<unsigned int>(static_cast<int>(pD)) == 0U) {
        rtDivisionByZeroError(k_emlrtRTEI);
      } else {
        m = static_cast<int>(static_cast<unsigned int>(ii) /
                             static_cast<unsigned int>(static_cast<int>(pD)));
      }
      m = ii - m * static_cast<int>(pD);
    }
    Lxup = xm * m;
    if (static_cast<int>(pD) == 0) {
      r = Lxup;
    } else {
      r = Lxup - div_s32(Lxup, static_cast<int>(pD)) * static_cast<int>(pD);
    }
    if ((ii + 1 < 1) || (ii + 1 > hStartList.size(1))) {
      rtDynamicBoundsError(ii + 1, 1, hStartList.size(1), emlrtBCI);
    }
    hStartList[ii] = r + 1;
    if ((ii + 1 < 1) || (ii + 1 > inpMultList.size(1))) {
      rtDynamicBoundsError(ii + 1, 1, inpMultList.size(1), b_emlrtBCI);
    }
    inpMultList[ii] = (xd_tmp * m + div_s32(Lxup, static_cast<int>(pD))) + 1;
  }
  if (Ly > 2147483646) {
    check_forloop_overflow_error();
  }
  m = Ly - 1;
#pragma omp parallel for num_threads(omp_get_max_threads()) private(           \
    hClStart, countInner1, yout, ixend, ihstart, i, mm)

  for (int iout = 0; iout <= m; iout++) {
    if (static_cast<unsigned int>(p) == 0U) {
      rtDivisionByZeroError(l_emlrtRTEI);
    } else {
      i = static_cast<int>(static_cast<unsigned int>(iout) /
                           static_cast<unsigned int>(p));
    }
    if (p == 0) {
      hClStart = iout + 1;
    } else {
      if (static_cast<unsigned int>(p) == 0U) {
        rtDivisionByZeroError(k_emlrtRTEI);
      } else {
        ihstart = static_cast<int>(static_cast<unsigned int>(iout) /
                                   static_cast<unsigned int>(p));
      }
      hClStart = (iout - ihstart * p) + 1;
    }
    if ((hClStart < 1) || (hClStart > hStartList.size(1))) {
      rtDynamicBoundsError(hClStart, 1, hStartList.size(1), c_emlrtBCI);
    }
    ihstart = hStartList[hClStart - 1];
    if (hClStart > inpMultList.size(1)) {
      rtDynamicBoundsError(hClStart, 1, inpMultList.size(1), d_emlrtBCI);
    }
    ixend = xdzxm * i + inpMultList[hClStart - 1];
    if (ixend > Lx) {
      ihstart += p * (ixend - Lx);
      ixend = Lx;
    }
    yout = 0.0;
    if (Lh < ihstart) {
      countInner1 = 0;
    } else {
      countInner1 = div_s32(Lh - ihstart, p) + 1;
    }
    if (countInner1 > ixend) {
      countInner1 = ixend;
    }
    hClStart = ihstart - p;
    if (countInner1 > 2147483646) {
      check_forloop_overflow_error();
    }
    for (mm = 0; mm < countInner1; mm++) {
      i = ixend - mm;
      if ((i < 1) || (i > xCol.size(0))) {
        rtDynamicBoundsError(i, 1, xCol.size(0), e_emlrtBCI);
      }
      ihstart = hClStart + p * (mm + 1);
      if ((ihstart < 1) || (ihstart > hCl.size(0))) {
        rtDynamicBoundsError(ihstart, 1, hCl.size(0), f_emlrtBCI);
      }
      yout += xCol[i - 1] * hCl[ihstart - 1];
    }
    if (iout + 1 > y.size(0)) {
      rtDynamicBoundsError(iout + 1, 1, y.size(0), g_emlrtBCI);
    }
    y[iout] = yout;
  }
}

} // namespace upfirdn
} // namespace internal
} // namespace b_signal
} // namespace coder

// End of code generation (upfirdnCoreImpl.cpp)
