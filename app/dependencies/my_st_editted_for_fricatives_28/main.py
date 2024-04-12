import numpy as np
from scipy.signal import stft


def my_st_editted_for_fricatives_28(y, fs):
    """
    Computes the S-transform output for the input waveform.
    
    Args:
    - y: Input waveform
    - fs: Sampling frequency
    
    Returns:
    - time_ref_wrt_input: Time scale relative to the input waveform
    - freq_scale: Frequency scale in number of points
    - s2: Time-frequency signal of the S-transform
    """

    # Preemphasis
    dy = np.diff(y)
    dy = np.append(dy[0], dy)  # Add the first element back

    # Frame size for computing S-transform in milliseconds
    frame_size_in_ms = 100
    frame_size = int(frame_size_in_ms * fs / 1000)

    # Dividing into frames without overlap
    yf = np.array([dy[i:i+frame_size] for i in range(0, len(dy), frame_size)])

    # Compute the S-transform for all frames
    s1 = []
    for frame in yf:
        _, _, S = stft(frame, fs=fs, nperseg=frame_size)
        s1.append(S)

    s1 = np.array(s1)
    s1 = np.abs(s1[:, :, :len(y)])  # Remove padded zeros

    # Time and frequency scales
    freq_resolution = fs / (2 * s1.shape[1])
    freq_scale = np.arange(1, s1.shape[1] + 1) * freq_resolution
    time_ref_wrt_input = np.arange(len(y)) + 1  # Time scale relative to input

    return time_ref_wrt_input, freq_scale, s1