#!/usr/bin/env python3
import sys
import random
import gi
gi.require_version('Gst', '1.0')
gi.require_version('Gtk', '3.0')

from gi.repository import GObject, Gst, GLib, Gtk

ball_motion = { 0: 'wavy', 1: 'sweep', 2: 'half-sweep' }

class Source(GObject.Object):
    def __init__(self, channel):
        GObject.Object.__init__(self)

        self.__channel = channel
        self.__fps     = 25
        self.__width   = 640
        self.__height  = 480
        self.__flip_angle = 0

        self.__pipeline = Gst.Pipeline.new('pipeline')

        self.source      = Gst.ElementFactory.make('videotestsrc', 'source')
        clock            = Gst.ElementFactory.make('clockoverlay', 'clock')
        time_overlay     = Gst.ElementFactory.make('timeoverlay', 'timeoverlay')
        self.fps_overlay = Gst.ElementFactory.make('textoverlay', 'textoverlay')
        self.capsfilter  = Gst.ElementFactory.make('capsfilter', 'capsfilter')
        self.videoflip   = Gst.ElementFactory.make('videoflip', 'flip')
        # videorate        = Gst.ElementFactory.make('videorate', 'videorate')
        # self.ratefilter  = Gst.ElementFactory.make('capsfilter', 'ratefilter')
        intervideosink   = Gst.ElementFactory.make('intervideosink', 'intervideosink')

        self.source.set_property('pattern', 0)
        clock.set_property('shaded-background', True)
        self.fps_overlay.set_property('text', 'FPS: {}'.format(self.__fps))
        self.fps_overlay.set_property('shaded-background', True)
        self.fps_overlay.set_property('valignment', 1)
        self.fps_overlay.set_property('halignment', 0)
        time_overlay.set_property('shaded-background', True)
        time_overlay.set_property('valignment', 1)
        time_overlay.set_property('halignment', 1)
        self.videoflip.set_property('video-direction', self.__flip_angle)
        intervideosink.set_property('channel', self.__channel)

        self.__pipeline.add(self.source)
        self.__pipeline.add(self.capsfilter)
        self.__pipeline.add(clock)
        self.__pipeline.add(self.fps_overlay)
        self.__pipeline.add(time_overlay)
        self.__pipeline.add(self.videoflip)
        # self.__pipeline.add(videorate)
        # self.__pipeline.add(self.ratefilter)
        self.__pipeline.add(intervideosink)

        self.source.link(self.capsfilter)
        self.capsfilter.link(clock)
        clock.link(self.fps_overlay)
        self.fps_overlay.link(time_overlay)
        time_overlay.link(self.videoflip)
        self.videoflip.link(intervideosink)
        # self.videoflip.link(self.ratefilter)
        # self.ratefilter.link(intervideosink)

        bus = self.__pipeline.get_bus()
        bus.add_signal_watch()
        bus.connect('message', self.bus_callback)

    def bus_callback(self, bus, msg):
        if msg.type == Gst.MessageType.STATE_CHANGED:
            (oldstate, newstate, pending) = msg.parse_state_changed()
            if msg.src == self.__pipeline:
                print('{0}: state changed {1} -> {2}, pending {3}'.format(msg.src.name, 
                            Gst.Element.state_get_name(oldstate),
                            Gst.Element.state_get_name(newstate),
                            Gst.Element.state_get_name(pending)))

                if newstate == Gst.State.PLAYING:
                    print('pipeline started')
                elif oldstate == Gst.State.PLAYING:
                    print('pipeline stopped')
        elif msg.type == Gst.MessageType.WARNING:
            (err, debug) = msg.parse_error()
            print('WARNING: {0}: {1}'.format(err, debug))
        elif msg.type == Gst.MessageType.ERROR:
            (err, debug) = msg.parse_error()
            print('ERROR: {0}: {1}'.format(err, debug))
        return True

    def start(self, res):
        w, h = res.split('x')
        self.__width, self.__height = int(w), int(h)
        caps = Gst.Caps.from_string('video/x-raw,width={},height={},framerate={}/1'.format(
                                self.__width, self.__height, self.__fps))
        self.capsfilter.set_property('caps', caps)
        # self.ratefilter.set_property('caps', caps)
        self.__pipeline.set_state(Gst.State.PLAYING)

    def pause(self):
        self.__pipeline.set_state(Gst.State.PAUSED)

    def stop(self):
        self.__pipeline.set_state(Gst.State.NULL)

    def flip(self):
        self.__flip_angle += 1
        if self.__flip_angle >= 4:
            self.__flip_angle = 0
        print("Flipping video by: {}\xB0".format(self.__flip_angle*90))
        self.videoflip.set_property('video-direction', self.__flip_angle)

    def change_pattern(self, pattern):
        global ball_motion
        self.source.set_property("pattern", pattern)
        if pattern == 14:
            self.source.set_property('kyt', 0x7fffffff)
        elif pattern == 18:
            self.source.set_property('background-color', 0xffff0000) 
            self.source.set_property('foreground-color', 0x00ffff00)
            motion = random.randint(0, 2)
            self.source.set_property('motion', motion)
            print('Setting ball motion to "{}"'.format(ball_motion[motion].upper()) )
        else:
            self.source.set_property('background-color', 0xff000000) 
            self.source.set_property('foreground-color', 0xffffffff)

    # def change_resolution(self, resolution):
    #     w, h = resolution.split('x')
    #     self.__width, self.__height = int(w), int(h)
    #     caps = Gst.Caps.from_string('video/x-raw,width={},height={},framerate={}/1'.format(
    #                             self.__width, self.__height, self.__fps))
    #     self.ratefilter.set_property('caps', caps)

