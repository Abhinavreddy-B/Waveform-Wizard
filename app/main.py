import os
import sys
from datetime import datetime
from time import sleep

import matplotlib.pyplot as plt
import numpy as np
import soundfile as sf
from dependencies.formant_CGDZP.main import formant_CGDZP
from dependencies.gammatonegram.main import gammatonegram
# from dependencies.pitch_srh.main import pitch_srh
from dependencies.resample.main import resample
from dependencies.SINGLE_FREQ_FILTER_FS.main import \
    SINGLE_FREQ_FILTER_FS as single_freq_filter_fs
from dependencies.voiced_unvoiced_own.main import voiced_unvoiced_own
from dependencies.ZERO_TIME_WIND_SPECTRUM.main import \
    wind as zero_time_wind_spectrum
from matplotlib.backends.backend_qt5agg import \
    FigureCanvasQTAgg as FigureCanvas
from matplotlib.backends.backend_qt5agg import \
    NavigationToolbar2QT as NavigationToolbar
from PyQt5.QtCore import Qt, QTimer
from PyQt5.QtWidgets import (QAction, QActionGroup, QApplication, QFileDialog,
                             QGroupBox, QHBoxLayout, QLabel, QMainWindow,
                             QMenu, QRadioButton, QSplitter, QTextEdit,
                             QToolButton, QVBoxLayout, QWidget)
from scipy.signal import spectrogram


def plot_spectrogram(data, fs):
    f, t, Sxx = spectrogram(data, nfft=fs, window='hamming', nperseg=160, noverlap=80)
    plt.pcolormesh(t, f, 10 * np.log10(Sxx))
    plt.ylabel('Frequency [Hz]')
    plt.xlabel('Time [sec]')
    plt.colorbar(label='Magnitude [dB]')
    plt.show()

def process_audio(audio):
    if audio.ndim == 1:
        # Type 1 audio (shape: (n,))
        return audio
    elif audio.ndim == 2 and audio.shape[1] == 2:
        # Type 2 audio (shape: (n, 2))
        # Take only the first channel
        return audio[:, 0]
    else:
        # Invalid audio format
        raise ValueError("Invalid audio format")

