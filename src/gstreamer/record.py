#!/usr/bin/env python3
import gi
gi.require_version('Gst', '1.0')
gi.require_version('Gtk', '3.0')

from gi.repository import Gst, Gtk, GObject, GLib

# gst-launch-1.0 videotestsrc ! tee name=t t. ! queue ! video/x-raw,width=640,height=480,framerate=30/1 \
# ! timeoverlay ! autovideosink t. ! queue ! video/x-raw,width=640,height=480 ! timeoverlay ! videorate \
# ! video/x-raw,framerate=1/1 ! videoconvert ! jpegenc ! multifilesink location="frame-%03d.jpeg"

class MainWindow(Gtk.Window):
    def __init__(self):
        super().__init__(title="GStreamer")
        self.connect('destroy', Gtk.main_quit)
        vbox = Gtk.VBox(spacing=6)
        self.add(vbox)

        self.start = Gtk.Button(label='Start')
        self.start.connect('clicked', self.start_video)
        self.snapshot = Gtk.Button(label='Snapshot')
        self.snapshot.connect('clicked', self.on_snapshot_click)

        vbox.add(self.start)
        vbox.add(self.snapshot)
        self.show_all()

        self.imgidx = 0
        self.pipeline      = Gst.Pipeline.new('pipeline')
        self.source        = Gst.ElementFactory.make('videotestsrc', 'source')
        self.timestamp     = Gst.ElementFactory.make('timeoverlay', 'timestamp')
        self.tee           = Gst.ElementFactory.make('tee', 'tee')
        self.q1            = Gst.ElementFactory.make('queue', 'q1')
        self.q2            = Gst.ElementFactory.make('queue', 'q2')
        self.sink          = Gst.ElementFactory.make('autovideosink', 'sink')
        self.srccapsfilter = Gst.ElementFactory.make('capsfilter')

        self.timestamp2    = Gst.ElementFactory.make('timeoverlay', 't2')
        self.videorate     = Gst.ElementFactory.make('videorate', 'videorate')
        self.ratefilter    = Gst.ElementFactory.make('capsfilter')
        self.converter     = Gst.ElementFactory.make('videoconvert')
        self.jpegenc       = Gst.ElementFactory.make('jpegenc')
        # self.filesink = Gst.ElementFactory.make('multifilesink', 'filesink')
        self.filesink = Gst.ElementFactory.make('filesink', 'filesink')

        # Set caps and properties
        self.srccaps = Gst.Caps.from_string('video/x-raw,width=640,height=480,framerate=30/1')
        self.srccapsfilter.set_property('caps', self.srccaps)
        self.timestamp.set_property('shaded-background', True)

        self.ratefiltercaps = Gst.Caps.from_string('video/x-raw,framerate=1/1')
        self.ratefilter.set_property('caps', self.ratefiltercaps)
        self.filesink.set_property('location', 'img-{0:03d}.jpeg'.format(self.imgidx))

        self.pipeline.add(self.source)
        self.pipeline.add(self.tee)
        self.pipeline.add(self.q1)
        self.pipeline.add(self.q2)
        self.pipeline.add(self.timestamp)
        self.pipeline.add(self.sink)
        self.pipeline.add(self.srccapsfilter)

        self.pipeline.add(self.timestamp2)
        self.pipeline.add(self.videorate)
        self.pipeline.add(self.ratefilter)
        self.pipeline.add(self.converter)
        self.pipeline.add(self.jpegenc)
        # self.pipeline.add(self.filesink)

        self.source.link(self.srccapsfilter)
        self.srccapsfilter.link(self.timestamp)
        # self.tee.link(self.q1)
        # self.q1.link(self.timestamp)
        self.timestamp.link(self.sink)

        # self.tee.link(self.q2)
        # self.q2.link(self.timestamp2)
        # self.timestamp2.link(self.videorate)
        # self.videorate.link(self.ratefilter)
        # self.ratefilter.link(self.converter)
        # self.converter.link(self.jpegenc)
        # self.jpegenc.link(self.filesink)

        self.bus = self.pipeline.get_bus()
        self.bus.add_signal_watch()
        self.bus.connect("message", self.on_message)

    def start_video(self, widget):
        self.pipeline.set_state(Gst.State.PLAYING)

    def on_snapshot_click(self, widget):
        if self.imgidx == 0:
            self.pipeline.add(self.filesink)
            self.filesink.sync_state_with_parent()
            
            # create a new tee src pad for image capture
            pad = Gst.Element.get_request_pad(self.tee, 'src_%u')
            name = Gst.Pad.get_name(pad)
            print('pad name: {}'.format(name))
            q2_pad = Gst.Element.get_static_pad(self.q2, 'sink')
            pad.link(q2_pad)
            self.q2.link(self.converter)
            self.converter.link(self.jpegenc)
            self.jpegenc.link(self.filesink)
            
            print('Check the image...')
        self.imgidx += 1
        
        # gst_element_get_static_pad (audio_queue, "sink");

        
        
        # self.pipeline.remove(self.filesink)
        
    def on_message(self, bus, message):
        t = message.type
        print('Received Message: ', t)
        if t == Gst.MessageType.EOS:
            self.pipeline.set_state(Gst.State.NULL)
            # self.button.set_label("Start")
        elif t == Gst.MessageType.ERROR:
            self.pipeline.set_state(Gst.State.NULL)
            err, debug = message.parse_error()
            print("Error: %s" % err, debug)
            # self.button.set_label("Start")
        # else:
        #     print(t)

#          gst_element_request_pad_simple (tee, "src_%u");
#   g_print ("Obtained request pad %s for audio branch.\n", gst_pad_get_name (tee_audio_pad));
#   queue_audio_pad = gst_element_get_static_pad (audio_queue, "sink");
#   tee_video_pad = gst_element_request_pad_simple (tee, "src_%u");
#   g_print ("Obtained request pad %s for video branch.\n", gst_pad_get_name (tee_video_pad));
#   queue_video_pad = gst_element_get_static_pad (video_queue, "sink");
#   if (gst_pad_link (tee_audio_pad, queue_audio_pad) != GST_PAD_LINK_OK ||
#       gst_pad_link (tee_video_pad, queue_video_pad) != GST_PAD_LINK_OK) {
#     g_printerr ("Tee could not be linked.\n");
#     gst_object_unref (pipeline);
#     return -1;
#   }
        # self.filesink.set_property('location', 'img-{:03d}.jpeg'.format(self.imgidx))

        # self.tee.link(self.q2)
        # self.q2.link(self.timestamp2)
        # self.timestamp2.link(self.videorate)
        # self.videorate.link(self.ratefilter)
        # self.ratefilter.link(self.converter)
        # self.converter.link(self.jpegenc)
        # self.jpegenc.link(self.filesink)

Gst.init(None)
MainWindow()
Gtk.main()