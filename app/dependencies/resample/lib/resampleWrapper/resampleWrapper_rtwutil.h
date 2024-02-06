//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// resampleWrapper_rtwutil.h
//
// Code generation for function 'resampleWrapper_rtwutil'
//

#ifndef RESAMPLEWRAPPER_RTWUTIL_H
#define RESAMPLEWRAPPER_RTWUTIL_H

// Include files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Declarations
struct rtBoundsCheckInfo;

struct rtDoubleCheckInfo;

struct rtEqualityCheckInfo;

// Function Declarations
extern void b_rtErrorWithMessageID(const char *r, const char *aFcnName,
                                   int aLineNum);

extern void c_rtErrorWithMessageID(const char *r, const char *aFcnName,
                                   int aLineNum);

extern void d_rtErrorWithMessageID(const char *r, const char *aFcnName,
                                   int aLineNum);

extern int div_s32(int numerator, int denominator);

extern void e_rtErrorWithMessageID(const char *r, const char *aFcnName,
                                   int aLineNum);

extern void emlrtDimSizeImpxCheckR2021b(const int aDim1, const int aDim2,
                                        const rtEqualityCheckInfo &aInfo);

extern void rtDivisionByZeroErrorN();

extern void rtDynamicBoundsError(int aIndexValue, int aLoBound, int aHiBound,
                                 const rtBoundsCheckInfo &aInfo);

extern void rtErrorWithMessageID(const char *aFcnName, int aLineNum);

extern void rtErrorWithMessageID(const char *r, const char *aFcnName,
                                 int aLineNum);

extern void rtIntegerError(const double aInteger,
                           const rtDoubleCheckInfo &aInfo);

extern boolean_T rtIsNullOrEmptyString(const char *aString);

extern void rtNonNegativeError(const double aPositive,
                               const rtDoubleCheckInfo &aInfo);

extern double rt_hypotd_snf(double u0, double u1);

#endif
// End of code generation (resampleWrapper_rtwutil.h)
