#!/usr/bin/env python3
import gi
gi.require_version('Gst', '1.0')
gi.require_version('Gtk', '3.0')
from gi.repository import Gst, GObject, Gtk

class GTKMain(Gtk.Window):
    def __init__(self):
        super().__init__(title="videotestsrc-players")
        self.connect('destroy', Gtk.main_quit, "WM destroy")
        vbox = Gtk.VBox(spacing=6)
        self.add(vbox)

        self.fps = 30
        self.width = 640
        self.height = 480

        patterns = [
            "smpte",
            "snow",
            "black",
            "white",
            "red",
            "green",
            "blue",
            "checkers-1",
            "checkers-2",
            "checkers-4",
            "checkers-8",
            "circular",
            "blink",
            "smpte75",
            "zone-plate",
            "gamut",
            "chroma-zone-plate",
            "solid-color",
            "ball",
            "smpte100",
            "bar",
            "pinwheel",
            "spokes",
            "gradient",
            "colors",
        ]
        self.pattern_combo = Gtk.ComboBoxText()
        self.pattern_combo.set_entry_text_column(0)        
        for pattern in patterns:
            self.pattern_combo.append_text(pattern)

        self.pattern_combo.set_active(0)
        # vbox.pack_start(self.pattern_combo, False, False, 0)

        resolutions = [
                "320x240",
                "640x480",
                "1024x768",
                "1920x1080",
         ]
        
        self.resolution_combo = Gtk.ComboBoxText()
        self.resolution_combo.set_entry_text_column(0)
        
        for r in resolutions:
            self.resolution_combo.append_text(r)

        self.start = Gtk.Button(label="Start")
        self.start.connect("clicked", self.start_video)
        self.stop = Gtk.Button(label="Stop")
        self.stop.connect("clicked", self.stop_video)
        self.pause = Gtk.Button(label="Pause")
        self.pause.connect("clicked", self.pause_video)
        self.rotate = Gtk.Button(label="Rotate(+90\xB0)")
        self.rotate.connect("clicked", self.rotate_video)
        self.fps_inc = Gtk.Button(label="FPS++ ({})".format(self.fps))
        self.fps_inc.connect("clicked", self.increase_fps)
        self.fps_dec = Gtk.Button(label="FPS-- ({})".format(self.fps))
        self.fps_dec.connect("clicked", self.decrease_fps)

        vbox.add(self.pattern_combo)
        vbox.add(self.resolution_combo)
        vbox.add(self.start)
        vbox.add(self.pause)
        vbox.add(self.stop)
        vbox.add(self.rotate)
        vbox.add(self.fps_inc)
        vbox.add(self.fps_dec)

        self.state = 'stopped'        
        self.show_all()

        self.player = Gst.Pipeline.new('player')
        self.source = Gst.ElementFactory.make('videotestsrc', 'video-source')
        # self.source = Gst.ElementFactory.make('v4l2src', 'video-source')
        # self.source.set_property('device', '/dev/video0')
        self.sink = Gst.ElementFactory.make('autovideosink', 'videororation-output')
        self.caps = Gst.Caps.from_string("video/x-raw, width={}, height={}, framerate={}/1".format(self.width, self.height, self.fps))
        self.filter = Gst.ElementFactory.make("capsfilter", "filter")
        self.filter.set_property('caps', self.caps)
        self.overlay = Gst.ElementFactory.make('timeoverlay', 'overlay')
        self.overlay.set_property('shaded-background', True)
        self.flip = Gst.ElementFactory.make('videoflip', 'flip')
        self.rotation = 0
        self.flip.set_property('video-direction', self.rotation)
        
        self.fps_txt = Gst.ElementFactory.make('textoverlay', 'textoverlay')
        self.fps_txt.set_property('text', 'FPS: {}'.format(self.fps))
        self.fps_txt.set_property('shaded-background', True)
        self.fps_txt.set_property('valignment', 1)
        self.fps_txt.set_property('halignment', 0)


        self.player.add(self.source)
        self.player.add(self.filter)
        self.player.add(self.overlay)
        self.player.add(self.fps_txt)
        self.player.add(self.flip)
        self.player.add(self.sink)

        self.source.link(self.filter)
        self.filter.link(self.flip)
        self.flip.link(self.overlay)
        self.overlay.link(self.fps_txt)
        self.fps_txt.link(self.sink)

        self.bus = self.player.get_bus()
        self.bus.add_signal_watch()
        self.bus.connect("message", self.on_message)

        self.pattern_combo.connect("changed", self.on_pattern_changed)
        self.resolution_combo.connect('changed', self.on_resolution_changed)
        self.resolution_combo.set_active(1)
        # @GObject.Signal
        # def fps_changed(self):
        #     print('fps_changed signal')

        # self.connect('fps_changed', self.on_fps_changed)

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
        if self.state == 'stopped' or self.state == 'paused':
            self.player.set_state(Gst.State.PLAYING)
            self.state = 'started'
        
    def stop_video(self, w):
        if self.state == 'started' or self.state == 'paused':
            self.player.set_state(Gst.State.NULL)
            self.state = 'stopped'

    def pause_video(self, w):
        if self.state == 'started':
            self.player.set_state(Gst.State.PAUSED)
            self.state = 'paused'
        

    def rotate_video(self, w):
        self.rotation += 1
        if self.rotation >= 4:
            self.rotation = 0
        print("Flipping video by: {}\xB0".format(self.rotation*90))
        self.flip.set_property('video-direction', self.rotation)

    def increase_fps(self, w):
        if self.fps < 30:
            self.fps += 1
            self.on_fps_changed()
            

    def decrease_fps(self, w):
        if self.fps > 1:
            self.fps -= 1
            self.on_fps_changed()
            

    def on_fps_changed(self):
        self.caps = Gst.Caps.from_string("video/x-raw, width={}, height={}, framerate={}/1".format(self.width, self.height, self.fps))
        self.filter.set_property('caps', self.caps)
        self.fps_txt.set_property('text', 'FPS: {}'.format(self.fps))
        self.fps_inc.set_label("FPS++ ({})".format(self.fps))
        self.fps_dec.set_label("FPS-- ({})".format(self.fps))

    def on_pattern_changed(self, combo):
        self.source.set_property("pattern", self.pattern_combo.get_active())

    def on_resolution_changed(self, combo):
        r = combo.get_active_text()
        w, h = r.split('x')
        self.width, self.height = int(w), int(h)
        # self.resize(self.width, self.height)
        self.caps = Gst.Caps.from_string("video/x-raw, width={}, height={}, framerate={}/1".format(self.width, self.height, self.fps))
        self.filter.set_property('caps', self.caps)

Gst.init(None)
GTKMain()
Gtk.main()
