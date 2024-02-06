//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// uniformResample.h
//
// Code generation for function 'uniformResample'
//

#ifndef UNIFORMRESAMPLE_H
#define UNIFORMRESAMPLE_H

// Include files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
namespace b_signal {
namespace internal {
namespace resample {
void resampleByDesignedFilter(const array<double, 1U> &xIn, double Lx,
                              const double xSize[2], double xNumel, double p,
                              double q, double Dim, const double xtrueSize[2],
                              double xtrueNumel, boolean_T xtrueIsRow,
                              array<double, 2U> &y, array<double, 2U> &hout);

}
} // namespace internal
} // namespace b_signal
} // namespace coder

#endif
// End of code generation (uniformResample.h)
