#!/usr/bin/env python3
'''
This script stream all 24 test pattern using RTSP server.
To listen to a particular stream use the following command:

# smpte pattern
gst-launch-1.0 rtspsrc location=rtsp://127.0.0.1:8554/stream0 latency=300 ! decodebin ! autovideosink

# ball pattern
gst-launch-1.0 rtspsrc location=rtsp://127.0.0.1:8554/stream0 latency=300 ! decodebin ! autovideosink

# web cam
gst-launch-1.0 rtspsrc location=rtsp://127.0.0.1:8554/webcam latency=0 ! decodebin ! autovideosink

# web cam - display and record
gst-launch-1.0 -e rtspsrc location=rtsp://192.168.x.x:8554/webcam latency=0 ! tee name=t t. 
    ! queue ! decodebin ! autovideosink t. ! queue ! rtph264depay ! mpegtsmux ! filesink location=test_video.mp4
etc
'''

import gi

gi.require_version('Gst', '1.0')
gi.require_version('GstRtspServer', '1.0')
from gi.repository import Gst, GstRtspServer, GObject, GLib

loop = GLib.MainLoop()
Gst.init(None)

# class TestRtspMediaFactory(GstRtspServer.RTSPMediaFactory):
#     def __init__(self) -> None:
#         GstRtspServer.RTSPMediaFactory.__init__(self)
#
#     def do_create_element(self, url):
#         src_demux = 'filesrc location=/home/aamir/Videos/dog.mp4 ! qtdemux name=demux'
#         h264_transcode = 'demux.video_0'
#         pipeline = '{0} {1} ! queue ! rtph264pay name=pay0 config-interval=1 pt=96'.format(src_demux, h264_transcode)
#         print('Element created ' + pipeline)
#         return Gst.parse_launch(pipeline)

class TestRtspMediaFactory(GstRtspServer.RTSPMediaFactory):
    def __init__(self, pattern=0):
        GstRtspServer.RTSPMediaFactory.__init__(self)
        self.pattern = pattern

    def do_create_element(self, url):
        if self.pattern == 18:
            self.pattern = '{} background-color=0x00ff0000 flip=1'.format(self.pattern)
        pipeline = 'videotestsrc pattern={} ! video/x-raw,width=1024,height=768,framerate=25/1 ! \
            timeoverlay shaded-background=1 ! x264enc ! h264parse ! rtph264pay name=pay0 pt=96'.format(self.pattern)
        return Gst.parse_launch(pipeline)

class WebCamMediaFactory(GstRtspServer.RTSPMediaFactory):
    def __init__(self):
        GstRtspServer.RTSPMediaFactory.__init__(self)

    def do_create_element(self, url):
        pipeline = 'v4l2src device=/dev/video0 ! timeoverlay shaded-background=1 ! videoconvert ! queue ! x264enc tune="zerolatency" byte-stream=true ! \
            video/x-h264,profile=main ! h264parse ! rtph264pay name=pay0 pt=96'
        return Gst.parse_launch(pipeline)

class Server(GstRtspServer.RTSPServer):
    def __init__(self):
        GstRtspServer.RTSPServer.__init__(self)
        self.connect('client-connected', self.__handle_client_connected)
        self.attach(None)
        self.factories = []
        mount_point = self.get_mount_points()
        for i in range(0, 25):
            factory = TestRtspMediaFactory(i)
            factory.set_shared(True)
            self.factories.append(factory)
            mount_point.add_factory('/stream{}'.format(i), factory)

        webcam_factory = WebCamMediaFactory()
        webcam_factory.set_shared(True)
        self.factories.append(webcam_factory)
        mount_point.add_factory('/webcam', webcam_factory)

    def __handle_client_connected(self, this, client):
        ip = client.get_connection().get_ip()
        print('connected client {}'.format(str(ip)), flush=True)
        client.connect('setup-request', self.__handle_client_setup_request)
        client.connect('teardown-request', self.__handle_teardown_request)
        client.connect('closed', self.__handle_client_closed)

    def __handle_client_setup_request(self, client, context):
        ip = client.get_connection().get_ip()
        uri = context.uri.abspath
        print('setup {} for {}'.format(uri, str(ip)), flush=True)

    def __handle_teardown_request(self, client, context):
        ip = client.get_connection().get_ip()
        uri = context.uri.abspath
        print('teardown {} for {}'.format(uri, str(ip)), flush=True)

    def __handle_client_closed(self, client):
        ip = client.get_connection().get_ip()
        print('closed connection with {}'.format(str(ip)), flush=True)

class GstreamerRtspServer():
    def __init__(self):
        self.rtspServer = Server()
        # self.rtspServer = GstRtspServer.RTSPServer()
        # factories = []
        # mount_point = self.rtspServer.get_mount_points()
        # for i in range(0, 25):
        #     factory = TestRtspMediaFactory(i)
        #     factory.set_shared(True)
        #     factories.append(factory)
        #     mount_point.add_factory('/stream{}'.format(i), factory)
        # self.rtspServer.attach(None)

        # factory = TestRtspMediaFactory()
        # factory.set_shared(True)
        # factory2 = TestRtspMediaFactory(1)
        # factory2.set_shared(True)
        # mount_point.add_factory('/stream1', factory)
        # mount_point.add_factory('/stream2', factory2)
        # self.rtspServer.attach(None)

if __name__ == '__main__':
    server = GstreamerRtspServer()
    loop.run()
