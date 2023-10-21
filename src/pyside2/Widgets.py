from PySide2.QtWidgets import *
from PySide2.QtCore import *
from PySide2.QtGui import *

import sys

class MainWindow(QMainWindow):

    def __init__(self, *args, **kwargs):
        super(MainWindow, self).__init__(*args, **kwargs)
        self.setWindowTitle("Widget App")
        self.layout = QVBoxLayout()
        self.widgets = [
            QCheckBox,
            QComboBox,
            QDateEdit,
            QDateTimeEdit,
            QDial,
            QDoubleSpinBox,
            QFontComboBox,
            QLCDNumber,
            QLabel,
            QLineEdit,
            QProgressBar,
            QPushButton,
            QRadioButton,
            QSlider,
            QSpinBox,
            QTimeEdit
        ]

        for w in self.widgets:
            self.layout.addWidget(w())
        
        self.widget = QWidget()
        self.widget.setLayout(self.layout)
        self.setCentralWidget(self.widget)

app = QApplication(sys.argv)
window = MainWindow()
window.show()
app.exec_()