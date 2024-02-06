//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// main.cpp
//
// Code generation for function 'main'
//

/*************************************************************************/
/* This automatically generated example C++ main file shows how to call  */
/* entry-point functions that MATLAB Coder generated. You must customize */
/* this file for your application. Do not modify this file directly.     */
/* Instead, make a copy of this file, modify it, and integrate it into   */
/* your development environment.                                         */
/*                                                                       */
/* This file initializes entry-point function arguments to a default     */
/* size and value before calling the entry-point functions. It does      */
/* not store or use any values returned from the entry-point functions.  */
/* If necessary, it does pre-allocate memory for returned values.        */
/* You can use this file as a starting point for a main function that    */
/* you can deploy in your application.                                   */
/*                                                                       */
/* After you copy the file, and before you deploy it, you must make the  */
/* following changes:                                                    */
/* * For variable-size function arguments, change the example sizes to   */
/* the sizes that your application requires.                             */
/* * Change the example values of function arguments to the values that  */
/* your application requires.                                            */
/* * If the entry-point functions return values, store these values or   */
/* otherwise use them as required by your application.                   */
/*                                                                       */
/*************************************************************************/

// Include files
#include "main.h"
#include "resampleWrapper.h"
#include "resampleWrapper_terminate.h"
#include "resampleWrapper_types.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "omp.h"
// #include <cstdio>
// #include <cstdlib>
// #include <sstream>
// #include <stdexcept>
#include <string>
#include <iostream>

// Function Declarations
static coder::array<double, 1U> argInit_Unboundedx1_real_T();

static double argInit_real_T();

static void l_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

// Function Definitions
static coder::array<double, 1U> argInit_Unboundedx1_real_T()
{
  coder::array<double, 1U> result;
  // Set the size of the array.
  // Change this size to the value that the application requires.
  result.set_size(100);
  // Loop over the array to initialize each element.
  for (int idx0{0}; idx0 < result.size(0); idx0++) {
    // Set the value of the array element.
    // Change this value to the value that the application requires.
    result[idx0] = argInit_real_T();
  }
  // std::cout<<result[1]<<'\n';
  return result;
}

static double argInit_real_T()
{
  return 10.0;
}

// static void l_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
// {
//   std::string errMsg;
//   std::stringstream outStream;
//   outStream << "Example main does not support command line arguments.";
//   outStream << "\n";
//   ((((outStream << "Error in ") << aFcnName) << " (line ") << aLineNum) << ")";
//   if (omp_in_parallel()) {
//     errMsg = outStream.str();
//     std::fprintf(stderr, "%s", errMsg.c_str());
//     std::abort();
//   } else {
//     throw std::runtime_error(outStream.str());
//   }
// }

std::vector<double> main_resampleWrapper(std::vector<double> input_data, int targetFs, int fs);

extern "C" {
    void resample(const double *data, int data_size, int tgt_rate, int rate, double **result_array, int *result_size) {
      std::vector<double> input_data(data, data + data_size);
      std::vector<double> output_data = main_resampleWrapper(input_data, tgt_rate, rate);

      *result_size = output_data.size();
      *result_array = (double *)malloc(sizeof(double) * output_data.size());
      std::copy(output_data.begin(), output_data.end(), *result_array);
    }

    void free_array(double *array) {
        free(array);
    }
}

int main(int argc, char **)
{
  // static rtRunTimeErrorInfo k_emlrtRTEI{
  //     1,                 // lineNo
  //     27,                // colNo
  //     "resampleWrapper", // fName
  //     "/home/abhinav/abhi/college/sem6/BTP/BTP_App/entry "
  //     "points/resampleWrapper.m" // pName
  // };
  // if (argc > 1) {
  //   l_rtErrorWithMessageID(k_emlrtRTEI.fName, k_emlrtRTEI.lineNo);
  // }
  // The initialize function is being called automatically from your entry-point
  // function. So, a call to initialize is not included here. Invoke the
  // entry-point functions.
  // You can call entry-point functions multiple times.

  // std::vector<double> input_data(100, 10);

  // std::vector<double> output_data = main_resampleWrapper(input_data, 10, 100);
  // for(auto &i: output_data){
  //   std::cout<<i<<' ';
  // }

  double data[100];
  for(int i=0; i<100; i++){
    data[i] = 10;
  }
  int data_size = sizeof(data) / sizeof(data[0]);
  int tgt_rate = 10;
  int rate = 100;

  // Call the resample function
  double *result_array;
  int result_size;
  resample(data, data_size, tgt_rate, rate, &result_array, &result_size);

  // Print the result
  std::cout << "Resampled data: ";
  for (int i = 0; i < result_size; ++i) {
      std::cout << result_array[i] << " ";
  }
  std::cout << std::endl;

  // Free the allocated memory
  free_array(result_array);

  return 0;
}

std::vector<double> main_resampleWrapper(std::vector<double> input_data, int targetFs, int fs)
{
  coder::array<double, 2U> data_resampled;
  coder::array<double, 1U> data(input_data);
  // double targetFs_tmp;
  // Initialize function 'resampleWrapper' input arguments.
  // Initialize function input argument 'data'.
  // data = argInit_Unboundedx1_real_T();
  // for(auto &i: data){
  //   std::cout<<i<<' ';
  // }
  // targetFs_tmp = argInit_real_T();
  // Call the entry-point 'resampleWrapper'.
  resampleWrapper(data, targetFs, fs, data_resampled);

  resampleWrapper_terminate();
  // std::cout<<'\n';
  // for(auto &i: data_resampled){
  //   std::cout<<i<<' ';
  // }

  std::vector<double> output_data(data_resampled);
  return output_data;
}
