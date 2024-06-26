//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// cmlri.cpp
//
// Code generation for function 'cmlri'
//

// Include files
#include "cmlri.h"
#include "eml_int_forloop_overflow_check.h"
#include "gammaln.h"
#include "resampleWrapper_data.h"
#include "resampleWrapper_rtwutil.h"
#include "resampleWrapper_types.h"
#include "rt_nonfinite.h"
#include "rt_defines.h"
#include <cmath>

// Function Declarations
static double rt_atan2d_snf(double u0, double u1);

// Function Definitions
static double rt_atan2d_snf(double u0, double u1)
{
  double y;
  if (std::isnan(u0) || std::isnan(u1)) {
    y = rtNaN;
  } else if (std::isinf(u0) && std::isinf(u1)) {
    int i;
    int i1;
    if (u0 > 0.0) {
      i = 1;
    } else {
      i = -1;
    }
    if (u1 > 0.0) {
      i1 = 1;
    } else {
      i1 = -1;
    }
    y = std::atan2(static_cast<double>(i), static_cast<double>(i1));
  } else if (u1 == 0.0) {
    if (u0 > 0.0) {
      y = RT_PI / 2.0;
    } else if (u0 < 0.0) {
      y = -(RT_PI / 2.0);
    } else {
      y = 0.0;
    }
  } else {
    y = std::atan2(u0, u1);
  }
  return y;
}

