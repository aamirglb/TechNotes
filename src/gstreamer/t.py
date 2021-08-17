#!/usr/bin/env python3
import sys
import gi
gi.require_version('Gst', '1.0')
gi.require_version('Gtk', '3.0')
from gi.repository import Gst, GObject, GLib

class Source:
    def __init__(self, name):
        self.name = name
        self.pipeline = Gst.Pipeline.new('new_pipe')
        source = Gst.ElementFactory.make('videotestsrc', 'source')
    
    def display(self):
        print('Class Name: {}'.format(self.name))


def main(args):
    Gst.init(None)
    s = Source('src1')
    s.display()


if __name__ == '__main__':
    main(sys.argv)