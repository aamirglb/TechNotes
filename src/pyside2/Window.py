import sys
from PySide2.QtWidgets import QApplication, QWidget, QLabel
from PySide2.QtGui import QPixmap

class MainWindow(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        self.setGeometry(100*2, 100*2, 400*2, 300*2)
        self.setWindowTitle('World Image')
        self.displayLabels()

        self.show()

    def contextMenuEvent(self, event):
        print("Context menu event!")
        
    def displayLabels(self):
        text = QLabel(self)
        text.setText("Hello")
        text.move(105, 5)

        image = "world_image.png"
        try:
            with open(image):
                world_image = QLabel(self)
                pixmap = QPixmap(image)
                world_image.setPixmap(pixmap)
                world_image.move(25, 40)
        except FileNotFoundError:
            print("Image not found.")

if __name__ == '__main__':
    app = QApplication(sys.argv)
    window = MainWindow()
    sys.exit(app.exec_())