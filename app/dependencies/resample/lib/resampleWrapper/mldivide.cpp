//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// mldivide.cpp
//
// Code generation for function 'mldivide'
//

// Include files
#include "mldivide.h"
#include "eml_int_forloop_overflow_check.h"
#include "resampleWrapper_types.h"
#include "rt_nonfinite.h"
#include "xgeqp3.h"
#include "coder_array.h"
#include "omp.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <string>

// Function Declarations
static void m_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void n_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

// Function Definitions
static void m_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream
      << "The call site of the LAPACK routine xGETRS requires unimplemented "
         "functionality of the reference implementation. It currently on"
         "ly supports trans=\'N\', ia0=1, lda=size(A,1), ib0=1, and "
         "ldb=size(B,1).";
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

static void n_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::string errMsg;
  std::stringstream outStream;
  outStream << "Matrix dimensions must agree.";
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
void mldivide(const array<double, 2U> &A, array<double, 1U> &B)
{
  static rtRunTimeErrorInfo k_emlrtRTEI{
      16,                                                              // lineNo
      19,                                                              // colNo
      "mldivide",                                                      // fName
      "/usr/local/MATLAB/R2023b/toolbox/eml/lib/matlab/ops/mldivide.m" // pName
  };
  static rtRunTimeErrorInfo l_emlrtRTEI{
      12,        // lineNo
      23,        // colNo
      "xzgetrs", // fName
      "/usr/local/MATLAB/R2023b/toolbox/eml/eml/+coder/+internal/+reflapack/"
      "xzgetrs.m" // pName
  };
  array<double, 2U> b_A;
  array<double, 1U> b_B;
  array<double, 1U> tau;
  array<int, 2U> jpvt;
  if (B.size(0) != A.size(0)) {
    n_rtErrorWithMessageID(k_emlrtRTEI.fName, k_emlrtRTEI.lineNo);
  }
  if ((A.size(0) == 0) || (A.size(1) == 0) || (B.size(0) == 0)) {
    int minmn;
    B.set_size(A.size(1));
    minmn = A.size(1);
    for (int ijA{0}; ijA < minmn; ijA++) {
      B[ijA] = 0.0;
    }
  } else if (A.size(0) == A.size(1)) {
    double tol;
    int LDA;
    int ijA;
    int maxmn;
    int minmn;
    int n;
    int u0;
    u0 = A.size(0);
    n = A.size(1);
    if (u0 <= n) {
      n = u0;
    }
    u0 = B.size(0);
    if (u0 <= n) {
      n = u0;
    }
    LDA = A.size(0);
    b_A.set_size(A.size(0), A.size(1));
    minmn = A.size(0) * A.size(1);
    for (ijA = 0; ijA < minmn; ijA++) {
      b_A[ijA] = A[ijA];
    }
    jpvt.set_size(1, n);
    if (n > 0) {
      jpvt[0] = 1;
      minmn = 1;
      if (n > 2147483646) {
        check_forloop_overflow_error();
      }
      for (int k{2}; k <= n; k++) {
        minmn++;
        jpvt[k - 1] = minmn;
      }
    }
    if (n >= 1) {
      int ldap1;
      ldap1 = A.size(0) + 1;
      u0 = n - 1;
      if (u0 > n) {
        u0 = n;
      }
      for (int j{0}; j < u0; j++) {
        int b_tmp;
        int mmj_tmp;
        int mn;
        int rankA;
        mmj_tmp = n - j;
        b_tmp = j * (LDA + 1);
        rankA = b_tmp + 2;
        if (mmj_tmp < 1) {
          maxmn = -1;
        } else {
          maxmn = 0;
          if (mmj_tmp > 1) {
            tol = std::abs(b_A[b_tmp]);
            for (int k{2}; k <= mmj_tmp; k++) {
              double s;
              s = std::abs(b_A[(b_tmp + k) - 1]);
              if (s > tol) {
                maxmn = k - 1;
                tol = s;
              }
            }
          }
        }
        if (b_A[b_tmp + maxmn] != 0.0) {
          if (maxmn != 0) {
            maxmn += j;
            jpvt[j] = maxmn + 1;
            for (int k{0}; k < n; k++) {
              minmn = k * LDA;
              mn = j + minmn;
              tol = b_A[mn];
              ijA = maxmn + minmn;
              b_A[mn] = b_A[ijA];
              b_A[ijA] = tol;
            }
          }
          mn = b_tmp + mmj_tmp;
          if ((b_tmp + 2 <= mn) && (mn > 2147483646)) {
            check_forloop_overflow_error();
          }
          for (int i{rankA}; i <= mn; i++) {
            b_A[i - 1] = b_A[i - 1] / b_A[b_tmp];
          }
        }
        minmn = b_tmp + LDA;
        maxmn = (b_tmp + ldap1) + 1;
        for (rankA = 0; rankA <= mmj_tmp - 2; rankA++) {
          tol = b_A[minmn + rankA * LDA];
          if (tol != 0.0) {
            mn = (mmj_tmp + maxmn) - 2;
            if ((maxmn <= mn) && (mn > 2147483646)) {
              check_forloop_overflow_error();
            }
            for (ijA = maxmn; ijA <= mn; ijA++) {
              b_A[ijA - 1] =
                  b_A[ijA - 1] + b_A[((b_tmp + ijA) - maxmn) + 1] * -tol;
            }
          }
          maxmn += LDA;
        }
      }
    }
    if (A.size(0) != b_A.size(0)) {
      m_rtErrorWithMessageID(l_emlrtRTEI.fName, l_emlrtRTEI.lineNo);
    }
    LDA = b_A.size(0);
    for (int i{0}; i <= n - 2; i++) {
      ijA = jpvt[i];
      if (ijA != i + 1) {
        tol = B[i];
        B[i] = B[ijA - 1];
        B[ijA - 1] = tol;
      }
    }
    for (int k{0}; k < n; k++) {
      minmn = LDA * k;
      if (B[k] != 0.0) {
        maxmn = k + 2;
        for (int i{maxmn}; i <= n; i++) {
          B[i - 1] = B[i - 1] - B[k] * b_A[(i + minmn) - 1];
        }
      }
    }
    for (int k{n}; k >= 1; k--) {
      minmn = LDA * (k - 1);
      tol = B[k - 1];
      if (tol != 0.0) {
        tol /= b_A[(k + minmn) - 1];
        B[k - 1] = tol;
        for (int i{0}; i <= k - 2; i++) {
          B[i] = B[i] - B[k - 1] * b_A[i + minmn];
        }
      }
    }
  } else {
    double tol;
    int ijA;
    int maxmn;
    int minmn;
    int mn;
    int rankA;
    int u0;
    b_A.set_size(A.size(0), A.size(1));
    minmn = A.size(0) * A.size(1);
    for (ijA = 0; ijA < minmn; ijA++) {
      b_A[ijA] = A[ijA];
    }
    internal::lapack::xgeqp3(b_A, tau, jpvt);
    rankA = 0;
    if (b_A.size(0) < b_A.size(1)) {
      minmn = b_A.size(0);
      maxmn = b_A.size(1);
    } else {
      minmn = b_A.size(1);
      maxmn = b_A.size(0);
    }
    if (minmn > 0) {
      tol = std::fmin(1.4901161193847656E-8,
                      2.2204460492503131E-15 * static_cast<double>(maxmn)) *
            std::abs(b_A[0]);
      while ((rankA < minmn) &&
             (!(std::abs(b_A[rankA + b_A.size(0) * rankA]) <= tol))) {
        rankA++;
      }
    }
    b_B.set_size(B.size(0));
    minmn = B.size(0);
    for (ijA = 0; ijA < minmn; ijA++) {
      b_B[ijA] = B[ijA];
    }
    B.set_size(b_A.size(1));
    minmn = b_A.size(1);
    for (ijA = 0; ijA < minmn; ijA++) {
      B[ijA] = 0.0;
    }
    maxmn = b_A.size(0);
    u0 = b_A.size(0);
    mn = b_A.size(1);
    if (u0 <= mn) {
      mn = u0;
    }
    if (mn > 2147483646) {
      check_forloop_overflow_error();
    }
    for (int j{0}; j < mn; j++) {
      if (tau[j] != 0.0) {
        tol = b_B[j];
        minmn = j + 2;
        if ((j + 2 <= maxmn) && (maxmn > 2147483646)) {
          check_forloop_overflow_error();
        }
        for (int i{minmn}; i <= maxmn; i++) {
          tol += b_A[(i + b_A.size(0) * j) - 1] * b_B[i - 1];
        }
        tol *= tau[j];
        if (tol != 0.0) {
          b_B[j] = b_B[j] - tol;
          for (int i{minmn}; i <= maxmn; i++) {
            b_B[i - 1] = b_B[i - 1] - b_A[(i + b_A.size(0) * j) - 1] * tol;
          }
        }
      }
    }
    if (rankA > 2147483646) {
      check_forloop_overflow_error();
    }
    for (int i{0}; i < rankA; i++) {
      B[jpvt[i] - 1] = b_B[i];
    }
    for (int j{rankA}; j >= 1; j--) {
      ijA = jpvt[j - 1];
      B[ijA - 1] = B[ijA - 1] / b_A[(j + b_A.size(0) * (j - 1)) - 1];
      for (int i{0}; i <= j - 2; i++) {
        B[jpvt[i] - 1] =
            B[jpvt[i] - 1] - B[ijA - 1] * b_A[i + b_A.size(0) * (j - 1)];
      }
    }
  }
}

} // namespace coder

// End of code generation (mldivide.cpp)
