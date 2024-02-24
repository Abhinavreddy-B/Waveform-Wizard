//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// diff.h
//
// Code generation for function 'diff'
//

#ifndef DIFF_H
#define DIFF_H

// Include files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
void diff(const array<creal_T, 2U> &x, array<creal_T, 2U> &y);

void diff(const array<double, 2U> &x, array<double, 2U> &y);

} // namespace coder

#endif
// End of code generation (diff.h)
