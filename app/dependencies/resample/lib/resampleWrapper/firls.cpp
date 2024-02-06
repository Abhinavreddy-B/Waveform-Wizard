//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// firls.cpp
//
// Code generation for function 'firls'
//

// Include files
#include "firls.h"
#include "any1.h"
#include "div.h"
#include "eml_int_forloop_overflow_check.h"
#include "eml_mtimes_helper.h"
#include "indexShapeCheck.h"
#include "minOrMax.h"
#include "mldivide.h"
#include "resampleWrapper_data.h"
#include "resampleWrapper_rtwutil.h"
#include "resampleWrapper_types.h"
#include "rt_nonfinite.h"
#include "validateattributes.h"
#include "coder_array.h"
#include "omp.h"
#include <cfloat>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <string>

// Function Declarations
static void e_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void f_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void g_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void h_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void minus(coder::array<double, 1U> &in1,
                  const coder::array<double, 1U> &in2);

static void plus(coder::array<double, 1U> &in1,
                 const coder::array<double, 1U> &in2);

static double rt_remd_snf(double u0, double u1);

// Function Definitions
static void e_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "Arrays have incompatible sizes for this operation.";
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

static void f_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "Filter order must be a real, positive integer.";
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

static void g_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "Frequencies in F must be non decreasing.";
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

static void h_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "Frequencies in F must be in range [0,1].";
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

static void minus(coder::array<double, 1U> &in1,
                  const coder::array<double, 1U> &in2)
{
  coder::array<double, 1U> b_in1;
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  if (in2.size(0) == 1) {
    loop_ub = in1.size(0);
  } else {
    loop_ub = in2.size(0);
  }
  b_in1.set_size(loop_ub);
  stride_0_0 = (in1.size(0) != 1);
  stride_1_0 = (in2.size(0) != 1);
  for (int i{0}; i < loop_ub; i++) {
    b_in1[i] = in1[i * stride_0_0] - in2[i * stride_1_0];
  }
  in1.set_size(b_in1.size(0));
  loop_ub = b_in1.size(0);
  for (int i{0}; i < loop_ub; i++) {
    in1[i] = b_in1[i];
  }
}

static void plus(coder::array<double, 1U> &in1,
                 const coder::array<double, 1U> &in2)
{
  coder::array<double, 1U> b_in1;
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  if (in2.size(0) == 1) {
    loop_ub = in1.size(0);
  } else {
    loop_ub = in2.size(0);
  }
  b_in1.set_size(loop_ub);
  stride_0_0 = (in1.size(0) != 1);
  stride_1_0 = (in2.size(0) != 1);
  for (int i{0}; i < loop_ub; i++) {
    b_in1[i] = in1[i * stride_0_0] + in2[i * stride_1_0];
  }
  in1.set_size(b_in1.size(0));
  loop_ub = b_in1.size(0);
  for (int i{0}; i < loop_ub; i++) {
    in1[i] = b_in1[i];
  }
}

static double rt_remd_snf(double u0, double u1)
{
  double y;
  if (std::isnan(u0) || std::isnan(u1) || std::isinf(u0)) {
    y = rtNaN;
  } else if (std::isinf(u1)) {
    y = u0;
  } else if ((u1 != 0.0) && (u1 != std::trunc(u1))) {
    double q;
    q = std::abs(u0 / u1);
    if (!(std::abs(q - std::floor(q + 0.5)) > DBL_EPSILON * q)) {
      y = 0.0 * u0;
    } else {
      y = std::fmod(u0, u1);
    }
  } else {
    y = std::fmod(u0, u1);
  }
  return y;
}