namespace coder {
int cmlri(const creal_T z, creal_T &y)
{
  double ack;
  double ak;
  double ap;
  double az;
  double bk;
  double ck_im;
  double ck_re;
  double flooraz;
  double p1_im;
  double p1_re;
  double p2_im;
  double p2_re;
  double pt_im;
  double pt_re;
  double rho2;
  double rz_im;
  double rz_re;
  double tst;
  int i;
  int icounter;
  int nz;
  boolean_T earlyExit;
  boolean_T exitg1;
  nz = 0;
  az = rt_hypotd_snf(z.re, z.im);
  flooraz = std::floor(az);
  if (z.im == 0.0) {
    ck_re = (flooraz + 1.0) / z.re;
    ck_im = 0.0;
    rz_re = 2.0 / z.re;
    rz_im = 0.0;
  } else if (z.re == 0.0) {
    ck_re = 0.0;
    ck_im = -((flooraz + 1.0) / z.im);
    rz_re = 0.0;
    rz_im = -(2.0 / z.im);
  } else {
    ack = std::abs(z.re);
    rho2 = std::abs(z.im);
    if (ack > rho2) {
      tst = z.im / z.re;
      bk = z.re + tst * z.im;
      ck_re = ((flooraz + 1.0) + tst * 0.0) / bk;
      ck_im = (0.0 - tst * (flooraz + 1.0)) / bk;
      tst = z.im / z.re;
      bk = z.re + tst * z.im;
      rz_re = (tst * 0.0 + 2.0) / bk;
      rz_im = (0.0 - tst * 2.0) / bk;
    } else {
      if (rho2 == ack) {
        if (z.re > 0.0) {
          bk = 0.5;
        } else {
          bk = -0.5;
        }
        if (z.im > 0.0) {
          ap = 0.5;
        } else {
          ap = -0.5;
        }
        ck_re = ((flooraz + 1.0) * bk + 0.0 * ap) / ack;
        ck_im = (0.0 * bk - (flooraz + 1.0) * ap) / ack;
      } else {
        tst = z.re / z.im;
        bk = z.im + tst * z.re;
        ck_re = tst * (flooraz + 1.0) / bk;
        ck_im = (tst * 0.0 - (flooraz + 1.0)) / bk;
      }
      if (rho2 == ack) {
        if (z.re > 0.0) {
          bk = 0.5;
        } else {
          bk = -0.5;
        }
        if (z.im > 0.0) {
          ap = 0.5;
        } else {
          ap = -0.5;
        }
        rz_re = (2.0 * bk + 0.0 * ap) / ack;
        rz_im = (0.0 * bk - 2.0 * ap) / ack;
      } else {
        tst = z.re / z.im;
        bk = z.im + tst * z.re;
        rz_re = tst * 2.0 / bk;
        rz_im = (tst * 0.0 - 2.0) / bk;
      }
    }
  }
  p1_re = 0.0;
  p1_im = 0.0;
  p2_re = 1.0;
  p2_im = 0.0;
  ack = ((flooraz + 1.0) + 1.0) / az;
  rho2 = ack * ack - 1.0;
  if (rho2 < 0.0) {
    e_rtErrorWithMessageID("sqrt", j_emlrtRTEI.fName, j_emlrtRTEI.lineNo);
  }
  rho2 = std::sqrt(rho2);
  ack += rho2;
  rho2 = ack * ack;
  tst = (rho2 + rho2) / ((rho2 - 1.0) * (ack - 1.0)) / 2.2204460492503131E-16;
  ak = flooraz + 1.0;
  earlyExit = true;
  icounter = 1;
  i = 0;
  exitg1 = false;
  while ((!exitg1) && (i < 80)) {
    icounter++;
    pt_re = p2_re;
    pt_im = p2_im;
    ack = ck_re * p2_re - ck_im * p2_im;
    rho2 = ck_re * p2_im + ck_im * p2_re;
    p2_re = p1_re - ack;
    p2_im = p1_im - rho2;
    p1_re = pt_re;
    p1_im = pt_im;
    ck_re += rz_re;
    ck_im += rz_im;
    if (rt_hypotd_snf(p2_re, p2_im) > tst * ak * ak) {
      earlyExit = false;
      exitg1 = true;
    } else {
      ak++;
      i++;
    }
  }
  if (earlyExit) {
    nz = -2;
  } else {
    int kcounter;
    boolean_T guard1;
    kcounter = 1;
    guard1 = false;
    if (static_cast<int>(flooraz) <= 0) {
      int itime;
      p1_re = 0.0;
      p1_im = 0.0;
      p2_re = 1.0;
      p2_im = 0.0;
      if (z.im == 0.0) {
        ck_re = 1.0 / z.re;
        ck_im = 0.0;
      } else if (z.re == 0.0) {
        ck_re = 0.0;
        ck_im = -(1.0 / z.im);
      } else {
        tst = std::abs(z.re);
        rho2 = std::abs(z.im);
        if (tst > rho2) {
          tst = z.im / z.re;
          bk = z.re + tst * z.im;
          ck_re = (tst * 0.0 + 1.0) / bk;
          ck_im = (0.0 - tst) / bk;
        } else if (rho2 == tst) {
          if (z.re > 0.0) {
            bk = 0.5;
          } else {
            bk = -0.5;
          }
          if (z.im > 0.0) {
            ap = 0.5;
          } else {
            ap = -0.5;
          }
          ck_re = (bk + 0.0 * ap) / tst;
          ck_im = (0.0 * bk - ap) / tst;
        } else {
          tst = z.re / z.im;
          bk = z.im + tst * z.re;
          ck_re = tst / bk;
          ck_im = (tst * 0.0 - 1.0) / bk;
        }
      }
      tst = std::sqrt(1.0 / az / 2.2204460492503131E-16);
      itime = 1;
      earlyExit = true;
      i = 0;
      exitg1 = false;
      while ((!exitg1) && (i < 80)) {
        kcounter++;
        pt_re = p2_re;
        pt_im = p2_im;
        ack = ck_re * p2_re - ck_im * p2_im;
        rho2 = ck_re * p2_im + ck_im * p2_re;
        p2_re = p1_re - ack;
        p2_im = p1_im - rho2;
        p1_re = pt_re;
        p1_im = pt_im;
        ck_re += rz_re;
        ck_im += rz_im;
        ap = rt_hypotd_snf(p2_re, p2_im);
        if (ap >= tst * ak * ak) {
          if (itime == 2) {
            earlyExit = false;
            exitg1 = true;
          } else {
            ack = rt_hypotd_snf(ck_re, ck_im);
            rho2 = ack * ack - 1.0;
            if (rho2 < 0.0) {
              e_rtErrorWithMessageID("sqrt", j_emlrtRTEI.fName,
                                     j_emlrtRTEI.lineNo);
            }
            rho2 = std::sqrt(rho2);
            ack = std::fmin(ack + rho2, ap / rt_hypotd_snf(pt_re, pt_im));
            rho2 = ack / (ack * ack - 1.0);
            if (rho2 < 0.0) {
              e_rtErrorWithMessageID("sqrt", j_emlrtRTEI.fName,
                                     j_emlrtRTEI.lineNo);
            }
            rho2 = std::sqrt(rho2);
            tst *= rho2;
            itime = 2;
            i++;
          }
        } else {
          i++;
        }
      }
      if (earlyExit) {
        nz = -2;
      } else {
        guard1 = true;
      }
    } else {
      guard1 = true;
    }
    if (guard1) {
      icounter += static_cast<int>(flooraz);
      if (icounter >= kcounter) {
        kcounter = icounter;
      }
      ap = kcounter;
      p1_re = 0.0;
      p1_im = 0.0;
      p2_re = 1.0020841800044864E-289;
      p2_im = 0.0;
      rho2 = static_cast<double>(kcounter) + 1.0;
      gammaln(rho2);
      ack = static_cast<double>(kcounter) + 1.0;
      gammaln(ack);
      tst = 1.0;
      gammaln(tst);
      bk = std::exp((rho2 - ack) - tst);
      ak = 0.0;
      az = 0.0;
      if (kcounter > 2147483646) {
        check_forloop_overflow_error();
      }
      for (i = 0; i < kcounter; i++) {
        pt_re = p2_re;
        pt_im = p2_im;
        rho2 = ap * rz_re;
        ack = ap * rz_im;
        tst = rho2 * p2_re - ack * p2_im;
        ack = rho2 * p2_im + ack * p2_re;
        p2_re = p1_re + tst;
        p2_im = p1_im + ack;
        p1_re = pt_re;
        p1_im = pt_im;
        ack = bk * (1.0 - 0.0 / ap);
        tst = ack + bk;
        ak += tst * pt_re;
        az += tst * pt_im;
        bk = ack;
        ap--;
      }
      y.re = p2_re;
      y.im = p2_im;
      if (rz_im == 0.0) {
        if (rz_re < 0.0) {
          ck_re = std::log(std::abs(rz_re));
          ck_im = 3.1415926535897931;
        } else {
          ck_re = std::log(rz_re);
          ck_im = 0.0;
        }
      } else if ((std::abs(rz_re) > 8.9884656743115785E+307) ||
                 (std::abs(rz_im) > 8.9884656743115785E+307)) {
        ck_re = std::log(rt_hypotd_snf(rz_re / 2.0, rz_im / 2.0)) +
                0.69314718055994529;
        ck_im = rt_atan2d_snf(rz_im, rz_re);
      } else {
        ck_re = std::log(rt_hypotd_snf(rz_re, rz_im));
        ck_im = rt_atan2d_snf(rz_im, rz_re);
      }
      rho2 = 0.0 * ck_re - 0.0 * ck_im;
      ack = 0.0 * ck_im + 0.0 * ck_re;
      ap = 1.0;
      gammaln(ap);
      ck_re = (rho2 + z.re) - ap;
      ck_im = ack + z.im;
      p2_re += ak;
      p2_im += az;
      p1_re = 1.0 / rt_hypotd_snf(p2_re, p2_im);
      if (ck_re == 0.0) {
        ck_re = std::cos(ck_im);
        ck_im = std::sin(ck_im);
      } else if (ck_im == 0.0) {
        ck_re = std::exp(ck_re);
        ck_im = 0.0;
      } else if (std::isinf(ck_im) && std::isinf(ck_re) && (ck_re < 0.0)) {
        ck_re = 0.0;
        ck_im = 0.0;
      } else {
        rho2 = std::exp(ck_re / 2.0);
        ck_re = rho2 * (rho2 * std::cos(ck_im));
        ck_im = rho2 * (rho2 * std::sin(ck_im));
      }
      ack = ck_re * p1_re - ck_im * 0.0;
      ck_im = ck_re * 0.0 + ck_im * p1_re;
      rho2 = p2_re * p1_re + p2_im * 0.0;
      p2_im = p2_re * 0.0 - p2_im * p1_re;
      ck_re = ack * rho2 - ck_im * p2_im;
      ck_im = ack * p2_im + ck_im * rho2;
      ack = y.re * ck_im + y.im * ck_re;
      y.re = y.re * ck_re - y.im * ck_im;
      y.im = ack;
    }
  }
  return nz;
}

} // namespace coder

// End of code generation (cmlri.cpp)
