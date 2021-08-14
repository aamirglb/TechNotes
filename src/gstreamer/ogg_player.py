#!/usr/bin/env python3
import sys
import gi
gi.require_version('Gst', '1.0')
from gi.repository import Gst, GObject, GLib

def bus_call(bus, message, loop):
    t = message.type
    if t == Gst.MessageType.EOS:
        sys.stdout.write("End-of-stream\n")
        loop.quit()
    elif t == Gst.MessageType.ERROR:
        err, debug = message.parse_error()
        sys.stderr.write("Error: %s: %s\n" % (err, debug))
        loop.quit()
    else:
        print(t)
    return True

# Reference: https://gist.github.com/tylercubell/3bdf6e4ce7691907d1f0175a2d8747c0
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
    
    loop = GLib.MainLoop()

    bus = pipeline.get_bus()
    bus.add_signal_watch()
    bus.connect ("message", bus_call, loop)
    
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


