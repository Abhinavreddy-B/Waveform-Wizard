#include "resampleWrapper.h"
#include "resampleWrapper_terminate.h"
#include "resampleWrapper_types.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "omp.h"

std::vector<double> main_resampleWrapper(std::vector<double> input_data, int targetFs, int fs)
{
  coder::array<double, 2U> data_resampled;
  coder::array<double, 1U> data(input_data);
  resampleWrapper(data, targetFs, fs, data_resampled);

  resampleWrapper_terminate();

  std::vector<double> output_data(data_resampled);
  return output_data;
}

extern "C" {
    void resample(const double *data, int data_size, int tgt_rate, int rate, double **result_array, int *result_size) {
      std::vector<double> input_data(data, data + data_size);
      std::vector<double> output_data = main_resampleWrapper(input_data, tgt_rate, rate);

      *result_size = output_data.size();
      *result_array = (double *)malloc(sizeof(double) * output_data.size());
      std::copy(output_data.begin(), output_data.end(), *result_array);
    }

    void free_array(int *array) {
        free(array);
    }
}
