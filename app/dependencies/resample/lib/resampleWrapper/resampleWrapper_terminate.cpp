//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// resampleWrapper_terminate.cpp
//
// Code generation for function 'resampleWrapper_terminate'
//

// Include files
#include "resampleWrapper_terminate.h"
#include "resampleWrapper_data.h"
#include "rt_nonfinite.h"
#include "omp.h"

// Function Definitions
void resampleWrapper_terminate()
{
  omp_destroy_nest_lock(&resampleWrapper_nestLockGlobal);
  isInitialized_resampleWrapper = false;
}

// End of code generation (resampleWrapper_terminate.cpp)
