//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// resampleWrapper.h
//
// Code generation for function 'resampleWrapper'
//

#ifndef RESAMPLEWRAPPER_H
#define RESAMPLEWRAPPER_H

// Include files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
extern void resampleWrapper(const coder::array<double, 1U> &data,
                            double targetFs, double fs,
                            coder::array<double, 2U> &data_resampled);

#endif
// End of code generation (resampleWrapper.h)
