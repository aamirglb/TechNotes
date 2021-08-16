#!/usr/bin/env python3
import sys
import gi
gi.require_version('Gst', '1.0')
from gi.repository import Gst, GObject, GLib

counter = 0

def format_ns(ns):
    s, ns = divmod(ns, 1000000000)
    m, s = divmod(s, 60)
    h, m = divmod(m, 60)

    return "%u:%02u:%02u.%09u" % (h, m, s, ns)

def bus_call(bus, message, loop, pipeline):
    t = message.type
    if t == Gst.MessageType.EOS:
        sys.stdout.write("End-of-stream\n")
        loop.quit()
    elif t == Gst.MessageType.ERROR:
        err, debug = message.parse_error()
        sys.stderr.write("Error: %s: %s\n" % (err, debug))
        loop.quit()
    elif t == Gst.MessageType.DURATION_CHANGED:
        pass
        # the duration has changed, invalidate the current one
        # duration = Gst.CLOCK_TIME_NONE
    elif t == Gst.MessageType.TAG:
        taglist = message.parse_tag()
        for n in range(taglist.n_tags()):
            tag = taglist.nth_tag_name(n)
            print(tag, end=" : ")
            for i in range(taglist.get_tag_size(tag)):
                value = taglist.get_value_index(tag, i)
                print(value, end=", ")
            print("")



    elif t == Gst.MessageType.STATE_CHANGED:
        old_state, new_state, pending_state = message.parse_state_changed()
        if message.src == pipeline:
            print("Pipeline state changed from '{0:s}' to '{1:s}'".format(
                Gst.Element.state_get_name(old_state),
                Gst.Element.state_get_name(new_state)))

            # remember whether we are in the playing state or not
            # self.playing = new_state == Gst.State.PLAYING
    else:
        print("ERROR: Unexpected message received", end=": ")
        print(t)

    return True

def cb_print_position(pipeline):
    global counter
    counter += 1
    ret, current = pipeline.query_position(Gst.Format.TIME)
    if not ret:
        print("ERROR: could not query current position")

    ret, duration = pipeline.query_duration(Gst.Format.TIME)
    if not ret:
        print("ERROR: Could not query stream duration")

    print("Position {0} / {1}".format(format_ns(current), format_ns(duration)))

    # seek every 5 seconds
    if counter % (5 * 5) == 0:
        if (duration - current) > 10 * Gst.SECOND:
            print("Seeking 10s...")
            pipeline.seek_simple(Gst.Format.TIME, 
                                Gst.SeekFlags.FLUSH | Gst.SeekFlags.KEY_UNIT, 
                                current + (10 * Gst.SECOND))

    return True

# References: 
# https://gist.github.com/tylercubell/3bdf6e4ce7691907d1f0175a2d8747c0
# https://github.com/gkralik/python-gst-tutorial/blob/master/basic-tutorial-4.py
def on_pad_added(element, pad, decoder):
    pad_type = pad.get_current_caps().get_structure(0).get_name()
    print('pad_type {}'.format(pad_type))
    pad.link(decoder.get_static_pad('sink'))

def main(args):
    if len(args) != 2:
        sys.stderr.write("usage: %s <media file>\n" % args[0])

    Gst.init(None)

    pipeline = Gst.Pipeline.new('pipeline')
    source   = Gst.ElementFactory.make('filesrc', 'file_source')
    demuxer  = Gst.ElementFactory.make('oggdemux', 'ogg_demuxer')
    decoder  = Gst.ElementFactory.make('vorbisdec', 'vorbis_decoder')
    conv     = Gst.ElementFactory.make('audioconvert', 'converter')
    sink     = Gst.ElementFactory.make('autoaudiosink', 'audio_output')

    # Set properties
    source.set_property('location', args[1])
    pipeline.add(source)
    pipeline.add(demuxer)
    pipeline.add(decoder)
    pipeline.add(conv)
    pipeline.add(sink)

    source.link(demuxer)
    # demuxer.link(decoder)
    decoder.link(conv)
    conv.link(sink)
    
    GLib.timeout_add(200, cb_print_position, pipeline)

    loop = GLib.MainLoop()

    bus = pipeline.get_bus()
    bus.add_signal_watch()
    bus.connect ("message", bus_call, loop, pipeline)
    
    demuxer.connect("pad-added", on_pad_added, decoder)

    # start play back and listed to events
    pipeline.set_state(Gst.State.PLAYING)

    try:
      loop.run()
    except:
      pass
    
    # cleanup
    pipeline.set_state(Gst.State.NULL)

if __name__ == '__main__':
    sys.exit(main(sys.argv))


