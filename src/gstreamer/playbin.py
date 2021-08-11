#!/usr/bin/env python3
import gi
gi.require_version('Gst', '1.0')
from gi.repository import Gst

Gst.init(None)

pb = Gst.ElementFactory.make('playbin', 'playbin')
assert pb
print(pb)