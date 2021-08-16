#!/usr/bin/env python3
import gi
gi.require_version('Gst', '1.0')
gi.require_version('Gtk', '3.0')

from gi.repository import Gst, Gtk, GObject, GLib

# gst-launch-1.0 videotestsrc ! tee name=t t. ! queue ! video/x-raw,width=640,height=480,framerate=30/1 \
# ! timeoverlay ! autovideosink t. synch=false ! queue ! video/x-raw,width=640,height=480 ! timeoverlay ! videorate \
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

        self.recording = False
        self.imgidx = 0
        self.pipeline      = Gst.Pipeline.new('pipeline')
        self.source        = Gst.ElementFactory.make('videotestsrc', 'source')
        self.timestamp     = Gst.ElementFactory.make('timeoverlay', 'timestamp')
        self.tee           = Gst.ElementFactory.make('tee', 'tee')
        self.q1            = Gst.ElementFactory.make('queue', 'q1')
        self.sink          = Gst.ElementFactory.make('autovideosink', 'sink')
        self.srccapsfilter = Gst.ElementFactory.make('capsfilter')

        self.recbin        = Gst.Bin.new('recording_bin')
        self.q2            = Gst.ElementFactory.make('queue', 'q2')
        self.encoder       = Gst.ElementFactory.make('x264enc', 'encoder')
        self.muxer         = Gst.ElementFactory.make('mpegtsmux', 'muxer')
        self.filesink      = Gst.ElementFactory.make('filesink', 'filesink')
        
        # self.converter     = Gst.ElementFactory.make('videoconvert')
        self.recbin.add(self.q2)
        self.recbin.add(self.encoder)
        self.recbin.add(self.muxer)
        self.recbin.add(self.filesink)

        # create a ghost pad for recording bin
        pad = Gst.Element.get_static_pad(self.q2, 'sink')
        self.ghost_pad = Gst.GhostPad.new('sink', pad)
        self.ghost_pad.set_active(True)
        self.recbin.add_pad(self.ghost_pad)

        self.q2.link(self.encoder)
        self.encoder.link(self.muxer)
        self.muxer.link(self.filesink)

        # Set caps and properties
        self.srccaps = Gst.Caps.from_string('video/x-raw,width=640,height=480,framerate=30/1')
        self.srccapsfilter.set_property('caps', self.srccaps)
        self.timestamp.set_property('shaded-background', True)

        # self.ratefiltercaps = Gst.Caps.from_string('video/x-raw,framerate=1/1')
        # self.ratefilter.set_property('caps', self.ratefiltercaps)
        # self.filesink.set_property('location', 'img-{0:03d}.jpeg'.format(self.imgidx))

        self.pipeline.add(self.source)
        self.pipeline.add(self.tee)
        self.pipeline.add(self.q1)
        self.pipeline.add(self.timestamp)
        self.pipeline.add(self.sink)
        self.pipeline.add(self.srccapsfilter)

        self.source.link(self.srccapsfilter)
        self.srccapsfilter.link(self.timestamp)
        self.timestamp.link(self.tee)
        self.tee.link(self.q1)
        self.q1.link(self.sink)

        self.bus = self.pipeline.get_bus()
        self.bus.add_signal_watch()
        self.bus.connect("message", self.on_message)

    def start_video(self, widget):
        self.pipeline.set_state(Gst.State.PLAYING)

    def pad_probe_cb(self, pad, info):
        print("pad blocked")
        Gst.Pad.remove_probe(pad, info.id)
        # Gst.Pad.send_event(pad, Gst.Event.new_eos())

        return Gst.PadProbeReturn.OK

# stPad * pad, GstPadProbeInfo * info, gpointer user_data)
# {
#   GstPad *srcpad, *sinkpad;

#   GST_DEBUG_OBJECT (pad, "pad is blocked now");

#   /* remove the probe first */
#   gst_pad_remove_probe (pad, GST_PAD_PROBE_INFO_ID (info));

#   /* install new probe for EOS */
#   srcpad = gst_element_get_static_pad (cur_effect, "src");
#   gst_pad_add_probe (srcpad, GST_PAD_PROBE_TYPE_BLOCK |
#       GST_PAD_PROBE_TYPE_EVENT_DOWNSTREAM, event_probe_cb, user_data, NULL);
#   gst_object_unref (srcpad);

#   /* push EOS into the element, the probe will be fired when the
#    * EOS leaves the effect and it has thus drained all of its data */
#   sinkpad = gst_element_get_static_pad (cur_effect, "sink");
#   gst_pad_send_event (sinkpad, gst_event_new_eos ());
#   gst_object_unref (sinkpad);

#   return GST_PAD_PROBE_OK;

    def on_snapshot_click(self, widget):
        # if recording not started
        if not self.recording:
            self.imgidx += 1
            self.filesink.set_property('location', 'testvideo-{0:02}.mp4'.format(self.imgidx))
            print("Starting recording 'testvideo-{0:02}.mp4'".format(self.imgidx))
            self.recbin.set_state(Gst.State.PAUSED)
            self.pipeline.add(self.recbin)

            pad = Gst.Element.get_request_pad(self.tee, 'src_%u')
            bin_pad = Gst.Element.get_static_pad(self.recbin, 'sink')
            pad.link(bin_pad)
            self.recbin.set_state(Gst.State.PLAYING)
            self.recording = True
        else:
            # stop recording
            self.recording = False
            pad = Gst.Element.get_static_pad(self.tee, 'src_1')
            bin_pad = Gst.Element.get_static_pad(self.recbin, 'sink')
            pad.add_probe(Gst.PadProbeType.BLOCK_DOWNSTREAM, self.pad_probe_cb)
            self.recbin.set_state(Gst.State.NULL)
            pad.unlink(bin_pad)
            self.pipeline.remove(self.recbin)
            
        
    def on_message(self, bus, message):
        t = message.type
        if t == Gst.MessageType.EOS:
            self.pipeline.set_state(Gst.State.NULL)
            # self.button.set_label("Start")
        elif t == Gst.MessageType.ERROR:
            self.pipeline.set_state(Gst.State.NULL)
            err, debug = message.parse_error()
            print("Error: %s" % err, debug)
            # self.button.set_label("Start")
        elif t == Gst.MessageType.STATE_CHANGED:
            old_state, new_state, pending_state = message.parse_state_changed()
            print("Pipeline state changed from '{0:s}' to '{1:s}'".format(
                Gst.Element.state_get_name(old_state),
                Gst.Element.state_get_name(new_state)))
        else:
            pass


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