class Streamer:
    def __init__(self, channel):
        self.__pipeline = Gst.Pipeline.new('pipeline')
        self.channel = channel
        videosource      = Gst.ElementFactory.make('intervideosrc', 'videosrc')
        converter        = Gst.ElementFactory.make('videoconvert', 'converter')
        videorate        = Gst.ElementFactory.make('videorate', 'videorate')
        self.ratefilter  = Gst.ElementFactory.make('capsfilter', 'ratefilter')

        sink        = Gst.ElementFactory.make('autovideosink', 'sink')

        videosource.set_property('channel', self.channel)
        self.__pipeline.add(videosource)
        self.__pipeline.add(converter)
        self.__pipeline.add(videorate)
        self.__pipeline.add(self.ratefilter)
        self.__pipeline.add(sink)

        videosource.link(converter)
        converter.link(videorate)
        videorate.link(self.ratefilter)
        self.ratefilter.link(sink)

    def start(self):
        self.__pipeline.set_state(Gst.State.PLAYING)

    def pause(self):
        self.__pipeline.set_state(Gst.State.PAUSED)

    def stop(self):
        self.__pipeline.set_state(Gst.State.NULL)

    def change_resolution(self, resolution):
        w, h = resolution.split('x')
        self.__width, self.__height = int(w), int(h)
        caps = Gst.Caps.from_string('video/x-raw,width={},height={},framerate={}/1'.format(
                                self.__width, self.__height, self.__fps))
        self.ratefilter.set_property('caps', caps)

class Snapshoter:
    def __init__(self, channel):
        self.channel = channel
        self.__pipeline = Gst.Pipeline.new('snap_pipeline')

        videosource = Gst.ElementFactory.make('intervideosrc', 'videosource')
        videosource.set_property('channel', self.channel)
        encoder = Gst.ElementFactory.make('jpegenc', 'encoder')
        encoder.set_property('snapshot', True)
        self.filesink = Gst.ElementFactory.make('filesink', 'filesink')

        self.__pipeline.add(videosource)
        self.__pipeline.add(encoder)
        self.__pipeline.add(self.filesink)

        videosource.link(encoder)
        encoder.link(self.filesink)

        bus = self.__pipeline.get_bus()
        bus.add_signal_watch()
        bus.connect('message', self.bus_callback)

    def bus_callback(self, bus, msg):
        if msg.type == Gst.MessageType.EOS:
            print('Got EOS')
            self.__pipeline.set_state(Gst.State.NULL)
        return True

    def __update_file_location(self):
        self.filesink.set_property('location', self.__filepath)

    def start(self, path):
        self.__filepath = path
        (change, state, pending) = self.__pipeline.get_state(0)
        print('Snapshoter-start: state {0}: {1} -> {2}'.format(Gst.Element.state_change_return_get_name(change),
                                            Gst.Element.state_get_name(state),
                                            Gst.Element.state_get_name(pending)))
        if change == Gst.StateChangeReturn.SUCCESS or change == Gst.StateChangeReturn.NO_PREROLL:
            if state == Gst.State.NULL:
                self.__update_file_location()
                self.__pipeline.set_state(Gst.State.PLAYING)
           