class AudioComponent(QGroupBox):
    def __init__(self):
        super().__init__("Select a File to continue")
        self.initUI()

        self.data = None
        self.fs = None

    def initUI(self):
        self.layout_area = QVBoxLayout()

        # First graph for regular waveform
        self.plot_waveform = plt.figure()
        self.ax_waveform = self.plot_waveform.add_subplot(111)
        self.canvas_waveform = FigureCanvas(self.plot_waveform)

        self.action_button_layout_waveform = QHBoxLayout()
        self.zoom_in_action = QAction('\U0001F50D +')
        self.zoom_in_action.triggered.connect(self.zoom_in)
        self.tool_button_zoom_in = QToolButton(self)
        self.tool_button_zoom_in.setDefaultAction(self.zoom_in_action)
        self.zoom_out_action = QAction('\U0001F50D -')
        self.zoom_out_action.triggered.connect(self.zoom_out)
        self.tool_button_zoom_out = QToolButton(self)
        self.tool_button_zoom_out.setDefaultAction(self.zoom_out_action)
        self.move_right_action = QAction('\u2192')
        self.move_right_action.triggered.connect(self.move_right)
        self.tool_button_move_right = QToolButton(self)
        self.tool_button_move_right.setDefaultAction(self.move_right_action)
        self.move_left_action = QAction('\u2190')
        self.move_left_action.triggered.connect(self.move_left)
        self.tool_button_move_left = QToolButton(self)
        self.tool_button_move_left.setDefaultAction(self.move_left_action)
        self.action_button_layout_waveform.addWidget(self.tool_button_move_left)
        self.action_button_layout_waveform.addWidget(self.tool_button_zoom_in)
        self.action_button_layout_waveform.addWidget(self.tool_button_zoom_out)
        self.action_button_layout_waveform.addWidget(self.tool_button_move_right)
        self.action_button_layout_waveform.addStretch()
        
        self.layout_area.addLayout(self.action_button_layout_waveform)
        self.layout_area.addWidget(self.canvas_waveform)

        # Second graph for other types of plots
        self.plot_other = plt.figure()
        self.ax_other = self.plot_other.add_subplot(111)
        self.canvas_other = FigureCanvas(self.plot_other)
        self.other_toolbar = NavigationToolbar(self.canvas_other, self)
        self.layout_area.addWidget(self.other_toolbar)
        self.layout_area.addWidget(self.canvas_other)


        self.prepareRadioButtons()

        self.setLayout(self.layout_area)

    def prepareRadioButtons(self):
        self.radioButtonLayout = QHBoxLayout()
        # self.radioButton1 = QRadioButton('WafeForm')
        # self.radioButton1.clicked.connect(self.update_plot)
        # self.radioButton1.setDisabled(True)
        self.radioButton2 = QRadioButton('Spectogram')
        self.radioButton2.clicked.connect(self.update_spectogram_plot)
        self.radioButton2.setDisabled(True)
        self.radioButton3 = QRadioButton('Zero Time Wind Spectrum')
        self.radioButton3.clicked.connect(self.update_zero_time_wind_spectrum_plot)
        self.radioButton3.setDisabled(True)
        self.radioButton4 = QRadioButton('Gammatonegram')
        self.radioButton4.clicked.connect(self.update_gammatonegram_plot)
        self.radioButton4.setDisabled(True)
        self.radioButton5 = QRadioButton('sff')
        self.radioButton5.clicked.connect(self.update_single_freq_filter_fs)
        self.radioButton5.setDisabled(True)
        self.radioButton6 = QRadioButton('Formant Peaks')
        self.radioButton6.clicked.connect(self.update_formant_peaks)
        self.radioButton6.setDisabled(True)
        self.radioButton7 = QRadioButton('VAD')
        self.radioButton7.clicked.connect(self.update_vad_plot)
        self.radioButton7.setDisabled(True)

        # self.radioButtonLayout.addWidget(self.radioButton1)
        self.radioButtonLayout.addWidget(self.radioButton2)
        self.radioButtonLayout.addWidget(self.radioButton3)
        self.radioButtonLayout.addWidget(self.radioButton4)
        self.radioButtonLayout.addWidget(self.radioButton5)
        self.radioButtonLayout.addWidget(self.radioButton6)
        self.radioButtonLayout.addWidget(self.radioButton7)
        self.layout_area.addLayout(self.radioButtonLayout)

    def disable_radio_buttons(self):
        # self.radioButton1.setDisabled(True)
        self.radioButton2.setDisabled(True)
        self.radioButton3.setDisabled(True)
        self.radioButton4.setDisabled(True)
        self.radioButton5.setDisabled(True)
        self.radioButton6.setDisabled(True)
        self.radioButton7.setDisabled(True)

    
    def enable_radio_buttons(self):
        # self.radioButton1.setDisabled(False)
        self.radioButton2.setDisabled(False)
        self.radioButton3.setDisabled(False)
        self.radioButton4.setDisabled(False)
        self.radioButton5.setDisabled(False)
        self.radioButton6.setDisabled(False)
        self.radioButton7.setDisabled(False)

    def update_plot(self):
        self.disable_radio_buttons()
        # self.set_loading_screen_in_plot()
        self.ax_waveform.clear()
        self.ax_waveform.plot(self.data)
        self.canvas_waveform.draw()
        self.enable_radio_buttons()

    def update_spectogram_plot(self):
        self.disable_radio_buttons()
        self.set_loading_screen_in_plot()
        f, t, Sxx = spectrogram(self.data, nfft=self.fs, window='hamming', nperseg=160, noverlap=80)
        
        self.ax_other.pcolormesh(t, f, 10 * np.log10(Sxx))
        self.ax_other.set_ylabel('Frequency [Hz]')
        self.ax_other.set_xlabel('Time [sec]')

        self.canvas_other.draw()
        self.enable_radio_buttons()

    def update_zero_time_wind_spectrum_plot(self):
        self.disable_radio_buttons()

        self.set_loading_screen_in_plot()
        
        result_SPEC, result_HNGD_SPEC = zero_time_wind_spectrum(self.resampled_data, self.resampled_fs)
    
        time_bins = result_HNGD_SPEC.shape[1]
        tz = np.arange(time_bins) * len(self.resampled_data) / (time_bins - 1) / self.resampled_fs
        freq_bins = result_HNGD_SPEC.shape[0]
        fsn = self.resampled_fs / 2
        fz = np.arange(freq_bins) * fsn / (freq_bins - 1)
        
        print('Starting', datetime.now())
        T, F = np.meshgrid(tz, fz)
        print('Ending', datetime.now())
        
        self.ax_other.pcolormesh(T, F, abs(result_HNGD_SPEC), shading='auto')
        # self.ax.colorbar(label='Magnitude')
        self.ax_other.set_xlabel('Time')
        self.ax_other.set_ylabel('Frequency')
        self.canvas_other.draw()

        self.enable_radio_buttons()

    def update_gammatonegram_plot(self):
        self.disable_radio_buttons()

        self.set_loading_screen_in_plot()
        YG = gammatonegram(self.resampled_data, self.resampled_fs)
        f_bins = YG.shape[0]
        fg = np.arange(0, f_bins) * self.resampled_fs / (2 * f_bins)
        time_bins_g = YG.shape[1]
        ts_g = np.arange(0, time_bins_g) * len(self.resampled_data) / time_bins_g
        ts_g = ts_g / self.resampled_fs
        T_g, F_g = np.meshgrid(ts_g, fg)
        print(T_g.shape, F_g.shape)    
        self.ax_other.pcolormesh(T_g, F_g, np.abs(YG), shading='auto')
        # self.ax_other.colorbar(label='Magnitude')
        # self.ax_other.xlabel('Time')
        # self.ax_other.ylabel('Frequency')
        self.canvas_other.draw()

        self.enable_radio_buttons()
        # plot_gammatone_2d(T_g, F_g, np.abs(YG))

    def update_single_freq_filter_fs(self):

        self.disable_radio_buttons()

        self.set_loading_screen_in_plot()

        # sleep(10)
        env, _ = single_freq_filter_fs(self.resampled_data, self.resampled_fs, 20, 0, self.resampled_fs/2, 0.98)
        # env, _ = single_freq_filter_fs(self.resampled_data, self.resampled_fs)
        env = env.T

        freq_bins_s, time_bins_s = env.shape

        fsn = self.resampled_fs / 2
        fs_s = np.arange(1, freq_bins_s + 1) * fsn / freq_bins_s    

        ts_s = np.arange(1, time_bins_s + 1) * len(self.resampled_data) / time_bins_s
        ts_s = ts_s / self.resampled_fs

        T_s, F_s = np.meshgrid(ts_s, fs_s)

        self.ax_other.pcolormesh(T_s, F_s, np.abs(env), shading='auto')
        self.ax_other.set_xlabel('Time')
        self.ax_other.set_ylabel('Frequency')

        self.canvas_other.draw()

        self.enable_radio_buttons()

        print("Exiting parent function")

    def update_formant_peaks(self):
    #     f0min = 80
    #     f0max = 500
    #     hopsize = 10
                
    #     F0s, VUVDecisions, _, _ = pitch_srh(self.resampled_data, self.resampled_fs, f0min, f0max, hopsize)
    #     F0s = F0s * VUVDecisions
        
    #     s1 = spectrogram(self.resampled_data, self.resampled_fs, nperseg=80, noverlap=48, nfft=512, mode='magnitude')
        
    #     t_analysis, formantPeaks = formant_CGDZP(self.resampled_data, self.resampled_fs)
    #     F1 = formantPeaks[:len(F0s), 0] * VUVDecisions
    #     F2 = formantPeaks[:len(F0s), 1] * VUVDecisions
    #     F3 = formantPeaks[:len(F0s), 2] * VUVDecisions
        
    #     F1[F1 < np.mean(F1) / 10] = np.nan
    #     F2[F2 < np.mean(F2) / 10] = np.nan
    #     F3[F3 < np.mean(F3) / 10] = np.nan
        
    #     freq_bins_sp1 = s1[1].size
    #     fsn = self.resampled_fs / 2
    #     fs_sp1 = np.arange(1, freq_bins_sp1 + 1) * fsn / freq_bins_sp1
        
    #     time_bins_sp1 = s1[1].T.size
    #     ts_sp1 = np.arange(0, time_bins_sp1) * len(self.resampled_data) / (time_bins_sp1 - 1) / self.resampled_fs
        
    #     T_sp1, F_sp1 = np.meshgrid(ts_sp1, fs_sp1)
        
    #     self.ax_other.pcolormesh(T_sp1, F_sp1, 10 * np.log10(s1[2]), shading='auto')
    #     self.ax_other.set_xlabel('Time')
    #     self.ax_other.set_ylabel('Frequency')
    #     self.canvas_other.draw()

    #     self.enable_radio_buttons()
        print("Exiting parent function")

    def update_vad_plot(self):
        self.disable_radio_buttons()
        self.set_loading_screen_in_plot()

        vuv, _ = voiced_unvoiced_own(self.data, self.fs)

        t = np.arange(len(self.data)) / self.fs

        plt.plot(t, vuv * 0.6)
        plt.ylim(0, 1)

        self.ax_other.plot(t, vuv*0.6)
        self.ax_other.set_xlabel('Time')
        self.ax_other.set_ylabel('Voiced/Unvoiced')
        self.ax_other.set_ylim(0, 1)

        self.canvas_other.draw()

        self.enable_radio_buttons()

    def set_data(self, data, fs):
        print(data.shape)
        self.data = data
        self.fs = fs

        self.resampled_data = resample(self.data, 8000, self.fs)
        self.resampled_fs = 8000

        self.update_plot()
        self.enable_radio_buttons()

    def set_loading_screen_in_plot(self):
        print('Inside clear function')
        self.ax_other.clear()
        self.canvas_other.draw()

        self.ax_other.set_axis_off()
        self.ax_other.text(0.5, 0.5, 'Loading....', horizontalalignment='center', verticalalignment='center', fontsize=12)
        self.canvas_other.draw()

        self.ax_other.clear()
        print('Exiting clear function')

    def zoom_in(self):
        xlim = self.ax_waveform.get_xlim()
        # ylim = self.ax.get_ylim()
        center = (xlim[0] + xlim[1])/2
        self.ax_waveform.set_xlim(center - (center - xlim[0]) * 0.9, center + (xlim[1] - center) * 0.9)
        # self.ax.set_ylim(ylim[0] * 0.9, ylim[1] * 0.9)
        self.canvas_waveform.draw()

    def zoom_out(self):
        xlim = self.ax_waveform.get_xlim()
        # ylim = self.ax.get_ylim()
        center = (xlim[0] + xlim[1])/2
        self.ax_waveform.set_xlim(center - (center - xlim[0]) * 1.1, center + (xlim[1] - center) * 1.1)
        # self.ax.set_ylim(ylim[0] * 1.1, ylim[1] * 1.1)
        self.canvas_waveform.draw()

    def move_right(self):
        xlim = self.ax_waveform.get_xlim()
        # ylim = self.ax.get_ylim()
        width = (xlim[1] - xlim[0])
        shift = width * 0.1
        self.ax_waveform.set_xlim(xlim[0]+shift, xlim[1]+shift)
        # self.ax.set_ylim(ylim[0] * 0.9, ylim[1] * 0.9)
        self.canvas_waveform.draw()
    
    def move_left(self):
        xlim = self.ax_waveform.get_xlim()
        # ylim = self.ax.get_ylim()
        width = (xlim[1] - xlim[0])
        shift = width * 0.1
        self.ax_waveform.set_xlim(xlim[0]-shift, xlim[1]-shift)
        # self.ax.set_ylim(ylim[0] * 0.9, ylim[1] * 0.9)
        self.canvas_waveform.draw()


class MyMainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.logs = []
        self.file_path = None
        self.file_base_name = None
        self.file_path_2 = None
        self.file_base_name_2 = None
        self.initUI()

    def initUI(self):
        self.createFileMenu()
        self.createOrientationMenu()

        central_widget = QWidget(self)
        main_layout = QHBoxLayout(central_widget)

        self.splitter = QSplitter(self)

        self.left_component = AudioComponent()
        self.right_component = AudioComponent()
        self.splitter.addWidget(self.left_component)

        ## Code change: self.right_component is only added when the user want to load new file. 
        ## otherwise it wont even be rendered
        ## check loadFile for more info.
        # self.splitter.addWidget(self.right_component)

        main_layout.addWidget(self.splitter)

        self.setCentralWidget(central_widget)

        self.setGeometry(100, 100, 800, 600)
        self.setWindowTitle('Wavvy')
        self.showMaximized()  # Start the application in full-screen mode

    def createFileMenu(self):
        file_menu = self.menuBar().addMenu('File')

        load_action = QAction('Load Single File', self)
        load_action.triggered.connect(self.loadFile)
        file_menu.addAction(load_action)

        compare_action = QAction('Compare with File', self)
        compare_action.triggered.connect(self.compareFiles)
        file_menu.addAction(compare_action)

    def createOrientationMenu(self):
        orientation_menu = self.menuBar().addMenu('Orientation')

        swap_files = QAction('Swap Files', self)
        swap_files.triggered.connect(lambda: self._log_action('swapping...'))
        orientation_menu.addAction(swap_files)

        horizontal_alignment_action = self.createAlignmentAction('Horizontal', 'horizontal alignment')
        vertical_alignment_action = self.createAlignmentAction('Vertical', 'vertical alignment')

        separator_action = QAction('Alignment', self)
        separator_action.setSeparator(True)

        orientation_menu.addAction(separator_action)
        orientation_menu.addAction(horizontal_alignment_action)
        orientation_menu.addAction(vertical_alignment_action)

        alignment_actions = QActionGroup(self)
        alignment_actions.addAction(horizontal_alignment_action)
        alignment_actions.addAction(vertical_alignment_action)
        horizontal_alignment_action.setChecked(True)

    def createAlignmentAction(self, text, log_text):
        alignment_action = QAction(text, self)
        alignment_action.setCheckable(True)
        alignment_action.triggered.connect(lambda: self.change_orientation(text))
        return alignment_action

    def change_orientation(self, text):
        if(text == 'Vertical'):
            self.splitter.setOrientation(Qt.Vertical)
        else:
            self.splitter.setOrientation(Qt.Horizontal)
        print('inside, ', text)

    def loadFile(self):
        options = QFileDialog.Options()
        fileName, _ = QFileDialog.getOpenFileName(self, "Load Single File", "", "All Files (*);;Text Files (*.txt)", options=options)
        if fileName:
            if self.file_path == None:
                # print(f"Selected file: {fileName}")
                self._log_action(f"Selected file: {fileName}")
                self.file_path = fileName
                self.file_base_name = os.path.basename(fileName)
                self.refresh_left_area()

                data, samplerate = sf.read(self.file_path)
                data = process_audio(data)
                # print(data, samplerate)

                # plot_spectrogram(data, samplerate)
                self.left_component.set_data(data, samplerate)

    def compareFiles(self):
        options = QFileDialog.Options()
        fileName, _ = QFileDialog.getOpenFileName(self, "Load Single File", "", "All Files (*);;Text Files (*.txt)", options=options)
        
        if fileName:
            if self.file_path_2 == None:
                self._log_action(f"Selected file: {fileName}")
                self.file_path_2 = fileName
                self.file_base_name_2 = os.path.basename(fileName)
                self.refresh_right_area()

                data, samplerate = sf.read(self.file_path_2)
                data = process_audio(data)
                
                self.right_component.set_data(data, samplerate)
                self.splitter.addWidget(self.right_component)

    def refresh_left_area(self):
        self.left_component.setTitle(self.file_base_name)

    def refresh_right_area(self):
        self.right_component.setTitle(self.file_base_name_2)

    def _log_action(self, text):
        print(text)
        self.logs.append(text)

# data = np.array([-1.0891, 0.0326, 0.5525, 1.1006, 1.5442, 0.0859, -1.4916,-0.7423, -1.0616, 2.3505, -0.6156, 0.7481, -0.1924, 0.8886, -0.7648, -1.4023, -1.4224, 0.4882, -0.1774, -0.1961])
# fs = 16000
        
if __name__ == '__main__':
    app = QApplication(sys.argv)
    mainWindow = MyMainWindow()
    mainWindow.show()
    sys.exit(app.exec_())
