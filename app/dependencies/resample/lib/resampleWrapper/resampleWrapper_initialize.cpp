//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// resampleWrapper_initialize.cpp
//
// Code generation for function 'resampleWrapper_initialize'
//

// Include files
#include "resampleWrapper_initialize.h"
#include "resampleWrapper_data.h"
#include "rt_nonfinite.h"
#include "omp.h"

// Function Definitions
void resampleWrapper_initialize()
{
  omp_init_nest_lock(&resampleWrapper_nestLockGlobal);
  isInitialized_resampleWrapper = true;
}

// End of code generation (resampleWrapper_initialize.cpp)
