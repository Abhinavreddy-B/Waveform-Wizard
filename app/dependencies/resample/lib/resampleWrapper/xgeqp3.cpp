//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// xgeqp3.cpp
//
// Code generation for function 'xgeqp3'
//

// Include files
#include "xgeqp3.h"
#include "eml_int_forloop_overflow_check.h"
#include "resampleWrapper_rtwutil.h"
#include "rt_nonfinite.h"
#include "xnrm2.h"
#include "xzlarf.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
namespace coder {
namespace internal {
namespace lapack {
void xgeqp3(array<double, 2U> &A, array<double, 1U> &tau, array<int, 2U> &jpvt)
{
  array<double, 1U> vn1;
  array<double, 1U> vn2;
  array<double, 1U> work;
  int i;
  int ix;
  int m;
  int n;
  int u1;
  m = A.size(0);
  n = A.size(1);
  ix = A.size(0);
  u1 = A.size(1);
  if (ix <= u1) {
    u1 = ix;
  }
  tau.set_size(u1);
  for (i = 0; i < u1; i++) {
    tau[i] = 0.0;
  }
  if ((A.size(0) == 0) || (A.size(1) == 0) || (u1 < 1)) {
    jpvt.set_size(1, A.size(1));
    ix = A.size(1);
    for (i = 0; i < ix; i++) {
      jpvt[i] = 0;
    }
    if (A.size(1) > 2147483646) {
      check_forloop_overflow_error();
    }
    for (int j{0}; j < n; j++) {
      jpvt[j] = j + 1;
    }
  } else {
    double smax;
    int j;
    int ma;
    jpvt.set_size(1, A.size(1));
    ix = A.size(1);
    for (i = 0; i < ix; i++) {
      jpvt[i] = 0;
    }
    if (A.size(1) > 2147483646) {
      check_forloop_overflow_error();
    }
    ma = A.size(0);
    work.set_size(A.size(1));
    vn1.set_size(A.size(1));
    vn2.set_size(A.size(1));
    for (int k{0}; k < n; k++) {
      jpvt[k] = k + 1;
      work[k] = 0.0;
      vn1[k] = 0.0;
      vn2[k] = 0.0;
    }
    if (A.size(1) > 2147483646) {
      check_forloop_overflow_error();
    }
    for (j = 0; j < n; j++) {
      smax = blas::xnrm2(m, A, j * ma + 1);
      vn1[j] = smax;
      vn2[j] = smax;
    }
    if (u1 > 2147483646) {
      check_forloop_overflow_error();
    }
    for (int b_i{0}; b_i < u1; b_i++) {
      double s;
      double temp2;
      int ii;
      int ii_tmp;
      int ip1;
      int mmi;
      int nmi;
      int pvt;
      ip1 = b_i + 2;
      ii_tmp = b_i * ma;
      ii = ii_tmp + b_i;
      nmi = n - b_i;
      mmi = m - b_i;
      if (nmi < 1) {
        ix = -1;
      } else {
        ix = 0;
        if (nmi > 1) {
          smax = std::abs(vn1[b_i]);
          if (nmi > 2147483646) {
            check_forloop_overflow_error();
          }
          for (int k{2}; k <= nmi; k++) {
            s = std::abs(vn1[(b_i + k) - 1]);
            if (s > smax) {
              ix = k - 1;
              smax = s;
            }
          }
        }
      }
      pvt = b_i + ix;
      if (pvt + 1 != b_i + 1) {
        ix = pvt * ma;
        if (m > 2147483646) {
          check_forloop_overflow_error();
        }
        for (int k{0}; k < m; k++) {
          j = ix + k;
          smax = A[j];
          i = ii_tmp + k;
          A[j] = A[i];
          A[i] = smax;
        }
        ix = jpvt[pvt];
        jpvt[pvt] = jpvt[b_i];
        jpvt[b_i] = ix;
        vn1[pvt] = vn1[b_i];
        vn2[pvt] = vn2[b_i];
      }
      if (b_i + 1 < m) {
        temp2 = A[ii];
        ii_tmp = ii + 2;
        tau[b_i] = 0.0;
        if (mmi > 0) {
          smax = blas::xnrm2(mmi - 1, A, ii + 2);
          if (smax != 0.0) {
            s = rt_hypotd_snf(A[ii], smax);
            if (A[ii] >= 0.0) {
              s = -s;
            }
            if (std::abs(s) < 1.0020841800044864E-292) {
              boolean_T overflow_tmp;
              ix = 0;
              j = ii + mmi;
              overflow_tmp = ((ii + 2 <= j) && (j > 2147483646));
              do {
                ix++;
                if (overflow_tmp) {
                  check_forloop_overflow_error();
                }
                for (int k{ii_tmp}; k <= j; k++) {
                  A[k - 1] = 9.9792015476736E+291 * A[k - 1];
                }
                s *= 9.9792015476736E+291;
                temp2 *= 9.9792015476736E+291;
              } while ((std::abs(s) < 1.0020841800044864E-292) && (ix < 20));
              smax = blas::xnrm2(mmi - 1, A, ii + 2);
              s = rt_hypotd_snf(temp2, smax);
              if (temp2 >= 0.0) {
                s = -s;
              }
              tau[b_i] = (s - temp2) / s;
              smax = 1.0 / (temp2 - s);
              for (int k{ii_tmp}; k <= j; k++) {
                A[k - 1] = smax * A[k - 1];
              }
              for (int k{0}; k < ix; k++) {
                s *= 1.0020841800044864E-292;
              }
              temp2 = s;
            } else {
              tau[b_i] = (s - A[ii]) / s;
              smax = 1.0 / (A[ii] - s);
              ix = ii + mmi;
              if ((ii + 2 <= ix) && (ix > 2147483646)) {
                check_forloop_overflow_error();
              }
              for (int k{ii_tmp}; k <= ix; k++) {
                A[k - 1] = smax * A[k - 1];
              }
              temp2 = s;
            }
          }
        }
        A[ii] = temp2;
      } else {
        tau[b_i] = 0.0;
      }
      if (b_i + 1 < n) {
        temp2 = A[ii];
        A[ii] = 1.0;
        reflapack::xzlarf(mmi, nmi - 1, ii + 1, tau[b_i], A, (ii + ma) + 1, ma,
                          work);
        A[ii] = temp2;
      }
      if ((b_i + 2 <= n) && (n > 2147483646)) {
        check_forloop_overflow_error();
      }
      for (j = ip1; j <= n; j++) {
        ix = b_i + (j - 1) * ma;
        smax = vn1[j - 1];
        if (smax != 0.0) {
          s = std::abs(A[ix]) / smax;
          s = 1.0 - s * s;
          if (s < 0.0) {
            s = 0.0;
          }
          temp2 = smax / vn2[j - 1];
          temp2 = s * (temp2 * temp2);
          if (temp2 <= 1.4901161193847656E-8) {
            if (b_i + 1 < m) {
              smax = blas::xnrm2(mmi - 1, A, ix + 2);
              vn1[j - 1] = smax;
              vn2[j - 1] = smax;
            } else {
              vn1[j - 1] = 0.0;
              vn2[j - 1] = 0.0;
            }
          } else {
            vn1[j - 1] = smax * std::sqrt(s);
          }
        }
      }
    }
  }
}

} // namespace lapack
} // namespace internal
} // namespace coder

// End of code generation (xgeqp3.cpp)
