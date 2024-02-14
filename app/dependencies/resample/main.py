import ctypes
import numpy as np

# Load the shared library
lib = ctypes.CDLL("./dependencies/resample/lib/resampleWrapper/resampleWrapper.so")  # Update with the actual library name

# Define the argument and return types for the functions
lib.resample.argtypes = [
    ctypes.POINTER(ctypes.c_double),  # data
    ctypes.c_int,                      # data_size
    ctypes.c_int,                      # tgt_rate
    ctypes.c_int,                      # rate
    ctypes.POINTER(ctypes.POINTER(ctypes.c_double)),  # result_array
    ctypes.POINTER(ctypes.c_int)       # result_size
]
lib.resample.restype = None

lib.free_array.argtypes = [ctypes.POINTER(ctypes.c_double)]  # array
lib.free_array.restype = None

# Define a function to call resample and handle the memory properly
def resample(data, tgt_rate, rate):
    data_size = len(data)
    data_ptr = (ctypes.c_double * data_size)(*data)
    
    result_array = ctypes.POINTER(ctypes.c_double)()
    result_size = ctypes.c_int()
    
    lib.resample(data_ptr, data_size, tgt_rate, rate, ctypes.byref(result_array), ctypes.byref(result_size))
    result = np.zeros(result_size.value, dtype=np.double)
    for i in range(result_size.value):
        result[i] = result_array[i]
    
    lib.free_array(result_array)
    
    return result

if __name__ == "__main__":
    # Example usage
    data = np.array([10.0 for _ in range(100)], dtype=np.double)
    tgt_rate = 10
    rate = 100

    result = resample(data, tgt_rate, rate)
    # print(result)

    data = np.random.rand(100)
    resampled_data = resample(data, tgt_rate, rate)

    import matplotlib.pyplot as plt

    plt.plot(data)
    plt.show()

    plt.plot(resampled_data)
    plt.show()