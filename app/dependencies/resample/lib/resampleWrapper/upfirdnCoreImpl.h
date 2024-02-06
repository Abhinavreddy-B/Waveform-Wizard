//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// upfirdnCoreImpl.h
//
// Code generation for function 'upfirdnCoreImpl'
//

#ifndef UPFIRDNCOREIMPL_H
#define UPFIRDNCOREIMPL_H

// Include files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
namespace b_signal {
namespace internal {
namespace upfirdn {
void upfirdnCoreImpl(const array<double, 1U> &xCol,
                     const array<double, 1U> &hCl, double LxD, double LhD,
                     double pD, double qD, array<double, 1U> &y);

}
} // namespace internal
} // namespace b_signal
} // namespace coder

#endif
// End of code generation (upfirdnCoreImpl.h)
