gst_init (0, 0);

// prepare the pipeline
GstElement *pipeline = gst_parse_launch ("playbin uri=rtsp://192.168.1.44:1935 uridecodebin0::source::latency=0", NULL);

// prepare the ui
QWidget *window = new QWidget(this);
window->setWindowTitle("MyWidget");
window->resize(300,400);
window->show();

WId xwinid = this->winId();
//WId xwinid = window->winId();
qDebug() << "[WIDGET ID] :" << xwinid;
//this is the call to overlay the gstreamer's output to the Qt Widgets...
gst_video_overlay_set_window_handle (GST_VIDEO_OVERLAY (pipeline), xwinid);


// run the pipeline
GstStateChangeReturn sret = gst_element_set_state (pipeline, GST_STATE_PLAYING);
if (sret == GST_STATE_CHANGE_FAILURE)
{
  gst_element_set_state (pipeline, GST_STATE_NULL);
  gst_object_unref (pipeline);
  // Exit application
  QTimer::singleShot(0, QApplication::activeWindow(), SLOT(quit()));
}