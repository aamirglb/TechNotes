#!/usr/bin/env python3
import sys
import gi
import logging

gi.require_version("GLib", "2.0")
gi.require_version("GObject", "2.0")
gi.require_version("Gst", "1.0")

from gi.repository import Gst, GLib, GObject


logging.basicConfig(level=logging.DEBUG, format="[%(name)s] [%(levelname)8s] - %(message)s")
logger = logging.getLogger(__name__)

# Initialize GStreamer
Gst.init(sys.argv[1:])

if len(sys.argv) > 1:
    _framerate = sys.argv[1]
else:
    _framerate = 1

# Working GStreamer pipeline using gst-launch
#
# gst-launch-1.0 -v v4l2src device=/dev/video1 \
# ! video/x-raw,width=640,height=480,framerate=30/1 \
# !  videoconvert \
# ! timeoverlay \
# ! videorate \
# ! video/x-raw,framerate=1/1 \
# ! xvimagesink
#

# Create the elements
source = Gst.ElementFactory.make("v4l2src", "source")
caps_filter = Gst.ElementFactory.make("capsfilter", "filter")
caps_filter.props.caps = Gst.caps_from_string('video/x-raw,width=640,height=480,framerate=30/1')
overlay = Gst.ElementFactory.make("timeoverlay", "overlay")
vrate = Gst.ElementFactory.make("videorate", "vrate")
vrate_caps_filter = Gst.ElementFactory.make("capsfilter", "ratefilter")
vrate_caps_filter.props.caps = Gst.caps_from_string(f'video/x-raw,framerate={_framerate}/1')

# self._capsfilter.set_property('caps', gst.Caps(self._getCapsString()))
# src_caps = Gst.caps_from_string('video/x-raw,width=640,height=480,framerate=30/1')
# source.set_property('')
# self._capsfilter.set_property('caps', gst.Caps(self._getCapsString()))

convert = Gst.ElementFactory.make("videoconvert", "convert")
sink = Gst.ElementFactory.make("autovideosink", "sink")

# Create the empty pipeline
pipeline = Gst.Pipeline.new("test-pipeline")

if not pipeline or not source or not convert or not sink:
    logger.error("Not all elements could be created.")
    sys.exit(1)


# Build the pipeline
pipeline.add(source)
pipeline.add(caps_filter)
pipeline.add(convert)
pipeline.add(overlay)
pipeline.add(vrate)
pipeline.add(vrate_caps_filter)
pipeline.add(sink)

if not source.link(caps_filter):
    logger.error("Elements could not be linked.")
    sys.exit(1)

if not caps_filter.link(convert):
    logger.error("Element could not be linked.")
    sys.exit(1)

if not convert.link(overlay):
    logger.error("Element could not be linked.")
    sys.exit(1)

if not overlay.link(vrate):
    logger.error("Element could not be linked.")
    sys.exit(1)

if not vrate.link(vrate_caps_filter):
    logger.error("Element could not be linked.")
    sys.exit(1)

if not vrate_caps_filter.link(sink):
    logger.error("Element could not be linked.")
    sys.exit(1)

# Modify the source's properties
source.props.device = '/dev/video0'
overlay.set_property("shaded-background", True)

# Can alternatively be done using `source.set_property("pattern",0)`
# or using `Gst.util_set_object_arg(source, "pattern", 0)`

# Start playing
ret = pipeline.set_state(Gst.State.PLAYING)
if ret == Gst.StateChangeReturn.FAILURE:
    logger.error("Unable to set the pipeline to the playing state.")
    sys.exit(1)

# Wait for EOS or error
bus = pipeline.get_bus()
msg = bus.timed_pop_filtered(Gst.CLOCK_TIME_NONE, Gst.MessageType.ERROR | Gst.MessageType.EOS)

# Parse message
if msg:
    if msg.type == Gst.MessageType.ERROR:
        err, debug_info = msg.parse_error()
        logger.error(f"Error received from element {msg.src.get_name()}: {err.message}")
        logger.error(f"Debugging information: {debug_info if debug_info else 'none'}")
    elif msg.type == Gst.MessageType.EOS:
        logger.info("End-Of-Stream reached.")
    else:
        # This should not happen as we only asked for ERRORs and EOS
        logger.error("Unexpected message received.")

pipeline.set_state(Gst.State.NULL)