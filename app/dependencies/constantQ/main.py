import librosa
import librosa.display
import matplotlib.pyplot as plt
import numpy as np


def constantq(data, fs):
    C = librosa.cqt(data, sr=fs, fmin=10, n_bins=librosa.note_to_midi('C8') - librosa.note_to_midi('C1'))
    fs_bins_cq = librosa.cqt_frequencies(C.shape[0], fmin=librosa.note_to_hz('C2'))
    return np.abs(C), fs_bins_cq
