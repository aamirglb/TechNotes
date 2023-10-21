from PySide2.QtWidgets import *
from PySide2.QtCore import *
from PySide2.QtGui import *
import sys

class MainWindow(QMainWindow):
    def __init__(self, *args, **kwargs):
        super(MainWindow, self).__init__(*args, **kwargs)

        self.setWindowTitle("ComboxBox Example")
        self.widget = QComboBox()
        self.widget.setEditable(True)
        self.widget.addItems(["One", "Two", "Three", "Four", "Five", "Six"])
        self.widget.currentIndexChanged.connect(self.onSelectionChangeInt)
        self.widget.currentIndexChanged[str].connect(self.onSelectionChange)
        self.setCentralWidget(self.widget)

    def onSelectionChangeInt(self, i):
        print("int: {}".format(i))

    def onSelectionChange(self, s):
        print("str: {}".format(s))

app = QApplication(sys.argv)
window = MainWindow()
window.show()
app.exec_()