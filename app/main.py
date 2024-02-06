import sys
from PyQt5.QtWidgets import QApplication, QMainWindow, QMenu, QAction, QFileDialog, QActionGroup, QTextEdit, QWidget, QVBoxLayout, QLabel, QHBoxLayout, QGroupBox, QSplitter, QToolButton
from PyQt5.QtCore import Qt
import os
import soundfile as sf
import matplotlib.pyplot as plt
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas, NavigationToolbar2QT as NavigationToolbar

class LeftComponent(QGroupBox):
    def __init__(self):
        super().__init__("Left Box")
        self.initUI()

    def initUI(self):
        self.left_layout = QVBoxLayout()

        self.left_plot = plt.figure()
        self.ax = self.left_plot.add_subplot(111)
        self.left_canvas = FigureCanvas(self.left_plot)
        self.left_toolbar = NavigationToolbar(self.left_canvas, self)

        self.left_layout.addWidget(self.left_toolbar)
        self.zoom_in_action = QAction('Zoom In')
        self.zoom_in_action.triggered.connect(self.zoom_in)
        self.tool_button_zoom_in = QToolButton(self)
        self.tool_button_zoom_in.setDefaultAction(self.zoom_in_action)
        self.zoom_out_action = QAction('Zoom In')
        self.zoom_out_action.triggered.connect(self.zoom_out)
        self.tool_button_zoom_out = QToolButton(self)
        self.tool_button_zoom_out.setDefaultAction(self.zoom_out_action)
        self.left_layout.addWidget(self.tool_button_zoom_in)
        self.left_layout.addWidget(self.tool_button_zoom_out)
        self.left_layout.addWidget(self.left_canvas)
        self.setLayout(self.left_layout)

    def update_plot(self, data):
        self.ax.clear()
        self.ax.plot(data)
        self.left_canvas.draw()

    def zoom_in(self):
        xlim = self.ax.get_xlim()
        ylim = self.ax.get_ylim()
        self.ax.set_xlim(xlim[0] * 0.9, xlim[1] * 0.9)
        # self.ax.set_ylim(ylim[0] * 0.9, ylim[1] * 0.9)
        self.left_canvas.draw()

    def zoom_out(self):
        xlim = self.ax.get_xlim()
        ylim = self.ax.get_ylim()
        self.ax.set_xlim(xlim[0] * 1.1, xlim[1] * 1.1)
        # self.ax.set_ylim(ylim[0] * 1.1, ylim[1] * 1.1)
        self.left_canvas.draw()


class MyMainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.logs = []
        self.file_path = None
        self.file_base_name = None
        self.initUI()

    def initUI(self):
        self.createFileMenu()
        self.createOrientationMenu()

        central_widget = QWidget(self)
        main_layout = QHBoxLayout(central_widget)

        self.splitter = QSplitter(self)

        self.left_component = LeftComponent()
        self.right_component = LeftComponent()
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
            print(f"Selected file: {fileName}")
            self._log_action(f"Selected file: {fileName}")
            self.file_path = fileName
            self.file_base_name = os.path.basename(fileName)
            self.refresh_left_area()

            data, samplerate = sf.read(self.file_path)
            print(data, samplerate)

            self.left_component.update_plot(data)

    def refresh_left_area(self):
        self.left_component.setTitle(self.file_base_name)

    def _log_action(self, text):
        print(text)
        self.logs.append(text)

if __name__ == '__main__':
    app = QApplication(sys.argv)
    mainWindow = MyMainWindow()
    mainWindow.show()
    sys.exit(app.exec_())