namespace coder {
void eFirls(double N, const double freq[4], array<double, 2U> &h,
            array<double, 1U> &a)
{
  static rtBoundsCheckInfo b_emlrtBCI{
      -1,                                                   // iFirst
      -1,                                                   // iLast
      9,                                                    // lineNo
      47,                                                   // colNo
      "",                                                   // aName
      "sinc",                                               // fName
      "/usr/local/MATLAB/R2023b/toolbox/signal/eml/sinc.m", // pName
      0                                                     // checkKind
  };
  static rtBoundsCheckInfo c_emlrtBCI{
      -1,                                                   // iFirst
      -1,                                                   // iLast
      12,                                                   // lineNo
      21,                                                   // colNo
      "",                                                   // aName
      "sinc",                                               // fName
      "/usr/local/MATLAB/R2023b/toolbox/signal/eml/sinc.m", // pName
      0                                                     // checkKind
  };
  static rtBoundsCheckInfo d_emlrtBCI{
      -1,                                                   // iFirst
      -1,                                                   // iLast
      13,                                                   // lineNo
      22,                                                   // colNo
      "",                                                   // aName
      "sinc",                                               // fName
      "/usr/local/MATLAB/R2023b/toolbox/signal/eml/sinc.m", // pName
      0                                                     // checkKind
  };
  static rtBoundsCheckInfo e_emlrtBCI{
      -1,                                                       // iFirst
      -1,                                                       // iLast
      326,                                                      // lineNo
      28,                                                       // colNo
      "",                                                       // aName
      "eFirls",                                                 // fName
      "/usr/local/MATLAB/R2023b/toolbox/signal/signal/firls.m", // pName
      0                                                         // checkKind
  };
  static rtBoundsCheckInfo emlrtBCI{
      -1,                                                   // iFirst
      -1,                                                   // iLast
      9,                                                    // lineNo
      19,                                                   // colNo
      "",                                                   // aName
      "sinc",                                               // fName
      "/usr/local/MATLAB/R2023b/toolbox/signal/eml/sinc.m", // pName
      0                                                     // checkKind
  };
  static rtBoundsCheckInfo f_emlrtBCI{
      -1,                                                       // iFirst
      -1,                                                       // iLast
      327,                                                      // lineNo
      28,                                                       // colNo
      "",                                                       // aName
      "eFirls",                                                 // fName
      "/usr/local/MATLAB/R2023b/toolbox/signal/signal/firls.m", // pName
      0                                                         // checkKind
  };
  static rtBoundsCheckInfo g_emlrtBCI{
      -1,                                                       // iFirst
      -1,                                                       // iLast
      328,                                                      // lineNo
      28,                                                       // colNo
      "",                                                       // aName
      "eFirls",                                                 // fName
      "/usr/local/MATLAB/R2023b/toolbox/signal/signal/firls.m", // pName
      0                                                         // checkKind
  };
  static rtBoundsCheckInfo h_emlrtBCI{
      -1,                                                       // iFirst
      -1,                                                       // iLast
      329,                                                      // lineNo
      28,                                                       // colNo
      "",                                                       // aName
      "eFirls",                                                 // fName
      "/usr/local/MATLAB/R2023b/toolbox/signal/signal/firls.m", // pName
      0                                                         // checkKind
  };
  static rtBoundsCheckInfo i_emlrtBCI{
      -1,                                                       // iFirst
      -1,                                                       // iLast
      337,                                                      // lineNo
      39,                                                       // colNo
      "",                                                       // aName
      "eFirls",                                                 // fName
      "/usr/local/MATLAB/R2023b/toolbox/signal/signal/firls.m", // pName
      0                                                         // checkKind
  };
  static rtBoundsCheckInfo j_emlrtBCI{
      -1,                                                       // iFirst
      -1,                                                       // iLast
      337,                                                      // lineNo
      43,                                                       // colNo
      "",                                                       // aName
      "eFirls",                                                 // fName
      "/usr/local/MATLAB/R2023b/toolbox/signal/signal/firls.m", // pName
      0                                                         // checkKind
  };
  static rtBoundsCheckInfo k_emlrtBCI{
      -1,                                                       // iFirst
      -1,                                                       // iLast
      337,                                                      // lineNo
      66,                                                       // colNo
      "",                                                       // aName
      "eFirls",                                                 // fName
      "/usr/local/MATLAB/R2023b/toolbox/signal/signal/firls.m", // pName
      0                                                         // checkKind
  };
  static rtBoundsCheckInfo l_emlrtBCI{
      -1,                                                       // iFirst
      -1,                                                       // iLast
      337,                                                      // lineNo
      80,                                                       // colNo
      "",                                                       // aName
      "eFirls",                                                 // fName
      "/usr/local/MATLAB/R2023b/toolbox/signal/signal/firls.m", // pName
      0                                                         // checkKind
  };
  static rtBoundsCheckInfo m_emlrtBCI{
      -1,                                                       // iFirst
      -1,                                                       // iLast
      337,                                                      // lineNo
      27,                                                       // colNo
      "",                                                       // aName
      "eFirls",                                                 // fName
      "/usr/local/MATLAB/R2023b/toolbox/signal/signal/firls.m", // pName
      0                                                         // checkKind
  };
  static rtBoundsCheckInfo n_emlrtBCI{
      -1,                                                       // iFirst
      -1,                                                       // iLast
      337,                                                      // lineNo
      31,                                                       // colNo
      "",                                                       // aName
      "eFirls",                                                 // fName
      "/usr/local/MATLAB/R2023b/toolbox/signal/signal/firls.m", // pName
      0                                                         // checkKind
  };
  static rtBoundsCheckInfo o_emlrtBCI{
      -1,                                                       // iFirst
      -1,                                                       // iLast
      357,                                                      // lineNo
      31,                                                       // colNo
      "",                                                       // aName
      "eFirls",                                                 // fName
      "/usr/local/MATLAB/R2023b/toolbox/signal/signal/firls.m", // pName
      0                                                         // checkKind
  };
  static rtBoundsCheckInfo p_emlrtBCI{
      -1,                                                       // iFirst
      -1,                                                       // iLast
      357,                                                      // lineNo
      37,                                                       // colNo
      "",                                                       // aName
      "eFirls",                                                 // fName
      "/usr/local/MATLAB/R2023b/toolbox/signal/signal/firls.m", // pName
      0                                                         // checkKind
  };
  static rtBoundsCheckInfo q_emlrtBCI{
      -1,                                                       // iFirst
      -1,                                                       // iLast
      357,                                                      // lineNo
      39,                                                       // colNo
      "",                                                       // aName
      "eFirls",                                                 // fName
      "/usr/local/MATLAB/R2023b/toolbox/signal/signal/firls.m", // pName
      0                                                         // checkKind
  };
  static rtBoundsCheckInfo r_emlrtBCI{
      -1,                                                       // iFirst
      -1,                                                       // iLast
      357,                                                      // lineNo
      16,                                                       // colNo
      "",                                                       // aName
      "eFirls",                                                 // fName
      "/usr/local/MATLAB/R2023b/toolbox/signal/signal/firls.m", // pName
      0                                                         // checkKind
  };
  static rtBoundsCheckInfo s_emlrtBCI{
      -1,                                                       // iFirst
      -1,                                                       // iLast
      357,                                                      // lineNo
      23,                                                       // colNo
      "",                                                       // aName
      "eFirls",                                                 // fName
      "/usr/local/MATLAB/R2023b/toolbox/signal/signal/firls.m", // pName
      0                                                         // checkKind
  };
  static rtBoundsCheckInfo t_emlrtBCI{
      -1,                                                       // iFirst
      -1,                                                       // iLast
      353,                                                      // lineNo
      15,                                                       // colNo
      "",                                                       // aName
      "eFirls",                                                 // fName
      "/usr/local/MATLAB/R2023b/toolbox/signal/signal/firls.m", // pName
      0                                                         // checkKind
  };
  static rtDoubleCheckInfo b_emlrtDCI{
      297,                                                      // lineNo
      23,                                                       // colNo
      "eFirls",                                                 // fName
      "/usr/local/MATLAB/R2023b/toolbox/signal/signal/firls.m", // pName
      1                                                         // checkKind
  };
  static rtDoubleCheckInfo c_emlrtDCI{
      300,                                                      // lineNo
      19,                                                       // colNo
      "eFirls",                                                 // fName
      "/usr/local/MATLAB/R2023b/toolbox/signal/signal/firls.m", // pName
      1                                                         // checkKind
  };
  static rtDoubleCheckInfo d_emlrtDCI{
      303,                                                      // lineNo
      19,                                                       // colNo
      "eFirls",                                                 // fName
      "/usr/local/MATLAB/R2023b/toolbox/signal/signal/firls.m", // pName
      1                                                         // checkKind
  };
  static rtDoubleCheckInfo e_emlrtDCI{
      310,                                                      // lineNo
      32,                                                       // colNo
      "eFirls",                                                 // fName
      "/usr/local/MATLAB/R2023b/toolbox/signal/signal/firls.m", // pName
      1                                                         // checkKind
  };
  static rtDoubleCheckInfo emlrtDCI{
      278,                                                      // lineNo
      42,                                                       // colNo
      "eFirls",                                                 // fName
      "/usr/local/MATLAB/R2023b/toolbox/signal/signal/firls.m", // pName
      1                                                         // checkKind
  };
  static rtDoubleCheckInfo f_emlrtDCI{
      317,                                                      // lineNo
      31,                                                       // colNo
      "eFirls",                                                 // fName
      "/usr/local/MATLAB/R2023b/toolbox/signal/signal/firls.m", // pName
      1                                                         // checkKind
  };
  static rtDoubleCheckInfo g_emlrtDCI{
      357,                                                      // lineNo
      39,                                                       // colNo
      "eFirls",                                                 // fName
      "/usr/local/MATLAB/R2023b/toolbox/signal/signal/firls.m", // pName
      1                                                         // checkKind
  };
  static rtDoubleCheckInfo h_emlrtDCI{
      357,                                                      // lineNo
      16,                                                       // colNo
      "eFirls",                                                 // fName
      "/usr/local/MATLAB/R2023b/toolbox/signal/signal/firls.m", // pName
      1                                                         // checkKind
  };
  static rtEqualityCheckInfo b_emlrtECI{
      1,                                                       // nDims
      299,                                                     // lineNo
      13,                                                      // colNo
      "eFirls",                                                // fName
      "/usr/local/MATLAB/R2023b/toolbox/signal/signal/firls.m" // pName
  };
  static rtEqualityCheckInfo c_emlrtECI{
      1,                                                       // nDims
      301,                                                     // lineNo
      18,                                                      // colNo
      "eFirls",                                                // fName
      "/usr/local/MATLAB/R2023b/toolbox/signal/signal/firls.m" // pName
  };
  static rtEqualityCheckInfo d_emlrtECI{
      1,                                                       // nDims
      301,                                                     // lineNo
      13,                                                      // colNo
      "eFirls",                                                // fName
      "/usr/local/MATLAB/R2023b/toolbox/signal/signal/firls.m" // pName
  };
  static rtEqualityCheckInfo emlrtECI{
      1,                                                       // nDims
      299,                                                     // lineNo
      33,                                                      // colNo
      "eFirls",                                                // fName
      "/usr/local/MATLAB/R2023b/toolbox/signal/signal/firls.m" // pName
  };
  static rtRunTimeErrorInfo k_emlrtRTEI{
      159,                                                     // lineNo
      5,                                                       // colNo
      "eFirls",                                                // fName
      "/usr/local/MATLAB/R2023b/toolbox/signal/signal/firls.m" // pName
  };
  static rtRunTimeErrorInfo l_emlrtRTEI{
      59,                  // lineNo
      9,                   // colNo
      "constructErrorObj", // fName
      "/usr/local/MATLAB/R2023b/toolbox/signal/signal/private/firchk.m" // pName
  };
  static rtRunTimeErrorInfo m_emlrtRTEI{
      207,                                                     // lineNo
      5,                                                       // colNo
      "eFirls",                                                // fName
      "/usr/local/MATLAB/R2023b/toolbox/signal/signal/firls.m" // pName
  };
  static rtRunTimeErrorInfo n_emlrtRTEI{
      13,                     // lineNo
      27,                     // colNo
      "assertCompatibleDims", // fName
      "/usr/local/MATLAB/R2023b/toolbox/shared/coder/coder/lib/+coder/"
      "+internal/assertCompatibleDims.m" // pName
  };
  static const signed char A[4]{1, 1, 0, 0};
  array<double, 2U> G;
  array<double, 2U> m;
  array<double, 2U> sinc2A;
  array<double, 2U> sinc3A;
  array<double, 2U> sinc4A;
  array<double, 1U> b_y;
  array<double, 1U> c_y;
  array<double, 1U> k;
  array<double, 1U> y_tmp;
  double i2Map;
  double k2;
  double k3;
  double k4;
  int b_i2;
  unsigned int i1Map;
  boolean_T b_b1;
  if (std::isinf(N) || std::isnan(N)) {
    rtErrorWithMessageID("input number 1, n,", emlrtRTEI.fName,
                         emlrtRTEI.lineNo);
  }
  if (N <= 0.0) {
    b_rtErrorWithMessageID("input number 1, n,", b_emlrtRTEI.fName,
                           b_emlrtRTEI.lineNo);
  }
  validateattributes(freq);
  if ((internal::maximum(freq) > 1.0) || (internal::minimum(freq) < 0.0)) {
    h_rtErrorWithMessageID(k_emlrtRTEI.fName, k_emlrtRTEI.lineNo);
  } else {
    double F[4];
    double L;
    double b0;
    double dF_idx_1;
    int y[2];
    int b_loop_ub;
    int b_s;
    int c_loop_ub;
    int i;
    int i1;
    int i1Start;
    int i2;
    int loop_ub;
    int md2;
    int nG;
    int nx;
    unsigned int tmpStorageLen;
    boolean_T dF[3];
    boolean_T Nodd;
    boolean_T need_matrix;
    if (N != std::round(N)) {
      f_rtErrorWithMessageID(l_emlrtRTEI.fName, l_emlrtRTEI.lineNo);
    }
    N++;
    F[0] = freq[0] / 2.0;
    F[1] = freq[1] / 2.0;
    F[2] = freq[2] / 2.0;
    F[3] = freq[3] / 2.0;
    dF_idx_1 = F[2] - F[1];
    dF[0] = (F[1] < 0.0);
    dF[1] = (dF_idx_1 < 0.0);
    dF[2] = (F[3] - F[2] < 0.0);
    if (any(dF)) {
      g_rtErrorWithMessageID(m_emlrtRTEI.fName, m_emlrtRTEI.lineNo);
    }
    L = (N - 1.0) / 2.0;
    Nodd = (rt_remd_snf(N, 2.0) == 1.0);
    b0 = 0.0;
    if (!Nodd) {
      m.set_size(1, static_cast<int>(L) + 1);
      loop_ub = static_cast<int>(L);
      for (i = 0; i <= loop_ub; i++) {
        m[i] = static_cast<double>(i) + 0.5;
      }
    } else {
      m.set_size(1, static_cast<int>(L) + 1);
      loop_ub = static_cast<int>(L);
      for (i = 0; i <= loop_ub; i++) {
        m[i] = i;
      }
    }
    k.set_size(m.size(1));
    loop_ub = m.size(1);
    for (i = 0; i < loop_ub; i++) {
      k[i] = m[i];
    }
    need_matrix = (dF_idx_1 != 0.0);
    nG = k.size(0);
    if (need_matrix) {
      G.set_size(k.size(0), k.size(0));
      loop_ub = k.size(0) * k.size(0);
      for (i = 0; i < loop_ub; i++) {
        G[i] = 0.0;
      }
      tmpStorageLen = (static_cast<unsigned int>(k.size(0)) << 1) - 1U;
    } else {
      G.set_size(0, 0);
      tmpStorageLen = 0U;
    }
    if (static_cast<double>(tmpStorageLen) != static_cast<int>(tmpStorageLen)) {
      rtIntegerError(static_cast<double>(tmpStorageLen), emlrtDCI);
    }
    m.set_size(1, static_cast<int>(tmpStorageLen));
    sinc2A.set_size(1, static_cast<int>(tmpStorageLen));
    sinc3A.set_size(1, static_cast<int>(tmpStorageLen));
    sinc4A.set_size(1, static_cast<int>(tmpStorageLen));
    if (Nodd) {
      i1Start = -1;
      if (k.size(0) < 2) {
        i = 0;
        i1 = 0;
      } else {
        i = 1;
        i1 = k.size(0);
      }
      y[0] = 1;
      loop_ub = i1 - i;
      y[1] = loop_ub;
      internal::indexShapeCheck(k.size(0), y);
      for (i1 = 0; i1 < loop_ub; i1++) {
        k[i1] = k[i + i1];
      }
      k.set_size(loop_ub);
    } else {
      i1Start = 0;
    }
    a.set_size(k.size(0));
    loop_ub = k.size(0);
    for (i = 0; i < loop_ub; i++) {
      a[i] = 0.0;
    }
    loop_ub = k.size(0);
    b_loop_ub = k.size(0);
    c_loop_ub = k.size(0);
    for (int s{0}; s < 2; s++) {
      double b1;
      double b1_tmp;
      double b_m_s_tmp;
      double d;
      double f1;
      double m_s;
      signed char m_s_tmp;
      boolean_T b;
      b_s = (s << 1) + 1;
      m_s_tmp = A[b_s - 1];
      b_m_s_tmp = F[b_s - 1];
      d = F[b_s];
      dF_idx_1 = d - b_m_s_tmp;
      m_s = static_cast<double>(A[b_s] - m_s_tmp) / dF_idx_1;
      b1_tmp = m_s * b_m_s_tmp;
      b1 = static_cast<double>(m_s_tmp) - b1_tmp;
      if (Nodd) {
        f1 = (static_cast<double>(b_s) + 1.0) / 2.0;
        if (f1 != std::floor(f1)) {
          rtIntegerError(f1, b_emlrtDCI);
        }
        b0 += b1 * dF_idx_1 + m_s / 2.0 * (d * d - b_m_s_tmp * b_m_s_tmp);
      }
      y_tmp.set_size(k.size(0));
      for (i = 0; i < loop_ub; i++) {
        y_tmp[i] = 6.2831853071795862 * k[i];
      }
      c_y.set_size(y_tmp.size(0));
      md2 = y_tmp.size(0);
      for (i = 0; i < md2; i++) {
        c_y[i] = y_tmp[i] * F[b_s];
      }
      nx = c_y.size(0);
      if (c_y.size(0) > 2147483646) {
        check_forloop_overflow_error();
      }
      for (md2 = 0; md2 < nx; md2++) {
        c_y[md2] = std::cos(c_y[md2]);
        y_tmp[md2] = y_tmp[md2] * b_m_s_tmp;
      }
      nx = y_tmp.size(0);
      if (y_tmp.size(0) > 2147483646) {
        check_forloop_overflow_error();
      }
      for (md2 = 0; md2 < nx; md2++) {
        y_tmp[md2] = std::cos(y_tmp[md2]);
      }
      b = ((c_y.size(0) != y_tmp.size(0)) &&
           ((c_y.size(0) != 1) && (y_tmp.size(0) != 1)));
      if (b) {
        emlrtDimSizeImpxCheckR2021b(c_y.size(0), y_tmp.size(0), emlrtECI);
      }
      d = (static_cast<double>(b_s) + 1.0) / 2.0;
      i = static_cast<int>(std::floor(d));
      if (d != i) {
        rtIntegerError(d, c_emlrtDCI);
      }
      f1 = m_s / 39.478417604357432;
      if (c_y.size(0) == y_tmp.size(0)) {
        md2 = c_y.size(0);
        for (i1 = 0; i1 < md2; i1++) {
          c_y[i1] = f1 * (c_y[i1] - y_tmp[i1]);
        }
      } else {
        binary_expand_op_1(c_y, f1, y_tmp);
      }
      b_y.set_size(k.size(0));
      for (i1 = 0; i1 < b_loop_ub; i1++) {
        b_y[i1] = k[i1] * k[i1];
      }
      if ((c_y.size(0) != 1) && (b_y.size(0) != 1) &&
          (c_y.size(0) != b_y.size(0))) {
        e_rtErrorWithMessageID(n_emlrtRTEI.fName, n_emlrtRTEI.lineNo);
      }
      if (c_y.size(0) == b_y.size(0)) {
        md2 = c_y.size(0);
        for (i1 = 0; i1 < md2; i1++) {
          c_y[i1] = c_y[i1] / b_y[i1];
        }
      } else {
        rdivide(c_y, b_y);
      }
      md2 = a.size(0);
      if ((a.size(0) != c_y.size(0)) &&
          ((a.size(0) != 1) && (c_y.size(0) != 1))) {
        emlrtDimSizeImpxCheckR2021b(a.size(0), c_y.size(0), b_emlrtECI);
      }
      if (a.size(0) == c_y.size(0)) {
        for (i1 = 0; i1 < md2; i1++) {
          a[i1] = a[i1] + c_y[i1];
        }
      } else {
        plus(a, c_y);
      }
      y_tmp.set_size(k.size(0));
      for (i1 = 0; i1 < c_loop_ub; i1++) {
        y_tmp[i1] = 2.0 * k[i1];
      }
      f1 = F[b_s];
      f1 *= m_s * f1 + b1;
      b_y.set_size(y_tmp.size(0));
      md2 = y_tmp.size(0);
      for (i1 = 0; i1 < md2; i1++) {
        b_y[i1] = y_tmp[i1] * F[b_s];
      }
      i1 = b_y.size(0);
      for (md2 = 0; md2 < i1; md2++) {
        if (md2 + 1 > b_y.size(0)) {
          rtDynamicBoundsError(md2 + 1, 1, b_y.size(0), emlrtBCI);
        }
        if (std::abs(b_y[md2]) < 1.0020841800044864E-292) {
          if (md2 + 1 > b_y.size(0)) {
            rtDynamicBoundsError(md2 + 1, 1, b_y.size(0), b_emlrtBCI);
          }
          b_y[md2] = 1.0;
        } else {
          if (md2 + 1 > b_y.size(0)) {
            rtDynamicBoundsError(md2 + 1, 1, b_y.size(0), c_emlrtBCI);
          }
          b_y[md2] = 3.1415926535897931 * b_y[md2];
          if (md2 + 1 > b_y.size(0)) {
            rtDynamicBoundsError(md2 + 1, 1, b_y.size(0), d_emlrtBCI);
          }
          b_y[md2] = std::sin(b_y[md2]) / b_y[md2];
        }
      }
      md2 = b_y.size(0);
      dF_idx_1 = b_m_s_tmp * (b1_tmp + b1);
      for (i1 = 0; i1 < md2; i1++) {
        b_y[i1] = f1 * b_y[i1];
        y_tmp[i1] = y_tmp[i1] * b_m_s_tmp;
      }
      i1 = y_tmp.size(0);
      for (md2 = 0; md2 < i1; md2++) {
        if (md2 + 1 > y_tmp.size(0)) {
          rtDynamicBoundsError(md2 + 1, 1, y_tmp.size(0), emlrtBCI);
        }
        if (std::abs(y_tmp[md2]) < 1.0020841800044864E-292) {
          if (md2 + 1 > y_tmp.size(0)) {
            rtDynamicBoundsError(md2 + 1, 1, y_tmp.size(0), b_emlrtBCI);
          }
          y_tmp[md2] = 1.0;
        } else {
          if (md2 + 1 > y_tmp.size(0)) {
            rtDynamicBoundsError(md2 + 1, 1, y_tmp.size(0), c_emlrtBCI);
          }
          y_tmp[md2] = 3.1415926535897931 * y_tmp[md2];
          if (md2 + 1 > y_tmp.size(0)) {
            rtDynamicBoundsError(md2 + 1, 1, y_tmp.size(0), d_emlrtBCI);
          }
          y_tmp[md2] = std::sin(y_tmp[md2]) / y_tmp[md2];
        }
      }
      md2 = y_tmp.size(0);
      for (i1 = 0; i1 < md2; i1++) {
        y_tmp[i1] = dF_idx_1 * y_tmp[i1];
      }
      if (b) {
        emlrtDimSizeImpxCheckR2021b(b_y.size(0), y_tmp.size(0), c_emlrtECI);
      }
      i1 = static_cast<int>(d);
      if (i1 != i) {
        rtIntegerError(d, d_emlrtDCI);
      }
      if (b_y.size(0) == y_tmp.size(0)) {
        md2 = b_y.size(0);
        for (i2 = 0; i2 < md2; i2++) {
          b_y[i2] = b_y[i2] - y_tmp[i2];
        }
      } else {
        minus(b_y, y_tmp);
      }
      md2 = a.size(0);
      if ((a.size(0) != b_y.size(0)) &&
          ((a.size(0) != 1) && (b_y.size(0) != 1))) {
        emlrtDimSizeImpxCheckR2021b(a.size(0), b_y.size(0), d_emlrtECI);
      }
      if (a.size(0) == b_y.size(0)) {
        for (i2 = 0; i2 < md2; i2++) {
          a[i2] = a[i2] + b_y[i2];
        }
      } else {
        plus(a, b_y);
      }
      if (need_matrix) {
        if (i1 != i) {
          rtIntegerError(d, e_emlrtDCI);
        }
        f1 = 2.0 * F[b_s];
        dF_idx_1 = 2.0 * b_m_s_tmp;
        if (static_cast<double>(tmpStorageLen) !=
            static_cast<int>(tmpStorageLen)) {
          rtIntegerError(static_cast<double>(tmpStorageLen), f_emlrtDCI);
        }
        md2 = static_cast<int>(tmpStorageLen) - 1;
#pragma omp parallel for num_threads(omp_get_max_threads()) private(           \
    k4, k3, k2, i2Map, b_i2, i1Map)

        for (int ii = 0; ii <= md2; ii++) {
          i1Map = static_cast<unsigned int>((static_cast<double>(ii) + 1.0) +
                                            static_cast<double>(i1Start));
          b_i2 = static_cast<int>((static_cast<double>(ii) + 1.0) -
                                  static_cast<double>(nG));
          i2Map = f1 * static_cast<double>(i1Map);
          k2 = dF_idx_1 * static_cast<double>(i1Map);
          k3 = f1 * static_cast<double>(b_i2);
          k4 = dF_idx_1 * static_cast<double>(b_i2);
          if (std::abs(i2Map) < 1.0020841800044864E-292) {
            if ((static_cast<int>(static_cast<unsigned int>(ii) + 1U) < 1) ||
                (static_cast<int>(static_cast<unsigned int>(ii) + 1U) >
                 m.size(1))) {
              rtDynamicBoundsError(
                  static_cast<int>(static_cast<unsigned int>(ii) + 1U), 1,
                  m.size(1), e_emlrtBCI);
            }
            m[ii] = 1.0;
          } else {
            i2Map *= 3.1415926535897931;
            if ((static_cast<int>(static_cast<unsigned int>(ii) + 1U) < 1) ||
                (static_cast<int>(static_cast<unsigned int>(ii) + 1U) >
                 m.size(1))) {
              rtDynamicBoundsError(
                  static_cast<int>(static_cast<unsigned int>(ii) + 1U), 1,
                  m.size(1), e_emlrtBCI);
            }
            m[ii] = std::sin(i2Map) / i2Map;
          }
          if (std::abs(k2) < 1.0020841800044864E-292) {
            if ((static_cast<int>(static_cast<unsigned int>(ii) + 1U) < 1) ||
                (static_cast<int>(static_cast<unsigned int>(ii) + 1U) >
                 sinc2A.size(1))) {
              rtDynamicBoundsError(
                  static_cast<int>(static_cast<unsigned int>(ii) + 1U), 1,
                  sinc2A.size(1), f_emlrtBCI);
            }
            sinc2A[ii] = 1.0;
          } else {
            i2Map = 3.1415926535897931 * k2;
            if ((static_cast<int>(static_cast<unsigned int>(ii) + 1U) < 1) ||
                (static_cast<int>(static_cast<unsigned int>(ii) + 1U) >
                 sinc2A.size(1))) {
              rtDynamicBoundsError(
                  static_cast<int>(static_cast<unsigned int>(ii) + 1U), 1,
                  sinc2A.size(1), f_emlrtBCI);
            }
            sinc2A[ii] = std::sin(i2Map) / i2Map;
          }
          if (std::abs(k3) < 1.0020841800044864E-292) {
            if ((static_cast<int>(static_cast<unsigned int>(ii) + 1U) < 1) ||
                (static_cast<int>(static_cast<unsigned int>(ii) + 1U) >
                 sinc3A.size(1))) {
              rtDynamicBoundsError(
                  static_cast<int>(static_cast<unsigned int>(ii) + 1U), 1,
                  sinc3A.size(1), g_emlrtBCI);
            }
            sinc3A[ii] = 1.0;
          } else {
            i2Map = 3.1415926535897931 * k3;
            if ((static_cast<int>(static_cast<unsigned int>(ii) + 1U) < 1) ||
                (static_cast<int>(static_cast<unsigned int>(ii) + 1U) >
                 sinc3A.size(1))) {
              rtDynamicBoundsError(
                  static_cast<int>(static_cast<unsigned int>(ii) + 1U), 1,
                  sinc3A.size(1), g_emlrtBCI);
            }
            sinc3A[ii] = std::sin(i2Map) / i2Map;
          }
          if (std::abs(k4) < 1.0020841800044864E-292) {
            if ((static_cast<int>(static_cast<unsigned int>(ii) + 1U) < 1) ||
                (static_cast<int>(static_cast<unsigned int>(ii) + 1U) >
                 sinc4A.size(1))) {
              rtDynamicBoundsError(
                  static_cast<int>(static_cast<unsigned int>(ii) + 1U), 1,
                  sinc4A.size(1), h_emlrtBCI);
            }
            sinc4A[ii] = 1.0;
          } else {
            i2Map = 3.1415926535897931 * k4;
            if ((static_cast<int>(static_cast<unsigned int>(ii) + 1U) < 1) ||
                (static_cast<int>(static_cast<unsigned int>(ii) + 1U) >
                 sinc4A.size(1))) {
              rtDynamicBoundsError(
                  static_cast<int>(static_cast<unsigned int>(ii) + 1U), 1,
                  sinc4A.size(1), h_emlrtBCI);
            }
            sinc4A[ii] = std::sin(i2Map) / i2Map;
          }
        }
        md2 = nG - 1;
#pragma omp parallel for num_threads(omp_get_max_threads()) private(           \
    i2Map, i1Map, b_i2, b_b1)

        for (int ii = 0; ii <= md2; ii++) {
          for (b_i2 = 0; b_i2 < nG; b_i2++) {
            i1Map = (static_cast<unsigned int>(b_i2) +
                     static_cast<unsigned int>(ii)) +
                    1U;
            i2Map = static_cast<double>(b_i2 - ii) + static_cast<double>(nG);
            if (b_i2 + 1 > G.size(0)) {
              rtDynamicBoundsError(b_i2 + 1, 1, G.size(0), i_emlrtBCI);
            }
            if (ii + 1 > G.size(1)) {
              rtDynamicBoundsError(ii + 1, 1, G.size(1), j_emlrtBCI);
            }
            b_b1 = ((static_cast<int>(i1Map) < 1) ||
                    (static_cast<int>(i1Map) > m.size(1)));
            if (b_b1) {
              rtDynamicBoundsError(static_cast<int>(i1Map), 1, m.size(1),
                                   k_emlrtBCI);
            }
            b_b1 = ((static_cast<int>(i2Map) < 1) ||
                    (static_cast<int>(i2Map) > sinc3A.size(1)));
            if (b_b1) {
              rtDynamicBoundsError(static_cast<int>(i2Map), 1, sinc3A.size(1),
                                   l_emlrtBCI);
            }
            if (b_i2 + 1 > G.size(0)) {
              rtDynamicBoundsError(b_i2 + 1, 1, G.size(0), m_emlrtBCI);
            }
            if (ii + 1 > G.size(1)) {
              rtDynamicBoundsError(ii + 1, 1, G.size(1), n_emlrtBCI);
            }
            G[b_i2 + G.size(0) * ii] =
                G[b_i2 + G.size(0) * ii] +
                0.25 * (f1 * (m[static_cast<int>(i1Map) - 1] +
                              sinc3A[static_cast<int>(i2Map) - 1]) -
                        dF_idx_1 * (sinc2A[static_cast<int>(i1Map) - 1] +
                                    sinc4A[static_cast<int>(i2Map) - 1]));
          }
        }
      }
    }
    if (Nodd) {
      k.set_size(a.size(0) + 1);
      k[0] = b0;
      loop_ub = a.size(0);
      for (i = 0; i < loop_ub; i++) {
        k[i + 1] = a[i];
      }
      a.set_size(k.size(0));
      loop_ub = k.size(0);
      for (i = 0; i < loop_ub; i++) {
        a[i] = k[i];
      }
    }
    if (need_matrix) {
      mldivide(G, a);
    } else {
      loop_ub = a.size(0);
      for (i = 0; i < loop_ub; i++) {
        a[i] = 4.0 * a[i];
      }
      if (Nodd) {
        if (a.size(0) < 1) {
          rtDynamicBoundsError(1, 1, a.size(0), t_emlrtBCI);
        }
        a[0] = a[0] / 2.0;
      }
    }
    if (Nodd) {
      if (L + 1.0 < 2.0) {
        i = 0;
        i1 = 1;
        i2 = -1;
      } else {
        if (L + 1.0 != static_cast<int>(std::floor(L + 1.0))) {
          rtIntegerError(L + 1.0, h_emlrtDCI);
        }
        if ((static_cast<int>(L + 1.0) < 1) ||
            (static_cast<int>(L + 1.0) > a.size(0))) {
          rtDynamicBoundsError(static_cast<int>(L + 1.0), 1, a.size(0),
                               r_emlrtBCI);
        }
        i = static_cast<int>(L + 1.0) - 1;
        i1 = -1;
        if (a.size(0) < 2) {
          rtDynamicBoundsError(2, 1, a.size(0), s_emlrtBCI);
        }
        i2 = 1;
      }
      y[0] = 1;
      loop_ub = div_s32(i2 - i, i1);
      y[1] = loop_ub + 1;
      internal::indexShapeCheck(a.size(0), y);
      if (L + 1.0 < 2.0) {
        i2 = 0;
        md2 = 0;
      } else {
        if (a.size(0) < 2) {
          rtDynamicBoundsError(2, 1, a.size(0), p_emlrtBCI);
        }
        i2 = 1;
        if (L + 1.0 != static_cast<int>(std::floor(L + 1.0))) {
          rtIntegerError(L + 1.0, g_emlrtDCI);
        }
        if ((static_cast<int>(L + 1.0) < 1) ||
            (static_cast<int>(L + 1.0) > a.size(0))) {
          rtDynamicBoundsError(static_cast<int>(L + 1.0), 1, a.size(0),
                               q_emlrtBCI);
        }
        md2 = static_cast<int>(L + 1.0);
      }
      y[0] = 1;
      nx = md2 - i2;
      y[1] = nx;
      internal::indexShapeCheck(a.size(0), y);
      if (a.size(0) < 1) {
        rtDynamicBoundsError(1, 1, a.size(0), o_emlrtBCI);
      }
      h.set_size(1, ((loop_ub + md2) - i2) + 2);
      for (md2 = 0; md2 <= loop_ub; md2++) {
        h[md2] = a[i + i1 * md2] / 2.0;
      }
      h[loop_ub + 1] = a[0];
      for (i = 0; i < nx; i++) {
        h[(i + loop_ub) + 2] = a[i2 + i] / 2.0;
      }
    } else {
      b_y.set_size(a.size(0));
      loop_ub = a.size(0);
      for (i = 0; i < loop_ub; i++) {
        b_y[i] = a[i];
      }
      nx = a.size(0) - 1;
      md2 = a.size(0) >> 1;
      for (b_s = 0; b_s < md2; b_s++) {
        dF_idx_1 = b_y[b_s];
        loop_ub = nx - b_s;
        b_y[b_s] = b_y[loop_ub];
        b_y[loop_ub] = dF_idx_1;
      }
      h.set_size(1, b_y.size(0) + a.size(0));
      loop_ub = b_y.size(0);
      for (i = 0; i < loop_ub; i++) {
        h[i] = 0.5 * b_y[i];
      }
      loop_ub = a.size(0);
      for (i = 0; i < loop_ub; i++) {
        h[i + b_y.size(0)] = 0.5 * a[i];
      }
    }
    a.set_size(1);
    a[0] = 1.0;
  }
}

} // namespace coder

// End of code generation (firls.cpp)
