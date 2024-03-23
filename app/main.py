import sys
from PyQt5.QtWidgets import QApplication, QMainWindow, QMenu, QAction, QFileDialog, QActionGroup, QTextEdit, QWidget, QVBoxLayout, QLabel, QHBoxLayout, QGroupBox, QSplitter, QToolButton, QRadioButton
from PyQt5.QtCore import Qt, QTimer
import os
import soundfile as sf
import matplotlib.pyplot as plt
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas, NavigationToolbar2QT as NavigationToolbar
from scipy.signal import spectrogram
import numpy as np

from dependencies.resample.main import resample
from dependencies.ZERO_TIME_WIND_SPECTRUM.main import wind as zero_time_wind_spectrum
from dependencies.SINGLE_FREQ_FILTER_FS.main import SINGLE_FREQ_FILTER_FS as single_freq_filter_fs
from datetime import datetime
from time import sleep

def plot_spectrogram(data, fs):
    f, t, Sxx = spectrogram(data, nfft=fs, window='hamming', nperseg=160, noverlap=80)
    plt.pcolormesh(t, f, 10 * np.log10(Sxx))
    plt.ylabel('Frequency [Hz]')
    plt.xlabel('Time [sec]')
    plt.colorbar(label='Magnitude [dB]')
    plt.show()


