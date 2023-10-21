import typing
import PySide2.QtCore
from PySide2.QtWidgets import *
from PySide2.QtCore import *
from PySide2.QtGui import *

import sys

import PySide2.QtWidgets

class MainWindow(QMainWindow) :

    def __init__(self, *args, **kwargs) -> None:
        super(MainWindow, self).__init__(*args, **kwargs)

        self.windowTitleChanged.connect(self.onWindowTitleChange)
        self.windowTitleChanged.connect(lambda x: self.my_custom_fn())
        self.windowTitleChanged.connect(lambda x: self.my_custom_fn(x))

        self.setWindowTitle("My First PySide App")
        # label = QLabel("<h1>This is AWESOME!!</h1>")
        # label.setAlignment(Qt.AlignCenter)
        # self.setCentralWidget(label)

        self.button = QPushButton("Change Title")
        self.button.clicked.connect(self.on_button_click)
        # self.button.setAlignment(Qt.AlignCenter)
        self.setCentralWidget(self.button)

        self.toolbar = QToolBar("Main Toolbar")
        self.toolbar.setIconSize(QSize(16, 16))
        self.addToolBar(self.toolbar)

        self.button_action = QAction(QIcon("bug.png"), "Button", self)
        self.button_action.setStatusTip("This is the button")
        self.button_action.setCheckable(True)
        self.button_action.triggered.connect(self.onToolBarButtonClick)
        self.toolbar.addAction(self.button_action)

        self.toolbar.addSeparator()

        self.button_action2 = QAction(QIcon("bug.png"), "Button-2", self)
        self.button_action2.setStatusTip("Button-2")
        self.button_action2.triggered.connect(self.onToolBarButtonClick)
        self.button_action2.setCheckable(True)
        self.toolbar.addAction(self.button_action2)

        self.toolbar.addSeparator()

        self.toolbar.addWidget(QLabel("Hello"))
        self.toolbar.addSeparator()
        self.toolbar.addWidget(QCheckBox())

        self.menu = self.menuBar()
        self.file_menu = self.menu.addMenu("&File")
        self.file_menu.addAction(self.button_action)
        self.file_menu.addSeparator()
        self.file_menu.addAction(self.button_action2)

        self.setStatusBar(QStatusBar(self))
        self.counter = 1

    def onToolBarButtonClick(self, s):
        print("button clicked", s)

    def ContextMenuEvent(self, event):
        print("Contextmenu event!!")

    def on_button_click(self):
        self.setWindowTitle("Title {}".format(self.counter))
        self.counter += 1

    def onWindowTitleChange(self, s):
        print(s)

    def my_custom_fn(self, a="Hello!!"):
        print(a)

app = QApplication(sys.argv)
window = MainWindow()
window.show()
app.exec_()