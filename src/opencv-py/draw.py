import cv2 as cv
import numpy as np

blank = np.zeros((500, 500, 3), dtype="uint8")
cv.imshow('Blank', blank)

# blank[:] = 0,255,0
# cv.imshow('Blank', blank)
cv.rectangle(blank, (0,0), (250, 250), (0, 0, 255), thickness=2)
cv.imshow('Rectangle', blank)

img = cv.imread('C:/Users/aamir.ali/Pictures/demo-lib/DSLR-0000.jpg')
cv.waitKey(0)