class AudioComponent(QGroupBox):
    def __init__(self):
        super().__init__("Select a File to continue")
        self.initUI()

        self.data = None
        self.fs = None

    def initUI(self):
        self.layout_area = QVBoxLayout()
        self.prepareRadioButtons()

        self.plot = plt.figure()
        self.ax = self.plot.add_subplot(111)
        self.left_canvas = FigureCanvas(self.plot)
        # self.left_toolbar = NavigationToolbar(self.left_canvas, self)

        # self.layout_area.addWidget(self.left_toolbar)
        # self.zoom_in_action = QAction('Zoom In')
        # self.zoom_in_action.triggered.connect(self.zoom_in)
        # self.tool_button_zoom_in = QToolButton(self)
        # self.tool_button_zoom_in.setDefaultAction(self.zoom_in_action)
        # self.zoom_out_action = QAction('Zoom Out')
        # self.zoom_out_action.triggered.connect(self.zoom_out)
        # self.tool_button_zoom_out = QToolButton(self)
        # self.tool_button_zoom_out.setDefaultAction(self.zoom_out_action)
        # self.layout_area.addWidget(self.tool_button_zoom_in)
        # self.layout_area.addWidget(self.tool_button_zoom_out)
        self.layout_area.addWidget(self.left_canvas)
        self.setLayout(self.layout_area)

    def prepareRadioButtons(self):
        self.radioButtonLayout = QHBoxLayout()
        self.radioButton1 = QRadioButton('WafeForm')
        self.radioButton1.clicked.connect(self.update_plot)
        self.radioButton1.setDisabled(True)
        self.radioButton2 = QRadioButton('Spectogram')
        self.radioButton2.clicked.connect(self.update_spectogram_plot)
        self.radioButton2.setDisabled(True)
        self.radioButton3 = QRadioButton('Zero Time Wind Spectrum')
        self.radioButton3.clicked.connect(self.update_zero_time_wind_spectrum_plot)
        self.radioButton3.setDisabled(True)
        self.radioButton4 = QRadioButton('sff')
        self.radioButton4.clicked.connect(self.update_single_freq_filter_fs)
        self.radioButton4.setDisabled(True)

        self.radioButtonLayout.addWidget(self.radioButton1)
        self.radioButtonLayout.addWidget(self.radioButton2)
        self.radioButtonLayout.addWidget(self.radioButton3)
        self.radioButtonLayout.addWidget(self.radioButton4)

        self.layout_area.addLayout(self.radioButtonLayout)

    def disable_radio_buttons(self):
        self.radioButton1.setDisabled(True)
        self.radioButton2.setDisabled(True)
        self.radioButton3.setDisabled(True)
        self.radioButton4.setDisabled(True)
    
    def enable_radio_buttons(self):
        self.radioButton1.setDisabled(False)
        self.radioButton2.setDisabled(False)
        self.radioButton3.setDisabled(False)
        self.radioButton4.setDisabled(False)

    def update_plot(self):
        self.disable_radio_buttons()
        self.set_loading_screen_in_plot()
        self.ax.plot(self.data)
        self.left_canvas.draw()
        self.enable_radio_buttons()

    def update_spectogram_plot(self):
        self.disable_radio_buttons()
        self.set_loading_screen_in_plot()
        f, t, Sxx = spectrogram(self.data, nfft=self.fs, window='hamming', nperseg=160, noverlap=80)
        
        self.ax.pcolormesh(t, f, 10 * np.log10(Sxx))
        self.ax.set_ylabel('Frequency [Hz]')
        self.ax.set_xlabel('Time [sec]')

        self.left_canvas.draw()
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
        
        self.ax.pcolormesh(T, F, abs(result_HNGD_SPEC), shading='auto')
        # self.ax.colorbar(label='Magnitude')
        self.ax.set_xlabel('Time')
        self.ax.set_ylabel('Frequency')
        self.left_canvas.draw()

        self.enable_radio_buttons()

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

        self.ax.pcolormesh(T_s, F_s, np.abs(env), shading='auto')
        self.ax.set_xlabel('Time')
        self.ax.set_ylabel('Frequency')

        self.left_canvas.draw()
        sleep(10)

        self.enable_radio_buttons()

        print("Exiting parent function")

    def set_data(self, data, fs):
        print(data.shape)
        self.data = data
        self.fs = fs

        self.resampled_data = resample(self.data, 8000, self.fs)
        self.resampled_fs = 8000

        self.enable_radio_buttons()

    def set_loading_screen_in_plot(self):
        print('Inside clear function')
        self.ax.clear()
        self.left_canvas.draw()

        self.ax.set_axis_off()
        self.ax.text(0.5, 0.5, 'Loading....', horizontalalignment='center', verticalalignment='center', fontsize=12)
        self.left_canvas.draw()

        self.ax.clear()
        print('Exiting clear function')

    def zoom_in(self):
        xlim = self.ax.get_xlim()
        # ylim = self.ax.get_ylim()
        center = (xlim[0] + xlim[1])/2
        self.ax.set_xlim(center - (center - xlim[0]) * 0.9, center + (xlim[1] - center) * 0.9)
        # self.ax.set_ylim(ylim[0] * 0.9, ylim[1] * 0.9)
        self.left_canvas.draw()

    def zoom_out(self):
        xlim = self.ax.get_xlim()
        # ylim = self.ax.get_ylim()
        center = (xlim[0] + xlim[1])/2
        self.ax.set_xlim(center - (center - xlim[0]) * 1.1, center + (xlim[1] - center) * 1.1)
        # self.ax.set_ylim(ylim[0] * 1.1, ylim[1] * 1.1)
        self.left_canvas.draw()


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
        self.splitter.addWidget(self.right_component)

        main_layout.addWidget(self.splitter)

        self.setCentralWidget(central_widget)

        self.setGeometry(100, 100, 800, 600)
        self.setWindowTitle('Application')

    def createFileMenu(self):
        file_menu = self.menuBar().addMenu('File')

        load_action = QAction('Load Single File', self)
        load_action.triggered.connect(self.loadFile)
        file_menu.addAction(load_action)

        compare_action = QAction('Compare with File', self)
        # compare_action.triggered.connect(self.compareFiles)
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
        alignment_action.triggered.connect(lambda: self._log_action(log_text))
        return alignment_action


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
                print(data, samplerate)

                # plot_spectrogram(data, samplerate)
                self.left_component.set_data(data, samplerate)
            else:
                self._log_action(f"Selected file: {fileName}")
                self.file_path_2 = fileName
                self.file_base_name_2 = os.path.basename(fileName)
                self.refresh_right_area()

                data, samplerate = sf.read(self.file_path_2)
                
                self.right_component.set_data(data, samplerate)

    def refresh_left_area(self):
        self.left_component.setTitle(self.file_base_name)

    def refresh_right_area(self):
        self.right_component .setTitle(self.file_base_name_2)

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
