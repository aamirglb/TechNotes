/*
gcc appsrc2.c -o appsrc2 `pkg-config --cflags --libs gstreamer-1.0`
*/
#include <gst/gst.h>

static GMainLoop *loop;

static void
cb_need_data (GstElement *appsrc,
          guint       unused_size,
          gpointer    user_data)
{
  static gboolean white = FALSE;
  static gint color = 0;
  static GstClockTime timestamp = 0;
  GstBuffer *buffer;
  guint size;
  GstFlowReturn ret;

  size = 640 * 480 * 3;
  
  buffer = gst_buffer_new_allocate (NULL, size, NULL);

  /* this makes the image black/white */
//   gst_buffer_memset (buffer, 0, white ? 0xff : 0x0, size);
  gst_buffer_memset (buffer, 0, color, size);
  ++color;
  if(color > 255) color = 0;
  g_print("color: %d ", color);
  white = !white;

  for(int i = 0; i < size/9; i++) {
    // set red channel
    gst_buffer_memset(buffer, (i*3), 0xFF, 1);
    // set green channel
    gst_buffer_memset(buffer, (i*3)+1, 0x0, 1);
    // set blue channel
    gst_buffer_memset(buffer, (i*3)+2, 0x0, 1);
  }
  for(int i = size/9; i < (size/9)*2; i++) {
    // set red channel
    gst_buffer_memset(buffer, (i*3), 0x0, 1);
    // set green channel
    gst_buffer_memset(buffer, (i*3)+1, 0xFF, 1);
    // set blue channel
    gst_buffer_memset(buffer, (i*3)+2, 0x0, 1);
  }
  for(int i = (size/9)*2; i < size; i++) {
    // set red channel
    gst_buffer_memset(buffer, (i*3), 0x0, 1);
    // set green channel
    gst_buffer_memset(buffer, (i*3)+1, 0x0, 1);
    // set blue channel
    gst_buffer_memset(buffer, (i*3)+2, 0xFF, 1);
  }
  // int grid_size = size/32;
  // for(int i = 0; i < 32; i++) {
  //   if(i % 2 == 0)
  //     gst_buffer_memset(buffer, i*grid_size, 0x0, grid_size);    
  //   else
  //     gst_buffer_memset(buffer, i*grid_size, 0xFF, grid_size);
  // }
  // gst_buffer_memset(buffer, 0, 0x0, size/2);
  // gst_buffer_memset(buffer, size/2, 0xFF, size/2);

  GST_BUFFER_PTS (buffer) = timestamp;
  GST_BUFFER_DURATION (buffer) = gst_util_uint64_scale_int (1, GST_SECOND, 2);

  timestamp += GST_BUFFER_DURATION (buffer);

  g_signal_emit_by_name (appsrc, "push-buffer", buffer, &ret);
  gst_buffer_unref (buffer);

  if (ret != GST_FLOW_OK) {
    /* something wrong, stop pushing */
    g_main_loop_quit (loop);
  }
}

gint
main (gint   argc,
      gchar *argv[])
{
  GstElement *pipeline, *appsrc, *conv, *videosink;

  /* init GStreamer */
  gst_init (&argc, &argv);
  loop = g_main_loop_new (NULL, FALSE);

  /* setup pipeline */
  pipeline = gst_pipeline_new ("pipeline");
  appsrc = gst_element_factory_make ("appsrc", "source");
  conv = gst_element_factory_make ("videoconvert", "conv");
  videosink = gst_element_factory_make ("xvimagesink", "videosink");

  /* setup */
  g_object_set (G_OBJECT (appsrc), "caps",
        gst_caps_new_simple ("video/x-raw",
                     "format", G_TYPE_STRING, "RGB",
                     "width", G_TYPE_INT, 640,
                     "height", G_TYPE_INT, 480,
                     "framerate", GST_TYPE_FRACTION, 0, 1,
                     NULL), NULL);
  gst_bin_add_many (GST_BIN (pipeline), appsrc, conv, videosink, NULL);
  gst_element_link_many (appsrc, conv, videosink, NULL);

  /* setup appsrc */
  g_object_set (G_OBJECT (appsrc),
        "stream-type", 0,
        "format", GST_FORMAT_TIME, NULL);
  g_signal_connect (appsrc, "need-data", G_CALLBACK (cb_need_data), NULL);

  /* play */
  gst_element_set_state (pipeline, GST_STATE_PLAYING);
  g_main_loop_run (loop);

  /* clean up */
  gst_element_set_state (pipeline, GST_STATE_NULL);
  gst_object_unref (GST_OBJECT (pipeline));
  g_main_loop_unref (loop);

  return 0;
  }