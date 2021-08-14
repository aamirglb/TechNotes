#!/usr/bin/env python3
import gi
gi.require_version('Gst', '1.0')
gi.require_version('Gtk', '3.0')

from gi.repository import Gst, GLib, Gtk, GObject

class MainWindow(Gtk.Window):
    def __init__(self):
        super().__init__(title='VideoRate')
        self.connect('destroy', Gtk.main_quit)
        vbox = Gtk.VBox(spacing=6)
        self.add(vbox)

        self.fps = 30
        self.width = 640
        self.height = 480

        self.start = Gtk.Button(label="Start")
        self.start.connect("clicked", self.start_video)

        self.stop = Gtk.Button(label="Stop")
        self.stop.connect("clicked", self.stop_video)
        
        self.fps_inc = Gtk.Button(label="FPS++ ({})".format(self.fps))
        self.fps_inc.connect("clicked", self.increase_fps)

        self.fps_dec = Gtk.Button(label="FPS-- ({})".format(self.fps))
        self.fps_dec.connect("clicked", self.decrease_fps)

        vbox.add(self.start)
        vbox.add(self.stop)
        vbox.add(self.fps_inc)
        vbox.add(self.fps_dec)

        self.show_all()

        self.player = Gst.Pipeline.new('player')
        self.source = Gst.ElementFactory.make('videotestsrc')
        self.sink = Gst.ElementFactory.make('autovideosink')
        self.caps = Gst.Caps.from_string("video/x-raw, width={}, height={}, framerate=30/1".format(self.width, self.height))
        self.filter = Gst.ElementFactory.make("capsfilter", "filter")
        self.filter.set_property('caps', self.caps)

        self.converter = Gst.ElementFactory.make('videoconvert')
        self.videorate = Gst.ElementFactory.make('videorate')
        self.ratefilter = Gst.ElementFactory.make("capsfilter")
        self.filtercaps = Gst.Caps.from_string('video/x-raw, framerate={}/1'.format(self.fps))
        self.ratefilter.set_property('caps', self.filtercaps)

        self.fps_txt = Gst.ElementFactory.make('textoverlay', 'textoverlay')
        self.fps_txt.set_property('text', 'FPS: {}'.format(self.fps))
        self.fps_txt.set_property('shaded-background', True)
        self.fps_txt.set_property('valignment', 1)
        self.fps_txt.set_property('halignment', 0)

        self.player.add(self.source)
        self.player.add(self.filter)
        self.player.add(self.converter)
        self.player.add(self.videorate)
        self.player.add(self.ratefilter)
        self.player.add(self.fps_txt)
        self.player.add(self.sink)

        self.source.link(self.filter)
        self.filter.link(self.converter)
        self.converter.link(self.videorate)
        self.videorate.link(self.ratefilter)
        self.ratefilter.link(self.fps_txt)
        self.fps_txt.link(self.sink)

        self.bus = self.player.get_bus()
        self.bus.add_signal_watch()
        self.bus.connect("message", self.on_message)

    def on_message(self, bus, message):
        t = message.type
        if t == Gst.MessageType.EOS:
            self.player.set_state(Gst.State.NULL)
            # self.button.set_label("Start")
        elif t == Gst.MessageType.ERROR:
            self.player.set_state(Gst.State.NULL)
            err, debug = message.parse_error()
            print("Error: %s" % err, debug)
            # self.button.set_label("Start")
        # else:
        #     print(t)

    def start_video(self, w):
        self.player.set_state(Gst.State.PLAYING)
            
        
    def stop_video(self, w):
        self.player.set_state(Gst.State.NULL)
            

    def increase_fps(self, w):
        if self.fps < 30:
            self.fps += 1
            self.on_fps_changed()
            

    def decrease_fps(self, w):
        if self.fps > 1:
            self.fps -= 1
            self.on_fps_changed()
            

    def on_fps_changed(self):
        # self.caps = Gst.Caps.from_string("video/x-raw, width={}, height={}, framerate={}/1".format(self.width, self.height, self.fps))
        # self.filter.set_property('caps', self.caps)
        self.fps_txt.set_property('text', 'FPS: {}'.format(self.fps))
        self.filtercaps = Gst.Caps.from_string('video/x-raw, framerate={}/1'.format(self.fps))
        self.ratefilter.set_property('caps', self.filtercaps)
        self.fps_inc.set_label("FPS++ ({})".format(self.fps))
        self.fps_dec.set_label("FPS-- ({})".format(self.fps))

Gst.init(None)
MainWindow()
Gtk.main()
