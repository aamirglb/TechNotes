import cv2 as cv

def rescaleFrame(frame, scale=0.75):
    width = int(frame.shape[1] * scale)
    height = int(frame.shape[0] * scale)
    dimensions = (width, height)
    return cv.resize(frame, dimensions, interpolation=cv.INTER_AREA)


# img = cv.imread('C:/Users/aamir.ali/Pictures/demo-lib/DSLR-0000.jpg')
# cv.imshow('Pic', img)
# cv.waitKey(0)

# capture = cv.VideoCapture('C:/Users/aamir.ali/Pictures/demo-lib/P4_Clip_001.mp4')
capture = cv.VideoCapture('C:/Users/aamir.ali/Pictures/demo-lib/FMX_Clip.mov')

while True:
    isTrue, frame = capture.read()
    resized_frame = rescaleFrame(frame, .5)

    if cv.waitKey(20) & 0xFF == ord('d') or not isTrue:
        break

    cv.imshow('Video', frame)
    cv.imshow('Resized Video', resized_frame)

capture.release()
cv.destroyAllWindows()
# cv.waitKey(0)