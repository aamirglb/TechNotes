#!/usr/bin/env python3
import sys
import gi
from threading import Thread

gi.require_version("Gst", "1.0")
gi.require_version("GLib", "2.0")
gi.require_version("GObject", "2.0")

from gi.repository import Gst, GLib, GObject
from time import sleep

pipeline = None
bus = None
message = None

Gst.init(sys.argv[1:])

main_loop = GLib.MainLoop()
main_loop_thread = Thread(target=main_loop.run)
main_loop_thread.start()

pipeline = Gst.parse_launch("v4l2src device=/dev/video0 \
    ! video/x-raw,width=640,height=480,framerate=30/1 \
    !  videoconvert \
    ! timeoverlay \
    ! videorate \
    ! video/x-raw,framerate=1/1 \
    ! xvimagesink")

pipeline.set_state(Gst.State.PLAYING)

try:
    while True:
        sleep(0.01)
except KeyboardInterrupt:
    pass

pipeline.set_state(Gst.State.NULL)
main_loop.quit()
main_loop_thread.join()