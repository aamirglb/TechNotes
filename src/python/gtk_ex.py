#!/usr/bin/python
import gi
gi.require_version('Gtk', '3.0')
from gi.repository import Gtk, GObject, GLib
from datetime import datetime

class MainWindow(Gtk.Window):
    def __init__(self):
        Gtk.Window.__init__(self, title="App")
        self.box = Gtk.Box(spacing=6)
        self.add(self.box)

        self.label = Gtk.Label()
        self.box.pack_start(self.label, True, True, 0)

    def displayClock(self):
        datetimenow = str(datetime.now())
        self.label.set_label(datetimenow)
        return True

    def startClockTimer(self):
        GLib.timeout_add(1000, self.displayClock)

win = MainWindow()
win.connect("delete-event", Gtk.main_quit)
win.show_all()
win.startClockTimer()
Gtk.main()