//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// firls.h
//
// Code generation for function 'firls'
//

#ifndef FIRLS_H
#define FIRLS_H

// Include files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
void eFirls(double N, const double freq[4], array<double, 2U> &h,
            array<double, 1U> &a);

}

#endif
// End of code generation (firls.h)