class Manager(Gtk.Window):
    def __init__(self):
        super().__init__(title="GStreamer")
        self.connect('destroy', Gtk.main_quit)
        self.__paused = False

        vbox = Gtk.VBox(spacing=6)
        self.add(vbox)

        self.patterns = [
            "smpte",              "snow",        "black",       "white",
            "red",                "green",       "blue",        "checkers-1",
            "checkers-2",         "checkers-4",  "checkers-8",  "circular",
            "blink",              "smpte75",     "zone-plate",  "gamut",
            "chroma-zone-plate",  "solid-color", "ball",        "smpte100",
            "bar",                "pinwheel",    "spokes",      "gradient",
            "colors",
        ]

        self.pattern_combo = Gtk.ComboBoxText()
        self.pattern_combo.set_entry_text_column(0)        
        for pattern in self.patterns:
            self.pattern_combo.append_text(pattern)

        self.pattern_combo.set_active(0)

        self.resolutions = [
                "320x240",
                "640x480",
                "720x480",
                "1024x768",
                "1920x1080",
         ]
        
        self.resolution_combo = Gtk.ComboBoxText()
        self.resolution_combo.set_entry_text_column(0)
        
        for res in self.resolutions:
            self.resolution_combo.append_text(res)

        self.start = Gtk.Button(label='Start')
        self.start.connect('clicked', self.on_start_click)
        self.pause = Gtk.Button(label='Pause')
        self.pause.connect('clicked', self.on_pause_click)
        self.pause.set_sensitive(False)
        self.stop = Gtk.Button(label='Stop')
        self.stop.connect('clicked', self.on_stop_click)
        self.stop.set_sensitive(False)
        self.rotate = Gtk.Button(label="Rotate(+90\xB0)")
        self.rotate.connect('clicked', self.on_rotate_click)
        self.rotate.set_sensitive(False)
        self.snapshot = Gtk.Button(label='Snapshot')
        self.snapshot.connect('clicked', self.on_snapshot_click)
        self.snapshot.set_sensitive(False)

        vbox.add(self.pattern_combo)
        vbox.add(self.resolution_combo)
        vbox.add(self.start)
        vbox.add(self.pause)
        vbox.add(self.stop)
        vbox.add(self.rotate)
        vbox.add(self.snapshot)
        self.show_all()

        self.pattern_combo.connect("changed", self.on_pattern_changed)
        self.resolution_combo.connect('changed', self.on_resolution_changed)
        self.resolution_combo.set_active(1)

    def on_start_click(self, widget):
        if self.__paused:
            self.streamer.start()
            self.source.start(self.resolution_combo.get_active_text())
            self.__paused = False
        else:
            # Starting for the first time
            self.source = Source('vid0')
            self.source.start(self.resolution_combo.get_active_text())
            self.streamer = Streamer('vid0')
            self.streamer.start()
            self.snap = Snapshoter('vid0')
            self.imgidx = 0
        self.start.set_sensitive(False)
        self.pause.set_sensitive(True)
        self.stop.set_sensitive(True)
        self.rotate.set_sensitive(True)
        self.snapshot.set_sensitive(True)

    def on_pause_click(self, widget):
        self.source.pause()
        self.streamer.pause()
        self.__paused = True
        self.pause.set_sensitive(False)
        self.start.set_sensitive(True)

    def on_stop_click(self, widget):
        self.source.stop()
        self.streamer.stop()
        self.start.set_sensitive(True)
        self.pause.set_sensitive(False)
        self.stop.set_sensitive(False)
        self.rotate.set_sensitive(False)
        self.snapshot.set_sensitive(False)
        self.__paused = False

    def on_pattern_changed(self, combo):
        self.source.change_pattern(combo.get_active())
    
    def on_resolution_changed(self, combo):
        self.streamer.change_resolution(combo.get_active_text())

    def on_snapshot_click(self, widget):
        self.imgidx += 1
        self.snap.start('test_img_{0:02}.jpeg'.format(self.imgidx))

    def on_rotate_click(self, widget):
        self.source.flip()

def main(args):
    Gst.init(None)
    Manager()
    Gtk.main()

if __name__ == '__main__':
    sys.exit(main(sys.argv))
        

